TEMPLATE = app

QT       += core gui xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG	+= qt
CONFIG	+= warn_on
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv fftw3 zlib
# LIBS += -lfftw3_threads
DEFINES += cimg_use_fftw3 cimg_use_zlib

isEmpty(GMIC_PATH) {
  GMIC_PATH = ../../gmic/src/
}
message( GMIC_PATH is $$GMIC_PATH )

unix {
   VERSION = $$system(grep \"define.ZART_VERSION \" include/Common.h | sed -e \"s/.*VERSION //\")
}

isEmpty( VERSION ):{
   VERSION = 0.0.0
   message( Warning: VERSION was not found in include/Common.h. Set to $$VERSION )
}

# enable OpenMP by default on with g++, except on OS X
!macx:*g++* {
    CONFIG += openmp
}

!win32 {
 LIBS += -lfftw3_threads
}

# use qmake CONFIG+=openmp ... to force using openmp
# For example, on OS X with GCC 4.8 installed:
# qmake -spec unsupported/macx-clang QMAKE_CXX=g++-4.8 QMAKE_LINK=g++-4.8 CONFIG+=openmp
# Notes:
#  - the compiler name is g++-4.8 on Homebrew and g++-mp-4.8 on MacPorts
#  - we use the unsupported/macx-clang config because macx-g++ uses arch flags that are not recognized by GNU GCC
openmp {
    DEFINES += cimg_use_openmp
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_LFLAGS += -fopenmp
}

# use qmake CONFIG+=enable_dynamic_linking ... to link against libgmic.so
CONFIG(enable_dynamic_linking) {
    isEmpty(GMIC_LIB_PATH) {
	GMIC_LIB_PATH = $$GMIC_PATH/..
    }
    LIBS += -L$$GMIC_LIB_PATH -lgmic
} else {
    # compile our own version of gmic, with the same cimg_* flags as zart
    #LIBS += $$GMIC_PATH/libgmic.a
    SOURCES += $$GMIC_PATH/gmic.cpp
}

DEFINES += gmic_build gmic_is_parallel cimg_use_abort

INCLUDEPATH += $$PWD $$PWD/include $$PWD/$$GMIC_PATH/

DEPENDPATH += $$PWD/include

HEADERS	+= $$GMIC_PATH/gmic.h \
    $$GMIC_PATH/gmic_stdlib.h \
    $$GMIC_PATH/CImg.h \
    include/ImageView.h \
    include/MainWindow.h \
    include/FilterThread.h \
    include/CommandEditor.h \
    include/DialogAbout.h \
    include/ImageConverter.h \
    include/DialogLicense.h \
    include/ImageSource.h \
    include/WebcamSource.h \
    include/StillImageSource.h \
    include/VideoFileSource.h \
    include/Common.h \
    include/TreeWidgetPresetItem.h \
    include/AbstractParameter.h \
    include/IntParameter.h \
    include/CommandParamsWidget.h \
    include/SeparatorParameter.h \
    include/NoteParameter.h \
    include/FloatParameter.h \
    include/BoolParameter.h \
    include/ChoiceParameter.h \
    include/ColorParameter.h \
    include/CriticalRef.h \
    include/FullScreenWidget.h \
    include/FileParameter.h \
    include/FolderParameter.h \
    include/TextParameter.h \
    include/LinkParameter.h \
    include/ConstParameter.h \
    include/OutputWindow.h

SOURCES	+= \
    src/ImageView.cpp \
    src/MainWindow.cpp \
    src/ZArt.cpp \
    src/FilterThread.cpp \
    src/DialogAbout.cpp \
    src/CommandEditor.cpp \
    src/ImageConverter.cpp \
    src/DialogLicense.cpp \
    src/ImageSource.cpp \
    src/WebcamSource.cpp \
    src/StillImageSource.cpp \
    src/VideoFileSource.cpp \
    src/TreeWidgetPresetItem.cpp \
    src/AbstractParameter.cpp \
    src/IntParameter.cpp \
    src/CommandParamsWidget.cpp \
    src/SeparatorParameter.cpp \
    src/NoteParameter.cpp \
    src/FloatParameter.cpp \
    src/BoolParameter.cpp \
    src/ChoiceParameter.cpp \
    src/ColorParameter.cpp \
    src/FullScreenWidget.cpp \
    src/FileParameter.cpp \
    src/FolderParameter.cpp \
    src/TextParameter.cpp \
    src/LinkParameter.cpp \
    src/ConstParameter.cpp \
    src/OutputWindow.cpp

RESOURCES = zart.qrc
DEPENDPATH += $$PWD/images

FORMS = ui/MainWindow.ui \
    ui/DialogAbout.ui \
    ui/DialogLicense.ui \
    ui/FullScreenWidget.ui \
    ui/OutputWindow.ui

PRE_TARGETDEPS +=

CONFIG(release, debug|release) {
    message(Release build)
    DEFINES += QT_NO_DEBUG_OUTPUT
#    QMAKE_CXXFLAGS += -ffast-math
}

CONFIG(debug, debug|release) {
    message(Debug build)
    DEFINES += _ZART_DEBUG_
    QMAKE_CXXFLAGS_DEBUG += -fsanitize=address -Dcimg_verbosity=3
    QMAKE_LFLAGS_DEBUG +=  -fsanitize=address
}

UI_DIR = .ui
MOC_DIR = .moc
RCC_DIR = .qrc
OBJECTS_DIR = .obj

unix:!macx { DEFINES += _IS_UNIX_ }

macx {  DEFINES += _IS_MACOS_ }

DEFINES += cimg_display=0

#QMAKE_LIBS =
#QMAKE_LFLAGS_DEBUG = -lcxcore -lcv -lhighgui -lml
#QMAKE_LFLAGS_RELEASE = -lcxcore -lcv -lhighgui -lml
