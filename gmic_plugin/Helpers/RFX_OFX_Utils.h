/*
 #
 #  File        : RFX_OFX_Utils.h
 #
 #  Description : A self-contained header file with helper functions to make    
 #                using the OpenFX SDK/API a bit easier to use    
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

#ifndef _RFX_OFX_UTILS_H
#define _RFX_OFX_UTILS_H

#pragma once
#include <stdexcept>
#include <new>
#include <cstring>
#include <math.h>
#include <stdlib.h>
#include "ofxImageEffect.h"
#include "ofxMemory.h"
#include "ofxUtilities.H"

#ifndef NO_MULTITHREADED_CONVERSION
#include <thread>
#endif

#include <string>
#include "RFX_Utils.h"
#include "RFX_Parameter.h"
#include "RFX_StringUtils.h"
using namespace std;
using namespace reduxfx;

#ifdef ABOUT_DIALOG
#include "TMsgDlg.h"
#endif

#undef OFX_64
#undef OFX_32

#if defined(_M_AMD64) || defined(_AMD64_) || defined(_M_IA64) || defined(_IA64_) || defined(_WIN64) || defined(__x86_64__) || defined(__LP64__)
#define OFX_64
#undef OFX_32
#else
#define OFX_32
#undef OFX_64
#endif

#define PF_Err_NONE 0
#define PF_Err_INTERNAL_STRUCT_DAMAGED 512
#define A_long long

struct ContextData
{
	OfxImageEffectHandle instance;
	OfxPropertySetHandle inArgs;
	OfxPropertySetHandle outArgs;
};

extern void* createCustomGlobalData();
extern void destroyCustomGlobalData(void* customGlobalDataP);
extern void* createCustomSequenceData();
extern void destroyCustomSequenceData(void* customSequenceDataP);
extern void* flattenCustomSequenceData(void* customUnflatSequenceDataP, int& flatSize);
extern void* unflattenCustomSequenceData(void* customFlatSequenceDataP, int flatSize);

extern int pluginParamChange(int index, SequenceData* sequenceDataP, GlobalData* globalDataP, ContextData* contextDataP);
extern int pluginSetup(GlobalData* globalDataP, ContextData* contextDataP);
extern int pluginSetdown(GlobalData* globalDataP, ContextData* contextDataP);
extern int pluginProcess(SequenceData* sequenceDataP, GlobalData* globalDataP, ContextData* contextDataP);

extern int getNofPlugins();
extern void getPluginInfo(int pluginIndex, PluginInfo& pluginInfo);

#if defined __APPLE__ || defined linux || defined __FreeBSD__
#define EXPORT __attribute__((visibility("default")))
#elif defined _WIN32
#define EXPORT OfxExport
#else
#error Not building on your operating system quite yet
#endif

template <class T> inline T Maximum(T a, T b) {return a > b ? a : b;}
template <class T> inline T Minimum(T a, T b) {return a < b ? a : b;}

const float MAX_CHAN8 = 255.f;
const float I_MAX_CHAN8 = 1.f / 255.f;
const float MAX_CHAN16 = 32768.f;
const float I_MAX_CHAN16 = 1.f / 32768.f;

#ifdef PLANAR_BUFFER
const int stepWidth = 1;
#else
const int stepWidth = 4;
#endif

inline void setContextData(ContextData &cd, OfxImageEffectHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	cd.instance = instance;
	cd.inArgs = inArgs;
	cd.outArgs = outArgs;
}

// pointers64 to various bits of the host
OfxHost					*gHost;
OfxImageEffectSuiteV1	*gEffectHost = 0;
OfxPropertySuiteV1		*gPropHost = 0;
OfxParameterSuiteV1		*gParamHost = 0;
OfxMemorySuiteV1		*gMemoryHost = 0;
OfxMultiThreadSuiteV1	*gThreadHost = 0;
OfxMessageSuiteV1		*gMessageSuite = 0;
OfxInteractSuiteV1		*gInteractHost = 0;

// some flags about the host's behaviour
int gHostSupportsMultipleBitDepths = false;

// GlobalData* globalDataP = NULL;
vector<OfxPlugin> gPlugins;
vector<GlobalData> globalData;

// private instance data type
struct MyInstanceData {
	bool isGeneralEffect;
	SequenceData* sequenceDataP;
	OfxParamHandle param[MAX_NOF_PARAMS];
	OfxImageClipHandle input[MAX_NOF_LAYERS];
	OfxImageClipHandle output;
	OfxParamHandle seqDataH;
};

// Convenience wrapper to get private data 
static MyInstanceData* getMyInstanceData(OfxImageEffectHandle effect)
{
	// get the property handle for the plugin
	OfxPropertySetHandle effectProps;
	gEffectHost->getPropertySet(effect, &effectProps);

	// get my data pointer out of that
	MyInstanceData* myData = NULL;
	gPropHost->propGetPointer(effectProps, kOfxPropInstanceData, 0, (void **)&myData);
	return myData;
}

static OfxStatus onLoad(int pluginIndex)
{
	globalData[pluginIndex].customGlobalDataP = createCustomGlobalData();
	pluginSetup(&globalData[pluginIndex], NULL);
	return kOfxStatOK;
}

static OfxStatus onUnload(int pluginIndex)
{
	pluginSetdown(&globalData[pluginIndex], NULL);
	destroyCustomGlobalData(globalData[pluginIndex].customGlobalDataP);
	return kOfxStatOK;
}

static OfxStatus syncPrivateData(int pluginIndex, OfxImageEffectHandle effect)
{
	MyInstanceData* myData = getMyInstanceData(effect);
	if (myData && myData->sequenceDataP && myData->sequenceDataP->customSequenceDataP) {
		int flatSize = 0;
		char* flatCustomSequenceDataP = (char*)flattenCustomSequenceData(myData->sequenceDataP->customSequenceDataP, flatSize);
		string s = bufferToHexString((unsigned char*)flatCustomSequenceDataP, flatSize);
		gParamHost->paramSetValue(myData->seqDataH, s.c_str());
		delete flatCustomSequenceDataP;
	}
	return kOfxStatOK;
}

// instance construction
static OfxStatus createInstance(int pluginIndex, OfxImageEffectHandle effect)
{
	// get a pointer to the effect properties
	OfxPropertySetHandle effectProps;
	gEffectHost->getPropertySet(effect, &effectProps);

	// get a pointer to the effect's parameter set
	OfxParamSetHandle paramSet;
	gEffectHost->getParamSet(effect, &paramSet);

	// make private instance data
	MyInstanceData* myData = new MyInstanceData;
	myData->sequenceDataP = new SequenceData();
	for (int i = 0; i < globalData[pluginIndex].nofParams; i++) {
		myData->sequenceDataP->textValue[i] = globalData[pluginIndex].param[i].text;
		for (int j = 0; j < 4; j++) {
			myData->sequenceDataP->floatValue[i][j] = globalData[pluginIndex].param[i].defaultValue[j];
		}
	}
	myData->sequenceDataP->contextP = (void*)effect;

	gParamHost->paramGetHandle(paramSet, "SequenceData", &(myData->seqDataH), 0);

	char* flatCustomSequenceDataP = NULL;
	gParamHost->paramGetValue(myData->seqDataH, &flatCustomSequenceDataP);
	if (flatCustomSequenceDataP) {
		string s = string(flatCustomSequenceDataP);
		unsigned char* buf = NULL;
		if (s != "") {
			buf = new unsigned char[(int)s.size() / 2];
			hexStringToBuffer(s, buf);
		}
		if (buf) {
			myData->sequenceDataP->customSequenceDataP = unflattenCustomSequenceData(buf, (int)s.size() / 2);
			delete [] buf;
		} else {
			myData->sequenceDataP->customSequenceDataP = createCustomSequenceData();
		}
	} else {
		myData->sequenceDataP->customSequenceDataP = createCustomSequenceData();
	}
		
	char *context = 0;

	// is this instance a general effect ?
	gPropHost->propGetString(effectProps, kOfxImageEffectPropContext, 0, &context);
	myData->isGeneralEffect = context && (strcmp(context, kOfxImageEffectContextGeneral) == 0);

	myData->param[0] = NULL;
	int l = 0;
	for (int i = 0; i < globalData[pluginIndex].nofParams; i++) {
		if (globalData[pluginIndex].param[i].paramType == PT_LAYER) {
			gEffectHost->clipGetHandle(effect, globalData[pluginIndex].param[i].paramName.c_str(), &(myData->input[l]), 0);
			l++;
		}
		gParamHost->paramGetHandle(paramSet, globalData[pluginIndex].param[i].paramName.c_str(), &(myData->param[i]), 0);
	}
	gEffectHost->clipGetHandle(effect, "Output", &myData->output, 0);
	
	// set my private instance data
	gPropHost->propSetPointer(effectProps, kOfxPropInstanceData, 0, (void*)myData);

	return kOfxStatOK;
}

// instance destruction
static OfxStatus destroyInstance(int pluginIndex, OfxImageEffectHandle effect)
{
	// get my instance data
	MyInstanceData* myData = getMyInstanceData(effect);
	if (myData->sequenceDataP) {
		if (myData->sequenceDataP->customSequenceDataP) {
			destroyCustomSequenceData(myData->sequenceDataP->customSequenceDataP);
			myData->sequenceDataP->customSequenceDataP = NULL;
		}
		delete (SequenceData*)myData->sequenceDataP;
		myData->sequenceDataP = NULL;
	}

	// and delete it
	if (myData) delete myData;
	return kOfxStatOK;
}

static void getAllParamData(int pluginIndex, MyInstanceData* myData, OfxTime t)
{
	for (int i = 0; i < globalData[pluginIndex].nofParams; i++) {
		if (globalData[pluginIndex].param[i].paramType == PT_FLOAT) {
			double v;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
			myData->sequenceDataP->floatValue[i][0] = (float)v;
		} else if (globalData[pluginIndex].param[i].paramType == PT_INT) {
			int v;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
			myData->sequenceDataP->floatValue[i][0] = (float)v;
		} else if (globalData[pluginIndex].param[i].paramType == PT_COLOR) {
			double myR, myG, myB;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &myR, &myG, &myB);
			myData->sequenceDataP->floatValue[i][0] = (float)myR;
			myData->sequenceDataP->floatValue[i][1] = (float)myG;
			myData->sequenceDataP->floatValue[i][2] = (float)myB;
		} else if (globalData[pluginIndex].param[i].paramType == PT_POINT) {
			double myX, myY;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &myX, &myY);
			myData->sequenceDataP->floatValue[i][0] = (float)myX;
			myData->sequenceDataP->floatValue[i][1] = (float)myY;
		} else if (globalData[pluginIndex].param[i].paramType == PT_ANGLE) {
			double v;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
			if (globalData[pluginIndex].param[i].flags > 0)
				myData->sequenceDataP->floatValue[i][0] = -M_PI * (float)v / 180.0f;
			else
				myData->sequenceDataP->floatValue[i][0] = (float)v;
		} else if (globalData[pluginIndex].param[i].paramType == PT_SELECT) {
			int v;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
			myData->sequenceDataP->floatValue[i][0] = (float)v;
		} else if (globalData[pluginIndex].param[i].paramType == PT_BOOL) {
			int v;
			gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
			myData->sequenceDataP->floatValue[i][0] = (float)v;
		}
	}
}

static void getParamData(int pluginIndex, int paramIndex, MyInstanceData* myData, OfxTime t)
{
	int i = paramIndex;
	if (globalData[pluginIndex].param[i].paramType == PT_FLOAT) {
		double v;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
		myData->sequenceDataP->floatValue[i][0] = (float)v;
	} else if (globalData[pluginIndex].param[i].paramType == PT_INT) {
		int v;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
		myData->sequenceDataP->floatValue[i][0] = (float)v;
	} else if (globalData[pluginIndex].param[i].paramType == PT_COLOR) {
		double myR, myG, myB;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &myR, &myG, &myB);
		myData->sequenceDataP->floatValue[i][0] = (float)myR;
		myData->sequenceDataP->floatValue[i][1] = (float)myG;
		myData->sequenceDataP->floatValue[i][2] = (float)myB;
	} else if (globalData[pluginIndex].param[i].paramType == PT_POINT) {
		double myX, myY;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &myX, &myY);
		myData->sequenceDataP->floatValue[i][0] = (float)myX;
		myData->sequenceDataP->floatValue[i][1] = (float)myY;
	} else if (globalData[pluginIndex].param[i].paramType == PT_ANGLE) {
		double v;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
		if (globalData[pluginIndex].param[i].flags > 0)
			myData->sequenceDataP->floatValue[i][0] = -M_PI * (float)v / 180.0f;
		else
			myData->sequenceDataP->floatValue[i][0] = (float)v;
	} else if (globalData[pluginIndex].param[i].paramType == PT_SELECT) {
		int v;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
		myData->sequenceDataP->floatValue[i][0] = (float)v;
	} else if (globalData[pluginIndex].param[i].paramType == PT_BOOL) {
		int v;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
		myData->sequenceDataP->floatValue[i][0] = (float)v;
	} else if (globalData[pluginIndex].param[i].paramType == PT_TEXT) {
		char* v = NULL;
		gParamHost->paramGetValueAtTime(myData->param[i], t, &v);
		myData->sequenceDataP->textValue[i] = string(v);
	}
}

static void setParamData(int pluginIndex, MyInstanceData* myData)
{
	for (int i = 0; i < globalData[pluginIndex].nofParams; i++) {
		if (globalData[pluginIndex].param[i].paramType == PT_FLOAT) {
			double v = (double)(myData->sequenceDataP->floatValue[i][0]);
			gParamHost->paramSetValue(myData->param[i], v);
		} else if (globalData[pluginIndex].param[i].paramType == PT_INT) {
			int v = (int)myData->sequenceDataP->floatValue[i][0];
			gParamHost->paramSetValue(myData->param[i], v);
		} else if (globalData[pluginIndex].param[i].paramType == PT_COLOR) {
			double myR = (double)myData->sequenceDataP->floatValue[i][0];
			double myG = (double)myData->sequenceDataP->floatValue[i][1];
			double myB = (double)myData->sequenceDataP->floatValue[i][2];
			gParamHost->paramSetValue(myData->param[i], myR, myG, myB);
		} else if (globalData[pluginIndex].param[i].paramType == PT_POINT) {
			double myX = (double)myData->sequenceDataP->floatValue[i][0];
			double myY = (double)myData->sequenceDataP->floatValue[i][1];
			gParamHost->paramSetValue(myData->param[i], myX, myY);
		} else if (globalData[pluginIndex].param[i].paramType == PT_ANGLE) {
			double v;
			if (globalData[pluginIndex].param[i].flags > 0)
				v = (double)180.f * myData->sequenceDataP->floatValue[i][0] / -M_PI;
			else
				v = (double)myData->sequenceDataP->floatValue[i][0];
			gParamHost->paramSetValue(myData->param[i], v);
		} else if (globalData[pluginIndex].param[i].paramType == PT_SELECT) {
			int v = (int)myData->sequenceDataP->floatValue[i][0];
			gParamHost->paramSetValue(myData->param[i], v);
		} else if (globalData[pluginIndex].param[i].paramType == PT_BOOL) {
			int v = (int)myData->sequenceDataP->floatValue[i][0];
			gParamHost->paramSetValue(myData->param[i], v);
		} else if (globalData[pluginIndex].param[i].paramType == PT_TEXT) {
			string s = myData->sequenceDataP->textValue[i];
			gParamHost->paramSetValue(myData->param[i], s.c_str());
		}
	}
}

// tells the host what region we are capable of filling
OfxStatus getSpatialRoD(int pluginIndex, OfxImageEffectHandle effect, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	// retrieve any instance data associated with this effect
	MyInstanceData *myData = getMyInstanceData(effect);

	OfxTime time;
	gPropHost->propGetDouble(inArgs, kOfxPropTime, 0, &time);
	
	// my RoD is the same as my input's
	OfxRectD rod;
	gEffectHost->clipGetRegionOfDefinition(myData->input[0], time, &rod);

	// set the rod in the out args
	gPropHost->propSetDoubleN(outArgs, kOfxImageEffectPropRegionOfDefinition, 4, &rod.x1);
	return kOfxStatOK;
}

// tells the host how much of the input we need to fill the given window
OfxStatus getSpatialRoI(int pluginIndex, OfxImageEffectHandle effect, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	// get the RoI the effect is interested in from inArgs
	OfxRectD roi;
	gPropHost->propGetDoubleN(inArgs, kOfxImageEffectPropRegionOfInterest, 4, &roi.x1);

	// the input needed is the same as the output, so set that on the source clip
	gPropHost->propSetDoubleN(outArgs, "OfxImageClipPropRoI_Source", 4, &roi.x1);

	return kOfxStatOK;
}

// Tells the host how many frames we can fill, only called in the general context.
// This is actually redundant as this is the default behaviour, but for illustrative
// purposes.
OfxStatus getTemporalDomain(int pluginIndex, OfxImageEffectHandle effect, OfxPropertySetHandle /*inArgs*/, OfxPropertySetHandle outArgs)
{
	MyInstanceData *myData = getMyInstanceData(effect);
	double sourceRange[2];
	
	// get the frame range of the source clip
	OfxPropertySetHandle props; gEffectHost->clipGetPropertySet(myData->input[0], &props);
	gPropHost->propGetDoubleN(props, kOfxImageEffectPropFrameRange, 2, sourceRange);

	// set it on the out args
	gPropHost->propSetDoubleN(outArgs, kOfxImageEffectPropFrameRange, 2, sourceRange);
	
	return kOfxStatOK;
}

// Set our clip preferences 
static OfxStatus getClipPreferences(int pluginIndex, OfxImageEffectHandle effect, OfxPropertySetHandle /*inArgs*/, OfxPropertySetHandle outArgs)
{
	// retrieve any instance data associated with this effect
	MyInstanceData *myData = getMyInstanceData(effect);
	
	// get the component type and bit depth of our main input
	int	bitDepth;
	bool isRGBA;
	ofxuClipGetFormat(myData->input[0], bitDepth, isRGBA, true); // get the unmapped clip component

	// get the strings used to label the various bit depths
	const char *bitDepthStr = bitDepth == 8 ? kOfxBitDepthByte : (bitDepth == 16 ? kOfxBitDepthShort : kOfxBitDepthFloat);
	const char *componentStr = isRGBA ? kOfxImageComponentRGBA : kOfxImageComponentAlpha;

	// set out output to be the same same as the input, component and bitdepth
	gPropHost->propSetString(outArgs, "OfxImageClipPropComponents_Output", 0, componentStr);
	if (gHostSupportsMultipleBitDepths) {
		gPropHost->propSetString(outArgs, "OfxImageClipPropDepth_Output", 0, bitDepthStr);
	}
	return kOfxStatOK;
}

// are the settings of the effect performing an identity operation
static OfxStatus isIdentity(int pluginIndex, OfxImageEffectHandle effect, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	return kOfxStatReplyDefault;
}

static void showAboutDialog(int pluginIndex, MyInstanceData* myData)
{
	try
	{
		// normal about dialog
		string sDescription = globalData[pluginIndex].pluginInfo.description;
		strReplace(sDescription, "\\r", "\r");
		strReplace(sDescription, "\\n", "\n");
		sDescription = sDescription.substr(0, 201);
		string sName = string(PLUGIN_NAME);
		char msg[250];
		sprintf(msg, "%s %d.%d\r%s", sName.c_str(), MAJOR_VERSION, MINOR_VERSION, sDescription.c_str());
#ifdef ABOUT_DIALOG
		CTMsgDlg dlg(400, 150);
		dlg.ShowDialog(sName, string(msg), "", "", "OK", false, "");
#endif
	}
	catch(...)
	{
	}
}

////////////////////////////////////////////////////////////////////////////////
// function called when the instance has been changed by anything
static OfxStatus instanceChanged(int pluginIndex, OfxImageEffectHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	ContextData contextData;
	setContextData(contextData, instance, inArgs, outArgs);

	// see why it changed
	char *changeReason;
	gPropHost->propGetString(inArgs, kOfxPropChangeReason, 0, &changeReason);

	// we are only interested in user edits
	if (strcmp(changeReason, kOfxChangeUserEdited) != 0) return kOfxStatReplyDefault;

	// fetch the type of the object that changed
	char *typeChanged;
	gPropHost->propGetString(inArgs, kOfxPropType, 0, &typeChanged);

	// was it a clip or a param?
	bool isClip = strcmp(typeChanged, kOfxTypeClip) == 0;
	bool isParam = strcmp(typeChanged, kOfxTypeParameter) == 0;

	// get the name of the thing that changed
	char *objChanged;
	gPropHost->propGetString(inArgs, kOfxPropName, 0, &objChanged);

	// retrieve any instance data associated with this effect
	MyInstanceData* myData = getMyInstanceData(instance);
	
	if (isParam) {
		if (strcmp(objChanged, "SequenceData") == 0) {
			char* flatCustomSequenceDataP = NULL;
			gParamHost->paramGetValue(myData->seqDataH, &flatCustomSequenceDataP);
			if (myData->sequenceDataP->customSequenceDataP) {
				destroyCustomSequenceData(myData->sequenceDataP->customSequenceDataP);
				myData->sequenceDataP->customSequenceDataP = NULL;
			}

			string s = string(flatCustomSequenceDataP);
			unsigned char* buf = NULL;
			if (s != "") {
				buf = new unsigned char[(int)s.size() / 2];
				hexStringToBuffer(s, buf);
			}
			if (buf) {
				myData->sequenceDataP->customSequenceDataP = unflattenCustomSequenceData(buf, (int)s.size() / 2);
				delete [] buf;
			} else {
				myData->sequenceDataP->customSequenceDataP = createCustomSequenceData();
			}
		}
		OfxParamSetHandle paramSet;
		gEffectHost->getParamSet(instance, &paramSet);
		OfxParamHandle param; 
		OfxPropertySetHandle props;
		gParamHost->paramGetHandle(paramSet, objChanged, &param, &props);
		char* paramType;
		gPropHost->propGetString(props, kOfxParamPropType, 0, &paramType);

#ifdef ABOUT_DIALOG
		if (strcmp(objChanged, "About") == 0) {
			showAboutDialog(myData);
		}
#endif
		for (int i = 0; i < globalData[pluginIndex].nofParams; i++) {
			if (globalData[pluginIndex].param[i].paramName == string(objChanged)) {
				OfxTime time;
				gPropHost->propGetDouble(inArgs, kOfxPropTime, 0, &time);
				getParamData(pluginIndex, i, myData, time);
				pluginParamChange(i, myData->sequenceDataP, &globalData[pluginIndex], &contextData);
				break;
			}
		}


	}
	
	// don't trap any 
	return kOfxStatReplyDefault;
}

#define NOF_CONVERT_THREADS 8

class ConvertData
{
public:
	void* srcData;
	int srcRowBytes;
	void* dstData;
	int dstRowBytes;
	int width;
	int height;
	float scale;
	
	ConvertData(void* _srcData = NULL, int _srcRowBytes = 0, void* _dstData = NULL, int _dstRowBytes = 0, int _width = 0, int _height = 0, float _scale = 1.f)
	{
		srcData = _srcData;
		dstData = _dstData;
		srcRowBytes = _srcRowBytes;
		dstRowBytes = _dstRowBytes;
		width = _width;
		height = _height;
		scale = _scale;
	};
};

void convert_RGBA8P_to_RGBA8(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		unsigned char* in_pixR = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 0));
		unsigned char* in_pixG = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 1));
		unsigned char* in_pixB = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 2));
		unsigned char* in_pixA = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 3));
#ifdef IMG_FLIP_Y
		unsigned char* out_pix = (unsigned char*)((char*)data.dstData + ((data.height-1-y) * data.dstRowBytes));
#else
		unsigned char* out_pix = (unsigned char*)((char*)data.dstData + (y * data.dstRowBytes));
#endif
		for (int x = 0; x < data.width; x++) {
			*out_pix++ = *in_pixR; in_pixR += stepWidth;
			*out_pix++ = *in_pixG; in_pixG += stepWidth;
			*out_pix++ = *in_pixB; in_pixB += stepWidth;
			*out_pix++ = *in_pixA; in_pixA += stepWidth;
		}
	}
}

void convert_RGBA8P_to_RGBA32(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		unsigned char* in_pixR = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 0));
		unsigned char* in_pixG = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 1));
		unsigned char* in_pixB = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 2));
		unsigned char* in_pixA = (unsigned char*)((char*)data.srcData + sizeof(unsigned char) * data.width * (y + data.height * 3));
#ifdef IMG_FLIP_Y
		float* out_pix = (float*)((char*)data.dstData + ((data.height-1-y) * data.dstRowBytes));
#else
		float* out_pix = (float*)((char*)data.dstData + (y * data.dstRowBytes));
#endif
		for (int x = 0; x < data.width; x++) {
			*out_pix++ = ((float)(*in_pixR) * I_MAX_CHAN8 * data.scale); in_pixR += stepWidth;
			*out_pix++ = ((float)(*in_pixG) * I_MAX_CHAN8 * data.scale); in_pixG += stepWidth;
			*out_pix++ = ((float)(*in_pixB) * I_MAX_CHAN8 * data.scale); in_pixB += stepWidth;
			*out_pix++ = ((float)(*in_pixA) * I_MAX_CHAN8 * data.scale); in_pixA += stepWidth;
		}
	}
}

void convert_RGBA8_to_RGBA8P(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
#ifdef IMG_FLIP_Y
		unsigned char* in_pix = (unsigned char*)((char*)data.srcData + ((data.height-1-y) * data.srcRowBytes));
#else
		unsigned char* in_pix = (unsigned char*)((char*)data.srcData + (y * data.srcRowBytes));
#endif
		unsigned char* out_pixR = (unsigned char*)((char*)data.dstData + sizeof(unsigned char) * data.width * (y + data.height * 0));
		unsigned char* out_pixG = (unsigned char*)((char*)data.dstData + sizeof(unsigned char) * data.width * (y + data.height * 1));
		unsigned char* out_pixB = (unsigned char*)((char*)data.dstData + sizeof(unsigned char) * data.width * (y + data.height * 2));
		unsigned char* out_pixA = (unsigned char*)((char*)data.dstData + sizeof(unsigned char) * data.width * (y + data.height * 3));
		for (int x = 0; x < data.width; x++) {
			*out_pixR = *in_pix++; out_pixR += stepWidth;
			*out_pixG = *in_pix++; out_pixG += stepWidth;
			*out_pixB = *in_pix++; out_pixB += stepWidth;
			*out_pixA = *in_pix++; out_pixA += stepWidth;
		}
	}
}

void convert_RGBA32P_to_RGBA32(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		float* in_pixR = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 0));
		float* in_pixG = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 1));
		float* in_pixB = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 2));
		float* in_pixA = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 3));
#ifdef IMG_FLIP_Y
		float* out_pix = (float*)((char*)data.dstData + ((data.height-1-y) * data.dstRowBytes));
#else
		float* out_pix = (float*)((char*)data.dstData + (y * data.dstRowBytes));
#endif
		for (int x = 0; x < data.width; x++) {
			*out_pix++ = *in_pixR * data.scale; in_pixR += stepWidth;
			*out_pix++ = *in_pixG * data.scale; in_pixG += stepWidth;
			*out_pix++ = *in_pixB * data.scale; in_pixB += stepWidth;
			*out_pix++ = *in_pixA * data.scale; in_pixA += stepWidth;
		}
	}
}

void convert_RGBA32_to_RGBA32(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		float* in_pix = (float*)((char*)data.srcData + ((data.height-1-y) * data.srcRowBytes));
#ifdef IMG_FLIP_Y
		float* out_pix = (float*)((char*)data.dstData + ((data.height-1-y) * data.dstRowBytes));
#else
		float* out_pix = (float*)((char*)data.dstData + (y * data.dstRowBytes));
#endif
		for (int x = 0; x < data.width; x++) {
			*out_pix++ = *in_pix++ * data.scale;
		}
	}
}
void convert_RGBA32P_to_RGBA8(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		float* in_pixR = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 0));
		float* in_pixG = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 1));
		float* in_pixB = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 2));
		float* in_pixA = (float*)((char*)data.srcData + sizeof(float) * data.width * (y + data.height * 3));
#ifdef IMG_FLIP_Y
		unsigned char* out_pix = (unsigned char*)((char*)data.dstData + ((data.height-1-y) * data.dstRowBytes));
#else
		unsigned char* out_pix = (unsigned char*)((char*)data.dstData + (y * data.dstRowBytes));
#endif
		for (int x = 0; x < data.width; x++) {
			*out_pix++ = (unsigned char)(saturate(*in_pixR * data.scale) * MAX_CHAN8 + 0.5f); in_pixR += stepWidth;
			*out_pix++ = (unsigned char)(saturate(*in_pixG * data.scale) * MAX_CHAN8 + 0.5f); in_pixG += stepWidth;
			*out_pix++ = (unsigned char)(saturate(*in_pixB * data.scale) * MAX_CHAN8 + 0.5f); in_pixB += stepWidth;
			*out_pix++ = (unsigned char)(saturate(*in_pixA * data.scale) * MAX_CHAN8 + 0.5f); in_pixA += stepWidth;
		}
	}
}

void convert_RGBA32_to_RGBA32P(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
#ifdef IMG_FLIP_Y
		float* in_pix = (float*)((char*)data.srcData + ((data.height-1-y) * data.srcRowBytes));
#else
		float* in_pix = (float*)((char*)data.srcData + (y * data.srcRowBytes));
#endif
		float* out_pixR = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 0));
		float* out_pixG = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 1));
		float* out_pixB = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 2));
		float* out_pixA = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 3));
		for (int x = 0; x < data.width; x++) {
			*out_pixR = (*in_pix++) * data.scale; out_pixR += stepWidth;
			*out_pixG = (*in_pix++) * data.scale; out_pixG += stepWidth;
			*out_pixB = (*in_pix++) * data.scale; out_pixB += stepWidth;
			*out_pixA = (*in_pix++) * data.scale; out_pixA += stepWidth;
		}
	}
}

void convert_RGBA8_to_RGBA32(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		unsigned char* in_pix = (unsigned char*)((char*)data.srcData + (y * data.srcRowBytes));
		float* out_pixR = (float*)((char*)data.dstData + (y * data.dstRowBytes));
		float* out_pixG = out_pixR + 1;
		float* out_pixB = out_pixR + 2;
		float* out_pixA = out_pixR + 3;
		for (int x = 0; x < data.width; x++) {
			*out_pixR = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixR += stepWidth;
			*out_pixG = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixG += stepWidth;
			*out_pixB = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixB += stepWidth;
			*out_pixA = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixA += stepWidth;
		}
	}
}

void convert_RGBA8_to_RGBA32P(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		unsigned char* in_pix = (unsigned char*)((char*)data.srcData + (y * data.srcRowBytes));
		float* out_pixR = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 0));
		float* out_pixG = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 1));
		float* out_pixB = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 2));
		float* out_pixA = (float*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 3));
		for (int x = 0; x < data.width; x++) {
			*out_pixR = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixR += stepWidth;
			*out_pixG = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixG += stepWidth;
			*out_pixB = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixB += stepWidth;
			*out_pixA = ((float)(*in_pix++) * I_MAX_CHAN8 * data.scale); out_pixA += stepWidth;
		}
	}
}

void convert_RGBA32_to_RGBA8(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		float* in_pix = (float*)((char*)data.srcData + (y * data.srcRowBytes));
		unsigned char* out_pixR = (unsigned char*)((char*)data.dstData + (y * data.dstRowBytes));
		unsigned char* out_pixG = out_pixR + 1;
		unsigned char* out_pixB = out_pixR + 2;
		unsigned char* out_pixA = out_pixR + 3;
		for (int x = 0; x < data.width; x++) {
			*out_pixR = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixR += stepWidth;
			*out_pixG = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixG += stepWidth;
			*out_pixB = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixB += stepWidth;
			*out_pixA = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixA += stepWidth;
		}
	}
}

void convert_RGBA32_to_RGBA8P(ConvertData& data, const int startLine, const int endLine)
{
	for (int y = startLine; y < endLine; y++) {
		float* in_pix = (float*)((char*)data.srcData + (y * data.srcRowBytes));
		unsigned char* out_pixR = (unsigned char*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 0));
		unsigned char* out_pixG = (unsigned char*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 1));
		unsigned char* out_pixB = (unsigned char*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 2));
		unsigned char* out_pixA = (unsigned char*)((char*)data.dstData + sizeof(float) * data.width * (y + data.height * 3));
		for (int x = 0; x < data.width; x++) {
			*out_pixR = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixR += stepWidth;
			*out_pixG = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixG += stepWidth;
			*out_pixB = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixB += stepWidth;
			*out_pixA = (unsigned char)(saturate(*in_pix++ * data.scale) * MAX_CHAN8 + 0.5f); out_pixA += stepWidth;
		}
	}
}

// the process code that the host sees
static OfxStatus render(int pluginIndex, OfxImageEffectHandle instance, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	ContextData contextData;
	setContextData(contextData, instance, inArgs, outArgs);

	// get the render window and the time from the inArgs
	OfxTime time;
	OfxRectI renderWindow;
	OfxStatus status = kOfxStatOK;

	gPropHost->propGetDouble(inArgs, kOfxPropTime, 0, &time);
	double time_step = 1.f;
	gPropHost->propGetIntN(inArgs, kOfxImageEffectPropRenderWindow, 4, &renderWindow.x1);

	// retrieve any instance data associated with this effect
	MyInstanceData *myData = getMyInstanceData(instance);

	OfxPropertySetHandle outputImg = NULL;
	OfxPropertySetHandle sourceImg[MAX_NOF_LAYERS] = { 0 };
	bool customInputData[MAX_NOF_LAYERS] = { 0 };
	bool customOutputData = false;
	for (int i = 0; i < globalData[pluginIndex].nofInputs; i++) {
		sourceImg[i] = NULL;
		customInputData[i] = false;
	}

	bool dstIsAlpha = false;
	void* dstData = NULL;

#ifndef NO_MULTITHREADED_CONVERSION
	thread t[NOF_CONVERT_THREADS];
#endif

	try
	{
		// get the output image
		int dstRowBytes, dstBitDepth;
		OfxRectI dstRect;
		outputImg = ofxuGetImage(myData->output, time, dstRowBytes, dstBitDepth, dstIsAlpha, dstRect, dstData);
		if (outputImg == NULL) throw OfxuNoImageException();
		float scale = globalData[pluginIndex].scale;

		OfxPointD renderScale;
		gPropHost->propGetDoubleN(inArgs, kOfxImageEffectPropRenderScale, 2, &renderScale.x);
		OfxRectI renderWindow;
		gPropHost->propGetIntN(inArgs, kOfxImageEffectPropRenderWindow, 4, &renderWindow.x1);

		myData->sequenceDataP->time = time;
		
		getAllParamData(pluginIndex, myData, time);

		// get the input image(s)
		int i = 0;
		for (int p = 0; p < globalData[pluginIndex].nofParams; p++) {
			if (globalData[pluginIndex].param[p].paramType != PT_LAYER) continue;
			int srcRowBytes, srcBitDepth;
			OfxRectI srcRect;
			bool srcIsAlpha = false;
			void *srcData = NULL;

			myData->sequenceDataP->inputConnected[i] = false;
			if (ofxuIsClipConnected(instance, globalData[pluginIndex].param[p].paramName.c_str())) {
				myData->sequenceDataP->inputConnected[i] = true;
				double tofs = time;
				int ofs = (int)(myData->sequenceDataP->floatValue[i][0]);
				int ofs_type = (int)(myData->sequenceDataP->floatValue[i][1]); //0:relative,1:absolute,2:granularity
				if (ofs_type == 0) {
					tofs += ofs * (1 + myData->sequenceDataP->timeSpread) * time_step;
				} else if (ofs_type == 1) {
					tofs = ofs * time_step;
				} else {
					if (ofs <= 0) {
						tofs = 0;
					} else if (ofs > 1) {
						tofs = (int)(floor( (float)tofs/ ( (float)ofs * time_step) ) * (float)ofs) * time_step;
					}
				}
				if (tofs < 0) tofs = 0;
				sourceImg[i] = ofxuGetImage(myData->input[i], tofs, srcRowBytes, srcBitDepth, srcIsAlpha, srcRect, srcData);
			}
			if (sourceImg[i] == NULL) {
				myData->sequenceDataP->inputConnected[i] = false;
				if (i == 0) {
					throw OfxuNoImageException();
				} else {
					myData->sequenceDataP->inWorld[i].data = NULL;
					break;
				}
			}

			myData->sequenceDataP->inWorld[i].width = (srcRect.x2 - srcRect.x1);
			myData->sequenceDataP->inWorld[i].height = (srcRect.y2 - srcRect.y1);
			myData->sequenceDataP->inWorld[i].bitDepth = srcBitDepth;
			myData->sequenceDataP->inWorld[i].pixelFormat = PF_RGBA;
			myData->sequenceDataP->inWorld[i].data = srcData;
			myData->sequenceDataP->inWorld[i].rowBytes = srcRowBytes;


#if defined(CONVERT_INT_TO_FLOAT)
			if (srcBitDepth == 8) {
				myData->sequenceDataP->inWorld[i].rowBytes = myData->sequenceDataP->inWorld[i].width * sizeof(OfxRGBAColourF);
				myData->sequenceDataP->inWorld[i].data = new unsigned char[myData->sequenceDataP->inWorld[i].height * myData->sequenceDataP->inWorld[i].rowBytes];
				myData->sequenceDataP->inWorld[i].bitDepth = 32;
				ConvertData data(srcData, srcRowBytes, myData->sequenceDataP->inWorld[i].data, myData->sequenceDataP->inWorld[i].rowBytes, myData->sequenceDataP->inWorld[i].width, myData->sequenceDataP->inWorld[i].height, scale);
	
#ifndef NO_MULTITHREADED_CONVERSION
				int nofLines = (int)(floor((float)myData->sequenceDataP->inWorld[i].height / (float)NOF_CONVERT_THREADS) + 1.f);
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
					int startLine = j * nofLines;
					int endLine = min((j + 1) * nofLines, myData->sequenceDataP->inWorld[i].height);
#ifdef PLANAR_BUFFER
					t[j] = thread(convert_RGBA8_to_RGBA32P, data, startLine, endLine);
#else
					t[j] = thread(convert_RGBA8_to_RGBA32, data, startLine, endLine);
#endif
				}
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else

#ifdef PLANAR_BUFFER
				convert_RGBA8_to_RGBA32P(data, 0, myData->sequenceDataP->inWorld[i].height);
#else
				convert_RGBA8_to_RGBA32(data, 0, myData->sequenceDataP->inWorld[i].height);
#endif

#endif
				customInputData[i] = true;
#ifdef PLANAR_BUFFER
			} else if (srcBitDepth == 32) {
				myData->sequenceDataP->inWorld[i].rowBytes = myData->sequenceDataP->inWorld[i].width * sizeof(OfxRGBAColourF);
				myData->sequenceDataP->inWorld[i].data = new unsigned char[myData->sequenceDataP->inWorld[i].height * myData->sequenceDataP->inWorld[i].rowBytes];
				myData->sequenceDataP->inWorld[i].bitDepth = 32;
				ConvertData data(srcData, srcRowBytes, myData->sequenceDataP->inWorld[i].data, myData->sequenceDataP->inWorld[i].rowBytes, myData->sequenceDataP->inWorld[i].width, myData->sequenceDataP->inWorld[i].height, scale);
#ifndef NO_MULTITHREADED_CONVERSION
				int nofLines = (int)(floor((float)myData->sequenceDataP->inWorld[i].height / (float)NOF_CONVERT_THREADS) + 1.f);
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
					int startLine = j * nofLines;
					int endLine = min((j + 1) * nofLines, myData->sequenceDataP->inWorld[i].height);
					t[j] = thread(convert_RGBA32_to_RGBA32P, data, startLine, endLine);
				}
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else				
				convert_RGBA32_to_RGBA32P(data, 0, myData->sequenceDataP->inWorld[i].height);
#endif
				customInputData[i] = true;
#endif			
			}



#elif defined(CONVERT_FLOAT_TO_INT)
			if (srcBitDepth == 32) {
				myData->sequenceDataP->inWorld[i].rowBytes = myData->sequenceDataP->inWorld[i].width * sizeof(OfxRGBAColourB);
				myData->sequenceDataP->inWorld[i].data = new unsigned char[myData->sequenceDataP->inWorld[i].height * myData->sequenceDataP->inWorld[i].rowBytes];
				myData->sequenceDataP->inWorld[i].bitDepth = 8;
				ConvertData data(srcData, srcRowBytes, myData->sequenceDataP->inWorld[i].data, myData->sequenceDataP->inWorld[i].rowBytes, myData->sequenceDataP->inWorld[i].width, myData->sequenceDataP->inWorld[i].height, scale);
#ifndef NO_MULTITHREADED_CONVERSION
				int nofLines = (int)(floor((float)myData->sequenceDataP->inWorld[i].height / (float)NOF_CONVERT_THREADS) + 1.f);
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
					int startLine = j * nofLines;
					int endLine = min((j + 1) * nofLines, myData->sequenceDataP->inWorld[i].height);
#ifdef PLANAR_BUFFER
					t[j] = thread(convert_RGBA32_to_RGBA8P, data, startLine, endLine);
#else
					t[j] = thread(convert_RGBA32_to_RGBA8, data, startLine, endLine);
#endif
				}
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else

#ifdef PLANAR_BUFFER
				convert_RGBA32_to_RGBA8P(data, 0, myData->sequenceDataP->inWorld[i].height);
#else
				convert_RGBA32_to_RGBA8(data, 0, myData->sequenceDataP->inWorld[i].height);
#endif

#endif
				customInputData[i] = true;
#ifdef PLANAR_BUFFER
			} else if (srcBitDepth == 8) {
				myData->sequenceDataP->inWorld[i].rowBytes = myData->sequenceDataP->inWorld[i].width * sizeof(OfxRGBAColourB);
				myData->sequenceDataP->inWorld[i].data = new unsigned char[myData->sequenceDataP->inWorld[i].height * myData->sequenceDataP->inWorld[i].rowBytes];
				myData->sequenceDataP->inWorld[i].bitDepth = 8;
				ConvertData data(srcData, srcRowBytes, myData->sequenceDataP->inWorld[i].data, myData->sequenceDataP->inWorld[i].rowBytes, myData->sequenceDataP->inWorld[i].width, myData->sequenceDataP->inWorld[i].height, scale);
#ifndef NO_MULTITHREADED_CONVERSION
				int nofLines = (int)(floor((float)myData->sequenceDataP->inWorld[i].height / (float)NOF_CONVERT_THREADS) + 1.f);
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
					int startLine = j * nofLines;
					int endLine = min((j + 1) * nofLines, myData->sequenceDataP->inWorld[i].height);
					t[j] = thread(convert_RGBA8_to_RGBA8P, data, startLine, endLine);
				}
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else				
				convert_RGBA8_to_RGBA8P(data, 0, myData->sequenceDataP->inWorld[i].height);
#endif
				customInputData[i] = true;
#endif
			}
#elif defined(PLANAR_BUFFER)
			if (srcBitDepth == 8) {
				myData->sequenceDataP->inWorld[i].rowBytes = myData->sequenceDataP->inWorld[i].width * sizeof(OfxRGBAColourB);
				myData->sequenceDataP->inWorld[i].data = new unsigned char[myData->sequenceDataP->inWorld[i].height * myData->sequenceDataP->inWorld[i].rowBytes];
				myData->sequenceDataP->inWorld[i].bitDepth = 8;
				ConvertData data(srcData, srcRowBytes, myData->sequenceDataP->inWorld[i].data, myData->sequenceDataP->inWorld[i].rowBytes, myData->sequenceDataP->inWorld[i].width, myData->sequenceDataP->inWorld[i].height, scale);
#ifndef NO_MULTITHREADED_CONVERSION
				int nofLines = (int)(floor((float)myData->sequenceDataP->inWorld[i].height / (float)NOF_CONVERT_THREADS) + 1.f);
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
					int startLine = j * nofLines;
					int endLine = min((j + 1) * nofLines, myData->sequenceDataP->inWorld[i].height);
					t[j] = thread(convert_RGBA8_to_RGBA8P, data, startLine, endLine);
				}
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else				
				convert_RGBA8_to_RGBA8P(data, 0, myData->sequenceDataP->inWorld[i].height);
#endif
			} else if (srcBitDepth == 32) {
				myData->sequenceDataP->inWorld[i].rowBytes = myData->sequenceDataP->inWorld[i].width * sizeof(OfxRGBAColourF);
				myData->sequenceDataP->inWorld[i].data = new unsigned char[myData->sequenceDataP->inWorld[i].height * myData->sequenceDataP->inWorld[i].rowBytes];
				myData->sequenceDataP->inWorld[i].bitDepth = 32;
				ConvertData data(srcData, srcRowBytes, myData->sequenceDataP->inWorld[i].data, myData->sequenceDataP->inWorld[i].rowBytes, myData->sequenceDataP->inWorld[i].width, myData->sequenceDataP->inWorld[i].height, scale);
#ifndef NO_MULTITHREADED_CONVERSION
				int nofLines = (int)(floor((float)myData->sequenceDataP->inWorld[i].height / (float)NOF_CONVERT_THREADS) + 1.f);
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
					int startLine = j * nofLines;
					int endLine = min((j + 1) * nofLines, myData->sequenceDataP->inWorld[i].height);
					t[j] = thread(convert_RGBA32_to_RGBA32P, data, startLine, endLine);
				}
				for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else				
				convert_RGBA32_to_RGBA32P(data, 0, myData->sequenceDataP->inWorld[i].height);
#endif
			}
			customInputData[i] = true;

#endif
			i++;
		}

		myData->sequenceDataP->outWorld.pixelFormat = PF_RGBA;
		myData->sequenceDataP->outWorld.width = (dstRect.x2 - dstRect.x1);
		myData->sequenceDataP->outWorld.height = (dstRect.y2 - dstRect.y1);
		myData->sequenceDataP->outWorld.rowBytes = dstRowBytes;
		myData->sequenceDataP->outWorld.bitDepth = dstBitDepth;
		myData->sequenceDataP->outWorld.data = dstData;

#if defined(CONVERT_INT_TO_FLOAT)
		if (dstBitDepth == 8) {
			myData->sequenceDataP->outWorld.rowBytes = myData->sequenceDataP->outWorld.width * sizeof(OfxRGBAColourF);
			myData->sequenceDataP->outWorld.data = new unsigned char[myData->sequenceDataP->outWorld.height * myData->sequenceDataP->outWorld.rowBytes];
			customOutputData = true;
#ifdef PLANAR_BUFFER
		} else if (dstBitDepth == 32) {
			myData->sequenceDataP->outWorld.rowBytes = myData->sequenceDataP->outWorld.width * sizeof(OfxRGBAColourF);
			myData->sequenceDataP->outWorld.data = new unsigned char[myData->sequenceDataP->outWorld.height * myData->sequenceDataP->outWorld.rowBytes];
			customOutputData = true;
#endif
		}
#elif defined(CONVERT_FLOAT_TO_INT)
		if (dstBitDepth == 32) {
			myData->sequenceDataP->outWorld.rowBytes = myData->sequenceDataP->outWorld.width * sizeof(OfxRGBAColourB);
			myData->sequenceDataP->outWorld.data = new unsigned char[myData->sequenceDataP->outWorld.height * myData->sequenceDataP->outWorld.rowBytes];
			customOutputData = true;
#ifdef PLANAR_BUFFER
		} else if (dstBitDepth == 8) {
			myData->sequenceDataP->outWorld.rowBytes = myData->sequenceDataP->outWorld.width * sizeof(OfxRGBAColourB);
			myData->sequenceDataP->outWorld.data = new unsigned char[myData->sequenceDataP->outWorld.height * myData->sequenceDataP->outWorld.rowBytes];
			customOutputData = true;
#endif
		}
#elif defined(PLANAR_BUFFER)
		if (dstBitDepth == 8) {
			myData->sequenceDataP->outWorld.rowBytes = myData->sequenceDataP->outWorld.width * sizeof(OfxRGBAColourB);
			myData->sequenceDataP->outWorld.data = new unsigned char[myData->sequenceDataP->outWorld.height * myData->sequenceDataP->outWorld.rowBytes];
		} else if (dstBitDepth == 32) {
			myData->sequenceDataP->outWorld.rowBytes = myData->sequenceDataP->outWorld.width * sizeof(OfxRGBAColourF);
			myData->sequenceDataP->outWorld.data = new unsigned char[myData->sequenceDataP->outWorld.height * myData->sequenceDataP->outWorld.rowBytes];
		}
		customOutputData = true;
#endif

		// here we call the actual processing function of the plugin!
		pluginProcess(myData->sequenceDataP, &globalData[pluginIndex], &contextData);

#if defined(CONVERT_INT_TO_FLOAT)
		if (dstBitDepth == 8) {
			ConvertData data(myData->sequenceDataP->outWorld.data, myData->sequenceDataP->outWorld.rowBytes, dstData, dstRowBytes, myData->sequenceDataP->outWorld.width, myData->sequenceDataP->outWorld.height, 1.f / scale);
#ifndef NO_MULTITHREADED_CONVERSION
			int nofLines = (int)(floor((float)myData->sequenceDataP->outWorld.height / (float)NOF_CONVERT_THREADS) + 1.f);
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
				int startLine = j * nofLines;
				int endLine = min((j + 1) * nofLines, myData->sequenceDataP->outWorld.height);
#ifdef PLANAR_BUFFER
				t[j] = thread(convert_RGBA32P_to_RGBA8, data, startLine, endLine);
#else
				t[j] = thread(convert_RGBA32_to_RGBA8, data, startLine, endLine);
#endif
			}
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else

#ifdef PLANAR_BUFFER
			convert_RGBA32P_to_RGBA8(data, 0, myData->sequenceDataP->outWorld.height);
#else
			convert_RGBA32_to_RGBA8(data, 0, myData->sequenceDataP->outWorld.height);
#endif

#endif

#ifdef PLANAR_BUFFER
		} else if (dstBitDepth == 32) {
			ConvertData data(myData->sequenceDataP->outWorld.data, myData->sequenceDataP->outWorld.rowBytes, dstData, dstRowBytes, myData->sequenceDataP->outWorld.width, myData->sequenceDataP->outWorld.height, 1.f / scale);
#ifndef NO_MULTITHREADED_CONVERSION
			int nofLines = (int)(floor((float)myData->sequenceDataP->outWorld.height / (float)NOF_CONVERT_THREADS) + 1.f);
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
				int startLine = j * nofLines;
				int endLine = min((j + 1) * nofLines, myData->sequenceDataP->outWorld.height);
				t[j] = thread(convert_RGBA32P_to_RGBA32, data, startLine, endLine);
			}
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else
			convert_RGBA32P_to_RGBA32(data, 0, myData->sequenceDataP->outWorld.height);
#endif
#endif
		}


#elif defined(CONVERT_FLOAT_TO_INT)
		if (dstBitDepth == 32) {
			ConvertData data(myData->sequenceDataP->outWorld.data, myData->sequenceDataP->outWorld.rowBytes, dstData, dstRowBytes, myData->sequenceDataP->outWorld.width, myData->sequenceDataP->outWorld.height, 1.f / scale);
#ifndef NO_MULTITHREADED_CONVERSION
			int nofLines = (int)(floor((float)myData->sequenceDataP->outWorld.height / (float)NOF_CONVERT_THREADS) + 1.f);
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
				int startLine = j * nofLines;
				int endLine = min((j + 1) * nofLines, myData->sequenceDataP->outWorld.height);
#ifdef PLANAR_BUFFER
				t[j] = thread(convert_RGBA8P_to_RGBA32, data, startLine, endLine);
#else
				t[j] = thread(convert_RGBA8_to_RGBA32, data, startLine, endLine);
#endif
			}
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else

#ifdef PLANAR_BUFFER
			convert_RGBA8P_to_RGBA32(data, 0, myData->sequenceDataP->outWorld.height);
#else
			convert_RGBA8_to_RGBA32(data, 0, myData->sequenceDataP->outWorld.height);
#endif

#endif

#ifdef PLANAR_BUFFER
		} else if (dstBitDepth == 8) {
			ConvertData data(myData->sequenceDataP->outWorld.data, myData->sequenceDataP->outWorld.rowBytes, dstData, dstRowBytes, myData->sequenceDataP->outWorld.width, myData->sequenceDataP->outWorld.height, 1.f / scale);
#ifndef NO_MULTITHREADED_CONVERSION
			int nofLines = (int)(floor((float)myData->sequenceDataP->outWorld.height / (float)NOF_CONVERT_THREADS) + 1.f);
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
				int startLine = j * nofLines;
				int endLine = min((j + 1) * nofLines, myData->sequenceDataP->outWorld.height);
				t[j] = thread(convert_RGBA8P_to_RGBA8, data, startLine, endLine);
			}
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else
			convert_RGBA8P_to_RGBA8(data, 0, myData->sequenceDataP->outWorld.height);
#endif
#endif

		}


#elif defined(PLANAR_BUFFER)
		if (dstBitDepth == 8) {
			ConvertData data(myData->sequenceDataP->outWorld.data, myData->sequenceDataP->outWorld.rowBytes, dstData, dstRowBytes, myData->sequenceDataP->outWorld.width, myData->sequenceDataP->outWorld.height, 1.f / scale);
#ifndef NO_MULTITHREADED_CONVERSION
			int nofLines = (int)(floor((float)myData->sequenceDataP->outWorld.height / (float)NOF_CONVERT_THREADS) + 1.f);
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
				int startLine = j * nofLines;
				int endLine = min((j + 1) * nofLines, myData->sequenceDataP->outWorld.height);
				t[j] = thread(convert_RGBA8P_to_RGBA8, data, startLine, endLine);
			}
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else
			convert_RGBA8P_to_RGBA8(data, 0, myData->sequenceDataP->outWorld.height);
#endif
		} else if (dstBitDepth == 32) {
			ConvertData data(myData->sequenceDataP->outWorld.data, myData->sequenceDataP->outWorld.rowBytes, dstData, dstRowBytes, myData->sequenceDataP->outWorld.width, myData->sequenceDataP->outWorld.height, 1.f / scale);
#ifndef NO_MULTITHREADED_CONVERSION
			int nofLines = (int)(floor((float)myData->sequenceDataP->outWorld.height / (float)NOF_CONVERT_THREADS) + 1.f);
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) {
				int startLine = j * nofLines;
				int endLine = min((j + 1) * nofLines, myData->sequenceDataP->outWorld.height);
				t[j] = thread(convert_RGBA32P_to_RGBA32, data, startLine, endLine);
			}
			for (int j = 0; j < NOF_CONVERT_THREADS; ++j) t[j].join();
#else
			convert_RGBA32P_to_RGBA32(data, 0, myData->sequenceDataP->outWorld.height);
#endif
		}
#endif


	} catch(OfxuNoImageException &ex) {
		// if we were interrupted, the failed fetch is fine, just return kOfxStatOK
		// otherwise, something weird happened
		if (!gEffectHost->abort(instance)) {
			// status = kOfxStatFailed;
		}
	} catch(OfxuStatusException &ex) {
		status = ex.status();
	}

	// release the data pointers
	for (int i = 0; i < globalData[pluginIndex].nofInputs; i++) {
		if (sourceImg[i]) {
			gEffectHost->clipReleaseImage(sourceImg[i]);
		}
		if (customInputData[i]) {
			delete (unsigned char*)myData->sequenceDataP->inWorld[i].data;
		}
	}
	if (customOutputData) delete (unsigned char*)myData->sequenceDataP->outWorld.data;
	if (outputImg) gEffectHost->clipReleaseImage(outputImg);
	
	return status;
}

static void paramAddFloat(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, double minValue, double maxValue, double defaultValue, int precision, int dflags)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeDouble, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	if (dflags > 0) gPropHost->propSetString(props, kOfxParamPropDoubleType, 0, kOfxParamDoubleTypeScale);
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 0, defaultValue);
	gPropHost->propSetDouble(props, kOfxParamPropMin, 0, minValue);
	gPropHost->propSetDouble(props, kOfxParamPropMax, 0, maxValue);
	gPropHost->propSetDouble(props, kOfxParamPropDisplayMin, 0, minValue);
	gPropHost->propSetDouble(props, kOfxParamPropDisplayMax, 0, maxValue);
	gPropHost->propSetDouble(props, kOfxParamPropIncrement, 0, 0.01);
	gPropHost->propSetDouble(props, kOfxParamPropDigits, 0, precision);	
}

static void paramAddColor(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, double red, double green, double blue)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeRGB, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 0, red);
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 1, green);
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 2, blue);
}

static void paramAddText(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, const char* defaultText, int textType)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeString, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetString(props, kOfxParamPropDefault, 0, defaultText);
	if (textType == 0) { // single-line
		gPropHost->propSetString(props, kOfxParamPropStringMode, 0, kOfxParamStringIsSingleLine);
	} else if (textType == 1) { // multi-line
		gPropHost->propSetString(props, kOfxParamPropStringMode, 0, kOfxParamStringIsMultiLine);
	} else if (textType == 2) { // file
		gPropHost->propSetString(props, kOfxParamPropStringMode, 0, kOfxParamStringIsFilePath);
		gPropHost->propSetInt(props, kOfxParamPropStringFilePathExists, 0, 0);
	} else if (textType == 3) { // folder
		gPropHost->propSetString(props, kOfxParamPropStringMode, 0, kOfxParamStringIsDirectoryPath);
	}
}

static void paramAddInt(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, int minValue, int maxValue, int defaultValue)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeInteger, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetInt(props, kOfxParamPropDefault, 0, defaultValue);
	gPropHost->propSetInt(props, kOfxParamPropMin, 0, minValue);
	gPropHost->propSetInt(props, kOfxParamPropMax, 0, maxValue);
	gPropHost->propSetInt(props, kOfxParamPropDisplayMin, 0, minValue);
	gPropHost->propSetInt(props, kOfxParamPropDisplayMax, 0, maxValue);
}

static void paramAddPoint(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, double defaultX, double defaultY)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeInteger2D, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 0, defaultX);
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 1, defaultY);
	gPropHost->propSetString(props, kOfxParamPropDoubleType, 0, kOfxParamDoubleTypeXY);
	gPropHost->propSetString(props, kOfxParamPropDefaultCoordinateSystem, 0, kOfxParamCoordinatesNormalised);
}

static void paramAddAngle(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, double defaultValue)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeDouble, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetDouble(props, kOfxParamPropDefault, 0, defaultValue);
	gPropHost->propSetString(props, kOfxParamPropDoubleType, 0, kOfxParamDoubleTypeAngle);
}

static void paramAddBool(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, int defaultValue)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeBoolean, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetInt(props, kOfxParamPropDefault, 0, defaultValue);
    gPropHost->propSetInt(props, kOfxParamPropAnimates, 0, 0);
}

static void paramAddChoice(OfxParamSetHandle effectParams, OfxPropertySetHandle& props, const char* paramName, int maxValue, int defaultValue, vector<string> choices)
{
	OfxStatus stat = gParamHost->paramDefine(effectParams, kOfxParamTypeChoice, paramName, &props);
	if (stat != kOfxStatOK) {
		throw OfxuStatusException(stat);
	}
	gPropHost->propSetInt(props, kOfxParamPropDefault, 0, defaultValue);
	for (int i = 0; i < min(maxValue, (int)choices.size()); i++) gPropHost->propSetString(props, kOfxParamPropChoiceOption, i, choices[i].c_str());
    gPropHost->propSetInt(props, kOfxParamPropAnimates, 0, false);
}

// describe the plugin in context
static OfxStatus describeInContext(int pluginIndex, OfxImageEffectHandle effect, OfxPropertySetHandle inArgs)
{
	// get the context from the inArgs handle
	char *context = NULL;
	gPropHost->propGetString(inArgs, kOfxImageEffectPropContext, 0, &context);
	bool isGeneralContext = strcmp(context, kOfxImageEffectContextGeneral) == 0;

	OfxPropertySetHandle props;
	// define the single output clip in both contexts
	gEffectHost->clipDefine(effect, "Output", &props);

	// set the component types we can handle on our output
	gPropHost->propSetString(props, kOfxImageEffectPropSupportedComponents, 0, kOfxImageComponentRGBA);

	gPropHost->propSetString(props, kOfxImageEffectPluginRenderThreadSafety, 0, kOfxImageEffectRenderUnsafe);//kOfxImageEffectRenderInstanceSafe);
	gPropHost->propSetInt(props, kOfxImageEffectPropSupportsTiles, 0, 0);
	gPropHost->propSetInt(props, kOfxImageEffectPluginPropHostFrameThreading, 0, 0);
	gPropHost->propSetInt(props, kOfxImageEffectPropSupportsMultiResolution, 0, 0);
	gPropHost->propSetInt(props, kOfxImageEffectPropTemporalClipAccess, 0, 1);

	// fetch the parameter set from the effect
	OfxParamSetHandle paramSet;
	gEffectHost->getParamSet(effect, &paramSet);

	{
	OfxPropertySetHandle props;
	gParamHost->paramDefine(paramSet, kOfxParamTypeCustom, "SequenceData", &props);
	gPropHost->propSetInt(props, kOfxParamPropSecret, 0, 1);
	}
	
#ifdef ABOUT_DIALOG
	{
	OfxPropertySetHandle props;
	gParamHost->paramDefine(paramSet, kOfxParamTypePushButton, "About", &props);
	}
#endif

	string group;
	int l = 0;
	for (int i = 0; i < globalData[pluginIndex].nofParams; i++) {
		OfxPropertySetHandle props;

		float mmin = globalData[pluginIndex].param[i].minValue;
		float mmax = globalData[pluginIndex].param[i].maxValue;
		
		if (globalData[pluginIndex].param[i].paramType == PT_FLOAT) {
			paramAddFloat(paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				mmin, //valid min
				mmax, //valid max
				globalData[pluginIndex].param[i].defaultValue[0], //default
				2, //precision
				globalData[pluginIndex].param[i].flags //display flags
				);
		} else if (globalData[pluginIndex].param[i].paramType == PT_COLOR) {
			paramAddColor(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				globalData[pluginIndex].param[i].defaultValue[0], 
				globalData[pluginIndex].param[i].defaultValue[1], 
				globalData[pluginIndex].param[i].defaultValue[2]
				); 
		} else if (globalData[pluginIndex].param[i].paramType == PT_TEXT) {
			paramAddText(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				globalData[pluginIndex].param[i].text.c_str(), globalData[pluginIndex].param[i].flags); 
		} else if (globalData[pluginIndex].param[i].paramType == PT_INT) {
			paramAddInt(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				(int)mmin, //valid min
				(int)mmax, //valid max
				(int)globalData[pluginIndex].param[i].defaultValue[0] //default
				);
		} else if (globalData[pluginIndex].param[i].paramType == PT_POINT) {
			paramAddPoint(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				globalData[pluginIndex].param[i].defaultValue[0], //default
				globalData[pluginIndex].param[i].defaultValue[1] //default
			);
		} else if (globalData[pluginIndex].param[i].paramType == PT_BOOL) {
			paramAddBool(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				(int)globalData[pluginIndex].param[i].defaultValue[0] //default
			);
		} else if (globalData[pluginIndex].param[i].paramType == PT_SELECT) {	
			string t = globalData[pluginIndex].param[i].text;
			t = strReplace(t, "|-|", "|(-|");
			vector<string> choices;
			strSplit(t, '|', choices);
			paramAddChoice(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				(int)globalData[pluginIndex].param[i].maxValue+1, //max
				(int)(min(globalData[pluginIndex].param[i].maxValue,globalData[pluginIndex].param[i].defaultValue[0])), //default
				choices // choices
			);
		} else if (globalData[pluginIndex].param[i].paramType == PT_ANGLE) {	
			paramAddAngle(
				paramSet, props,
				globalData[pluginIndex].param[i].paramName.c_str(), // param
				globalData[pluginIndex].param[i].defaultValue[0] //default
			);
		} else if (globalData[pluginIndex].param[i].paramType == PT_LAYER) {
			gEffectHost->clipDefine(effect, globalData[pluginIndex].param[i].paramName.c_str(), &props);
			if (i > 0) {
				gPropHost->propSetInt(props, kOfxImageClipPropOptional, 0, 1);
			}
			gPropHost->propSetString(props, kOfxImageEffectPropSupportedComponents, 0, kOfxImageComponentRGBA);
			l++;
			continue;
		} else if (globalData[pluginIndex].param[i].paramType == PT_TOPIC_START) {	
			gParamHost->paramDefine(paramSet, kOfxParamTypeGroup, globalData[pluginIndex].param[i].paramName.c_str(), &props);
			if (globalData[pluginIndex].param[i].flags>0) gPropHost->propSetInt(props, kOfxParamPropGroupOpen, 0, 0);
			gPropHost->propSetInt(props, kOfxParamPropAnimates, 0, 0);
			gPropHost->propSetInt(props, kOfxParamPropGroupOpen, 0, globalData[pluginIndex].param[i].flags>0?0:1);
			group = globalData[pluginIndex].param[i].paramName;
		} else if (globalData[pluginIndex].param[i].paramType == PT_TOPIC_END) {	
			group = "";
			continue;
		} else {
			continue;
		}

		if (globalData[pluginIndex].param[i].displayStatus == DS_DISABLED) {
			gPropHost->propSetInt(props, kOfxParamPropEnabled, 0, 0);
		} else if (globalData[pluginIndex].param[i].displayStatus == DS_HIDDEN) {
			gPropHost->propSetInt(props, kOfxParamPropSecret, 0, 1);
		}
		gPropHost->propSetString(props, kOfxParamPropScriptName, 0, globalData[pluginIndex].param[i].paramName.c_str());
		gPropHost->propSetString(props, kOfxPropLabel, 0, globalData[pluginIndex].param[i].displayName.c_str());

		if (group != "" && globalData[pluginIndex].param[i].paramType != PT_TOPIC_START) 
			gPropHost->propSetString(props, kOfxParamPropParent, 0, group.c_str());
	}
	if (globalData[pluginIndex].nofInputs == 0) {
		globalData[pluginIndex].nofInputs = l;
	}

	return kOfxStatOK;
}

////////////////////////////////////////////////////////////////////////////////
// the plugin's description routine
static OfxStatus describe(int pluginIndex, OfxImageEffectHandle effect)
{
	// record a few host features
	gPropHost->propGetInt(gHost->host, kOfxImageEffectPropSupportsMultipleClipDepths, 0, &gHostSupportsMultipleBitDepths);

	// get the property handle for the plugin
	OfxPropertySetHandle effectProps;
	gEffectHost->getPropertySet(effect, &effectProps);

	// We can render both fields in a fielded images in one hit if there is no animation
	// So set the flag that allows us to do this
	gPropHost->propSetInt(effectProps, kOfxImageEffectPluginPropFieldRenderTwiceAlways, 0, 0);

	// say we cannot support multiple pixel depths
	gPropHost->propSetInt(effectProps, kOfxImageEffectPropSupportsMultipleClipDepths, 0, 0);
	
	// set the bit depths the plugin can handle
	gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedPixelDepths, 0, kOfxBitDepthFloat);
	gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedPixelDepths, 1, kOfxBitDepthByte);

	// set some labels and the group it belongs to
	gPropHost->propSetString(effectProps, kOfxPropLabel, 0, globalData[pluginIndex].pluginInfo.name.c_str());
	gPropHost->propSetString(effectProps, kOfxImageEffectPluginPropGrouping, 0, globalData[pluginIndex].pluginInfo.category.c_str());
	gPropHost->propSetString(effectProps, kOfxPropPluginDescription, 0, globalData[pluginIndex].pluginInfo.description.c_str());

	// define the contexts we can be used in
	gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedContexts, 0, kOfxImageEffectContextFilter);
	gPropHost->propSetString(effectProps, kOfxImageEffectPropSupportedContexts, 1, kOfxImageEffectContextGeneral);

	gPropHost->propSetString(effectProps, kOfxImageEffectPluginRenderThreadSafety, 0, kOfxImageEffectRenderInstanceSafe);
	gPropHost->propSetInt(effectProps, kOfxImageEffectPropSupportsTiles, 0, 0);
	gPropHost->propSetInt(effectProps, kOfxImageEffectPluginPropHostFrameThreading, 0, 0);
	gPropHost->propSetInt(effectProps, kOfxImageEffectPropSupportsMultiResolution, 0, 0);
	gPropHost->propSetInt(effectProps, kOfxImageEffectPropTemporalClipAccess, 0, 1);

	char *path = NULL;
	gPropHost->propGetString(effectProps, kOfxPluginPropFilePath, 0, &path);

	if (path) {
		string p = string(path);
	#ifdef _WIN32
		int iPos = (int)p.find_last_of("/\\");
	#else
		int iPos = (int)p.find_last_of("/");
	#endif
		if (iPos >= 0) {
			globalData[pluginIndex].pluginPath = p.substr(0, iPos);
			globalData[pluginIndex].pluginFilename = p.substr(iPos + 1);
		} else {
			globalData[pluginIndex].pluginPath = p;
			globalData[pluginIndex].pluginFilename = p;
		}
	}

	return kOfxStatOK;
}


////////////////////////////////////////////////////////////////////////////////
// The main function
static OfxStatus pluginMain(int pluginIndex, const char *action, const void *handle, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
	try {
	// cast to appropriate type
	OfxImageEffectHandle effect = (OfxImageEffectHandle)handle;

	if (strcmp(action, kOfxActionDescribe) == 0) {
		return describe(pluginIndex, effect);
	}
	else if (strcmp(action, kOfxImageEffectActionDescribeInContext) == 0) {
		return describeInContext(pluginIndex, effect, inArgs);
	}
	else if (strcmp(action, kOfxActionLoad) == 0) {
		return onLoad(pluginIndex);
	}
	else if (strcmp(action, kOfxActionUnload) == 0) {
		return onUnload(pluginIndex);
	}
	else if (strcmp(action, kOfxActionCreateInstance) == 0) {
		return createInstance(pluginIndex, effect);
	} 
	else if (strcmp(action, kOfxActionDestroyInstance) == 0) {
		return destroyInstance(pluginIndex, effect);
	} 
	else if (strcmp(action, kOfxImageEffectActionIsIdentity) == 0) {
		return isIdentity(pluginIndex, effect, inArgs, outArgs);
	}		
	else if (strcmp(action, kOfxImageEffectActionRender) == 0) {
		return render(pluginIndex, effect, inArgs, outArgs);
	}		
	else if (strcmp(action, kOfxImageEffectActionGetRegionOfDefinition) == 0) {
		return getSpatialRoD(pluginIndex, effect, inArgs, outArgs);
	}
	else if (strcmp(action, kOfxActionSyncPrivateData) == 0) {
		return syncPrivateData(pluginIndex, effect);
	}	
	else if (strcmp(action, kOfxImageEffectActionGetRegionsOfInterest) == 0) {
		return getSpatialRoI(pluginIndex, effect, inArgs, outArgs);
	}	
	else if (strcmp(action, kOfxImageEffectActionGetClipPreferences) == 0) {
		return getClipPreferences(pluginIndex, effect, inArgs, outArgs);
	}	
	else if (strcmp(action, kOfxActionInstanceChanged) == 0) {
		return instanceChanged(pluginIndex, effect, inArgs, outArgs);
	}	
	else if (strcmp(action, kOfxImageEffectActionGetTimeDomain) == 0) {
		return getTemporalDomain(pluginIndex, effect, inArgs, outArgs);
	}	
	} catch (std::bad_alloc) {
		// catch memory
		//std::cout << "OFX Plugin Memory error." << std::endl;
		return kOfxStatErrMemory;
	} catch (const std::exception& e) {
		// standard exceptions
		//std::cout << "OFX Plugin error: " << e.what() << std::endl;
		return kOfxStatErrUnknown;
	} catch (int err) {
		// ho hum, gone wrong somehow
		return err;
	} catch (...) {
		// everything else
		//std::cout << "OFX Plugin error" << std::endl;
		return kOfxStatErrUnknown;
	}

	// other actions to take the default value
	return kOfxStatReplyDefault;
}

// function to set the host structure
static void setHostFunc(OfxHost *hostStruct)
{
	gHost = hostStruct;
	OfxStatus stat = ofxuFetchHostSuites();
	if (stat == kOfxStatOK) {
	}
}

////////////////////////////////////////////////////////////////////////////////
// the plugin struct 

// this little macro/template trickery was originally found in Alexandre Gauthier-Foichat's OFX G'MIC plugin
template<int nth>
static OfxStatus pluginMainNth(const char *action, const void *handle, OfxPropertySetHandle inArgs, OfxPropertySetHandle outArgs)
{
    return pluginMain(nth, action, handle, inArgs, outArgs);
}
#define NTHFUNC(nth) case nth: return pluginMainNth<nth>;
#define NTHFUNC10(nth) NTHFUNC(nth); NTHFUNC(nth+1); NTHFUNC(nth+2); NTHFUNC(nth+3); NTHFUNC(nth+4); NTHFUNC(nth+5); NTHFUNC(nth+6); NTHFUNC(nth+7); NTHFUNC(nth+8); NTHFUNC(nth+9)
#define NTHFUNC100(nth) NTHFUNC10(nth); NTHFUNC10(nth+10); NTHFUNC10(nth+20); NTHFUNC10(nth+30); NTHFUNC10(nth+40); NTHFUNC10(nth+50); NTHFUNC10(nth+60); NTHFUNC10(nth+70); NTHFUNC10(nth+80); NTHFUNC10(nth+90)
#define NTHFUNC1000(nth) NTHFUNC100(nth); NTHFUNC100(nth+100); NTHFUNC100(nth+200); NTHFUNC100(nth+300); NTHFUNC100(nth+400); NTHFUNC100(nth+500); NTHFUNC100(nth+600); NTHFUNC100(nth+700); NTHFUNC100(nth+800); NTHFUNC100(nth+900)
static OfxPluginEntryPoint* pluginMainNthFunc(int nth)
{
    switch (nth) {
        NTHFUNC1000(0);
    }
    return 0;
}
#undef NTHFUNC

void initPlugins()
{
	int n = getNofPlugins();
	gPlugins.resize(n);
	globalData.resize(n);
	for (int i = 0; i < n; i++) {
		getPluginInfo(i, globalData[i].pluginInfo);
		globalData[i].pluginIndex = i;
		gPlugins[i].pluginApi = kOfxImageEffectPluginApi;
		gPlugins[i].apiVersion = 1;
		gPlugins[i].pluginIdentifier = globalData[i].pluginInfo.identifier.c_str();
		gPlugins[i].pluginVersionMajor = globalData[i].pluginInfo.major_version;
		gPlugins[i].pluginVersionMinor = globalData[i].pluginInfo.minor_version;
		gPlugins[i].setHost = setHostFunc;
		gPlugins[i].mainEntry = pluginMainNthFunc(i);
	}
}

// the two mandated functions
EXPORT OfxPlugin* OfxGetPlugin(int nth)
{
	if ((int)gPlugins.size() == 0) {
		initPlugins();
	}
	if (nth < (int)gPlugins.size()) return &gPlugins[nth];
	return NULL;
}
 
EXPORT int OfxGetNumberOfPlugins(void)
{
	initPlugins();
	int n = (int)gPlugins.size();
	return n;
} 

#endif

