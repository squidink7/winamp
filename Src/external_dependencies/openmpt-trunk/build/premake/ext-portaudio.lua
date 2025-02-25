                
                project "portaudio"
                uuid "189B867F-FF4B-45A1-B741-A97492EE69AF"
                language "C"
                location ( "../../build/" .. mpt_projectpathname .. "/ext" )
                mpt_projectname = "portaudio"
                dofile "../../build/premake/premake-defaults-LIBorDLL.lua"
                dofile "../../build/premake/premake-defaults.lua"
                targetname "openmpt-portaudio"
                includedirs { "../../include/portaudio/include", "../../include/portaudio/src/common", "../../include/portaudio/src/os/win" }
			filter {}
			filter { "action:vs*" }
		characterset "Unicode"
			filter {}
		if _OPTIONS["winxp"] then
	defines {
"PA_USE_ASIO=0",
"PA_USE_DS=1",
"PA_USE_WMME=1",
"PA_USE_WASAPI=1",
"PA_USE_WDMKS=0",
	}
		elseif _OPTIONS["uwp"] then
	defines {
"PA_USE_ASIO=0",
"PA_USE_DS=0",
"PA_USE_WMME=0",
"PA_USE_WASAPI=1",
"PA_USE_WDMKS=0",
	}
		else
	defines {
"PAWIN_USE_WDMKS_DEVICE_INFO",
"PA_WDMKS_NO_KSGUID_LIB",
"PA_USE_ASIO=0",
"PA_USE_DS=0",
"PA_USE_WMME=1",
"PA_USE_WASAPI=1",
"PA_USE_WDMKS=1",
	}
		end
			filter {}
                files {
                "../../include/portaudio/src/common/pa_allocation.c",
                "../../include/portaudio/src/common/pa_allocation.h",
                "../../include/portaudio/src/common/pa_converters.c",
                "../../include/portaudio/src/common/pa_converters.h",
                "../../include/portaudio/src/common/pa_cpuload.c",
                "../../include/portaudio/src/common/pa_cpuload.h",
                "../../include/portaudio/src/common/pa_debugprint.c",
                "../../include/portaudio/src/common/pa_debugprint.h",
                "../../include/portaudio/src/common/pa_dither.c",
                "../../include/portaudio/src/common/pa_dither.h",
                "../../include/portaudio/src/common/pa_endianness.h",
                "../../include/portaudio/src/common/pa_front.c",
                "../../include/portaudio/src/common/pa_gitrevision.h",
                "../../include/portaudio/src/common/pa_hostapi.h",
                "../../include/portaudio/src/common/pa_memorybarrier.h",
                "../../include/portaudio/src/common/pa_process.c",
                "../../include/portaudio/src/common/pa_process.h",
                "../../include/portaudio/src/common/pa_ringbuffer.c",
                "../../include/portaudio/src/common/pa_ringbuffer.h",
                "../../include/portaudio/src/common/pa_stream.c",
                "../../include/portaudio/src/common/pa_stream.h",
                "../../include/portaudio/src/common/pa_trace.c",
                "../../include/portaudio/src/common/pa_trace.h",
                "../../include/portaudio/src/common/pa_types.h",
                "../../include/portaudio/src/common/pa_util.h",
                "../../include/portaudio/src/hostapi/skeleton/pa_hostapi_skeleton.c",
                "../../include/portaudio/src/os/win/pa_win_coinitialize.c",
                "../../include/portaudio/src/os/win/pa_win_coinitialize.h",
                "../../include/portaudio/src/os/win/pa_win_hostapis.c",
                "../../include/portaudio/src/os/win/pa_win_util.c",
                "../../include/portaudio/src/os/win/pa_win_waveformat.c",
                "../../include/portaudio/src/os/win/pa_x86_plain_converters.c",
                "../../include/portaudio/src/os/win/pa_x86_plain_converters.h",
                }
			filter {}
		if _OPTIONS["winxp"] then
	files {
"../../include/portaudio/src/hostapi/wmme/pa_win_wmme.c",
"../../include/portaudio/src/hostapi/dsound/pa_win_ds.c",
"../../include/portaudio/src/hostapi/dsound/pa_win_ds_dynlink.c",
"../../include/portaudio/src/hostapi/dsound/pa_win_ds_dynlink.h",
"../../include/portaudio/src/hostapi/wasapi/pa_win_wasapi.c",
	}
		elseif _OPTIONS["uwp"] then
	files {
"../../include/portaudio/src/hostapi/wasapi/pa_win_wasapi.c",
	}
		else
	files {
"../../include/portaudio/src/hostapi/wmme/pa_win_wmme.c",
"../../include/portaudio/src/hostapi/wasapi/pa_win_wasapi.c",
"../../include/portaudio/src/hostapi/wdmks/pa_win_wdmks.c",
"../../include/portaudio/src/os/win/pa_win_wdmks_utils.c",
"../../include/portaudio/src/os/win/pa_win_wdmks_utils.h",
	}
		end
			filter {}
                files {
                "../../include/portaudio/include/pa_asio.h",
                "../../include/portaudio/include/pa_jack.h",
                "../../include/portaudio/include/pa_linux_alsa.h",
                "../../include/portaudio/include/pa_mac_core.h",
                "../../include/portaudio/include/pa_win_ds.h",
                "../../include/portaudio/include/pa_win_wasapi.h",
                "../../include/portaudio/include/pa_win_waveformat.h",
                "../../include/portaudio/include/pa_win_wdmks.h",
                "../../include/portaudio/include/pa_win_wmme.h",
                "../../include/portaudio/include/portaudio.h",
                }
                filter { "action:vs*" }
            buildoptions { "/wd4018", "/wd4091", "/wd4267", "/wd4312" }
                filter {}
                filter { "action:vs*" }
            buildoptions { "/wd6001", "/wd6011", "/wd6053", "/wd6216", "/wd6217", "/wd6255", "/wd6258", "/wd6385", "/wd6386", "/wd6387", "/wd28159" } -- /analyze
                filter {}
                filter { "action:vs*" }
                files { "../../build/premake/lnk/ext-portaudio.c" }
                filter {}
                filter { "configurations:Debug" }
                defines { "PA_ENABLE_DEBUG_OUTPUT" }
                filter { "configurations:DebugShared" }
                defines { "PA_ENABLE_DEBUG_OUTPUT" }
                filter { "configurations:DebugMDd" }
                defines { "PA_ENABLE_DEBUG_OUTPUT" }
                filter { "kind:SharedLib" }
			if _OPTIONS["winxp"] then
		files { "../../build/premake/def/ext-portaudio-retro.def" }
			else
		files { "../../include/portaudio/build/msvc/portaudio.def" }
			end
                filter {}
				