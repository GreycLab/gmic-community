#
#  File        : Makefile
#                ( Makefile for GNU 'make' utility )
#
#  Description : Makefile for compiling :
#
#                 . the G'MIC command line tool (type 'make cli').
#                 . the G'MIC plug-in for GIMP (type 'make gimp').
#                 . the G'MIC interpreter, as a C++ library (type 'make lib').
#                 . the ZArt software (type 'make zart').
#                 . To compile all of them, just type 'make', or 'make all').
#
#                ( http://gmic.eu )
#
#  Copyright   : David Tschumperle
#                ( http://tschumperle.users.greyc.fr/ )
#
#  License     : CeCILL v2.0
#                ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )
#
#  This software is governed by the CeCILL  license under French law and
#  abiding by the rules of distribution of free software.  You can  use,
#  modify and/ or redistribute the software under the terms of the CeCILL
#  license as circulated by CEA, CNRS and INRIA at the following URL
#  "http://www.cecill.info".
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
#  knowledge of the CeCILL license and that you accept its terms.
#

#----------------------------------
# Set correct variables and paths.
#----------------------------------
OS := $(shell uname)
ifeq ($(OS),Linux)
OS = Unix
endif
ifeq ($(OS),GNU/kFreeBSD)
OS = Unix
endif
ifeq ($(OS),GNU)
OS = Unix
endif
ifeq ($(OS),Darwin)
PLUGINDIR = ~/Library/Application\ Support/Gimp/plug-ins
ifeq (,$(wildcard /opt/local))
USR = /usr/local
else
USR = /opt/local
endif
WGET = curl -L --silent -o
else
PLUGINDIR = `gimptool-2.0 --gimpplugindir`/plug-ins
USR = /usr
WGET = wget --quiet -O
endif
ifeq ($(OSTYPE),msys)
EXE = .exe
endif
ifeq ($(OS),FreeBSD)
OS = Unix
USR = /usr/local
endif
ifeq ($(OS),NetBSD)
OS = Unix
endif
LIB=lib
BIN=bin
INCLUDE=include
ifdef NOSTRIP
STRIP=echo skip strip
else
STRIP=strip
endif

#----------------------------------
# Define flags to customize builds.
#----------------------------------

# Flags to describe a 'prerelease' version.
NO_PRERELEASE_CFLAGS = -Dgmic_prerelease="\\\"`date +%m%d%y`\\\""

# Flags that are mandatory to compile 'gmic'.
MANDATORY_CFLAGS = -Dgmic_build -Dcimg_use_zlib `pkg-config --cflags zlib || echo -I$(USR)/$(INCLUDE)` $(PRERELEASE_CFLAGS)
MANDATORY_LIBS = `pkg-config --libs zlib || echo -lz`
ifndef NO_SRIPDLIB
MANDATORY_CFLAGS += -std=c++11
endif
MANDATORY_LIBS += -L$(USR)/$(LIB)
ifeq ($(notdir $(CXX)),g++)
MANDATORY_CFLAGS += -Wall -W
MANDATORY_LIBS += -lm
endif
ifeq ($(OS),Unix)
MANDATORY_CFLAGS += -Dcimg_use_vt100
endif
ifeq ($(OS),Darwin)
ifndef NO_STDLIB
MANDATORY_CFLAGS += -stdlib=libc++
endif
endif
ifeq ($(OSTYPE),msys)
MANDATORY_LIBS = -Wl,--stack,16777216
endif

# Flags to enable debugging.
DEBUG_CFLAGS = -ansi -pedantic -Dcimg_verbosity=3 -g -fsanitize=address # -fsanitize=thread # -fsanitize=undefined #

# Flags to enable optimizations.
ifeq ($(notdir $(CXX)),g++)
OPT_CFLAGS = -O2 -mtune=generic
else
ifeq ($(notdir $(CXX)),icpc)
OPT_CFLAGS = -fast
else
OPT_CFLAGS = -O2
endif
endif

# Flags to enable parallel processing.
PARALLEL_CFLAGS = -Dgmic_is_parallel
ifneq ($(OSTYPE),msys)
PARALLEL_LIBS = -lpthread
endif

# Flags to enable extra checking of image buffer pointers.
ifneq ($(OS),Darwin)
CHECKIMAGE_CFLAGS = -Dgmic_check_image
endif

# Flags to enable more cancellation points in CImg library methods.
# (may slow down the code a little bit).
CIMG_ABORT_CFLAGS = -Dcimg_use_abort

# Flags to enable parallelization using OpenMP.
OPENMP_CFLAGS = -fopenmp -Dcimg_use_openmp
OPENMP_LIBS = -lgomp

# Flags to enable image display, using X11
# (keep /usr/ dirname here since X11 is located in /usr/ on Mac too).
# This requires the presence of the X11 include and library files.
ifneq ($(OS),Darwin)
X11_CFLAGS = -Dcimg_display=1 -Dcimg_appname=\\\"gmic\\\" `pkg-config --cflags x11 || echo -I/usr/X11R6/include` #-Dcimg_use_xrandr
X11_LIBS = `pkg-config --libs x11 || echo -L/usr/X11R6/lib -lX11` -lpthread #`pkg-config --libs xrandr || echo -lXrandr`
else
ifeq (,$(wildcard /usr/X11R6))
X11_CFLAGS = -Dcimg_display=0 -Dcimg_appname=\\\"gmic\\\" #-Dcimg_use_xrandr
X11_LIBS = -lpthread #`pkg-config --libs xrandr || echo -lXrandr`
else
X11_CFLAGS = -Dcimg_display=1 -Dcimg_appname=\\\"gmic\\\" `pkg-config --cflags x11 || echo -I/usr/X11R6/include` #-Dcimg_use_xrandr
X11_LIBS = -L/usr/X11R6/lib -lX11 -lpthread #`pkg-config --libs xrandr || echo -lXrandr`
endif
endif
# Flags to enable fast display, using XShm.
# This requires the presence of the X11 extension include and library files.
XSHM_CFLAGS = -Dcimg_use_xshm `pkg-config --cflags xcb-shm`
XSHM_LIBS = `pkg-config --libs xcb-shm || echo -L$(USR)/X11R6/lib -lXext`

# Flags to enable image display, using GDI32.
# This requires the presence of the GDI32 include and library files.
GDI32_CFLAGS = -Dcimg_display=2 -Dcimg_appname=\\\"gmic\\\"
GDI32_LIBS = -lgdi32

# Flags to enable native support for PNG image files, using the PNG library.
# This requires the presence of the libpng include and library files.
ifneq ($(OS),Darwin)
PNG_CFLAGS = -Dcimg_use_png `pkg-config --cflags libpng`
PNG_LIBS = `pkg-config --libs libpng || echo -lpng -lz`
else
ifeq (,$(wildcard /tmp/skl))
PNG_CFLAGS = -Dcimg_use_png `pkg-config --cflags libpng`
PNG_LIBS = `pkg-config --libs libpng || echo -lpng -lz`
else
PNG_CFLAGS = -Dcimg_use_png
PNG_LIBS = -lpng -lz
endif
endif

# Flags to enable native support for JPEG image files, using the JPEG library.
# This requires the presence of the libjpeg include and library files.
JPEG_CFLAGS = -Dcimg_use_jpeg
JPEG_LIBS = -ljpeg

# Flags to enable native support for TIFF image files, using the TIFF library.
# This requires the presence of the libtiff include and library files.
TIFF_CFLAGS = -Dcimg_use_tiff `pkg-config --cflags libtiff-4`
TIFF_LIBS = `pkg-config --libs libtiff-4 || echo -ltiff`

# Flags to enable native support for MINC2 image files, using the MINC2 library.
# ( http://en.wikibooks.org/wiki/MINC/Reference/MINC2.0_Users_Guide )
MINC2_CFLAGS = -Dcimg_use_minc2 -I${HOME}/local/include
MINC2_LIBS = -lminc_io -lvolume_io2 -lminc2 -lnetcdf -lhdf5 -lz -L${HOME}/local/lib

# Flags to enable native support for downloading files from the network.
# ( http://curl.haxx.se/libcurl/ )
CURL_CFLAGS = -Dcimg_use_curl `pkg-config --cflags libcurl`
CURL_LIBS = `pkg-config --libs libcurl || echo -lcurl`

# Flags to enable native support of webcams and video streaming, using the OpenCV library.
# This requires the presence of the OpenCV include and library files.
OPENCV_CFLAGS = -Dcimg_use_opencv  `pkg-config opencv --cflags || echo -I/usr/include/opencv` -I/usr/include/opencv
OPENCV_LIBS = `pkg-config opencv --libs || echo -lopencv_core -lopencv_highgui`

# Flags to enable native support of most classical image file formats, using the GraphicsMagick++ library.
# This requires the presence of the GraphicsMagick++ include and library files.
MAGICK_CFLAGS = -Dcimg_use_magick `pkg-config --cflags GraphicsMagick++ || echo -I$(USR)/$(INCLUDE)/GraphicsMagick`
MAGICK_LIBS = `pkg-config --libs GraphicsMagick++ || echo -lGraphicsMagick++`

# Flags to enable native support of EXR file format, using the OpenEXR library/
# This requires the presence of the OpenEXR include and library files.
EXR_CFLAGS = -Dcimg_use_openexr -I$(USR)/$(INCLUDE)/OpenEXR
EXR_LIBS = -lIlmImf -lHalf

# Flags to enable the use of the FFTW3 library.
# This requires the presence of the FFTW3 include and library files.
FFTW_CFLAGS = -Dcimg_use_fftw3 `pkg-config --cflags fftw3`
FFTW_LIBS = `pkg-config --libs fftw3 || echo -lfftw3`
ifneq ($(OSTYPE),msys)
FFTW_LIBS += -lfftw3_threads
endif

# Flags to enable the use of the BOARD library.
# This requires the presence of the BOARD include and library files.
BOARD_CFLAGS = -Dcimg_use_board
BOARD_LIBS = -lboard

#---------------------------------------------------------
# Predefine sets of flags to build default configurations.
#---------------------------------------------------------

# CLI interface: Standard build.
#-------------------------------
STD_CLI_CFLAGS = $(MANDATORY_CFLAGS) $(CIMG_ABORT_CFLAGS) $(PNG_CFLAGS) $(JPEG_CFLAGS) $(TIFF_CFLAGS) $(CURL_CFLAGS) $(FFTW_CFLAGS)
STD_CLI_LIBS = $(MANDATORY_LIBS) $(PNG_LIBS) $(JPEG_LIBS) $(TIFF_LIBS) $(CURL_LIBS) $(FFTW_LIBS)
ifeq ($(OS),Unix) # Unix.
STD_CLI_CFLAGS += $(PARALLEL_CFLAGS) $(OPENMP_CFLAGS) $(X11_CFLAGS) $(EXR_CFLAGS) $(OPENCV_CFLAGS) # $(XSHM_CFLAGS) $(MAGICK_CFLAGS)
STD_CLI_LIBS += $(PARALLEL_LIBS) $(OPENMP_LIBS) $(X11_LIBS) $(EXR_LIBS) $(OPENCV_LIBS) # $(XSHM_LIBS) # $(MAGICK_LIBS)
else
ifeq ($(OS),Darwin) # MacOSX.
STD_CLI_CFLAGS += $(PARALLEL_CFLAGS) $(X11_CFLAGS) $(EXR_CFLAGS)
STD_CLI_LIBS += $(PARALLEL_LIBS) $(X11_LIBS) $(EXR_LIBS) $(OPT_LIBS)
else # Windows.
STD_CLI_CFLAGS += $(PARALLEL_CFLAGS) $(OPENMP_CFLAGS) $(GDI32_CFLAGS) $(OPENCV_CFLAGS)
STD_CLI_LIBS += $(PARALLEL_LIBS) $(OPENMP_LIBS) $(GDI32_LIBS) $(OPENCV_LIBS)
endif
endif

# CLI interface: Static build.
#-----------------------------
STATIC_CLI_PATH = $(USR)/${LIB}/x86_64-linux-gnu
STATIC_CLI_EXTRA =
STATIC_CLI_CFLAGS = $(MANDATORY_CFLAGS) $(CIMG_ABORT_CFLAGS) $(PARALLEL_CFLAGS) $(PNG_CFLAGS) $(JPEG_CFLAGS) $(ZLIB_CFLAGS) $(FFTW_CFLAGS) -Dcimg_display=0
STATIC_CLI_LIBS = $(PARALLEL_LIBS) \
	          $(STATIC_CLI_PATH)/libpng.a \
	          $(STATIC_CLI_PATH)/libjpeg.a \
                  $(STATIC_CLI_PATH)/libz.a \
                  $(STATIC_CLI_PATH)/libfftw3.a $(STATIC_CLI_PATH)/libfftw3_threads.a \
	          $(STATIC_CLI_EXTRA)

# GIMP interface: Standard build.
#--------------------------------
STD_GIMP_CFLAGS = $(MANDATORY_CFLAGS) $(CIMG_ABORT_CFLAGS) $(PNG_CFLAGS) $(CURL_CFLAGS) $(FFTW_CFLAGS) -Dcimg_use_rng
STD_GIMP_LIBS = $(MANDATORY_LIBS) $(PNG_LIBS) $(CURL_LIBS) $(FFTW_LIBS)
ifeq ($(OS),Unix) # Unix.
STD_GIMP_CFLAGS += $(PARALLEL_CFLAGS) $(OPENMP_CFLAGS) $(X11_CFLAGS)
STD_GIMP_LIBS += $(PARALLEL_LIBS) $(OPENMP_LIBS) $(X11_LIBS)
else
ifeq ($(OS),Darwin) # MaxOSX.
STD_GIMP_CFLAGS += $(PARALLEL_CFLAGS) $(X11_CFLAGS)
STD_GIMP_LIBS += $(PARALLEL_LIBS) $(X11_LIBS)
else # Windows.
STD_GIMP_CFLAGS += $(PARALLEL_CFLAGS) $(OPENMP_CFLAGS) $(GDI32_CFLAGS)
STD_GIMP_LIBS += -mwindows $(PARALLEL_LIBS) $(OPENMP_LIBS) $(GDI32_LIBS) -lpthread -DPSAPI_VERSION=1 -lpsapi
endif
endif

# Libgmic interface: Standard build.
#-----------------------------------
STD_LIB_CFLAGS = $(MANDATORY_CFLAGS) $(CIMG_ABORT_CFLAGS) $(PNG_CFLAGS) $(JPEG_CFLAGS) $(TIFF_CFLAGS) $(CURL_CFLAGS) $(FFTW_CFLAGS)
STD_LIB_LIBS = $(MANDATORY_LIBS) $(PNG_LIBS) $(JPEG_LIBS) $(TIFF_LIBS) $(CURL_LIBS) $(FFTW_LIBS)
ifeq ($(OS),Unix) # Unix.
STD_LIB_CFLAGS += $(PARALLEL_CFLAGS) $(OPENMP_CFLAGS) $(X11_CFLAGS)
STD_LIB_LIBS += $(PARALLEL_LIBS) $(OPENMP_LIBS) $(X11_LIBS)
else
ifeq ($(OS),Darwin) # MacOSX.
STD_LIB_CFLAGS += $(PARALLEL_CFLAGS) $(X11_CFLAGS)
STD_LIB_LIBS += $(PARALLEL_LIBS) $(X11_LIBS)
else # Windows.
STD_LIB_CFLAGS += $(PARALLEL_CFLAGS) $(OPENMP_CFLAGS) $(GDI32_CFLAGS)
STD_LIB_LIBS += $(PARALLEL_LIBS) $(OPENMP_LIBS) $(GDI32_LIBS)
endif
endif

# G'MIC Online interface: Standard build.
#----------------------------------------
STD_GMICOL_CFLAGS = $(MANDATORY_CFLAGS) $(PARALLEL_CFLAGS) $(PNG_CFLAGS) $(JPEG_CFLAGS) $(ZLIB_CFLAGS) $(FFTW_CFLAGS) -Dcimg_display=0
STD_GMICOL_LIBS = $(MANDATORY_LIBS) $(PARALLEL_LIBS) $(PNG_LIBS) $(JPEG_LIBS) $(ZLIB_LIBS) /usr/lib/x86_64-linux-gnu/libfftw3.a /usr/lib/x86_64-linux-gnu/libfftw3_threads.a

#--------------------------
# Define Makefile entries.
#--------------------------

# Main default entries.
all: CImg.h gmic_stdlib.h
ifeq ($(OS),Unix)
	@echo "**"
	@echo "** Start building G'MIC with default Unix configuration."
	@echo "**"
	$(MAKE) cli gimp lib zart
else
ifeq ($(OS),Darwin)
	@echo "**"
	@echo "** Start building G'MIC with default MacOSX configuration."
	@echo "**"
	$(MAKE) cli gimp lib zart
else
	@echo "**"
	@echo "** Start building G'MIC with default Windows configuration."
	@echo "**"
	$(MAKE) cli gimp
endif
endif

cli:
	$(MAKE) "CFLAGS+=$(STD_CLI_CFLAGS) $(OPT_CFLAGS)" "LIBS+=$(STD_CLI_LIBS)" gmic
	$(STRIP) gmic$(EXE)

cli_s:
ifeq ($(OS),Darwin)
	c++ -o gmic gmic.cpp -Dgmic_main -Dgmic_build -Dcimg_use_zlib -I/opt/local/include  -Dgmic_prerelease=\"011316\" -std=c++11 -stdlib=libc++ -Dcimg_use_abort -Dcimg_use_png -Dcimg_use_jpeg -Dcimg_use_tiff -I/opt/local/include  -Dcimg_use_curl -I/opt/local/include  -Dcimg_use_fftw3 -I/opt/local/include  -Dgmic_is_parallel -Dcimg_display=1 -Dcimg_appname=\"gmic\" -I/opt/local/include -O2 -mmacosx-version-min=10.7 -L/tmp/skl/Gimp.app/Contents/Resources/lib -lpng -lz -ljpeg  -ltiff -lcurl -lfftw3  -lfftw3_threads -lpthread -lHalf -L/usr/X11R6/lib -lX11 -lpthread
	$(STRIP) gmic
endif

gimp:
	$(MAKE) "CFLAGS+=$(STD_GIMP_CFLAGS) $(OPT_CFLAGS)" "LIBS+=$(STD_GIMP_LIBS)" gmic_gimp

lib:
	$(MAKE) "CFLAGS+=$(STD_LIB_CFLAGS) $(OPT_CFLAGS)" "LIBS+=$(STD_LIB_LIBS)" libgmic

gmicol:
	$(MAKE) "CFLAGS+=$(STD_GMICOL_CFLAGS) $(OPT_CFLAGS)" "LIBS+=$(STD_GMICOL_LIBS)" gmic
	$(STRIP) gmic$(EXE)

static:
	$(MAKE) "CFLAGS+=$(STATIC_CLI_CFLAGS) $(OPT_CFLAGS)" "LIBS+=$(STATIC_CLI_LIBS)" gmic
	$(STRIP) gmic$(EXE)

debug:
	$(MAKE) "CFLAGS+=$(STD_CLI_CFLAGS) $(DEBUG_CFLAGS)" "LIBS+=$(STD_CLI_LIBS)" gmic

zart:
ifeq ($(OS),Darwin)
	cd ../zart && qmake zart.pro && $(MAKE) && $(STRIP) zart.app/Contents/MacOS/zart
else
	cd ../zart && qmake zart.pro && $(MAKE) && $(STRIP) zart
endif

# Internal rules to build compilation modules.
libgmic.o: gmic.cpp gmic.h gmic_stdlib.h CImg.h
	$(CXX) -o libgmic.o -c gmic.cpp -fPIC $(CFLAGS)

libgmic: libgmic.o gmic_use_lib.cpp
	ar rcs libgmic.a libgmic.o
ifeq ($(OS),Darwin)
	$(CXX) -shared -o libgmic.so libgmic.o $(LIBS)
else
	$(CXX) -shared -Wl,-soname,libgmic.so.1 -o libgmic.so libgmic.o $(LIBS)
	$(CXX) -o gmic_use_lib gmic_use_lib.cpp -L. -lgmic
endif

gmic_gimp.o: gmic.cpp gmic.h gmic_stdlib.h CImg.h
	$(CXX) -o gmic_gimp.o -c gmic.cpp -Dgmic_gimp $(CFLAGS)

gmic_gimp: gmic_gimp.o gmic_gimp.cpp
ifeq ($(OS),Darwin)
ifeq (,$(wildcard /tmp/skl))
	$(CXX) -o gmic_gimp gmic_gimp.cpp gmic_gimp.o -Dgmic_gimp `gimptool-2.0$(EXE) --cflags` $(CFLAGS) `gimptool-2.0$(EXE) --libs` $(LIBS)
else
	$(CXX) -o gmic_gimp gmic_gimp.cpp gmic_gimp.o -Dgmic_gimp `gimptool-2.0$(EXE) --cflags` $(CFLAGS) $(subst /opt/local,/tmp/skl/Gimp.app/Contents/Resources,$(shell gimptool-2.0$(EXE) --libs) $(LIBS))
endif
else
	$(CXX) -o gmic_gimp gmic_gimp.cpp gmic_gimp.o -Dgmic_gimp `gimptool-2.0$(EXE) --cflags` $(CFLAGS) `gimptool-2.0$(EXE) --libs` $(LIBS)
endif
	$(STRIP) gmic_gimp$(EXE)

gmic: gmic.cpp gmic.h gmic_stdlib.h CImg.h
	$(CXX) -o gmic gmic.cpp -Dgmic_main $(CFLAGS) $(LIBS)

gmic_stdlib.h:
	@echo -n "> Retrieve G'MIC Standard Library..."
	@$(WGET) gmic_stdlib.h http://gmic.eu/gmic_stdlib.h
	@touch gmic_stdlib.h
	@echo " done!"
CImg.h:
	@echo -n "> Retrieve CImg Library..."
	@if [ -f ../../CImg/CImg.h ]; then if [ ! -f ./CImg.h ]; then ln -s ../../CImg/CImg.h .; fi; else $(WGET) CImg.h https://github.com/dtschump/CImg/blob/master/CImg.h?raw=true; touch CImg.h; fi
	@echo " done!"

# Generate gmic_stdlib.h file (requires 'gmic' to be installed first).
stdlib:
	@echo "/*\n\
#\n\
#  File        : gmic_stdlib.h\n\
#                ( C++ header file )\n\
#\n\
#  Description : This file defines compressed buffers containing the command\n\
#                definitions of the G'MIC Standard Library, as well as the\n\
#                default filters in the G'MIC plug-in for GIMP.\n\
#                This file has been automatically generated by Makefile entry\n\
#                'stdlib:' (mainly from the G'MIC command file 'gmic_stdlib.gmic').\n\
#                ( http://gmic.eu )\n\
#\n\
#  Copyright   : David Tschumperle\n\
#                ( http://tschumperle.users.greyc.fr/ )\n\
#\n\
#  License     : CeCILL v2.0\n\
#                ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )\n\
#\n\
#  This software is governed by the CeCILL  license under French law and\n\
#  abiding by the rules of distribution of free software.  You can  use,\n\
#  modify and/ or redistribute the software under the terms of the CeCILL\n\
#  license as circulated by CEA, CNRS and INRIA at the following URL\n\
#  \"http://www.cecill.info\".\n\
#\n\
#  As a counterpart to the access to the source code and  rights to copy,\n\
#  modify and redistribute granted by the license, users are provided only\n\
#  with a limited warranty  and the software's author,  the holder of the\n\
#  economic rights,  and the successive licensors  have only  limited\n\
#  liability.\n\
#\n\
#  In this respect, the user's attention is drawn to the risks associated\n\
#  with loading,  using,  modifying and/or developing or reproducing the\n\
#  software by the user in light of its specific status of free software,\n\
#  that may mean  that it is complicated to manipulate,  and  that  also\n\
#  therefore means  that it is reserved for developers  and  experienced\n\
#  professionals having in-depth computer knowledge. Users are therefore\n\
#  encouraged to load and test the software's suitability as regards their\n\
#  requirements in conditions enabling the security of their systems and/or\n\
#  data to be ensured and,  more generally, to use and operate it in the\n\
#  same conditions as regards security.\n\
#\n\
#  The fact that you are presently reading this means that you have had\n\
#  knowledge of the CeCILL license and that you accept its terms.\n\
#\n\
*/\n" > gmic_stdlib.h
	@echo "#ifndef gmic_gimp" >> gmic_stdlib.h
	@\gmic gmic_stdlib.gmic raw:gmic_stdlib.gmic,char -compress_gmic 1 -a y -serialize char,1,0 -o -.h,uchar | sed 's/unsigned char/const unsigned char/' | sed 's/unnamed/gmic_stdlib/' >> gmic_stdlib.h
	@echo "#else" >> gmic_stdlib.h
	@\gmic gmic_stdlib.gmic -update_server \$$_version,0 raw:$(HOME)/.config/gmic/gimp_update\$$_version.gmic,char 1 -a y -serialize char,1,0 -o -.h,uchar | sed 's/unsigned char/const unsigned char/' | sed 's/unnamed/gmic_stdlib/' >> gmic_stdlib.h
	@\gmic -v - ../html/img/logoGMIC.ppm -permute cxyz -serialize uchar,1,0 -o -.h,uchar | sed 's/unsigned char/const unsigned char/' | sed 's/unnamed/gmic_logo/' >> gmic_stdlib.h
	@echo "const unsigned long size_data_gmic_logo = (unsigned long)sizeof(data_gmic_logo);" >> gmic_stdlib.h
	@echo "#endif" >> gmic_stdlib.h
	@echo "const unsigned long size_data_gmic_stdlib = (unsigned long)sizeof(data_gmic_stdlib);" >> gmic_stdlib.h
	@echo >>gmic_stdlib.h
	@\gmic -v - -_update_server_upload gmic_stdlib.h

# Generate bash completion script (requires 'gmic' to be installed first).
bashcompletion:
	@mkdir -p ../resources
	@\gmic -v - gmic_stdlib.gmic raw:gmic_stdlib.gmic,uchar -document_gmic bash 2> ../resources/gmic_bashcompletion.sh

# Generate man page (requires 'gmic' to be installed first).
man:
	@mkdir -p ../man
	@\gmic -v - gmic_stdlib.gmic raw:gmic_stdlib.gmic,uchar -__help man 2> ../man/gmic.1
	@gzip -f ../man/gmic.1

# Install/uninstall/clean procedures.
install:
	mkdir -p $(DESTDIR)$(PLUGINDIR)/
	cp -f gmic_gimp $(DESTDIR)$(PLUGINDIR)/
	mkdir -p $(DESTDIR)$(USR)/$(BIN)/
	cp -f gmic $(DESTDIR)$(USR)/$(BIN)/
	mkdir -p $(DESTDIR)$(USR)/$(INCLUDE)/
	cp -f gmic.h $(DESTDIR)$(USR)/$(INCLUDE)/

ifneq ($(OS),Darwin)
	mkdir -p $(DESTDIR)$(USR)/share
	mkdir -p $(DESTDIR)$(USR)/$(LIB)
	cp -f libgmic.so $(DESTDIR)$(USR)/$(LIB)/libgmic.so.1.6.9
	ln -fs libgmic.so.1.6.9 $(DESTDIR)$(USR)/$(LIB)/libgmic.so.1
	ln -fs libgmic.so.1 $(DESTDIR)$(USR)/$(LIB)/libgmic.so
	cp -f ../zart/zart $(DESTDIR)$(USR)/$(BIN)/
endif
	mkdir -p $(DESTDIR)$(USR)/share/man/
	mkdir -p $(DESTDIR)$(USR)/share/man/man1/
	mkdir -p $(DESTDIR)$(USR)/share/man/fr/man1/
	cp -f ../man/gmic.1.gz $(DESTDIR)$(USR)/share/man/man1/gmic.1.gz
	cp -f ../man/gmic.1.gz $(DESTDIR)$(USR)/share/man/fr/man1/gmic.1.gz
	if [ -d /etc/bash_completion.d/ ]; then mkdir -p $(DESTDIR)/etc/bash_completion.d/; cp -f ../resources/gmic_bashcompletion.sh $(DESTDIR)/etc/bash_completion.d/gmic; fi
	if [ -d /opt/local/etc/bash_completion.d/ ]; then mkdir -p $(DESTDIR)/opt/local/etc/bash_completion.d/; cp -f ../resources/gmic_bashcompletion.sh $(DESTDIR)/opt/local/etc/bash_completion.d/gmic; fi

uninstall:
	rm -f $(DESTDIR)$(USR)/$(BIN)/gmic
	rm -f $(DESTDIR)$(USR)/$(BIN)/zart
	rm -f $(DESTDIR)$(USR)/$(INCLUDE)/gmic.h
	rm -f $(DESTDIR)$(USR)/$(LIB)/libgmic.so.1.6.9
	rm -f $(DESTDIR)$(USR)/$(LIB)/libgmic.so.1
	rm -f $(DESTDIR)$(USR)/$(LIB)/libgmic.so
	rm -rf $(DESTDIR)$(USR)/share/doc/gmic/
	rm -f $(DESTDIR)$(USR)/share/man/man1/gmic.1.gz
	rm -f $(DESTDIR)$(USR)/share/man/fr/man1/gmic.1.gz

distclean: clean

clean:
	rm -rf gmic*.o gmic$(EXE) gmic_gimp$(EXE) gmic_use_lib$(EXE) libgmic* *~

# End of Makefile.
