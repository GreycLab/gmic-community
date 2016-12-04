PLUGINNAME = GMIC_OFX
PLUGINOBJECTS = ../gmic_plugin.o

SRCDIR = ../../
PATHTOROOT = $(SRCDIR)/ThirdParty/OpenFX/Examples
include Makefile.master

RESOURCES = GMIC_OFX.png

CXXFLAGS += \
-I$(SRCDIR)/Helpers \
-I$(SRCDIR)/ThirdParty/GMIC/src \
-I$(SRCDIR)/ThirdParty/OpenFX/include \
-I$(SRCDIR)/ThirdParty/OpenFX/Examples/include

LINKFLAGS += \
-lcgmic \
-L$(SRCDIR)/ThirdParty/GMIC

VPATH += \
$(SRCDIR)/ThirdParty/GMIC \
$(SRCDIR)/Helpers
