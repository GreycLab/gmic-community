/*
 #
 #  File        : gmic_plugin.cpp
 #
 #  Description : The sources for a plugin that can be compiled for both 
 #                After Effects and OpenFX hosts and which interface the
 #                G'MIC library     
 #
 #  Copyright   : Tobias Fleischer / reduxFX Productions (http://www.reduxfx.com)
 #
 #  Licenses        : This file is 'dual-licensed', you have to choose one
 #                    of the two licenses below to apply.
 #
 #                    CeCILL-C
 #                    The CeCILL-C license is close to the GNU LGPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html )
 #
 #                or  CeCILL v2.0
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )
 #
 #  This software is governed either by the CeCILL or the CeCILL-C license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL or CeCILL-C licenses as circulated by CEA, CNRS and INRIA
 #  at the following URL: "http://www.cecill.info".
 #
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability.
 #
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or
 #  data to be ensured and,  more generally, to use and operate it in the
 #  same conditions as regards security.
 #
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL and CeCILL-C licenses and that you accept its terms.
 #
*/


// name and description for the plugin
#define PLUGIN_DESCRIPTION	"OpenFX wrapper for the G'MIC framework (http://www.gmic.eu).\nWritten by Tobias Fleischer (http://www.reduxfx.com).";

#ifdef OFX_PLUGIN
#define PLUGIN_NAME	        "GMIC"
#define PLUGIN_CATEGORY		"GMIC"
#define PLUGIN_UNIQUEID		"GMIC"
#else
// AE plugin needs these with spaces to replace them with proper effect names in the gmic_ae_tool
#define PLUGIN_NAME	        "G'MIC Plugin                   "
#define PLUGIN_CATEGORY		"G'MIC                          "
#define PLUGIN_UNIQUEID		"gmic_plugin                    "
#endif

// version information
#define	MAJOR_VERSION		1
#define	MINOR_VERSION		0
#define	BUILD_VERSION		1

#ifndef OFX_PLUGIN
#ifndef AE_PLUGIN
#define OFX_PLUGIN
#endif
#endif

// the following flags apply to the OFX plugin interface only and are ignored if set in an AE plugin!
#define NO_MULTITHREADED_CONVERSION
#define IMG_FLIP_Y

// the following flags apply to the AE plugin interface only and are ignored if set in an OFX plugin!
#define	_PF_OutFlag2_AE13_5_THREADSAFE 4194304
#define _PF_OutFlag2_SUPPORTS_GET_FLATTENED_SEQUENCE_DATA 8388608
#define FX_OUT_FLAGS PF_OutFlag_NON_PARAM_VARY + PF_OutFlag_DEEP_COLOR_AWARE + PF_OutFlag_I_DO_DIALOG + PF_OutFlag_SEND_UPDATE_PARAMS_UI + PF_OutFlag_USE_OUTPUT_EXTENT + PF_OutFlag_CUSTOM_UI
#define FX_OUT_FLAGS2 PF_OutFlag2_SUPPORTS_SMART_RENDER + PF_OutFlag2_FLOAT_COLOR_AWARE + PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG + _PF_OutFlag2_AE13_5_THREADSAFE + _PF_OutFlag2_SUPPORTS_GET_FLATTENED_SEQUENCE_DATA

#ifndef PIPL

// if this is defined, 8bpc (0-255) input layers will be transformed into 32bpc (0.0-1.0) input layers
// this should in most cases be set, as you then only have to write algorithms for float data
#define CONVERT_INT_TO_FLOAT

// if this is defined, 32bpc (0.0-1.0) input layers will be transformed into 8bpc (0-255) input layers
// this should in most cases NOT be set, as you will lose precision
// #define CONVERT_FLOAT_TO_INT

// if this is defined, pixel data is not stored interleaved internally (RGBARGBARGBA...) but in a planar buffer (RRR... GGG... BBB... AAA...)
// this should in most cases NOT be set, unless you (or a specific library) need the pixel buffers in this format
#define PLANAR_BUFFER

#ifdef OFX_PLUGIN
    #include "RFX_OFX_Utils.h"
#else
    #include "RFX_AE_Utils.h"
#endif

#include "gmic_parser.h"
#include "gmic_libc.h"
#include <math.h>

using namespace reduxfx;

#ifdef OFX_PLUGIN
#include "gmic.h"
#include "gmic_stdlib.h"
#include <sstream>
#include <stdlib.h> 
string get_gmic_rc_path()
{
	string path;
	const char *_path_rc = 0;
/*	if (!_path_rc) _path_rc = getenv("GMIC_PATH");
	if (!_path_rc) _path_rc = getenv("GMIC_GIMP_PATH");
	if (!_path_rc) _path_rc = getenv("XDG_CONFIG_HOME"); */
	if (!_path_rc) {
#ifndef _WIN32
		_path_rc = getenv("HOME");
		if (_path_rc) {
			path = string(_path_rc) + "/.config/gmic/";
		}
#else
		_path_rc = getenv("APPDATA");
#endif
	}
	if (path == "") path = string(_path_rc) + "/gmic/";
	return path;
}

class PluginGlobalData
{
public:
	vector<EffectData> pluginData;
	vector<string> pluginContent;
	PluginGlobalData() {
		string effectContent = loadStringFromFile(get_gmic_rc_path() + "gmic_ofx.gmic");
		if (effectContent == "") effectContent = loadStringFromFile(get_gmic_rc_path() + "gmic_stdlib.gmic");
		if (effectContent == "") {
			const char* lib = gmic_get_stdlib();
            stringstream s;
            s << lib;
			gmic_delete_external((float*)lib);
			effectContent = s.str();
		}
		gmic_parse_multi(effectContent, &pluginData, &pluginContent);
	};
};
PluginGlobalData pluginGlobalData;

#endif

class MyGlobalData
{
public:
#ifdef AE_PLUGIN
	EffectData effectData;
	string effectContent;
#endif
	MyGlobalData() {};
	~MyGlobalData() {};
};

class MySequenceData
{
public:
	string command;
	gmic_interface_options options;

	MySequenceData() {
		options.error_message_buffer = new char[256];
		options.error_message_buffer[0] = '\0';
		options.ignore_stdlib = false;
		options.p_is_abort = NULL;
		options.p_progress = NULL;
		options.output_format = E_FORMAT_FLOAT;
		options.interleave_output = false;
	};
	~MySequenceData() {
		delete[] options.error_message_buffer;
	};
};

void* createCustomGlobalData() { return new MyGlobalData(); }
void destroyCustomGlobalData(void* customGlobalDataP) { delete (MyGlobalData*)customGlobalDataP; }
void* createCustomSequenceData() { return new MySequenceData(); }
void destroyCustomSequenceData(void* customSequenceDataP) { delete (MySequenceData*)customSequenceDataP; }
void* flattenCustomSequenceData(void* customUnflatSequenceDataP, int& flatSize) { return NULL; }
void* unflattenCustomSequenceData(void* customSequenceDataP, int flatSize) { return new MySequenceData(); }

int pluginSetdown(GlobalData* globalDataP, ContextData* contextDataP) { return 0; }

int pluginSetup(GlobalData* globalDataP, ContextData* contextDataP)
{
	globalDataP->scale = 255.f;
	globalDataP->buttonName = "Reload";

	MyGlobalData* myGlobalDataP = (MyGlobalData*)globalDataP->customGlobalDataP;

	EffectData effectData;
	effectData.multiLayer = true;
#ifdef AE_PLUGIN
	string filename = globalDataP->pluginFilename;
	int pos = (int)filename.find_last_of(".");
	if (pos > 0) filename = filename.substr(0, pos);
	filename = globalDataP->pluginPath + filename + ".gmic";
	string effectContent = loadStringFromFile(filename);
	effectContent = gmic_parse_single(effectContent, effectData);
	if (myGlobalDataP) {
		myGlobalDataP->effectContent = effectContent;
		myGlobalDataP->effectData = effectData;
	}
	bool hasContent = effectContent != "";
#else
	effectData = pluginGlobalData.pluginData[globalDataP->pluginIndex];
	bool hasContent = true;
#endif	
	
	globalDataP->inplaceProcessing = false;

	globalDataP->param[0] = Parameter("Input", PT_LAYER);
	int p = 1;
	for (int i = 0; i < (int)effectData.param.size(); i++) {
		int t = PT_FLOAT;
		int flags = 0;
		bool h = false;
		float d1 = 0.f;
		float d2 = 0.f;
		float d3 = 0.f;
		float d4 = 0.f;
		if (effectData.param[i].paramType == "color") {
			vector<string> r;
			t = PT_COLOR;
			strSplit(effectData.param[i].defaultValue + "|||", '|', r);
			d1 = (float)atof(r[0].c_str()) / 255.f;
			d2 = (float)atof(r[1].c_str()) / 255.f;
			d3 = (float)atof(r[2].c_str()) / 255.f;
			d4 = 1.0f;
		} else {
			d1 = (float)atof(effectData.param[i].defaultValue.c_str());
			d2 = d1; d3 = d1; d4 = d1;
		}
		if (effectData.param[i].paramType == "const") {
			h = true;
			t = PT_TEXT;
		} else if (effectData.param[i].paramType == "text") {
			t = PT_TEXT;
		} else if (effectData.param[i].paramType == "file") {
			t = PT_TEXT;
			flags = 2;
		} else if (effectData.param[i].paramType == "folder") {
			t = PT_TEXT;
			flags = 3;
		} else if (effectData.param[i].paramType == "int") {
			t = PT_INT;
		} else if (effectData.param[i].paramType == "bool") {
			t = PT_BOOL;
		} else if (effectData.param[i].paramType == "choice") {
			t = PT_SELECT;
		} else if (effectData.param[i].paramType == "input") {
			t = PT_LAYER;
		}
		globalDataP->param[p] = Parameter(
			effectData.param[i].name, t, (float)atof(effectData.param[i].minValue.c_str()), (float)atof(effectData.param[i].maxValue.c_str()), d1, d2, d3, d4, effectData.param[i].text);
		globalDataP->param[p].flags = flags;
		if (h) globalDataP->param[p].displayStatus = DS_HIDDEN;
		p++;
	}

//	globalDataP->param[p++] = Parameter("Dummy", PT_FLOAT);

	if (effectData.multiLayer) {
		globalDataP->param[p++] = Parameter("Ext. In 1", PT_LAYER);
		globalDataP->param[p++] = Parameter("Ext. In 2", PT_LAYER);
		globalDataP->param[p++] = Parameter("Ext. In 3", PT_LAYER);
		globalDataP->param[p++] = Parameter("Ext. In 4", PT_LAYER);
	}	
	globalDataP->param[p] = Parameter("Command", PT_TEXT, 0, 0, 0, 0, 0, 0, "-blur 2"); if (hasContent) globalDataP->param[p].displayStatus = DS_HIDDEN; p++;
	globalDataP->param[p] = Parameter("Advanced Options", PT_TOPIC_START); globalDataP->param[p].flags = 1; p++;
	globalDataP->param[p++] = Parameter("Output Layer", PT_SELECT, 0, 10, 1, 0, 0, 0, "Merged|Layer 0|Layer 1|Layer 2|Layer 3|Layer 4|Layer 5|Layer 6|Layer 7|Layer 8|Layer 9|");
	globalDataP->param[p++] = Parameter("Resize Mode", PT_SELECT, 0, 5, 1, 0, 0, 0, "Fixed (Inplace)|Dynamic|Downsample 1/2|Downsample 1/4|Downsample 1/8|Downsample 1/16");
	globalDataP->param[p++] = Parameter("Ignore Alpha", PT_BOOL, 0, 1, 0, 0, 0, 0, "");
	globalDataP->param[p] = Parameter("Preview/Draft Mode", PT_BOOL, 0, 1, 0, 0, 0, 0, ""); if (!hasContent || effectData.command == effectData.preview_command) globalDataP->param[p].displayStatus = DS_HIDDEN; p++;
	globalDataP->param[p++] = Parameter("Advanced Options", PT_TOPIC_END);
	globalDataP->nofParams = p;

	string d = effectData.notes;
/*
	for (int i = 0; i < effectData.notes.size(); i++)
		if (effectData.notes[i] >= 32 && effectData.notes[i] < 128) d += effectData.notes[i];
*/
	strReplace(d, "\n", "\\n");
	d = strRemoveXmlTags(d, false);
	globalDataP->pluginInfo.description = d;

	return 0;
}

#define PARAM_COMMAND (globalDataP->nofParams - 7)
#define PARAM_OUTPUT (globalDataP->nofParams - 5)
#define PARAM_RESIZE (globalDataP->nofParams - 4)
#define PARAM_NOALPHA (globalDataP->nofParams - 3)
#define PARAM_PREVIEW (globalDataP->nofParams - 2)

int pluginParamChange(int index, SequenceData* sequenceDataP, GlobalData* globalDataP, ContextData* contextDataP)
{
	if (index == PARAM_RESIZE) {
		globalDataP->inplaceProcessing = PAR_VAL(index) < 1.f;
	} else {
		MyGlobalData* myGlobalDataP = (MyGlobalData*)globalDataP->customGlobalDataP;

#ifdef AE_PLUGIN	
		string cmd = PAR_VAL(PARAM_PREVIEW) > 0 ? myGlobalDataP->effectData.preview_command:myGlobalDataP->effectData.command;
#else
		string cmd = PAR_VAL(PARAM_PREVIEW) > 0 ? pluginGlobalData.pluginData[globalDataP->pluginIndex].preview_command:pluginGlobalData.pluginData[globalDataP->pluginIndex].command;
#endif

		if (cmd == "") {
			cmd = PAR_TXT(PARAM_COMMAND);
		} else {
			cmd = "-" + strTrim(cmd, " \t\r\n") + " ";
			for (int i = 1; i < globalDataP->nofParams - 6; i++) {
				if (PAR_TYPE(i) == PT_INT || PAR_TYPE(i) == PT_BOOL || PAR_TYPE(i) == PT_SELECT)
					cmd += intToString((int)PAR_VAL(i)) + ",";
				else if (PAR_TYPE(i) == PT_FLOAT)
					cmd += floatToString(PAR_VAL(i)) + ",";
				else if (PAR_TYPE(i) == PT_TEXT) {
					if (i == PARAM_COMMAND && globalDataP->param[PARAM_COMMAND].displayStatus == DS_HIDDEN) continue;
					string s = PAR_TXT(i);
					cmd += "\"" + s + "\",";
				} else if (PAR_TYPE(i) == PT_COLOR)
					cmd += 
						intToString((int)(255.f * PAR_CH(i, 0))) + "," +
						intToString((int)(255.f * PAR_CH(i, 1))) + "," +
						intToString((int)(255.f * PAR_CH(i, 2))) + ",255,";
			}
			cmd = cmd.substr(0, cmd.size() - 1);
		}

		strReplace(cmd, "\r", " ");
		strReplace(cmd, "\n", " ");

		MySequenceData* mySequenceDataP = (MySequenceData*)sequenceDataP->customSequenceDataP;
		mySequenceDataP->command = cmd;
	}
	return 0;
}

int pluginProcess(SequenceData* sequenceDataP, GlobalData* globalDataP, ContextData* contextDataP)
{
	/*
	float* fi = (float*)sequenceDataP->inWorld[0].data;
	float* fo = (float*)sequenceDataP->outWorld.data;
	for (int x = 0; x < sequenceDataP->outWorld.width * sequenceDataP->outWorld.height * 4; x++)
	{
		*fo = *fi * 2.f;//(float)(rand() % 100) / 100.f;
		fi++;
		fo++;
	}
	return 0;
	*/

	int err = 0;

	MySequenceData* mySequenceDataP = (MySequenceData*)sequenceDataP->customSequenceDataP;
	mySequenceDataP->options.no_inplace_processing = !globalDataP->inplaceProcessing;
#ifdef AE_PLUGIN
	mySequenceDataP->options.custom_commands = ((MyGlobalData*)globalDataP->customGlobalDataP)->effectContent.c_str();
#else
	mySequenceDataP->options.custom_commands = pluginGlobalData.pluginContent[globalDataP->pluginIndex].c_str();
#endif

	gmic_interface_image images[MAX_NOF_LAYERS];
	unsigned int nofImages = 0;
	for (int i = 0; i < globalDataP->nofInputs; i++) {
		if (!sequenceDataP->inWorld[i].data || !sequenceDataP->inputConnected[i]) break;
		nofImages++;
	}
	if (nofImages == 0) return err;

	for (unsigned int i = 0; i < nofImages; i++) {
		images[i].width = sequenceDataP->inWorld[nofImages - i - 1].width;
		images[i].height = sequenceDataP->inWorld[nofImages - i - 1].height;
		images[i].data = sequenceDataP->inWorld[nofImages - i - 1].data;
		images[i].spectrum = 4;
		images[i].depth = 1;
		images[i].name[0] = '\0';
		images[i].format = E_FORMAT_FLOAT;
		images[i].is_interleaved = false;
		strcpy(images[i].name, string("input" + intToString(i)).c_str());
	}

	string cmd = mySequenceDataP->command;

	// if (cmd == "") 
	{
		pluginParamChange(0, sequenceDataP, globalDataP, contextDataP);
		cmd = mySequenceDataP->command;
	}

	if (PAR_VAL(PARAM_OUTPUT) == 0.f) {
		cmd += " -gimp_merge_layers";
	}

	if (PAR_VAL(PARAM_NOALPHA) > 0.f) {
		strReplace(cmd, "\"", "\\\"");
		cmd = "-apply_channels \"" + cmd + "\",rgb";
	}
	
	if (!globalDataP->inplaceProcessing) {
		float ds = PAR_VAL(PARAM_RESIZE);
		if (ds >= 2.f) {
			ds = pow(2.f, ds - 1.f);
			cmd = " -resize " + intToString(sequenceDataP->inWorld[0].width / (int)ds) + "," + intToString(sequenceDataP->inWorld[0].height / (int)ds) + " " + cmd;
		}
		cmd += " -resize " + intToString(sequenceDataP->inWorld[0].width) + "," + intToString(sequenceDataP->inWorld[0].height);
 	}
	cmd = "-v -1 " + cmd;
	// cmd += " -display";
	// set some variables that are defined globally for the GIMP plugin
	// not really needed as the effects should work independently of GIMP
//	cmd = "_input_mode=1 _output_mode=0 _verbosity_mode=0 _preview_mode=0 _preview_size=0 " + cmd;

	int result = gmic_call(cmd.c_str(), &nofImages, &images[0], &(((MySequenceData*)(sequenceDataP->customSequenceDataP))->options));

	if (result == 0) {
		if (!globalDataP->inplaceProcessing) {
			int idx = (int)PAR_VAL(PARAM_OUTPUT);
			if (idx > 0) {
				idx = nofImages - idx;
				if (idx < 0) idx = 0;
			}

			size_t sz = sequenceDataP->outWorld.width * sequenceDataP->outWorld.height * min(4, (int)images[idx].spectrum) * sizeof(float);
			memcpy((unsigned char*)sequenceDataP->outWorld.data, (unsigned char*)images[idx].data, sz);

			if (images[idx].spectrum < 4) {
				size_t sz2 = sequenceDataP->outWorld.width * sequenceDataP->outWorld.height;
				float* p = (float*)sequenceDataP->outWorld.data + sz2 * 3;
				std::fill(p, p + sz2 , 255.f);

				for (unsigned int i = 1; i < 4 - images[idx].spectrum; i++) {
					p = (float*)sequenceDataP->outWorld.data + sz2 * i;
					memcpy(p, sequenceDataP->outWorld.data, sz2 * sizeof(float));
				}
			}
		}
	} else {
		string errmsg = string(((MySequenceData*)(sequenceDataP->customSequenceDataP))->options.error_message_buffer);
#ifdef OFX_PLUGIN
		 if (gMessageSuite) {
			gMessageSuite->message(contextDataP->instance, kOfxMessageError, "G'MIC Error", errmsg.c_str());
		} else {
			cout << "ERROR: " << errmsg << endl;
		}
#endif
#ifdef AE_PLUGIN
		errmsg = errmsg.substr(0, 255);
		strcpy(contextDataP->out_data->return_msg, errmsg.c_str());
#endif
		err = PF_Err_INTERNAL_STRUCT_DAMAGED;
	}

	for (unsigned int i = 0; i < nofImages; i++) {
		bool found = false;
		for (int j = 0; j < globalDataP->nofInputs; j++) {
			if (images[i].data == sequenceDataP->inWorld[j].data) {
				found = true;
				break;
			}
		}
		if (!found) gmic_delete_external((float*)images[i].data);
	}
	return err;
}

#ifdef OFX_PLUGIN

int getNofPlugins()
{
	return (int)pluginGlobalData.pluginData.size();
}

void getPluginInfo(int pluginIndex, PluginInfo& pluginInfo)
{
	pluginInfo.name = pluginGlobalData.pluginData[pluginIndex].name;
	pluginInfo.identifier = pluginGlobalData.pluginData[pluginIndex].uniqueId;
	pluginInfo.category = pluginGlobalData.pluginData[pluginIndex].category;
	
	string d = pluginGlobalData.pluginData[pluginIndex].notes;

	strReplace(d, "\n", "\\n");
	strReplace(d, "<", "(");
	strReplace(d, ">", ")");

	pluginInfo.description = d;
	

	pluginInfo.major_version = MAJOR_VERSION;
	pluginInfo.minor_version = MINOR_VERSION;
}

#else

extern "C" DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP, void* extraP)
{
	if (cmd == PF_Cmd_DO_DIALOG) {
		GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
		pluginSetup(globalDataP, NULL);
		PF_UNLOCK_HANDLE(in_data->global_data);
		return PF_Err_NONE;
	} else {
		return pluginMain(cmd, in_data, out_data, param, outputP, extraP); 
	}
};

#endif

#endif
