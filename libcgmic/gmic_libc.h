/*
 #
 #  File        : gmic_libc.h
 #                ( C++ header file )
 #
 #  Description : GREYC's Magic for Image Computing
 #                ( http://gmic.eu )
 #
 #  Note        : Include this file in your C source code, if you
 #                want to use the G'MIC interpreter in your own program,
 #                through the C bridge to the G'MIC library.
 #
 #  Copyright   : Tobias Fleischer
 #                ( https://plus.google.com/u/0/b/117441237982283011318/+TobiasFleischer )
 #
 #  License     : CeCILL-B v1.0
 #                ( http://cecill.info/licences/Licence_CeCILL-B_V1-en.html )
 #
 #  This software is governed either by the CeCILL-B license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL-B licenses as circulated by CEA, CNRS and INRIA
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
 #  knowledge of the CeCILL-B licenses and that you accept its terms.
 #
*/

#ifndef _GMIC_LIBC_H_
#define _GMIC_LIBC_H_

#if !defined(_MSC_VER) || (_MSC_VER >= 1900)
#include <stdbool.h>
#endif

#if defined(WIN32) || defined(_WIN32)
	#ifdef gmic_core
		#define GMIC_DLLINTERFACE __declspec(dllexport)
	#else // #ifdef gmic_core
		#define GMIC_DLLINTERFACE __declspec(dllimport)
	#endif // #ifdef gmic_core
	#define GMIC_CALLCONV __stdcall
#else // #if defined(WIN32) || defined(_WIN32)
	#define GMIC_DLLINTERFACE
	#define GMIC_CALLCONV
#endif // #if defined(WIN32) || defined(_WIN32)

#define MAX_IMAGE_NAME_LENGTH 255

typedef enum {
  E_FORMAT_FLOAT = 0,
  E_FORMAT_BYTE = 1
} EPixelFormat;

typedef struct {
  void* data;
  unsigned int width;
  unsigned int height;
  unsigned int depth;
  unsigned int spectrum;
  bool is_interleaved;
  EPixelFormat format;
  char name[MAX_IMAGE_NAME_LENGTH + 1];
} gmic_interface_image;

typedef struct {
  const char* custom_commands;
  bool ignore_stdlib;
  float* p_progress;
  bool* p_is_abort;
  bool interleave_output;
  EPixelFormat output_format;
  bool no_inplace_processing;
  char* error_message_buffer;
} gmic_interface_options;

#ifdef __cplusplus
extern "C"
{
#endif

GMIC_DLLINTERFACE int GMIC_CALLCONV gmic_delete_external(float* p);
GMIC_DLLINTERFACE int GMIC_CALLCONV gmic_call(const char* _cmd, unsigned int* _nofImages,
                                              gmic_interface_image* _images, gmic_interface_options* _options);
GMIC_DLLINTERFACE const char* GMIC_CALLCONV gmic_get_stdlib();

#ifdef __cplusplus
} //#ifdef  __cplusplus
#endif

#endif // #ifndef _GMIC_LIBC_H
