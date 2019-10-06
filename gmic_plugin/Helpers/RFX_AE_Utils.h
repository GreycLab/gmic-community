/*
 #
 #  File        : RFX_AE_Utils.h
 #
 #  Description : A self-contained header file with helper functions to make
 #                using the Adobe After Effects SDK a bit easier to use
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

#ifndef _RFX_AE_UTILS_H
#define _RFX_AE_UTILS_H

#include <math.h>
#include <string>
#include "RFX_Utils.h"
#include "RFX_Parameter.h"
#include "RFX_StringUtils.h"
using namespace std;
using namespace reduxfx;

#undef AE_64
#undef AE_32

#if defined(_M_AMD64) || defined(_AMD64_) || defined(_M_IA64) || defined(_IA64_) || defined(_WIN64) || defined(__x86_64__) || defined(__LP64__)
#define AE_64
#undef AE_32
#else
#define AE_32
#undef AE_64
#endif

#ifndef PF_DEEP_COLOR_AWARE
#define PF_DEEP_COLOR_AWARE 1
#endif

#include "AEConfig.h"
#include "entry.h"
#ifdef AE_32
#include "PF_Suite_Helper.h"
#else
#include "AEFX_SuiteHelper.h"
#endif
#include "PrSDKAESupport.h"


#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#endif

#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_EffectCBSuites.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#include "String_Utils.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"

struct ContextData
{
	PF_InData* in_data;
	PF_OutData* out_data;
	PF_ParamDef* param;
	PF_LayerDef* outputP;
	void* extraP;
};

struct WorldData
{
	PF_EffectWorld* srcWorld[MAX_NOF_LAYERS];
};

struct PreRenderData
{
	PF_ParamDef param[MAX_NOF_PARAMS];
	PF_CheckoutResult in_result[MAX_NOF_LAYERS];
};

struct AE_GlobalData
{
	GlobalData* globalDataP;
};

extern void* createCustomGlobalData();
extern void destroyCustomGlobalData(void* customGlobalDataP);
extern void* createCustomSequenceData();
extern void destroyCustomSequenceData(void* customSequenceDataP);
extern void* flattenCustomSequenceData(void* unflatCustomSequenceDataP, int& flatSize);
extern void* unflattenCustomSequenceData(void* flatCustomSequenceDataP, int flatSize);

extern int pluginParamChange(int index, SequenceData* sequenceDataP, GlobalData* globalDataP, ContextData* contextDataP);
extern int pluginSetup(GlobalData* globalDataP, ContextData* contextDataP);
extern int pluginSetdown(GlobalData* globalDataP, ContextData* contextDataP);
extern int pluginProcess(SequenceData* sequenceDataP, GlobalData* globalDataP, ContextData* contextDataP);

// workaround to get these CC2014 features to compile with the CS6 SDK
#define _PF_Cmd_GET_FLATTENED_SEQUENCE_DATA (PF_Cmd_RESERVED3+1)
#define	_PF_OutFlag2_AE13_5_THREADSAFE 4194304
#define _PF_OutFlag2_SUPPORTS_GET_FLATTENED_SEQUENCE_DATA 8388608

#define PF_ADD_FLOAT(NAME, VALID_MIN, VALID_MAX, SLIDER_MIN, SLIDER_MAX, DFLT, PREC, DISP, FLAGS, ID)	\
	do {																										\
		def.flags = (FLAGS); \
		PF_ADD_FLOAT_SLIDER(NAME, VALID_MIN, VALID_MAX, SLIDER_MIN, SLIDER_MAX, 0, DFLT, PREC, DISP, 0, ID);	\
	} while (0)

#ifdef AE_64
#define PF_ADD_POINT_3D_EX(NAME, X_DFLT, Y_DFLT, Z_DFLT, ID) \
	do	{\
		PF_Err	priv_err = PF_Err_NONE; \
		def.param_type = PF_Param_POINT_3D; \
		PF_STRCPY(def.name, (NAME) ); \
		def.u.point3d_d.x_value = def.u.point3d_d.x_dephault = X_DFLT; \
		def.u.point3d_d.y_value = def.u.point3d_d.y_dephault = Y_DFLT; \
		def.u.point3d_d.z_value = def.u.point3d_d.z_dephault = Y_DFLT; \
		def.uu.id = (ID); \
		if ((priv_err = PF_ADD_PARAM(in_data, -1, &def)) != PF_Err_NONE) return priv_err; \
	} while (0)
#endif

#ifdef AE_32
#ifndef FLOAT2FIX
#define	FLOAT2FIX(F)			((PF_Fixed)((F) * 65536 + (((F) < 0) ? -0.5 : 0.5)))
#endif

#endif

#ifdef AE_32
#define AE_REFCON A_long
#else
#define AE_REFCON void*
#endif

inline void setContextData(ContextData &cd, PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP, void* extraP)
{
	cd.in_data = in_data;
	cd.out_data = out_data;
	cd.param = (PF_ParamDef*)param;
	cd.outputP = outputP;
	cd.extraP = extraP;
}

const float MAX_CHAN8 = 255.f;
const float I_MAX_CHAN8 = 1.f / 255.f;
const float MAX_CHAN16 = 32768.f;
const float I_MAX_CHAN16 = 1.f / 32768.f;

static void runScript(PF_InData *in_data, string script, string& result)
{
	if (in_data->appl_id == 'PrMr') return;
	PF_Err err = PF_Err_NONE;
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	AEGP_MemHandle resultMemH = NULL;
	char* prompt = new char[16384];
	memset(prompt, 0, 16384);
	if (script.length() > 16380) script[16381] = '\0';
	strcat(prompt, script.c_str());
	A_char *resultAC = NULL;
	ERR(suites.UtilitySuite5()->AEGP_ExecuteScript(NULL, prompt, FALSE, &resultMemH, NULL));
	ERR(suites.MemorySuite1()->AEGP_LockMemHandle(resultMemH, reinterpret_cast<void**>(&resultAC)));
	result = resultAC;
	delete [] prompt;
	ERR(suites.MemorySuite1()->AEGP_FreeMemHandle(resultMemH));
}

static void alert(PF_InData *in_data, string msg)
{
	string script, result;
	strReplace(msg, "'", "\"");
	strReplace(msg, "\r", "\\r");
	strReplace(msg, "\n", "\\n");
	strReplace(msg, "\t", " ");
	script = "alert('" + msg + "');";
	runScript(in_data, script, result);
}

#define _cmd(c) if (cmd == c) return #c;
static string cmd2str(int cmd)
{
	_cmd(PF_Cmd_ABOUT)
	_cmd(PF_Cmd_GLOBAL_SETUP)
	_cmd(PF_Cmd_UNUSED_0)
	_cmd(PF_Cmd_GLOBAL_SETDOWN)
	_cmd(PF_Cmd_PARAMS_SETUP)
	_cmd(PF_Cmd_SEQUENCE_SETUP)
	_cmd(PF_Cmd_SEQUENCE_RESETUP)
	_cmd(PF_Cmd_SEQUENCE_FLATTEN)
	_cmd(PF_Cmd_SEQUENCE_SETDOWN)
	_cmd(PF_Cmd_DO_DIALOG)
	_cmd(PF_Cmd_FRAME_SETUP)
	_cmd(PF_Cmd_RENDER)
	_cmd(PF_Cmd_FRAME_SETDOWN)
	_cmd(PF_Cmd_USER_CHANGED_PARAM)
	_cmd(PF_Cmd_UPDATE_PARAMS_UI)
	_cmd(PF_Cmd_EVENT)
	_cmd(PF_Cmd_GET_EXTERNAL_DEPENDENCIES)
	_cmd(PF_Cmd_COMPLETELY_GENERAL)
	_cmd(PF_Cmd_QUERY_DYNAMIC_FLAGS)
	_cmd(PF_Cmd_AUDIO_RENDER)
	_cmd(PF_Cmd_AUDIO_SETUP)
	_cmd(PF_Cmd_AUDIO_SETDOWN)
	_cmd(PF_Cmd_ARBITRARY_CALLBACK)
	_cmd(PF_Cmd_SMART_PRE_RENDER)
	_cmd(PF_Cmd_SMART_RENDER)
	_cmd(PF_Cmd_RESERVED1)
	_cmd(PF_Cmd_RESERVED2)
	return "unknown";
}

inline PF_PixelFloat* getPixel(PF_EffectWorld* inputP, const A_long x, const A_long y)
{
	return (PF_PixelFloat*)((char*)inputP->data + (y * inputP->rowbytes) + x * sizeof(PF_PixelFloat));
};

inline void setPixel(PF_EffectWorld* inputP, const A_long x, const A_long y, const PF_PixelFloat* col)
{
	*((PF_PixelFloat*)((char*)inputP->data + (y * inputP->rowbytes) + x * sizeof(PF_PixelFloat))) = *col;
};

inline PF_PixelFloat* getPixelSafe(PF_EffectWorld* inputP, A_long x, A_long y)
{
	if (x < 0) x = 0; else if (x >= inputP->width) x = inputP->width;
	if (y < 0) y = 0; else if (y >= inputP->height) y = inputP->height;
	return (PF_PixelFloat*)((char*)inputP->data + (y * inputP->rowbytes) + x * sizeof(PF_PixelFloat));
};

inline void setPixelSafe(PF_EffectWorld* inputP, A_long x, A_long y, const PF_PixelFloat* col)
{
	if (x < 0) x = 0; else if (x >= inputP->width) x = inputP->width;
	if (y < 0) y = 0; else if (y >= inputP->height) y = inputP->height;
	*((PF_PixelFloat*)((char*)inputP->data + (y * inputP->rowbytes) + x * sizeof(PF_PixelFloat))) = *col;
};

typedef struct {
	PF_InData* in_data;
	PF_EffectWorld* inWorld;
	PF_EffectWorld* outWorld;
	PF_Iterate8Suite1* pIterateSuite;
	float scale;
} IterateData;

#ifdef PLANAR_BUFFER
const int stepWidth = 1;
#else
const int stepWidth = 4;
#endif

static PF_Err it_Convert_ARGB8_to_RGBA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = *in_pix++; out_pixA += stepWidth;
		*out_pixR = *in_pix++; out_pixR += stepWidth;
		*out_pixG = *in_pix++; out_pixG += stepWidth;
		*out_pixB = *in_pix++; out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_ARGB16_to_RGBA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_short* in_pix = (A_u_short*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = (A_u_char)(*in_pix++ * I_MAX_CHAN16 * MAX_CHAN8 * i_data->scale); out_pixA += stepWidth;
		*out_pixR = (A_u_char)(*in_pix++ * I_MAX_CHAN16 * MAX_CHAN8 * i_data->scale); out_pixR += stepWidth;
		*out_pixG = (A_u_char)(*in_pix++ * I_MAX_CHAN16 * MAX_CHAN8 * i_data->scale); out_pixG += stepWidth;
		*out_pixB = (A_u_char)(*in_pix++ * I_MAX_CHAN16 * MAX_CHAN8 * i_data->scale); out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_ARGB32_to_RGBA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	float* in_pix = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixA += stepWidth;
		*out_pixR = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixR += stepWidth;
		*out_pixG = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixG += stepWidth;
		*out_pixB = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_BGRA8_to_RGBA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixB = *in_pix++; out_pixB += stepWidth;
		*out_pixG = *in_pix++; out_pixG += stepWidth;
		*out_pixR = *in_pix++; out_pixR += stepWidth;
		*out_pixA = *in_pix++; out_pixA += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_BGRA32_to_RGBA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	float* in_pix = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixB = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixB += stepWidth;
		*out_pixG = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixG += stepWidth;
		*out_pixR = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixR += stepWidth;
		*out_pixA = (A_u_char)(saturate(*in_pix++ * i_data->scale) * MAX_CHAN8 + 0.5f); out_pixA += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_ARGB8_to_RGBA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixA += stepWidth;
		*out_pixR = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixR += stepWidth;
		*out_pixG = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixG += stepWidth;
		*out_pixB = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_ARGB16_to_RGBA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_short* in_pix = (A_u_short*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = (float)(*in_pix++ * I_MAX_CHAN16 * i_data->scale); out_pixA += stepWidth;
		*out_pixR = (float)(*in_pix++ * I_MAX_CHAN16 * i_data->scale); out_pixR += stepWidth;
		*out_pixG = (float)(*in_pix++ * I_MAX_CHAN16 * i_data->scale); out_pixG += stepWidth;
		*out_pixB = (float)(*in_pix++ * I_MAX_CHAN16 * i_data->scale); out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_ARGB32_to_RGBA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	float* in_pix = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = (*in_pix++) * i_data->scale; out_pixA += stepWidth;
		*out_pixR = (*in_pix++) * i_data->scale; out_pixR += stepWidth;
		*out_pixG = (*in_pix++) * i_data->scale; out_pixG += stepWidth;
		*out_pixB = (*in_pix++) * i_data->scale; out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_BGRA8_to_RGBA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixB = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixB += stepWidth;
		*out_pixG = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixG += stepWidth;
		*out_pixR = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixR += stepWidth;
		*out_pixA = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixA += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_BGRA32_to_RGBA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	float* in_pix = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixB = (*in_pix++) * i_data->scale; out_pixB += stepWidth;
		*out_pixG = (*in_pix++) * i_data->scale; out_pixG += stepWidth;
		*out_pixR = (*in_pix++) * i_data->scale; out_pixR += stepWidth;
		*out_pixA = (*in_pix++) * i_data->scale; out_pixA += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_RGBA8_to_ARGB8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = *in_pix++; out_pixA += stepWidth;
		*out_pixR = *in_pix++; out_pixR += stepWidth;
		*out_pixG = *in_pix++; out_pixG += stepWidth;
		*out_pixB = *in_pix++; out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_RGBA8_to_ARGB16(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_short* out_pixR = (A_u_short*)((char*)i_data->outWorld->data + sizeof(A_u_short) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_short* out_pixG = (A_u_short*)((char*)i_data->outWorld->data + sizeof(A_u_short) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_short* out_pixB = (A_u_short*)((char*)i_data->outWorld->data + sizeof(A_u_short) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_short* out_pixA = (A_u_short*)((char*)i_data->outWorld->data + sizeof(A_u_short) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_short* out_pixR = (A_u_short*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_short* out_pixG = out_pixR + 1;
	A_u_short* out_pixB = out_pixR + 2;
	A_u_short* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = (A_u_short)(*in_pix++ * I_MAX_CHAN8 * MAX_CHAN16 * i_data->scale); out_pixA += stepWidth;
		*out_pixR = (A_u_short)(*in_pix++ * I_MAX_CHAN8 * MAX_CHAN16 * i_data->scale); out_pixR += stepWidth;
		*out_pixG = (A_u_short)(*in_pix++ * I_MAX_CHAN8 * MAX_CHAN16 * i_data->scale); out_pixG += stepWidth;
		*out_pixB = (A_u_short)(*in_pix++ * I_MAX_CHAN8 * MAX_CHAN16 * i_data->scale); out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_RGBA8_to_ARGB32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixA = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixA += stepWidth;
		*out_pixR = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixR += stepWidth;
		*out_pixG = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixG += stepWidth;
		*out_pixB = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixB += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_RGBA8_to_BGRA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	A_u_char* out_pixG = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	A_u_char* out_pixB = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	A_u_char* out_pixA = (A_u_char*)((char*)i_data->outWorld->data + sizeof(A_u_char) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	A_u_char* out_pixR = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	A_u_char* out_pixG = out_pixR + 1;
	A_u_char* out_pixB = out_pixR + 2;
	A_u_char* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixB = *in_pix++; out_pixB += stepWidth;
		*out_pixG = *in_pix++; out_pixG += stepWidth;
		*out_pixR = *in_pix++; out_pixR += stepWidth;
		*out_pixA = *in_pix++; out_pixA += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_RGBA8_to_BGRA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

	A_u_char* in_pix = (A_u_char*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
#ifdef PLANAR_BUFFER
	float* out_pixR = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 0));
	float* out_pixG = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 1));
	float* out_pixB = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 2));
	float* out_pixA = (float*)((char*)i_data->outWorld->data + sizeof(float) * i_data->outWorld->width * (i + i_data->outWorld->height * 3));
#else
	float* out_pixR = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));
	float* out_pixG = out_pixR + 1;
	float* out_pixB = out_pixR + 2;
	float* out_pixA = out_pixR + 3;
#endif

	for (int x = 0; x < i_data->inWorld->width; x++) {
		*out_pixB = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixB += stepWidth;
		*out_pixG = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixG += stepWidth;
		*out_pixR = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixR += stepWidth;
		*out_pixA = ((float)(*in_pix++) * I_MAX_CHAN8 * i_data->scale); out_pixA += stepWidth;
	}
	return err;
}

static PF_Err it_Convert_RGBA32_to_ARGB8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	A_u_char r, g, b, a;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

#ifdef PLANAR_BUFFER
	float* in_pixR = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 0));
	float* in_pixG = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 1));
	float* in_pixB = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 2));
	float* in_pixA = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 3));
#else
	float* in_pixR = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
	float* in_pixG = in_pixR + 1;
	float* in_pixB = in_pixR + 2;
	float* in_pixA = in_pixR + 3;
#endif
	A_u_char* out_pix = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));

	for (int x = 0; x < i_data->inWorld->width; x++) {
		r = (A_u_char)(saturate(*in_pixR * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixR += stepWidth;
		g = (A_u_char)(saturate(*in_pixG * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixG += stepWidth;
		b = (A_u_char)(saturate(*in_pixB * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixB += stepWidth;
		a = (A_u_char)(saturate(*in_pixA * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixA += stepWidth;
		*out_pix = a; out_pix++; *out_pix = r; out_pix++; *out_pix = g; out_pix++; *out_pix = b; out_pix++;
	}
	return err;
}

static PF_Err it_Convert_RGBA32_to_ARGB16(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	A_u_short r, g, b, a;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

#ifdef PLANAR_BUFFER
	float* in_pixR = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 0));
	float* in_pixG = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 1));
	float* in_pixB = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 2));
	float* in_pixA = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 3));
#else
	float* in_pixR = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
	float* in_pixG = in_pixR + 1;
	float* in_pixB = in_pixR + 2;
	float* in_pixA = in_pixR + 3;
#endif
	A_u_short* out_pix = (A_u_short*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));

	for (int x = 0; x < i_data->inWorld->width; x++) {
		r = (A_u_short)(saturate(*in_pixR * i_data->scale) * MAX_CHAN16 + 0.5f); in_pixR += stepWidth;
		g = (A_u_short)(saturate(*in_pixG * i_data->scale) * MAX_CHAN16 + 0.5f); in_pixG += stepWidth;
		b = (A_u_short)(saturate(*in_pixB * i_data->scale) * MAX_CHAN16 + 0.5f); in_pixB += stepWidth;
		a = (A_u_short)(saturate(*in_pixA * i_data->scale) * MAX_CHAN16 + 0.5f); in_pixA += stepWidth;
		*out_pix = a; out_pix++; *out_pix = r; out_pix++; *out_pix = g; out_pix++; *out_pix = b; out_pix++;
	}
	return err;
}

static PF_Err it_Convert_RGBA32_to_ARGB32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	float r, g, b, a;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

#ifdef PLANAR_BUFFER
	float* in_pixR = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 0));
	float* in_pixG = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 1));
	float* in_pixB = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 2));
	float* in_pixA = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 3));
#else
	float* in_pixR = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
	float* in_pixG = in_pixR + 1;
	float* in_pixB = in_pixR + 2;
	float* in_pixA = in_pixR + 3;
#endif
	float* out_pix = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));

	for (int x = 0; x < i_data->inWorld->width; x++) {
		r = (*in_pixR) * i_data->scale; in_pixR += stepWidth;
		g = (*in_pixG) * i_data->scale; in_pixG += stepWidth;
		b = (*in_pixB) * i_data->scale; in_pixB += stepWidth;
		a = (*in_pixA) * i_data->scale; in_pixA += stepWidth;
		*out_pix = a; out_pix++; *out_pix = r; out_pix++; *out_pix = g; out_pix++; *out_pix = b; out_pix++;
	}
	return err;
}

static PF_Err it_Convert_RGBA32_to_BGRA8(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	A_u_char r, g, b, a;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

#ifdef PLANAR_BUFFER
	float* in_pixR = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 0));
	float* in_pixG = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 1));
	float* in_pixB = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 2));
	float* in_pixA = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 3));
#else
	float* in_pixR = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
	float* in_pixG = in_pixR + 1;
	float* in_pixB = in_pixR + 2;
	float* in_pixA = in_pixR + 3;
#endif
	A_u_char* out_pix = (A_u_char*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));

	for (int x = 0; x < i_data->inWorld->width; x++) {
		r = (A_u_char)(saturate(*in_pixR * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixR += stepWidth;
		g = (A_u_char)(saturate(*in_pixG * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixG += stepWidth;
		b = (A_u_char)(saturate(*in_pixB * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixB += stepWidth;
		a = (A_u_char)(saturate(*in_pixA * i_data->scale) * MAX_CHAN8 + 0.5f); in_pixA += stepWidth;
		*out_pix = b; out_pix++; *out_pix = g; out_pix++; *out_pix = r; out_pix++; *out_pix = a; out_pix++;
	}
	return err;
}

static PF_Err it_Convert_RGBA32_to_BGRA32(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL)
{
	PF_Err err = PF_Err_NONE;
	IterateData* i_data = (IterateData*)refconPV;
	float r, g, b, a;
	if (thread_indexL == 0) err = PF_ABORT(i_data->in_data);

#ifdef PLANAR_BUFFER
	float* in_pixR = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 0));
	float* in_pixG = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 1));
	float* in_pixB = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 2));
	float* in_pixA = (float*)((char*)i_data->inWorld->data + sizeof(float) * i_data->inWorld->width * (i + i_data->inWorld->height * 3));
#else
	float* in_pixR = (float*)((char*)i_data->inWorld->data + (i * i_data->inWorld->rowbytes));
	float* in_pixG = in_pixR + 1;
	float* in_pixB = in_pixR + 2;
	float* in_pixA = in_pixR + 3;
#endif
	float* out_pix = (float*)((char*)i_data->outWorld->data + (i * i_data->outWorld->rowbytes));

	for (int x = 0; x < i_data->inWorld->width; x++) {
		r = (*in_pixR) * i_data->scale; in_pixR += stepWidth;
		g = (*in_pixG) * i_data->scale; in_pixG += stepWidth;
		b = (*in_pixB) * i_data->scale; in_pixB += stepWidth;
		a = (*in_pixA) * i_data->scale; in_pixA += stepWidth;
		*out_pix = b; out_pix++; *out_pix = g; out_pix++; *out_pix = r; out_pix++; *out_pix = a; out_pix++;
	}
	return err;
}

// two functions to get Premiere to run functions multi-threaded, as it does NOT support PF_Iterate8Suite1->iterate_generic!
typedef PF_Err (*GenericIterator)(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL);

typedef struct {
	PF_InData* in_data;
	GenericIterator fn_func;
	AE_REFCON refconPV;
	A_long height;
} FakeData;

static PF_Err MyFakeIterator(AE_REFCON refcon, A_long x, A_long y, PF_Pixel* in, PF_Pixel* out)
{
	PF_Err err = PF_Err_NONE;
	FakeData* i_data = (FakeData*)refcon;
	err = i_data->fn_func((void*)(i_data->refconPV), 1, y, i_data->height);
	return err;
}

typedef PF_Err (*GenericIterateFunc)(A_long iterationsL, void* refconPV, GenericIterator fn_func);

static PF_Err MyGenericIterateFunc(A_long iterationsL, void* refconPV, GenericIterator fn_func)
{
	PF_Err err = PF_Err_NONE;
	PF_InData** in_dataH = (PF_InData**)refconPV; // always put PF_InData first
	PF_InData* in_data = *in_dataH;
	if (((IterateData*)(refconPV))->pIterateSuite)
	{
		PF_EffectWorld fake_world;
		PF_NEW_WORLD(1, iterationsL, PF_NewWorldFlag_NONE, &fake_world);
		FakeData i_data = { in_data, fn_func, (AE_REFCON)(refconPV), iterationsL };
		err = ((IterateData*)(refconPV))->pIterateSuite->iterate(in_data, 0, iterationsL, &fake_world, NULL, (AE_REFCON)(&i_data), MyFakeIterator, &fake_world);
		PF_DISPOSE_WORLD(&fake_world);
	}
	else
	{
		for (int i = 0; i < iterationsL && !err; i++) err = fn_func((void*)(refconPV), 0, i, iterationsL);
	}
	return err;
}

#ifdef AE_32
#define PF_OutFlag2_AUTOMATIC_WIDE_TIME_INPUT 0
#define PrPixelFormat_BGRA_4444_32f_Linear PrPixelFormat_BGRA_4444_32f+1
#endif


static PF_Err sequenceSetup(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);

	if (in_data->sequence_data) suites.HandleSuite1()->host_dispose_handle(in_data->sequence_data);
	if (out_data->sequence_data) suites.HandleSuite1()->host_dispose_handle(out_data->sequence_data);

	PF_Handle sequenceDataH = suites.HandleSuite1()->host_new_handle(sizeof(SequenceData));
	if (!sequenceDataH) return PF_Err_OUT_OF_MEMORY;

	SequenceData* sequenceDataP = static_cast<SequenceData*>(suites.HandleSuite1()->host_lock_handle(sequenceDataH));
	if (sequenceDataP) {
		GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
		CLR_STRUCT(*sequenceDataP);
		sequenceDataP->update = true;
		sequenceDataP->customSequenceDataP = createCustomSequenceData();
		sequenceDataP->isFlat = false;
		sequenceDataP->timeSpread = 0;
//		sequenceDataP->convertInputFloatToInt = false;
//		sequenceDataP->convertInputIntToFloat = true;

		for (int i = 0; i < globalDataP->nofParams; i++) {
			sequenceDataP->textValue[i] = globalDataP->param[i].text;
			for (int j = 0; j < 4; j++) {
				sequenceDataP->floatValue[i][j] = globalDataP->param[i].defaultValue[j];
			}
		}

		out_data->sequence_data = sequenceDataH;
		suites.HandleSuite1()->host_unlock_handle(sequenceDataH);
		PF_UNLOCK_HANDLE(in_data->global_data);
	}
	if (!out_data->sequence_data) return PF_Err_INTERNAL_STRUCT_DAMAGED;
	return PF_Err_NONE;
}

static PF_Err sequenceSetdown(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	if (in_data->sequence_data) {
		SequenceData* sequenceDataP = reinterpret_cast<SequenceData*>(DH(in_data->sequence_data));
		destroyCustomSequenceData(sequenceDataP->customSequenceDataP);
		suites.HandleSuite1()->host_dispose_handle(in_data->sequence_data);
	}
	in_data->sequence_data = NULL;
	out_data->sequence_data = NULL;
	return PF_Err_NONE;
}

static PF_Err sequenceFlatten(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP, bool bDeleteUnflatData = true)
{
	PF_Err err = PF_Err_NONE;
	AEGP_SuiteHandler suites(in_data->pica_basicP);

	if (in_data->sequence_data) {
		SequenceData* unflatSequenceDataP = reinterpret_cast<SequenceData*>(DH(in_data->sequence_data));
		if (unflatSequenceDataP && !unflatSequenceDataP->isFlat) {

			SequenceData* flatSequenceDataP = NULL;
			int flatSize = sizeof(SequenceData);

			GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
			int textSize = sizeof(int);
			for (int i = 0; i < globalDataP->nofParams; i++) {
				textSize += sizeof(int); // length
				textSize += (int)unflatSequenceDataP->textValue[i].size();
			}
			flatSize += textSize;

			int customSize = 0;
			char* customSequenceDataP = (char*)flattenCustomSequenceData(unflatSequenceDataP->customSequenceDataP, customSize);
			flatSize += customSize + sizeof(int);

			PF_Handle flatSequenceDataH = suites.HandleSuite1()->host_new_handle(flatSize);
			if (flatSequenceDataH) {
				flatSequenceDataP = static_cast<SequenceData*>(suites.HandleSuite1()->host_lock_handle(flatSequenceDataH));
				if (flatSequenceDataP) {
					CLR_STRUCT(*flatSequenceDataP);

					unsigned char* p = (unsigned char*)((size_t)flatSequenceDataP + sizeof(SequenceData));
					*((int*)p) = customSize; p += sizeof(int);
					memcpy(p, customSequenceDataP, customSize);
					p += customSize;

					*((int*)p) = textSize; p += sizeof(int);
					for (int i = 0; i < globalDataP->nofParams; i++) {
						int l = (int)unflatSequenceDataP->textValue[i].size();
						*((int*)p) = l;
						p += sizeof(int);
						for (int j = 0; j < l; j++) {
							*p++ = unflatSequenceDataP->textValue[i][j];
						}
					}

					flatSequenceDataP->isFlat = true;
					out_data->sequence_data = flatSequenceDataH;
					suites.HandleSuite1()->host_unlock_handle(flatSequenceDataH);
				}
			} else {
				delete (char*)customSequenceDataP;
				err = PF_Err_INTERNAL_STRUCT_DAMAGED;
			}
			PF_UNLOCK_HANDLE(in_data->global_data);

			// delete the unflat data
			if (bDeleteUnflatData) {
				destroyCustomSequenceData(unflatSequenceDataP->customSequenceDataP);
				suites.HandleSuite1()->host_dispose_handle(in_data->sequence_data);
				in_data->sequence_data = NULL;
			}
		}
	} else {
		err = PF_Err_INTERNAL_STRUCT_DAMAGED;
	}
	return err;

}

static PF_Err sequenceResetup(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	PF_Err err = PF_Err_NONE;
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	// We got here because we're either opening a project w/saved (flat) sequence data,
	// or we've just been asked to flatten our sequence data (for a save) and now
	// we're blowing it back up.

	if (in_data->sequence_data) {
		SequenceData* flatSequenceDataP = reinterpret_cast<SequenceData*>(DH(in_data->sequence_data));
		if (flatSequenceDataP && flatSequenceDataP->isFlat) {
			flatSequenceDataP->update = true;
			PF_Handle unflatSequenceDataH = suites.HandleSuite1()->host_new_handle(sizeof(SequenceData));
			if (unflatSequenceDataH) {
				SequenceData* unflatSequenceDataP = static_cast<SequenceData*>(suites.HandleSuite1()->host_lock_handle(unflatSequenceDataH));
				GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
				if (unflatSequenceDataP) {
					CLR_STRUCT(*unflatSequenceDataP);

					unsigned char* p = (unsigned char*)((size_t)flatSequenceDataP + sizeof(SequenceData));
					int customSize = *((int*)p); p += sizeof(int);
					unflatSequenceDataP->customSequenceDataP = unflattenCustomSequenceData(p, customSize);
					p += customSize;

					int textSize = *((int*)p); p += sizeof(int);
					for (int i = 0; i < globalDataP->nofParams; i++) {
						int l = *((int*)p);
						p += sizeof(int);
						unflatSequenceDataP->textValue[i] = "";
						for (int j = 0; j < l; j++) {
							unflatSequenceDataP->textValue[i] += *p++;
						}
						if ((size_t)p >= (size_t)flatSequenceDataP + sizeof(SequenceData) + sizeof(int) + customSize + textSize)
							break;
					}

					unflatSequenceDataP->timeSpread = 0;
//					unflatSequenceDataP->convertInputFloatToInt = false;
//					unflatSequenceDataP->convertInputIntToFloat = true;
					unflatSequenceDataP->update = true;
					unflatSequenceDataP->isFlat = false;

					// if it all went well, set the sequence data to our new, inflated seq data.
					out_data->sequence_data = unflatSequenceDataH;
					suites.HandleSuite1()->host_dispose_handle(in_data->sequence_data);
					in_data->sequence_data = NULL;
				} else {
					err = PF_Err_INTERNAL_STRUCT_DAMAGED;
				}
				PF_UNLOCK_HANDLE(in_data->global_data);
				suites.HandleSuite1()->host_unlock_handle(unflatSequenceDataH);
			}
		}
	}
	return err;
}

#ifndef BUG_VERSION
#define BUG_VERSION 0
#endif

static PF_Err globalSetup(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	ContextData contextData;
	setContextData(contextData, in_data, out_data, param, outputP, NULL);
	PF_Err err = PF_Err_NONE;

	out_data->my_version = PF_VERSION(MAJOR_VERSION, MINOR_VERSION, BUG_VERSION, 0, BUILD_VERSION);
	out_data->out_flags = FX_OUT_FLAGS;
	out_data->out_flags2 = FX_OUT_FLAGS2;

	PF_Handle AEglobalDataH = NULL;
	AE_GlobalData* AEglobalDataP = NULL;
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	AEglobalDataH = suites.HandleSuite1()->host_new_handle(sizeof(AE_GlobalData));

	if (AEglobalDataH) {
		AEglobalDataP = static_cast<AE_GlobalData*>(suites.HandleSuite1()->host_lock_handle(AEglobalDataH));
		if (AEglobalDataP) {
			if (!err) out_data->global_data = AEglobalDataH;
			AEglobalDataP->globalDataP = new GlobalData();
			AEglobalDataP->globalDataP->customGlobalDataP = createCustomGlobalData();
		} else {
			return PF_Err_INTERNAL_STRUCT_DAMAGED;
		}
	} else {
		return PF_Err_INTERNAL_STRUCT_DAMAGED;
	}

	if (!err) {
		GlobalData* globalDataP = AEglobalDataP->globalDataP;

		if (in_data->appl_id != 'PrMr') {
			// This is only needed for the AEGP suites, which Premiere Pro doesn't support
			AEGP_PluginID id;
			ERR(suites.UtilitySuite3()->AEGP_RegisterWithAEGP(NULL, PLUGIN_NAME, &id));
//			globalDataP->id = id;
		}

		A_char pluginFolderPath[AEFX_MAX_PATH];
		PF_GET_PLATFORM_DATA(PF_PlatData_EXE_FILE_PATH_DEPRECATED, &pluginFolderPath);
		globalDataP->pluginPath = string(pluginFolderPath);
		globalDataP->pluginFilename = "";
		int pos = (int)globalDataP->pluginPath.find_last_of("\\/");
		if (pos >= 0) {
			globalDataP->pluginFilename = globalDataP->pluginPath.substr(pos + 1);
			globalDataP->pluginPath = globalDataP->pluginPath.substr(0, pos + 1);
		}

		PF_Boolean bIsRenderEngine = false;
#ifdef AE_64
		//AE CS5+ (64bit)
		suites.AppSuite4()->PF_IsRenderEngine(&bIsRenderEngine);
#else
		//AE CS4 (32bit)
		suites.AppSuite3()->PF_IsRenderEngine(&bIsRenderEngine);
#endif
		globalDataP->headlessMode = bIsRenderEngine>0;
/*
		stringstream ss;
		string host = "Unknown (" + intToString((long)in_data->appl_id) + ")";
		if (in_data->appl_id == 'PrMr') host = "Premiere Pro";
		else if (in_data->appl_id == 'FXTC') host = "After Effects";
		ss << host << " " << in_data->version.major << "." << in_data->version.minor;
		globalDataP->host = ss.str();
*/
		pluginSetup(globalDataP, &contextData);
//		if (error != "") PF_SPRINTF(out_data->return_msg, error.c_str(), string(PLUGIN_NAME).c_str());


		if (in_data->appl_id != 'PrMr' && globalDataP->buttonName != "") {
			PF_EffectUISuite1 *effect_ui_suiteP = NULL;
			AEFX_AcquireSuite(in_data, out_data, kPFEffectUISuite, kPFEffectUISuiteVersion1, NULL, (void**)&effect_ui_suiteP);
			ERR(effect_ui_suiteP->PF_SetOptionsButtonName(in_data->effect_ref, globalDataP->buttonName.c_str()));
			AEFX_ReleaseSuite(in_data, out_data, kPFEffectUISuite, kPFEffectUISuiteVersion1, NULL);
		}

		if (in_data->appl_id == 'PrMr') {
				PF_PixelFormatSuite1 *pfS = NULL;
				in_data->pica_basicP->AcquireSuite(kPFPixelFormatSuite, kPFPixelFormatSuiteVersion1, (const void **)&pfS);
				if (pfS) {

					pfS->AddSupportedPixelFormat(in_data->effect_ref, PrPixelFormat_BGRA_4444_32f);
					pfS->AddSupportedPixelFormat(in_data->effect_ref, PrPixelFormat_BGRA_4444_32f_Linear);
					pfS->AddSupportedPixelFormat(in_data->effect_ref, PrPixelFormat_BGRA_4444_8u);
					in_data->pica_basicP->ReleaseSuite(kPFPixelFormatSuite, kPFPixelFormatSuiteVersion1);
				}
		}
	}
	return err;
}

static PF_Err globalSetdown(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	if (in_data->global_data) {
		ContextData contextData;
		setContextData(contextData, in_data, out_data, param, outputP, NULL);
		AE_GlobalData* AEglobalDataP = (AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data);
		pluginSetdown(AEglobalDataP->globalDataP, &contextData);
		destroyCustomGlobalData(AEglobalDataP->globalDataP->customGlobalDataP);
		delete AEglobalDataP->globalDataP;
		PF_UNLOCK_HANDLE(in_data->global_data);
		suites.HandleSuite1()->host_dispose_handle(in_data->global_data);
	}
	return PF_Err_NONE;
}

static string showScriptDialog(PF_InData* in_data, const string title, const string text, bool edit = false, bool multiline = true)
{
	string t = text;
	strReplace(t, "\"", "\\\"");
	strReplace(t, "\r", "");
	strReplace(t, "\n", "\\r");
	strReplace(t, "\\n", "\\r");
	strToAscii(t);
	string opt = "{";
	if (multiline) opt += "wantReturn:true,multiline:true";
	opt += "}";
	string script = "function d(){var w=new Window('dialog','" + title + "'),g=w.add('group'),s=g.add('" + (edit?"edittext":"statictext") + "',undefined,\"" + t + "\"," + opt + "),g2=g.add('group'),b=g2.add('button',undefined,'OK');";
	if (edit) script += "b2=g2.add('button',undefined,'Cancel');b2.onClick=function(){s.text=\"\";w.close();};s.size=[600,400];";
	script += "g.orientation='column';g2.orientation='row';b.onClick=function(){w.close();};";
	script += "w.layout.layout();s.active=true;w.show();return s.text;};d();";
	string result;
	runScript(in_data, script, result);
	return result;
}

static PF_Err showAboutDialog(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	PF_Err err = PF_Err_NONE;
	GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
	string txt = globalDataP->pluginInfo.description;

//	strToAscii(txt);
	strReplace(txt, "  ", "\\r");
	txt = strRemoveXmlTags(txt, true);
	txt = globalDataP->pluginInfo.name + "\\nV" + intToString(MAJOR_VERSION) + "." + intToString(MINOR_VERSION) + "\\n\\n" + txt;
	if (in_data->appl_id != 'PrMr') { // if host is not Premiere Pro, we can do scripts
		showScriptDialog(in_data, "About", txt, false);
	} else {
		PF_SPRINTF(out_data->return_msg, "%s V%d.%d", globalDataP->pluginInfo.name.c_str(), MAJOR_VERSION, MINOR_VERSION);
	}
	PF_UNLOCK_HANDLE(in_data->global_data);
	return err;
}

static PF_Err paramsSetup(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	PF_Err err = PF_Err_NONE;
	GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
	PF_ParamDef def;
	int l = 1;

	for (int i = 1; i < globalDataP->nofParams; i++) {
		float dMin = globalDataP->param[i].minValue;
		float dMax = globalDataP->param[i].maxValue;

		CLR_STRUCT(def);
		if (globalDataP->param[i].displayStatus == DS_DISABLED) {
			def.ui_flags |= PF_PUI_DISABLED;
		} else if (globalDataP->param[i].displayStatus == DS_HIDDEN) {
			def.ui_flags |= PF_PUI_INVISIBLE;
		}

		if (PAR_TYPE(i) == PT_FLOAT) {
			PF_ADD_FLOAT(
				globalDataP->param[i].displayName.c_str(), // name
				dMin, //valid min
				dMax, //valid max
				dMin, //slider min
				dMax, //slider max
				globalDataP->param[i].defaultValue[0], //default
				2, //precision
				PF_ValueDisplayFlag_NONE, //display flags
				0, //flags
				i // id
				);
		} else if (PAR_TYPE(i) == PT_COLOR) {
			PF_ADD_COLOR(
				globalDataP->param[i].displayName.c_str(),
				(A_u_char)(globalDataP->param[i].defaultValue[0] * 255),
				(A_u_char)(globalDataP->param[i].defaultValue[1] * 255),
				(A_u_char)(globalDataP->param[i].defaultValue[2] * 255),
				i // id
				);
		} else if (PAR_TYPE(i) == PT_INT) {
			PF_ADD_FLOAT(
				globalDataP->param[i].displayName.c_str(), // name
				dMin, //valid min
				dMax, //valid max
				dMin, //slider min
				dMax, //slider max
				globalDataP->param[i].defaultValue[0], //default
				0, //precision
				globalDataP->param[i].flags>0?PF_ValueDisplayFlag_PERCENT:PF_ValueDisplayFlag_NONE, //display flags
				0, //flags
				i //id
				);
		} else if (PAR_TYPE(i) == PT_POINT || PAR_TYPE(i) == PT_VEC2) {
			A_long a1 = (A_long)(globalDataP->param[i].defaultValue[0]*100);
			A_long a2 = (A_long)(globalDataP->param[i].defaultValue[1]*100);
			if (a1 > 10000) a1 = 10000;
			if (a2 > 10000) a2 = 10000;
			PF_ADD_POINT(
				globalDataP->param[i].displayName.c_str(), // name
				a1, //default
				a2, //default
				0,
				i // id
			);
		} else if (PAR_TYPE(i) == PT_BOOL) {
			def.flags = PF_ParamFlag_SUPERVISE | PF_ParamFlag_CANNOT_INTERP;
			PF_ADD_CHECKBOX(
				globalDataP->param[i].displayName.c_str(), // name
				"", // text
				(PF_Boolean)globalDataP->param[i].defaultValue[0], //default
				0,
				i // id
			);
		} else if (PAR_TYPE(i) == PT_SELECT) {
			string t = globalDataP->param[i].text;
			t = strReplace(t, "|-|", "|(-|");
			def.flags = PF_ParamFlag_SUPERVISE | PF_ParamFlag_CANNOT_INTERP;
			PF_ADD_POPUP(
				globalDataP->param[i].displayName.c_str(), // name
				(A_short)globalDataP->param[i].maxValue + 1, //max
				1+(A_short)(min(globalDataP->param[i].maxValue, globalDataP->param[i].defaultValue[0])), //default
				t.c_str(), // text
				i // id
			);
		} else if (PAR_TYPE(i) == PT_ANGLE) {
			PF_ADD_ANGLE(
				globalDataP->param[i].displayName.c_str(), // name
				(A_long)(globalDataP->param[i].defaultValue[0]), //default
				i // id
			);
		} else if (PAR_TYPE(i) == PT_TEXT || PAR_TYPE(i) == PT_BUTTON) {
			bool bOk = true;
			if (in_data->appl_id == 'PrMr') bOk = false;
#ifdef AE_32
			bOk = false;
#endif
			if (bOk) {
#ifdef AE_64
				PF_ADD_BUTTON(
					globalDataP->param[i].displayName.c_str(), //name
					"Edit", // globalDataP->param[i].text.c_str(), // text,
					def.ui_flags, // display flags
					PF_ParamFlag_SUPERVISE | PF_ParamFlag_CANNOT_TIME_VARY | PF_ParamFlag_CANNOT_INTERP, // flags
					i // id
					);
#endif
			} else {
				def.ui_flags |= PF_PUI_INVISIBLE;
				PF_ADD_COLOR(
					globalDataP->param[i].displayName.c_str(),
					(A_u_char)(globalDataP->param[i].defaultValue[0] * 255),
					(A_u_char)(globalDataP->param[i].defaultValue[1] * 255),
					(A_u_char)(globalDataP->param[i].defaultValue[2] * 255),
					i // id
					);
			}
		} else if (PAR_TYPE(i) == PT_LAYER) {
			def.flags = PF_ParamFlag_SUPERVISE | PF_ParamFlag_CANNOT_INTERP;
			l++;
			PF_ADD_LAYER(
				globalDataP->param[i].displayName.c_str(), // name
				PF_LayerDefault_MYSELF, //default
				i // id
			);
		} else if (PAR_TYPE(i) == PT_TOPIC_START) {
			def.flags |= PF_ParamFlag_CANNOT_TIME_VARY;
			PF_ADD_TOPIC(
				globalDataP->param[i].displayName.c_str(), // name
				i // id
			);
		} else if (PAR_TYPE(i) == PT_TOPIC_END) {
			def.flags |= PF_ParamFlag_CANNOT_TIME_VARY;
			PF_END_TOPIC(
				i // id
			);
		} else {
			def.ui_flags |= PF_PUI_INVISIBLE;
			PF_ADD_FLOAT(
				globalDataP->param[i].displayName.c_str(), // name
				dMin, //valid min
				dMax, //valid max
				dMin, //slider min
				dMax, //slider max
				globalDataP->param[i].defaultValue[0], //default
				2, //precision
				PF_ValueDisplayFlag_NONE, //display flags
				0, //flags
				i // id
				);
		}
	}

	if (globalDataP->nofInputs == 0) {
		globalDataP->nofInputs = l;
	}
	out_data->num_params = globalDataP->nofParams;
	PF_UNLOCK_HANDLE(in_data->global_data);
	return err;
}

static PF_Err doRender(PF_InData* in_data, PF_OutData* out_data, SequenceData* sequenceDataP, GlobalData* globalDataP, WorldData* worldDataP, PF_LayerDef* outputP)
{
	PF_Err err = PF_Err_NONE;

	AEGP_SuiteHandler suites(in_data->pica_basicP);

	PF_PixelFormatSuite1 *pfS = NULL;
	PF_WorldSuite2 *wsP = NULL;
	IterateData i_data = {};
	i_data.scale = globalDataP->scale;
	err = in_data->pica_basicP->AcquireSuite(kPFPixelFormatSuite, kPFPixelFormatSuiteVersion1, (const void **)&pfS);
	err = in_data->pica_basicP->AcquireSuite(kPFWorldSuite, kPFWorldSuiteVersion2, (const void **)&wsP);
	bool isPremiere = in_data->appl_id == 'PrMr';
	if ((!pfS && isPremiere) || !wsP) {
		return err;
	}

	try {

	i_data.in_data = in_data;
	GenericIterateFunc iterate_generic = suites.Iterate8Suite1()->iterate_generic;
	if (iterate_generic == NULL) {
		iterate_generic = MyGenericIterateFunc;
		in_data->pica_basicP->AcquireSuite(kPFIterate8Suite, kPFIterate8SuiteVersion1, (const void **)&(i_data.pIterateSuite));
	}

	sequenceDataP->pixelsize_x = (float)in_data->pixel_aspect_ratio.num;
	sequenceDataP->pixelsize_y = (float)in_data->pixel_aspect_ratio.den;

	sequenceDataP->downsample_x = (float)in_data->downsample_x.num / (float)in_data->downsample_x.den;
	sequenceDataP->downsample_y = (float)in_data->downsample_y.num / (float)in_data->downsample_y.den;
	sequenceDataP->time = in_data->current_time;

	PF_PixelFormat worldFormat;

	PF_Handle worldH[MAX_NOF_LAYERS] = { 0 };
	PF_EffectWorld dstWorld[MAX_NOF_LAYERS] = { 0 };

	// create input worlds
	for (int i = 0; i < globalDataP->nofInputs; i++) {
		dstWorld[i].width = worldDataP->srcWorld[i]->width;
		dstWorld[i].height = worldDataP->srcWorld[i]->height;
		dstWorld[i].origin_x = worldDataP->srcWorld[i]->origin_x;
		dstWorld[i].origin_y = worldDataP->srcWorld[i]->origin_y;

		sequenceDataP->inWorld[i].width = dstWorld[i].width;
		sequenceDataP->inWorld[i].height = dstWorld[i].height;
		sequenceDataP->inWorld[i].origin_x = dstWorld[i].origin_x;
		sequenceDataP->inWorld[i].origin_y = dstWorld[i].origin_y;

		worldH[i] = NULL;
		wsP->PF_GetPixelFormat(worldDataP->srcWorld[i], &worldFormat);
		if (pfS && isPremiere) pfS->GetPixelFormat(worldDataP->srcWorld[i], (PrPixelFormat*)&worldFormat);

		sequenceDataP->inWorld[i].bitDepth = 32;

#ifndef CONVERT_INT_TO_FLOAT
		if (worldFormat == PF_PixelFormat_ARGB32 || worldFormat == PrPixelFormat_BGRA_4444_8u) {
			sequenceDataP->inWorld[i].bitDepth = 8;
		}
#endif

#ifdef CONVERT_FLOAT_TO_INT
		if (worldFormat == PF_PixelFormat_ARGB64 || worldFormat == PF_PixelFormat_ARGB128 ||
			worldFormat == PrPixelFormat_BGRA_4444_32f_Linear || worldFormat == PrPixelFormat_BGRA_4444_32f) {
			sequenceDataP->inWorld[i].bitDepth = 8;
		}
#endif
		int sz = 4 * ((sequenceDataP->inWorld[i].bitDepth == 8)?sizeof(char):sizeof(float));

		dstWorld[i].rowbytes = dstWorld[i].width * sz;
		sz = dstWorld[i].height * dstWorld[i].rowbytes;
		worldH[i] = PF_NEW_HANDLE(sz);
		dstWorld[i].data = (PF_PixelPtr)PF_LOCK_HANDLE(worldH[i]);
		sequenceDataP->inWorld[i].pixelFormat = PF_RGBA;
		sequenceDataP->inWorld[i].data = dstWorld[i].data;
		sequenceDataP->inWorld[i].rowBytes = dstWorld[i].rowbytes;

		i_data.inWorld = worldDataP->srcWorld[i];
		i_data.outWorld = &(dstWorld[i]);
		if (worldFormat == PF_PixelFormat_ARGB32)
			err = iterate_generic(dstWorld[i].height, &i_data, sequenceDataP->inWorld[i].bitDepth==8?it_Convert_ARGB8_to_RGBA8:it_Convert_ARGB8_to_RGBA32);
		else if (worldFormat == PF_PixelFormat_ARGB64)
			err = iterate_generic(dstWorld[i].height, &i_data, sequenceDataP->inWorld[i].bitDepth==8?it_Convert_ARGB16_to_RGBA8:it_Convert_ARGB16_to_RGBA32);
		else if (worldFormat == PF_PixelFormat_ARGB128)
			err = iterate_generic(dstWorld[i].height, &i_data, sequenceDataP->inWorld[i].bitDepth==8?it_Convert_ARGB32_to_RGBA8:it_Convert_ARGB32_to_RGBA32);
		else if (worldFormat == PrPixelFormat_BGRA_4444_8u)
			err = iterate_generic(dstWorld[i].height, &i_data, sequenceDataP->inWorld[i].bitDepth==8?it_Convert_BGRA8_to_RGBA8:it_Convert_BGRA8_to_RGBA32);
		else if (worldFormat == PrPixelFormat_BGRA_4444_32f_Linear || worldFormat == PrPixelFormat_BGRA_4444_32f)
			err = iterate_generic(dstWorld[i].height, &i_data, sequenceDataP->inWorld[i].bitDepth==8?it_Convert_BGRA32_to_RGBA8:it_Convert_BGRA32_to_RGBA32);
	}

	wsP->PF_GetPixelFormat(outputP, &worldFormat);
	if (pfS && isPremiere) pfS->GetPixelFormat(outputP, (PrPixelFormat *)&worldFormat);
	if (!globalDataP->inplaceProcessing) {
		// create output world
		sequenceDataP->outWorld.pixelFormat = reduxfx::PF_RGBA;
		sequenceDataP->outWorld.width = outputP->width;
		sequenceDataP->outWorld.height = outputP->height;
		sequenceDataP->outWorld.rowBytes = sequenceDataP->outWorld.width * sizeof(float) * 4;
		sequenceDataP->outWorld.origin_x = 0;
		sequenceDataP->outWorld.origin_y = 0;
		int i = globalDataP->nofInputs;
		int sz = sequenceDataP->outWorld.height * sequenceDataP->outWorld.rowBytes;
		worldH[i] = PF_NEW_HANDLE(sz);
		sequenceDataP->outWorld.data = (PF_PixelPtr)PF_LOCK_HANDLE(worldH[i]);
	}

	ERR(PF_ABORT(in_data));
	if (!err) {
		ContextData contextData;
		setContextData(contextData, in_data, out_data, NULL, outputP, NULL);
		err = pluginProcess(sequenceDataP, globalDataP, &contextData);
	}

	ERR(PF_ABORT(in_data));
	if (!err) {
		if (!globalDataP->inplaceProcessing) {
			int odx = globalDataP->nofInputs;
			dstWorld[odx].width = sequenceDataP->outWorld.width;
			dstWorld[odx].height = sequenceDataP->outWorld.height;
			dstWorld[odx].rowbytes = sequenceDataP->outWorld.rowBytes;
			dstWorld[odx].data = (PF_PixelPtr)(sequenceDataP->outWorld.data);
			i_data.inWorld = &(dstWorld[odx]);
		} else {
			i_data.inWorld = &(dstWorld[0]);
		}
		i_data.outWorld = outputP;
		i_data.scale = 1.f / globalDataP->scale;

		if (worldFormat == PF_PixelFormat_ARGB32)
			err = iterate_generic(outputP->height, &i_data, it_Convert_RGBA32_to_ARGB8);
		else if (worldFormat == PF_PixelFormat_ARGB64)
			err = iterate_generic(outputP->height, &i_data, it_Convert_RGBA32_to_ARGB16);
		else if (worldFormat == PF_PixelFormat_ARGB128)
			err = iterate_generic(outputP->height, &i_data, it_Convert_RGBA32_to_ARGB32);
		else if (worldFormat == PrPixelFormat_BGRA_4444_8u)
			err = iterate_generic(outputP->height, &i_data, it_Convert_RGBA32_to_BGRA8);
		else if (worldFormat == PrPixelFormat_BGRA_4444_32f_Linear || worldFormat == PrPixelFormat_BGRA_4444_32f)
			err = iterate_generic(outputP->height, &i_data, it_Convert_RGBA32_to_BGRA32);
	}
	for (int j = 0; j < globalDataP->nofInputs + globalDataP->inplaceProcessing?0:1; j++) {
		PF_DISPOSE_HANDLE(worldH[j]);
	}

	}
	catch(...)
	{
	}

	try
	{
	if (pfS) in_data->pica_basicP->ReleaseSuite(kPFPixelFormatSuite, kPFPixelFormatSuiteVersion1);
	if (wsP) in_data->pica_basicP->ReleaseSuite(kPFWorldSuite, kPFWorldSuiteVersion2);
	if (i_data.pIterateSuite) {
		in_data->pica_basicP->ReleaseSuite(kPFIterate8Suite, kPFIterate8SuiteVersion1);
	}
	}
	catch(...)
	{
	}
	return err;
}

static PF_Err getParamData(PF_InData* in_data, PF_ParamDef* param, SequenceData* sequenceDataP, GlobalData* globalDataP, WorldData* worldDataP)
{
	PF_Err err = PF_Err_NONE;

	int l = 0;
	for (int i = 0; i < globalDataP->nofParams; i++) {
		if (PAR_TYPE(i) == PT_FLOAT) {
			PAR_VAL(i) = (float)param[i].u.fs_d.value;
		} else if (PAR_TYPE(i) == PT_INT) {
			PAR_VAL(i) = floor((float)(param[i].u.fs_d.value));
		} else if (PAR_TYPE(i) == PT_COLOR) {
			PF_Pixel p = param[i].u.cd.value;
			PAR_CH(i, 0) = p.red / 255.0f;
			PAR_CH(i, 1) = p.green / 255.0f;
			PAR_CH(i, 2) = p.blue / 255.0f;
			PAR_CH(i, 3) = 1.0f;
		} else if (PAR_TYPE(i) == PT_POINT || PAR_TYPE(i) == PT_VEC2) {
			PAR_CH(i, 0) = (float)((A_long)(param[i].u.td.x_value >> 16));
			PAR_CH(i, 1) = (float)((A_long)(param[i].u.td.y_value >> 16));
		} else if (PAR_TYPE(i) == PT_VEC3) {
			PAR_CH(i, 0) = (float)param[i].u.point3d_d.x_value;
			PAR_CH(i, 1) = (float)param[i].u.point3d_d.y_value;
			PAR_CH(i, 2) = (float)param[i].u.point3d_d.z_value;
		} else if (PAR_TYPE(i) == PT_ANGLE) {
			PAR_VAL(i) = (float)(param[i].u.ad.value >> 16);
		} else if (PAR_TYPE(i) == PT_LAYER && worldDataP) {
			worldDataP->srcWorld[l] = &param[i].u.ld;
			l++;
		} else if (PAR_TYPE(i) == PT_BOOL) {
			PAR_VAL(i) = (float)(param[i].u.bd.value);
		} else if (PAR_TYPE(i) == PT_SELECT) {
			PAR_VAL(i) = (float)((A_long)(param[i].u.td.x_value) - 1);
		}
	}
	return err;
}

static PF_Err render(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP)
{
	PF_Err err = PF_Err_NONE;
	GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;

	vector<PF_ParamDef> vParams;
	vParams.resize(globalDataP->nofParams);
	vParams[0] = *(param[0]);

	WorldData worldData;
	SequenceData* sequenceDataP = (SequenceData*)PF_LOCK_HANDLE(in_data->sequence_data);

	int l = 0;
	sequenceDataP->inputConnected[0] = true;

	// checkout the required params
	for (int i = 1; i < globalDataP->nofParams; i++) {
		A_long t = in_data->current_time;
		if (PAR_TYPE(i) == PT_LAYER) {
			int ofs = (A_long)(sequenceDataP->floatValue[i][0]);
			int ofs_type = (A_long)(sequenceDataP->floatValue[i][1]); //0:relative,1:absolute,2:granularity
			if (ofs_type == 0) {
				t += ofs * (1 + sequenceDataP->timeSpread) * in_data->time_step;
			} else if (ofs_type == 1) {
				t = ofs * in_data->time_step;
			} else {
				if (ofs <= 0) {
					t = 0;
				} else if (ofs > 1) {
					t = (A_long)(floor( (float)t / ( (float)ofs * in_data->time_step) ) * (float)ofs) * in_data->time_step;
				}
			}
			if (t < 0) t = 0;
		}
		PF_CHECKOUT_PARAM(in_data, i, t, in_data->time_step, in_data->time_scale, &(vParams[i]));
		if (PAR_TYPE(i) == PT_LAYER) {
			PF_EffectWorld* p = &(vParams[i].u.ld);
			if (p->data == NULL) {
				vParams[i] = *(param[0]);
				sequenceDataP->inputConnected[l++] = false;
			} else {
				sequenceDataP->inputConnected[l++] = true;
			}
		}
	}

	getParamData(in_data, &vParams[0], sequenceDataP, globalDataP, &worldData);
	ERR(PF_ABORT(in_data));
	ERR(doRender(in_data, out_data, sequenceDataP, globalDataP, &worldData, outputP));

	// Always check in, no matter what the error condition!
	for (int i = 1; i < globalDataP->nofParams; i++) {
		PF_CHECKIN_PARAM(in_data, &(vParams[i]));
	}
	PF_UNLOCK_HANDLE(in_data->sequence_data);
	PF_UNLOCK_HANDLE(in_data->global_data);
	return err;
}

static PF_Err paramsChanged(PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP, PF_UserChangedParamExtra* extraP)
{
	ContextData contextData;
	setContextData(contextData, in_data, out_data, param, outputP, extraP);
	PF_Err err = PF_Err_NONE;
	SequenceData* sequenceDataP = (SequenceData*)PF_LOCK_HANDLE(in_data->sequence_data);
	if (!sequenceDataP) {
		PF_UNLOCK_HANDLE(in_data->sequence_data);
		return err;
	}
	GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	bool isPremiere = in_data->appl_id == 'PrMr';
	vector<PF_ParamDef> vParams;
	vParams.resize(globalDataP->nofParams);

	if (extraP) {
		out_data->out_flags = PF_OutFlag_REFRESH_UI | PF_OutFlag_FORCE_RERENDER;
		int g = extraP->param_index;
		PF_ParamDef p1 = *(param[g]);
		p1.uu.change_flags = PF_ChangeFlag_CHANGED_VALUE;
		#ifdef AE_64
		err = suites.ParamUtilsSuite3()->PF_UpdateParamUI(in_data->effect_ref, g, &p1);
		#else
		err = suites.ParamUtilsSuite1()->PF_UpdateParamUI(in_data->effect_ref, g, &p1);
		#endif

		if (PAR_TYPE(g) == PT_TEXT && !isPremiere) {
			sequenceDataP->update = true;
			string d = globalDataP->param[g].displayName;
			strReplace(d, "?", "");
			string txt = sequenceDataP->textValue[g];
			bool m = (globalDataP->param[g].maxValue == 0.f);
			txt = showScriptDialog(in_data, d, txt, true, m);
			if (txt != "") sequenceDataP->textValue[g] = txt;
		}

		if (globalDataP->param[g].displayStatus == DS_DISABLED) {
			AEGP_StreamRefH streamH = NULL;
			AEGP_EffectRefH meH = NULL;
			if (!isPremiere) {
				ERR(suites.PFInterfaceSuite1()->AEGP_GetNewEffectForEffect(NULL, in_data->effect_ref, &meH));
				ERR(suites.StreamSuite2()->AEGP_GetNewEffectStreamByIndex(NULL, meH, g, &streamH));
				ERR(suites.DynamicStreamSuite2()->AEGP_SetDynamicStreamFlag(streamH, AEGP_DynStreamFlag_DISABLED, FALSE, TRUE));
				if (meH) suites.EffectSuite2()->AEGP_DisposeEffect(meH);
				if (streamH) suites.StreamSuite2()->AEGP_DisposeStream(streamH);
			}
			p1.ui_flags |= PF_PUI_DISABLED;
		} else if (globalDataP->param[g].displayStatus == DS_HIDDEN) {
			AEGP_StreamRefH streamH = NULL;
			AEGP_EffectRefH meH = NULL;
			if (!isPremiere) {
				ERR(suites.PFInterfaceSuite1()->AEGP_GetNewEffectForEffect(NULL, in_data->effect_ref, &meH));
				ERR(suites.StreamSuite2()->AEGP_GetNewEffectStreamByIndex(NULL, meH, g, &streamH));
				ERR(suites.DynamicStreamSuite2()->AEGP_SetDynamicStreamFlag(streamH, AEGP_DynStreamFlag_HIDDEN, FALSE, TRUE));
				if (meH) suites.EffectSuite2()->AEGP_DisposeEffect(meH);
				if (streamH) suites.StreamSuite2()->AEGP_DisposeStream(streamH);
			}
			p1.ui_flags |= PF_PUI_INVISIBLE;
		}

		for (int i = 0; i < globalDataP->nofParams; i++) vParams[i] = *(param[i]);
		getParamData(in_data, &vParams[0], sequenceDataP, globalDataP, NULL);
//		PF_ParamDef params2[MAX_NOF_PARAMS];
//		for (int i = 0; i < globalDataP->nofParams; i++) params2[i] = *(param[i]);
//		getParamData(in_data, (PF_ParamDef*)&params2, sequenceDataP, globalDataP, NULL);
		pluginParamChange(g, sequenceDataP, globalDataP, &contextData);

	} else {
		for (int g = 0; g < globalDataP->nofParams; g++) {
			bool changed = false;
			PF_ParamDef p1 = *(param[g]);
			if (globalDataP->param[g].displayStatus == DS_DISABLED) {
				AEGP_StreamRefH streamH = NULL;
				AEGP_EffectRefH meH = NULL;
				if (!isPremiere) {
					ERR(suites.PFInterfaceSuite1()->AEGP_GetNewEffectForEffect(NULL, in_data->effect_ref, &meH));
					ERR(suites.StreamSuite2()->AEGP_GetNewEffectStreamByIndex(NULL, meH, g, &streamH));
					ERR(suites.DynamicStreamSuite2()->AEGP_SetDynamicStreamFlag(streamH, AEGP_DynStreamFlag_DISABLED, FALSE, TRUE));
					if (meH) suites.EffectSuite2()->AEGP_DisposeEffect(meH);
					if (streamH) suites.StreamSuite2()->AEGP_DisposeStream(streamH);
				}
				p1.ui_flags |= PF_PUI_DISABLED;
				p1.uu.change_flags = PF_ChangeFlag_CHANGED_VALUE;
				changed = true;
			} else if (globalDataP->param[g].displayStatus == DS_HIDDEN) {
				AEGP_StreamRefH streamH = NULL;
				AEGP_EffectRefH meH = NULL;
				if (!isPremiere) {
					ERR(suites.PFInterfaceSuite1()->AEGP_GetNewEffectForEffect(NULL, in_data->effect_ref, &meH));
					ERR(suites.StreamSuite2()->AEGP_GetNewEffectStreamByIndex(NULL, meH, g, &streamH));
					ERR(suites.DynamicStreamSuite2()->AEGP_SetDynamicStreamFlag(streamH, AEGP_DynStreamFlag_HIDDEN, FALSE, TRUE));
					if (meH) suites.EffectSuite2()->AEGP_DisposeEffect(meH);
					if (streamH) suites.StreamSuite2()->AEGP_DisposeStream(streamH);
				}
				p1.ui_flags |= PF_PUI_INVISIBLE;
				p1.uu.change_flags = PF_ChangeFlag_CHANGED_VALUE;
				changed = true;
			}
			if (changed) {
				p1.uu.change_flags = PF_ChangeFlag_CHANGED_VALUE;
				#ifdef AE_64
				err = suites.ParamUtilsSuite3()->PF_UpdateParamUI(in_data->effect_ref, g, &p1);
				#else
				err = suites.ParamUtilsSuite1()->PF_UpdateParamUI(in_data->effect_ref, g, &p1);
				#endif
			}
		}
		for (int i = 0; i < globalDataP->nofParams; i++) vParams[i] = *(param[i]);
		getParamData(in_data, &vParams[0], sequenceDataP, globalDataP, NULL);
//		PF_ParamDef params2[MAX_NOF_PARAMS];
//		for (int i = 0; i < globalDataP->nofParams; i++) params2[i] = *(param[i]);
//		getParamData(in_data, (PF_ParamDef*)&params2, sequenceDataP, globalDataP, NULL);
		pluginParamChange(0, sequenceDataP, globalDataP, &contextData);
	}
	PF_UNLOCK_HANDLE(in_data->sequence_data);
	PF_UNLOCK_HANDLE(in_data->global_data);
	return err;
}

static PF_Err preRender(PF_InData* in_data, PF_OutData* out_data, PF_PreRenderExtra* extraP)
{
	PF_Err err = PF_Err_NONE;
	GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;

	PF_RenderRequest req = extraP->input->output_request;
	PF_RenderRequest req2;
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	PF_Handle preRenderDataH = suites.HandleSuite1()->host_new_handle(sizeof(PreRenderData));
	SequenceData* sequenceDataP = (SequenceData*)PF_LOCK_HANDLE(in_data->sequence_data);
	PF_UNLOCK_HANDLE(in_data->sequence_data);

	if (preRenderDataH) {
		extraP->output->pre_render_data = preRenderDataH;

		PreRenderData* preRenderDataP = static_cast<PreRenderData*>(suites.HandleSuite1()->host_lock_handle(preRenderDataH));
		if (preRenderDataP) {
			CLR_STRUCT(*preRenderDataP);
			int l = 0;
			for (int i = 0; i < globalDataP->nofParams; i++) {
				A_long t = in_data->current_time;

				if (PAR_TYPE(i) == PT_LAYER) {
					int ofs = (A_long)(sequenceDataP->floatValue[i][0]);
					int ofs_type = (A_long)(sequenceDataP->floatValue[i][1]); //0:relative,1:absolute,2:granularity
					if (ofs_type == 0) {
						t += ofs * (1 + sequenceDataP->timeSpread) * in_data->time_step;
					} else if (ofs_type == 1) {
						t = ofs * in_data->time_step;
					} else {
						if (ofs <= 0) {
							t = 0;
						} else if (ofs > 1) {
							t = (A_long)(floor( (float)t / ( (float)ofs * in_data->time_step) ) * (float)ofs) * in_data->time_step;
						}
					}
					if (t < 0) t = 0;
					if (i > 0) {
						CLR_STRUCT(req2);
						ERR(extraP->cb->checkout_layer(in_data->effect_ref, i, 1000 + i, &req2, t, in_data->time_step, in_data->time_scale, &(preRenderDataP->in_result[l])));
						req.rect = preRenderDataP->in_result[l].max_result_rect;
					}
					ERR(extraP->cb->checkout_layer(in_data->effect_ref, i, i, &req, t, in_data->time_step, in_data->time_scale, &(preRenderDataP->in_result[l])));
					l++;
				} else {
					PF_CHECKOUT_PARAM(in_data, i, t, in_data->time_step, in_data->time_scale, &(preRenderDataP->param[i]));
				}
			}
		UnionLRect(&(preRenderDataP->in_result[0].result_rect), &extraP->output->result_rect);
		UnionLRect(&(preRenderDataP->in_result[0].max_result_rect), &extraP->output->max_result_rect);
		suites.HandleSuite1()->host_unlock_handle(preRenderDataH);
		}
	}
	PF_UNLOCK_HANDLE(in_data->global_data);
	return err;
}

static PF_Err smartRender(PF_InData* in_data, PF_OutData* out_data, PF_SmartRenderExtra* extraP)
{
	PF_Err err = PF_Err_NONE;
	GlobalData* globalDataP = ((AE_GlobalData*)PF_LOCK_HANDLE(in_data->global_data))->globalDataP;

	try {
	PF_EffectWorld* outputP;

	SequenceData* sequenceDataP = (SequenceData*)PF_LOCK_HANDLE(in_data->sequence_data);

	AEGP_SuiteHandler suites(in_data->pica_basicP);
	PreRenderData* preRenderDataP = static_cast<PreRenderData*>(suites.HandleSuite1()->host_lock_handle(static_cast<PF_Handle>(extraP->input->pre_render_data)));
	int l = 0;
	if (preRenderDataP) {
		// checkout the required params
		for (int i = 0; i < globalDataP->nofParams; i++) {
			if (PAR_TYPE(i) == PT_LAYER) {
				CLR_STRUCT(preRenderDataP->param[i]);
				PF_EffectWorld* layerP = NULL;
				ERR(extraP->cb->checkout_layer_pixels(in_data->effect_ref, i, &layerP));
				if (err) {
					extraP->cb->checkout_output(in_data->effect_ref, &outputP);
					suites.HandleSuite1()->host_unlock_handle(static_cast<PF_Handle>(extraP->input->pre_render_data));
					return err;
				}
				if (layerP == NULL) {
					sequenceDataP->inputConnected[l++] = false;
					preRenderDataP->param[i].u.ld = preRenderDataP->param[0].u.ld;
				} else {
					sequenceDataP->inputConnected[l++] = true;
					preRenderDataP->param[i].u.ld = *layerP;
				}
			}
		}

		ERR(extraP->cb->checkout_output(in_data->effect_ref, &outputP));
		if (err) {
			suites.HandleSuite1()->host_unlock_handle(static_cast<PF_Handle>(extraP->input->pre_render_data));
			return err;
		}

		ERR(PF_ABORT(in_data));

		WorldData worldData;
		if (!err) getParamData(in_data, (PF_ParamDef*)&(preRenderDataP->param), sequenceDataP, globalDataP, &worldData);
		suites.HandleSuite1()->host_unlock_handle(static_cast<PF_Handle>(extraP->input->pre_render_data));

		ERR(PF_ABORT(in_data));

		ERR(doRender(in_data, out_data, sequenceDataP, globalDataP, &worldData, outputP));

	}
	}
	catch(...)
	{
	}
	PF_UNLOCK_HANDLE(in_data->sequence_data);
	PF_UNLOCK_HANDLE(in_data->global_data);
	return err;
}

inline PF_Err pluginMain(PF_Cmd cmd, PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* param[], PF_LayerDef* outputP, void* extraP)
{
	PF_Err err = PF_Err_NONE;
	try
	{
	switch (cmd)
		{
		case PF_Cmd_ABOUT:
			{
			err = showAboutDialog(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_GLOBAL_SETUP:
			{
			err = globalSetup(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_SEQUENCE_SETUP:
			{
			err = sequenceSetup(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_SEQUENCE_RESETUP:
			{
			err = sequenceResetup(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_SEQUENCE_SETDOWN:
			{
			err = sequenceSetdown(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_SEQUENCE_FLATTEN:
			{
			err = sequenceFlatten(in_data, out_data, param, outputP, true);
			break;
			}
		case _PF_Cmd_GET_FLATTENED_SEQUENCE_DATA: // (workaround to get this CC2014 command to compile with the CS6 SDK)
			{
			err = sequenceFlatten(in_data, out_data, param, outputP, false);
			break;
			}
		case PF_Cmd_PARAMS_SETUP:
			{
			err = paramsSetup(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_RENDER:
			{
			err = render(in_data, out_data, param, outputP);
			break;
			}
		case PF_Cmd_SMART_PRE_RENDER:
			{
			err = preRender(in_data, out_data, static_cast<PF_PreRenderExtra*>(extraP));
			break;
			}
		case PF_Cmd_SMART_RENDER:
			{
			err = smartRender(in_data, out_data, static_cast<PF_SmartRenderExtra*>(extraP));
			break;
			}
		case PF_Cmd_USER_CHANGED_PARAM:
			{
			err = paramsChanged(in_data, out_data, param, outputP, static_cast<PF_UserChangedParamExtra*>(extraP));
			break;
			}
		case PF_Cmd_UPDATE_PARAMS_UI:
			{
			err = paramsChanged(in_data, out_data, param, outputP, NULL);
			break;
			}
		}
	}
	catch(PF_Err &thrown_err)
	{
		err = thrown_err;
	}
	catch(...)
	{
		err = PF_Err_INTERNAL_STRUCT_DAMAGED;
	}

	return err;
}

#endif
