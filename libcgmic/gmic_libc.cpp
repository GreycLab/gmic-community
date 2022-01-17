/*
 #
 #  File        : gmic_libc.cpp
 #                ( C++ source file )
 #
 #  Description : GREYC's Magic for Image Computing - C bridge to the libgmic
 #                ( http://gmic.eu )
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

#include <string>
#include "CImg.h"
#include "gmic.h"
#include "gmic_libc.h"

GMIC_DLLINTERFACE int GMIC_CALLCONV gmic_delete_external(float* p) {
  delete[] p;
  return 0;
}

GMIC_DLLINTERFACE int GMIC_CALLCONV gmic_call(const char* _cmd, unsigned int* _nofImages,
                                              gmic_interface_image* _images, gmic_interface_options* _options) {
  int err = 0;
  bool no_inplace = _options?_options->no_inplace_processing:false;
  int nofImages = 0;
  if (_nofImages && _images) nofImages = *_nofImages;
  gmic_list<float> images;
  gmic_list<char> images_names;
  images.assign(nofImages);
  images_names.assign(nofImages);

  for (unsigned int i = 0; i < images._width; ++i) {
    gmic_image<float>& img = images[i];
    if (_images[i].format == E_FORMAT_BYTE) {
      gmic_image<unsigned char> img_tmp;
      if (_images[i].is_interleaved) {
        img_tmp.assign((unsigned char*)_images[i].data, _images[i].spectrum, _images[i].width,
                       _images[i].height, _images[i].depth, true);
        img_tmp.permute_axes("YZCX");
      } else {
        img_tmp.assign((unsigned char*)_images[i].data, _images[i].width, _images[i].height,
                       _images[i].depth, _images[i].spectrum, true);
      }
      img = img_tmp;
    } else {
      if (no_inplace) {
        gmic_image<float> img_tmp;
        if (_images[i].is_interleaved) {
          img_tmp.assign((float*)_images[i].data, _images[i].spectrum, _images[i].width,
                         _images[i].height, _images[i].depth, true);
          img_tmp.permute_axes("YZCX");
        } else {
          img_tmp.assign((float*)_images[i].data, _images[i].width, _images[i].height,
                         _images[i].depth, _images[i].spectrum, true);
        }
        img = img_tmp;
      } else {
        if (_images[i].is_interleaved) {
          img.assign((float*)_images[i].data, _images[i].spectrum, _images[i].width,
                     _images[i].height, _images[i].depth, true);
          img.permute_axes("YZCX");
        } else {
          img.assign((float*)_images[i].data, _images[i].width, _images[i].height,
                     _images[i].depth, _images[i].spectrum, true);
        }
      }
    }
    images_names[i].assign(std::strlen(_images[i].name) + 1);
    std::strcpy(images_names[i], _images[i].name);
  }

  try {
    if (_options)
      gmic(_cmd, images, images_names, _options->custom_commands, !_options->ignore_stdlib,
           _options->p_progress, _options->p_is_abort);
    else
      gmic(_cmd, images, images_names);

  } catch (gmic_exception &e) { // catch exception, if an error occurred in the interpreter.
    std::string error_string = e.what();
    std::fprintf(stderr, "\n- Error encountered when calling G'MIC : '%s'\n", e.what());
    if (_options && _options->error_message_buffer) {
      std::strcpy(_options->error_message_buffer, error_string.substr(0, 255).c_str());
    }
    err = -1;
  }

  if (_nofImages && _images && err == 0) {
    *_nofImages = images._width;
    for (unsigned int i = 0; i < images._width; ++i) {
      gmic_image<float>& img = images[i];
      if (_options && _options->interleave_output) {
        img.permute_axes("CXYZ");
		    _images[i].is_interleaved = true;
        _images[i].width = img._height;
        _images[i].height = img._depth;
        _images[i].depth = img._spectrum;
        _images[i].spectrum = img._width;
      } else {
		    _images[i].is_interleaved = false;
        _images[i].width = img._width;
        _images[i].height = img._height;
        _images[i].depth = img._depth;
        _images[i].spectrum = img._spectrum;
	  }
      if (_options && _options->output_format == E_FORMAT_BYTE) {
        gmic_image<unsigned char> img_tmp;
        img_tmp = img;
        _images[i].format = E_FORMAT_BYTE;
        _images[i].data = img_tmp._data;
        img_tmp._is_shared = true;
        img._is_shared = false;
      } else {
        _images[i].format = E_FORMAT_FLOAT;
        _images[i].data = img._data;
        img._is_shared = true;
      }
      std::strcpy(_images[i].name, images_names[i]);
    }
  }
  images.assign(0U);
  images_names.assign(0U);
  return err;
}

GMIC_DLLINTERFACE const char* GMIC_CALLCONV gmic_get_stdlib() {
  gmic_image<char> lib = gmic::decompress_stdlib();
  lib._is_shared = true;
  return lib.data();
}
