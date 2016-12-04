#include "AEConfig.h"
#include "AE_EffectVers.h"

#define PIPL
#include "gmic_plugin.cpp"
#undef PIPL

#ifndef BUG_VERSION
#define BUG_VERSION 0
#endif

#define PF_OutFlag_NONE 0
#define PF_OutFlag_KEEP_RESOURCE_OPEN				(1 << 0)
#define PF_OutFlag_WIDE_TIME_INPUT					(1 << 1)
#define PF_OutFlag_NON_PARAM_VARY					(1 << 2)
#define PF_OutFlag_RESERVED6						(1 << 3)
#define PF_OutFlag_SEQUENCE_DATA_NEEDS_FLATTENING	(1 << 4)
#define PF_OutFlag_I_DO_DIALOG						(1 << 5)
#define PF_OutFlag_USE_OUTPUT_EXTENT				(1 << 6)
#define PF_OutFlag_SEND_DO_DIALOG					(1 << 7)
#define PF_OutFlag_DISPLAY_ERROR_MESSAGE			(1 << 8)
#define PF_OutFlag_I_EXPAND_BUFFER					(1 << 9)
#define PF_OutFlag_PIX_INDEPENDENT					(1 << 10)
#define PF_OutFlag_I_WRITE_INPUT_BUFFER				(1 << 11)
#define PF_OutFlag_I_SHRINK_BUFFER					(1 << 12)
#define PF_OutFlag_WORKS_IN_PLACE					(1 << 13)
#define PF_OutFlag_RESERVED8						(1 << 14)
#define PF_OutFlag_CUSTOM_UI						(1 << 15)
#define PF_OutFlag_RESERVED7						(1 << 16)
#define PF_OutFlag_REFRESH_UI						(1 << 17)
#define PF_OutFlag_NOP_RENDER						(1 << 18)
#define PF_OutFlag_I_USE_SHUTTER_ANGLE				(1 << 19)
#define PF_OutFlag_I_USE_AUDIO						(1 << 20)
#define PF_OutFlag_I_AM_OBSOLETE					(1 << 21)
#define PF_OutFlag_FORCE_RERENDER					(1 << 22)
#define PF_OutFlag_PiPL_OVERRIDES_OUTDATA_OUTFLAGS	(1 << 23)
#define PF_OutFlag_I_HAVE_EXTERNAL_DEPENDENCIES		(1 << 24)
#define PF_OutFlag_DEEP_COLOR_AWARE					(1 << 25)
#define PF_OutFlag_SEND_UPDATE_PARAMS_UI			(1 << 26)
#define PF_OutFlag_AUDIO_FLOAT_ONLY					(1 << 27)
#define PF_OutFlag_AUDIO_IIR						(1 << 28)
#define PF_OutFlag_I_SYNTHESIZE_AUDIO				(1 << 29)
#define PF_OutFlag_AUDIO_EFFECT_TOO					(1 << 30)
#define PF_OutFlag_AUDIO_EFFECT_ONLY				(1 << 31)
#define PF_OutFlag2_NONE 0
#define PF_OutFlag2_SUPPORTS_QUERY_DYNAMIC_FLAGS	(1 << 0)
#define PF_OutFlag2_I_USE_3D_CAMERA					(1 << 1)
#define PF_OutFlag2_I_USE_3D_LIGHTS					(1 << 2)
#define PF_OutFlag2_PARAM_GROUP_START_COLLAPSED_FLAG (1 << 3)
#define PF_OutFlag2_I_AM_THREADSAFE					(1 << 4)
#define PF_OutFlag2_CAN_COMBINE_WITH_DESTINATION	(1 << 5)
#define PF_OutFlag2_DOESNT_NEED_EMPTY_PIXELS		(1 << 6)
#define PF_OutFlag2_REVEALS_ZERO_ALPHA				(1 << 7)
#define PF_OutFlag2_PRESERVES_FULLY_OPAQUE_PIXELS	(1 << 8)
#define PF_OutFlag2_SUPPORTS_SMART_RENDER			(1 << 10)
#define PF_OutFlag2_RESERVED9						(1 << 11)
#define PF_OutFlag2_FLOAT_COLOR_AWARE				(1 << 12)
#define PF_OutFlag2_I_USE_COLORSPACE_ENUMERATION	(1 << 13)
#define PF_OutFlag2_I_AM_DEPRECATED					(1 << 14)
#define PF_OutFlag2_PPRO_DO_NOT_CLONE_SEQUENCE_DATA_FOR_RENDER	(1 << 15)
#define PF_OutFlag2_RESERVED10						(1 << 16)
#define PF_OutFlag2_AUTOMATIC_WIDE_TIME_INPUT		(1 << 17)
#define PF_OutFlag2_I_USE_TIMECODE					(1 << 18)
#define PF_OutFlag2_DEPENDS_ON_UNREFERENCED_MASKS	(1 << 19)
#define PF_OutFlag2_OUTPUT_IS_WATERMARKED			(1 << 20)

#ifndef AE_OS_WIN
#include "AE_General.r"
#endif

resource 'PiPL' (16000) {
	{	/* array properties: 12 elements */
		/* [1] */
		Kind {
			AEEffect
		},
		/* [2] */
		Name {
			PLUGIN_NAME
		},
		/* [3] */
		Category {
			PLUGIN_CATEGORY
		},
#ifdef AE_OS_WIN
	#ifdef AE_PROC_INTELx64
		CodeWin64X86 {"EntryPointFunc"},
	#else
		CodeWin32X86 {"EntryPointFunc"},
	#endif	
#else
	#ifdef AE_OS_MAC
		CodeMachOPowerPC {"EntryPointFunc"},
		CodeMacIntel32 {"EntryPointFunc"},
		CodeMacIntel64 {"EntryPointFunc"},
	#endif
#endif
		/* [6] */
		AE_PiPL_Version {
			2,
			0
		},
		/* [7] */
		AE_Effect_Spec_Version {
			PF_PLUG_IN_VERSION,
			PF_PLUG_IN_SUBVERS
		},
		/* [8] */
		AE_Effect_Version {
			(MAJOR_VERSION << 19) + (MINOR_VERSION << 15) + (BUG_VERSION << 11) + BUILD_VERSION
		},
		/* [9] */
		AE_Effect_Info_Flags {
			0
		},
		/* [10] */
		AE_Effect_Global_OutFlags {
			FX_OUT_FLAGS
		},
		AE_Effect_Global_OutFlags_2 {
			FX_OUT_FLAGS2
		},
		/* [11] */
		AE_Effect_Match_Name {
			PLUGIN_UNIQUEID
		},
		/* [12] */
		AE_Reserved_Info {
			8
		}
	}
};

