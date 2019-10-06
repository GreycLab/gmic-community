/*
 #
 #  File        : RFX_Parameter.h
 #
 #  Description : A self-contained header file with helper functions and structures
 #                for generic parameter handling in various plugin hosts
 #
 #  Copyright   : Tobias Fleischer / reduxFX Productions (http://www.reduxfx.com)
 #
 #  Licenses        : This file is 'dual-licensed', you have to choose one
 #                    of the two licenses below to apply.
 #
 #                    CeCILL-C
 #                    The CeCILL-C license is close to the GNU LGPL.
 #                    ( http://cecill.info/licences/Licence_CeCILL-C_V1-en.html )
 #
 #                or  CeCILL v2.0
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://cecill.info/licences/Licence_CeCILL_V2-en.html )
 #
 #  This software is governed either by the CeCILL or the CeCILL-C license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL or CeCILL-C licenses as circulated by CEA, CNRS and INRIA
 #  at the following URL: "http://cecill.info".
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


#pragma once

#ifndef _RFX_PARAMETER_H
#define _RFX_PARAMETER_H

// arbitrary bounds :)
#define MAX_NOF_LAYERS 32
#define MAX_NOF_PARAMS 256
#define MAX_NOF_TEXTS 32

#include <string>
using namespace std;

namespace reduxfx {

enum PixelFormat
{
	PF_RGBA = 0,
	PF_ARGB = 1,
	PF_BGRA = 2,
	PF_RGB = 3,
};

enum ParamType
{
	PT_NONE = -1,
	PT_INT = 0,
	PT_BOOL = 1,
	PT_SELECT = 2,
	PT_LAYER = 3,
	PT_FLOAT = 4,
	PT_COLOR = 5,
	PT_ANGLE = 6,
	PT_POINT = 7,
	PT_TOPIC_START = 8,
	PT_TOPIC_END = 9,
	PT_CUSTOM = 10,
	PT_BUTTON = 11,
	PT_VEC2 = 12,
	PT_VEC3 = 13,
	PT_TEXT = 14,
};

enum DisplayStatus
{
	DS_NORMAL = 0,
	DS_DISABLED = 1,
	DS_HIDDEN = 2,
};

class World
{
public:
	int width;
	int height;
	void* data;
	int bitDepth;
	int rowBytes;
	int origin_x;
	int origin_y;
	reduxfx::PixelFormat pixelFormat;
	World() {
		width = 0;
		height = 0;
		data = NULL;
		bitDepth = 8;
		rowBytes = 0;
		origin_x = 0;
		origin_y = 0;
	};
};

class PluginInfo
{
public:
	string name;
	string identifier;
	string category;
	string description;
	int major_version;
	int minor_version;
	PluginInfo() {
		major_version = 1;
		minor_version = 0;
	};
};

class Parameter
{
public:
	Parameter(string _paramName = "", string _displayName = "", int _paramType = PT_FLOAT, float _minValue = 0.f, float _maxValue = 1.f, float _defaultValue0 = 0.f, float _defaultValue1 = 0.f, float _defaultValue2 = 0.f, float _defaultValue3 = 0.f, string _text = "") {
		displayName = _displayName;
		paramName = _paramName;
		if (displayName == "") displayName = paramName;
		paramType = _paramType;
		defaultValue[0] = _defaultValue0;
		defaultValue[1] = _defaultValue1;
		defaultValue[2] = _defaultValue2;
		defaultValue[3] = _defaultValue3;
		minValue = _minValue;
		maxValue = _maxValue;
		text = _text;
		flags = 0;
		id = -1;
		displayStatus = DS_NORMAL;
	};
	int paramType;
	string paramName;
	string displayName;
	string text;
	float defaultValue[4];
	float minValue;
	float maxValue;
	DisplayStatus displayStatus;
	int id;
	int flags;
};

class SequenceData
{
public:
	bool isFlat;
	bool update;
	float floatValue[MAX_NOF_PARAMS][4];
	string textValue[MAX_NOF_PARAMS];
	double time;
	float downsample_x, downsample_y, pixelsize_x, pixelsize_y;
	reduxfx::World inWorld[MAX_NOF_LAYERS];
	reduxfx::World outWorld;
	int timeSpread;
	void* customSequenceDataP;
	void* contextP;
	bool inputConnected[MAX_NOF_LAYERS];
	SequenceData() {
		isFlat = false;
		update = false;
		for (int i = 0; i < MAX_NOF_PARAMS; i++)
			for (int j = 0; j < 4; j++) floatValue[i][j] = 0.f;
		for (int i = 0; i < MAX_NOF_LAYERS; i++) inputConnected[i] = false;
		time = 0;
		downsample_x = 1.f;
		downsample_y = 1.f;
		pixelsize_x = 1.f;
		pixelsize_y = 1.f;
		timeSpread = 1;
		customSequenceDataP = NULL;
		contextP = NULL;
	};
};

#define PAR_TYPE(idx) globalDataP->param[idx].paramType
#define PAR_VAL(idx) sequenceDataP->floatValue[idx][0]
#define PAR_TXT(idx) sequenceDataP->textValue[idx]
#define PAR_CH(idx, ch) sequenceDataP->floatValue[idx][ch]

class GlobalData
{
public:
	void* customGlobalDataP;
	reduxfx::Parameter param[MAX_NOF_PARAMS];
	int nofParams;
	int nofInputs;
	PluginInfo pluginInfo;
	string pluginPath;
	string pluginFilename;
	string buttonName;
	float scale;
	bool inplaceProcessing;
	int pluginIndex;
	bool headlessMode;

	GlobalData() {
		headlessMode = false;
		customGlobalDataP = NULL;
		// memset(&param[0], 0, sizeof(reduxfx::Parameter) * MAX_NOF_PARAMS);
		param[0] = reduxfx::Parameter("input", "Input", PT_LAYER);
		nofParams = 1;
		nofInputs = 0;
		buttonName = " ";
		scale = 1.f;
		inplaceProcessing = false;
		pluginIndex = 0;
#ifdef PLUGIN_NAME
		pluginInfo.name = PLUGIN_NAME;
#endif
#ifdef PLUGIN_CATEGORY
		pluginInfo.category = PLUGIN_CATEGORY;
#endif
#ifdef PLUGIN_DESCRIPTION
		pluginInfo.description = PLUGIN_DESCRIPTION;
#endif
#ifdef MINOR_VERSION
		pluginInfo.minor_version = MINOR_VERSION;
#endif
#ifdef MAJOR_VERSION
		pluginInfo.major_version = MAJOR_VERSION;
#endif
#ifdef PLUGIN_UNIQUEID
		pluginInfo.identifier = PLUGIN_UNIQUEID;
#endif
	}
};

};

#endif
