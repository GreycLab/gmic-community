/*
 #
 #  File        : RFX_Utils.h
 #
 #  Description : A self-contained header file with helper functions to make    
 #                handling and adressing pixel data a bit easier    
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

#ifdef _WIN32
#pragma warning (disable:4996)
#endif
#pragma once
#ifndef _RFX_UTILS_H
#define _RFX_UTILS_H

#include <map>
#include <string>
#include <sstream>
using namespace std;

#ifdef _WIN32
#include <Windows.h>
#endif

#include "RFX_Parameter.h"

#define	CLR_STRUCT(STRUCT) memset(&STRUCT, 0, sizeof(STRUCT));

#ifndef M_PI
#define M_PI	3.14159265358979323846f
#endif

#define clamp(a,mn,mx) ((a)>mx?mx:((a)<mn?mn:(a)))
#define remap(x, min1, max1, min2, max2) (min2 + (((x-min1)/(max1-min1))*(max2-min2)))
#define frac(a) (a-floor(a))
#define step(y,x) ((x>=y)?1.0f:0.0f)
#define mix(a, b, f) (a * (1.0f - f) + f * b)
#define fmax(a,b) (((a)>(b))?(a):(b))
#define fmin(a,b) (((a)<(b))?(a):(b))

inline float saturate(float a)
{
	return ((a)>1.0f?1.0f:((a)<0.0f?0.0f:(a)));
}
inline float linearStep(float edge0, float edge1, float x)
{
	return saturate((x - edge0)/(edge1 - edge0));
}
inline float smoothStep(float edge0, float edge1, float x)
{
	x = saturate((x - edge0)/(edge1 - edge0));
	return x*x*(3.0f - 2.0f*x);
}
inline float smootherStep(float edge0, float edge1, float x)
{
	x = saturate((x - edge0)/(edge1 - edge0));
	return x*x*x*(x*(x*6.0f - 15.0f) + 10.0f);
}
inline int round(float d)
{ 
	return (int)floor(d + 0.5f); 
}

typedef std::map<std::string, std::string> strStrMap;

namespace reduxfx {

inline void openOS(string s)
{
#ifdef _WIN32
	ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWNORMAL);
#else
	s = "open " + s;
	system(s.c_str());
#endif
}

inline void getPixel_RGBA_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	r = (*p++) / 255.f;
	g = (*p++) / 255.f;
	b = (*p++) / 255.f;
	a = (*p++) / 255.f;
	*buf = p;
}
inline void getPixel_ARGB_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	a = (*p++) / 255.f;
	r = (*p++) / 255.f;
	g = (*p++) / 255.f;
	b = (*p++) / 255.f;
	*buf = p;
}
inline void getPixel_BGRA_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	b = (*p++) / 255.f;
	g = (*p++) / 255.f;
	r = (*p++) / 255.f;
	a = (*p++) / 255.f;
	*buf = p;
}
inline void getPixel_RGB_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	r = (*p++) / 255.f;
	g = (*p++) / 255.f;
	b = (*p++) / 255.f;
	a = 1.f;
	*buf = p;
}

inline void getPixel_RGBA_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	r = (*p++) / 65535.f;
	g = (*p++) / 65535.f;
	b = (*p++) / 65535.f;
	a = (*p++) / 65535.f;
	*buf = (unsigned char*)p;
}
inline void getPixel_ARGB_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	a = (*p++) / 65535.f;
	r = (*p++) / 65535.f;
	g = (*p++) / 65535.f;
	b = (*p++) / 65535.f;
	*buf = (unsigned char*)p;
}
inline void getPixel_BGRA_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	b = (*p++) / 65535.f;
	g = (*p++) / 65535.f;
	r = (*p++) / 65535.f;
	a = (*p++) / 65535.f;
	*buf = (unsigned char*)p;
}
inline void getPixel_RGB_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	r = (*p++) / 65535.f;
	g = (*p++) / 65535.f;
	b = (*p++) / 65535.f;
	a = 1.f;
	*buf = (unsigned char*)p;
}

inline void getPixel_RGBA_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	r = (*p++);
	g = (*p++);
	b = (*p++);
	a = (*p++);
	*buf = (unsigned char*)p;
}
inline void getPixel_ARGB_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	a = (*p++);
	r = (*p++);
	g = (*p++);
	b = (*p++);
	*buf = (unsigned char*)p;
}
inline void getPixel_BGRA_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	b = (*p++);
	g = (*p++);
	r = (*p++);
	a = (*p++);
	*buf = (unsigned char*)p;
}
inline void getPixel_RGB_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	r = (*p++);
	g = (*p++);
	b = (*p++);
	a = 1.f;
	*buf = (unsigned char*)p;
}

inline void setPixel_RGBA_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	*p++ = (unsigned char)(r * 255.f);
	*p++ = (unsigned char)(g * 255.f);
	*p++ = (unsigned char)(b * 255.f);
	*p++ = (unsigned char)(a * 255.f);
	*buf = p;
}
inline void setPixel_ARGB_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	*p++ = (unsigned char)(a * 255.f);
	*p++ = (unsigned char)(r * 255.f);
	*p++ = (unsigned char)(g * 255.f);
	*p++ = (unsigned char)(b * 255.f);
	*buf = p;
}
inline void setPixel_BGRA_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	*p++ = (unsigned char)(b * 255.f);
	*p++ = (unsigned char)(g * 255.f);
	*p++ = (unsigned char)(r * 255.f);
	*p++ = (unsigned char)(a * 255.f);
	*buf = p;
}
inline void setPixel_RGB_8(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned char* p = *buf;
	*p++ = (unsigned char)(r * 255.f);
	*p++ = (unsigned char)(g * 255.f);
	*p++ = (unsigned char)(b * 255.f);
	*buf = p;
}

inline void setPixel_RGBA_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	*p++ = (unsigned short int)(r * 65535.f);
	*p++ = (unsigned short int)(g * 65535.f);
	*p++ = (unsigned short int)(b * 65535.f);
	*p++ = (unsigned short int)(a * 65535.f);
	*buf = (unsigned char*)p;
}
inline void setPixel_ARGB_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	*p++ = (unsigned short int)(a * 65535.f);
	*p++ = (unsigned short int)(r * 65535.f);
	*p++ = (unsigned short int)(g * 65535.f);
	*p++ = (unsigned short int)(b * 65535.f);
	*buf = (unsigned char*)p;
}
inline void setPixel_BGRA_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	*p++ = (unsigned short int)(b * 65535.f);
	*p++ = (unsigned short int)(g * 65535.f);
	*p++ = (unsigned short int)(r * 65535.f);
	*p++ = (unsigned short int)(a * 65535.f);
	*buf = (unsigned char*)p;
}
inline void setPixel_RGB_16(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	unsigned short int* p = (unsigned short int*)(*buf);
	*p++ = (unsigned short int)(r * 65535.f);
	*p++ = (unsigned short int)(g * 65535.f);
	*p++ = (unsigned short int)(b * 65535.f);
	*buf = (unsigned char*)p;
}

inline void setPixel_RGBA_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	*p++ = r;
	*p++ = g;
	*p++ = b;
	*p++ = a;
	*buf = (unsigned char*)p;
}
inline void setPixel_ARGB_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	*p++ = a;
	*p++ = r;
	*p++ = g;
	*p++ = b;
	*buf = (unsigned char*)p;
}
inline void setPixel_BGRA_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	*p++ = b;
	*p++ = g;
	*p++ = r;
	*p++ = a;
	*buf = (unsigned char*)p;
}
inline void setPixel_RGB_32(unsigned char** buf, float& r, float& g, float& b, float& a)
{
	float* p = (float*)(*buf);
	*p++ = r;
	*p++ = g;
	*p++ = b;
	*buf = (unsigned char*)p;
}

static float luma(const float r, const float g, const float b)
{
	return 0.299f * r + 0.587f * g + 0.114f * b;
}

static void convertRGB2YUV(const float r, const float g, const float b, float& y, float& u, float& v)
{
	y = 0.299f * r + 0.587f * g + 0.114f * b;
	u = (b - y) * 0.565f;
	v = (r - y) * 0.713f;
}

static void convertYUV2RGB(const float y, const float u, const float v, float& r, float& g, float& b)
{
	r = saturate(y + 1.403f * v);
	g = saturate(y - 0.344f * u - 1.403f * v);
	b = saturate(y + 1.770f * u);
}

static void convertRGB2HSL(const float r, const float g, const float b, float& h, float& s, float& l)
{
	h = 0.0f;
	s = 0.0f;
	l = 0.0f;
	float U, V;
	U = -fmin(r, fmin(g, b));
	V = fmax(r, fmax(g, b));
	l = (V - U) * 0.5f;
	float C = V + U;
	if (C != 0.0f) {
		float D2red = (V - r) / C;
		float D2green = (V - g) / C;
		float D2blue = (V - b) / C;
		float Dred = (D2red - D2blue) + 2.0f;
		float Dgreen = (D2green - D2red) + 4.0f;
		float Dblue = (D2blue - D2green) + 6.0f;
		Dblue = step(V, r) * Dblue;
		Dred = step(V, g) * Dred;
		Dgreen = step(V, b) * Dgreen;
		h = fmax(Dred, fmax(Dgreen, Dblue));
		h = frac(h / 6.0f);
		s = C / (1.0f - fabs(2.0f * l - 1.0f));
	}
}

static void convertHSL2RGB(const float h, const float s, const float l, float& r, float& g, float& b)
{
	float pred = saturate(fabs(h * 6.0f - 3.0f) - 1.0f);
	float pgreen = saturate(2.0f - fabs(h * 6.0f - 2.0f));
	float pblue = saturate(2.0f - fabs(h * 6.0f - 4.0f));
	float C = (1.0f - fabs(2.0f * l - 1.0f)) * s;
	r = (pred - 0.5f) * C + l;
	g = (pgreen - 0.5f) * C + l;
	b = (pblue - 0.5f) * C + l;
}

static void convertRGB2HSV(const float r, const float g, const float b, float& h, float& s, float& v)
{
	h = 0.0f;
	s = 0.0f;
	v = 0.0f;
	float M = fmin(r, fmin(g, b));
	v = fmax(r, fmax(g, b));
	float C = v - M;
	if (C != 0.0f) {
		s = C / v;
		float Dred = (((v - r) / 6.0f) + (C / 2.0f)) / C;
		float Dgreen = (((v - g) / 6.0f) + (C / 2.0f)) / C;
		float Dblue = (((v - b) / 6.0f) + (C / 2.0f)) / C;
		if (r == v) h = Dblue - Dgreen;
		else if (g == v) h = (1.0f/3.0f) + Dred - Dblue;
		else if (b == v) h = (2.0f/3.0f) + Dgreen - Dred;
		if (h < 0.0f) { h += 1.0f; }
		else if (h > 1.0f) { h -= 1.0f; }
	}
};

static void convertHSV2RGB(const float h, const float s, const float v, float& r, float& g, float& b)
{
	float pred = saturate(fabs(h * 6.0f - 3.0f) - 1.0f);
	float pgreen = saturate(2.0f - fabs(h * 6.0f - 2.0f));
	float pblue = saturate(2.0f - fabs(h * 6.0f - 4.0f));
	r = ((pred - 1.0f) * s + 1.0f) + v;
	g = ((pgreen - 1.0f) * s + 1.0f) + v;
	b = ((pblue - 1.0f) * s + 1.0f) + v;
};

inline float radians(float a)
{
	return M_PI * a / 180.0f;
}

static reduxfx::World convertWorld(const reduxfx::World& src, reduxfx::PixelFormat dstPixelFormat, int dstBitDepth, bool flipY = false)
{
	reduxfx::World dst;
	
	int dCh = dstPixelFormat == reduxfx::PF_RGB ? 3:4;
	int dBPP = dCh * (dstBitDepth / 8);
	dst.data = new char[src.width * src.height * dBPP];
	dst.rowBytes = src.width * dBPP;
	dst.pixelFormat = dstPixelFormat;
	dst.bitDepth = dstBitDepth;
	dst.width = src.width;
	dst.height = src.height;
	dst.origin_x = src.origin_x;
	dst.origin_y = src.origin_y;
	int sCh = src.pixelFormat == reduxfx::PF_RGB ? 3:4;

	unsigned char* srcBuf = (unsigned char*)(src.data);
	unsigned char* dstBuf = (unsigned char*)(dst.data);
	float r, g, b, a;

	void (*srcPixFunc)(unsigned char** buf, float& r, float& g, float& b, float& a);
	void (*dstPixFunc)(unsigned char** buf, float& r, float& g, float& b, float& a);

	if (src.bitDepth == 8) {
		if (src.pixelFormat == reduxfx::PF_RGBA) srcPixFunc = getPixel_RGBA_8;
		else if (src.pixelFormat == reduxfx::PF_ARGB) srcPixFunc = getPixel_ARGB_8;
		else if (src.pixelFormat == reduxfx::PF_BGRA) srcPixFunc = getPixel_BGRA_8;
		else srcPixFunc = getPixel_RGB_8;
	} else if (src.bitDepth == 16) {
		if (src.pixelFormat == reduxfx::PF_RGB) srcPixFunc = getPixel_RGB_16;
		else if (src.pixelFormat == reduxfx::PF_ARGB) srcPixFunc = getPixel_ARGB_16;
		else if (src.pixelFormat == reduxfx::PF_BGRA) srcPixFunc = getPixel_BGRA_16;
		else srcPixFunc = getPixel_RGB_16;
	} else {
		if (src.pixelFormat == reduxfx::PF_RGBA) srcPixFunc = getPixel_RGBA_32;
		else if (src.pixelFormat == reduxfx::PF_ARGB) srcPixFunc = getPixel_ARGB_32;
		else if (src.pixelFormat == reduxfx::PF_BGRA) srcPixFunc = getPixel_BGRA_32;
		else srcPixFunc = getPixel_RGB_32;
	}

	if (dstBitDepth == 8) {
		if (dstPixelFormat == reduxfx::PF_RGBA) dstPixFunc = setPixel_RGBA_8;
		else if (dstPixelFormat == reduxfx::PF_ARGB) dstPixFunc = setPixel_ARGB_8;
		else if (dstPixelFormat == reduxfx::PF_BGRA) dstPixFunc = setPixel_BGRA_8;
		else dstPixFunc = setPixel_RGB_8;
	} else if (dstBitDepth == 16) {
		if (dstPixelFormat == reduxfx::PF_RGBA) dstPixFunc = setPixel_RGBA_16;
		else if (dstPixelFormat == reduxfx::PF_ARGB) dstPixFunc = setPixel_ARGB_16;
		else if (dstPixelFormat == reduxfx::PF_BGRA) dstPixFunc = setPixel_BGRA_16;
		dstPixFunc = setPixel_RGB_16;
	} else {
		if (dstPixelFormat == reduxfx::PF_RGBA) dstPixFunc = setPixel_RGBA_32;
		else if (dstPixelFormat == reduxfx::PF_ARGB) dstPixFunc = setPixel_ARGB_32;
		else if (dstPixelFormat == reduxfx::PF_BGRA) dstPixFunc = setPixel_BGRA_32;
		else dstPixFunc = setPixel_RGB_32;
	}

	int srcStride = src.rowBytes - src.width * sCh * (src.bitDepth / 8);
	if (flipY) {
		srcStride -= 2 * src.rowBytes;
		srcBuf = (unsigned char*)(src.data) + src.rowBytes * (src.height - 1);
	}
	for (int y = 0; y < src.height; y++) {
		for (int x = 0; x < src.width; x++) {
			srcPixFunc(&srcBuf, r, g, b, a);
			dstPixFunc(&dstBuf, r, g, b, a);
		}
		srcBuf += srcStride;
	}
	
	return dst;
}

};


#endif