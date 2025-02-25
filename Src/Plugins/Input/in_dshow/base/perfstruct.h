	//------------------------------------------------------------------------------
	// File: PerfStruct.h
	//
	// Desc: Structures for DirectShow performance logging.
	//
	// Copyright (c) 2000-2001 Microsoft Corporation.  All rights reserved.
	//------------------------------------------------------------------------------
	
	
	#ifndef _PERFSTRUCT_H_
	#define _PERFSTRUCT_H_
	
	#include <wmistr.h>
	#include <evntrace.h>
	
	// {28CF047A-2437-4b24-B653-B9446A419A69}
	DEFINE_GUID(GUID_DSHOW_CTL,
	0x28cf047a, 0x2437, 0x4b24, 0xb6, 0x53, 0xb9, 0x44, 0x6a, 0x41, 0x9a, 0x69);
	
	// {D0DA7AD6-AE80-4de5-AAFC-C126711E7593}
	DEFINE_GUID(GUID_VIDEOREND,
	0xd0da7ad6, 0xae80, 0x4de5, 0xaa, 0xfc, 0xc1, 0x26, 0x71, 0x1e, 0x75, 0x93);
	
	// {DC70AC3E-93E5-48db-88AB-E42064EC276A}
	DEFINE_GUID(GUID_DSOUNDGLITCH,
	0xdc70ac3e, 0x93e5, 0x48db, 0x88, 0xab, 0xe4, 0x20, 0x64, 0xec, 0x27, 0x6a);
	
	// {3d7e7d93-2fc8-4a07-a719-e0922ff2899}
	DEFINE_GUID(GUID_STREAMTRACE,
	0x3d7e7d93, 0x2fc8, 0x4a07, 0xa7, 0x19, 0xe0, 0x92, 0x2f, 0xf2, 0x89, 0x9e);
	
	// AZFIX: the following GUIDs aren't useful right now.
	
	// {3C33F7F5-EE54-493c-BA25-1656539C05AC}
	DEFINE_GUID(GUID_GETTIME,
	0x3c33f7f5, 0xee54, 0x493c, 0xba, 0x25, 0x16, 0x56, 0x53, 0x9c, 0x5, 0xac);
	
	// {CC44B44D-8169-4952-9E4A-A4E13295E492}
	DEFINE_GUID(GUID_AUDIOREND,
	0xcc44b44d, 0x8169, 0x4952, 0x9e, 0x4a, 0xa4, 0xe1, 0x32, 0x95, 0xe4, 0x92);
	
	// {775D19BF-4D8B-4de6-8DC9-66BAC7B310A2}
	DEFINE_GUID(GUID_FRAMEDROP,
	0x775d19bf, 0x4d8b, 0x4de6, 0x8d, 0xc9, 0x66, 0xba, 0xc7, 0xb3, 0x10, 0xa2);
	
	// {56D29065-EFBE-42dc-8C29-E325DC9C27D5}
	DEFINE_GUID(GUID_AUDIOBREAK,
	0x56d29065, 0xefbe, 0x42dc, 0x8c, 0x29, 0xe3, 0x25, 0xdc, 0x9c, 0x27, 0xd5);
	
	// {E1E6EA87-95A8-497e-BFBA-0295AEBCC707}
	DEFINE_GUID(GUID_AUDIORECV,
	0xe1e6ea87, 0x95a8, 0x497e, 0xbf, 0xba, 0x2, 0x95, 0xae, 0xbc, 0xc7, 0x7);
	
	// {10F7768A-B1E7-4242-AD90-A2D44683D9F0}
	DEFINE_GUID(GUID_AUDIOSLAVE,
	0x10f7768a, 0xb1e7, 0x4242, 0xad, 0x90, 0xa2, 0xd4, 0x46, 0x83, 0xd9, 0xf0);
	
	// {8983803D-691A-49bc-8FF6-962A39C0198F}
	DEFINE_GUID(GUID_AUDIOADDBREAK,
	0x8983803d, 0x691a, 0x49bc, 0x8f, 0xf6, 0x96, 0x2a, 0x39, 0xc0, 0x19, 0x8f);
	
	#define GLITCHTYPE_DSOUNDFIRSTGOOD 0
	#define GLITCHTYPE_DSOUNDFIRSTBAD  1
	
	typedef struct PERFINFO_DSHOW_AUDIOGLITCH {
ULONGLONG   cycleCounter;
DWORD       glitchType;
LONGLONG   sampleTime;
LONGLONG   previousTime;
ULONG_PTR       instanceId;
	} PERFINFO_DSHOW_AUDIOGLITCH, *PPERFINFO_DSHOW_AUDIOGLITCH;
	
	typedef struct PERFINFO_WMI_AUDIOGLITCH {
EVENT_TRACE_HEADER          header;
PERFINFO_DSHOW_AUDIOGLITCH  data;
	} PERFINFO_WMI_AUDIO_GLITCH, *PPERFINFO_WMI_AUDIOGLITCH;
	
	typedef struct PERFINFO_DSHOW_GETTIME {
ULONGLONG    cycleCounter;
ULONGLONG    dshowClock;
	} PERFINFO_DSHOW_GETTIME, *PPERFINFO_DSHOW_GETTIME;
	
	typedef struct PERFINFO_WMI_GETTIME {
EVENT_TRACE_HEADER        header;
PERFINFO_DSHOW_GETTIME    data;
	} PERFINFO_WMI_GETTIME, *PPERFINFO_WMI_GETTIME;
	
	typedef struct PERFINFO_DSHOW_AVREND {
ULONGLONG    cycleCounter;
ULONGLONG    dshowClock;
ULONGLONG    sampleTime;
	} PERFINFO_DSHOW_AVREND, *PPERFINFO_DSHOW_AVREND;
	
	typedef struct PERFINFO_WMI_AVREND {
EVENT_TRACE_HEADER      header;
PERFINFO_DSHOW_AVREND   data;
	} PERFINFO_WMI_AVREND, *PPERFINFO_WMI_AVREND;
	
	typedef struct PERFINFO_DSHOW_AUDIOBREAK {
ULONGLONG    cycleCounter;
ULONGLONG    dshowClock;
ULONGLONG    sampleTime;
ULONGLONG    sampleDuration;
	} PERFINFO_DSHOW_AUDIOBREAK, *PPERFINFO_DSHOW_AUDIOBREAK;
	
	typedef struct PERFINFO_WMI_AUDIOBREAK {
EVENT_TRACE_HEADER          header;
PERFINFO_DSHOW_AUDIOBREAK   data;
	} PERFINFO_WMI_AUDIOBREAK, *PPERFINFO_WMI_AUDIOBREAK;
	
	typedef struct PERFINFO_DSHOW_FRAMEDROP {
ULONGLONG    cycleCounter;
ULONGLONG    dshowClock;
ULONGLONG    frameTime;
	} PERFINFO_DSHOW_FRAMEDROP, *PPERFINFO_DSHOW_FRAMEDROP;
	
	typedef struct PERFINFO_WMI_FRAMEDROP {
EVENT_TRACE_HEADER          header;
PERFINFO_DSHOW_FRAMEDROP    data;
	} PERFINFO_WMI_FRAMEDROP, *PPERFINFO_WMI_FRAMEDROP;
	
	#define PERFINFO_STREAMTRACE_MPEG2DEMUX_PTS_TRANSLATION     1
	#define PERFINFO_STREAMTRACE_MPEG2DEMUX_SAMPLE_RECEIVED     2
	#define PERFINFO_STREAMTRACE_VMR_BEGIN_ADVISE               3
	#define PERFINFO_STREAMTRACE_VMR_END_ADVISE                 4
	#define PERFINFO_STREAMTRACE_VMR_RECEIVE                    5
	#define PERFINFO_STREAMTRACE_VMR_BEGIN_DEINTERLACE          6
	#define PERFINFO_STREAMTRACE_VMR_END_DEINTERLACE            7
	#define PERFINFO_STREAMTRACE_VMR_BEGIN_DECODE               8
	#define PERFINFO_STREAMTRACE_VMR_END_DECODE                 9
	#define PERFINFO_STREAMTRACE_VMR_DROPPED_FRAME              10
	#define PERFINFO_STREAMTRACE_ENCDEC_DTFILTERINPUT           11
	#define PERFINFO_STREAMTRACE_ENCDEC_DTFILTEROUTPUT          12
	#define PERFINFO_STREAMTRACE_ENCDEC_ETFILTERINPUT           13
	#define PERFINFO_STREAMTRACE_ENCDEC_ETFILTEROUTPUT          14
	#define PERFINFO_STREAMTRACE_ENCDEC_XDSCODECINPUT           15
	#define PERFINFO_STREAMTRACE_SBE_DVRANALYSISINPUT_RECEIVE   16
	#define PERFINFO_STREAMTRACE_SBE_DVRANALYSISINPUT_DELIVER   17
	#define PERFINFO_STREAMTRACE_SBE_DVRINPUTPIN_RECEIVE        18
	#define PERFINFO_STREAMTRACE_SBE_DVROUTPUTPIN_RECEIVE       19
	#define PERFINFO_STREAMTRACE_VMR_RENDER_TIME                20
	
	typedef struct _PERFINFO_DSHOW_STREAMTRACE {
ULONG        id;
ULONG        reserved;
ULONGLONG    dshowClock;
ULONGLONG    data[ 4 ];
	} PERFINFO_DSHOW_STREAMTRACE, *PPERFINFO_DSHOW_STREAMTRACE;
	
	typedef struct _PERFINFO_WMI_STREAMTRACE {
EVENT_TRACE_HEADER          header;
PERFINFO_DSHOW_STREAMTRACE  data;
	} PERFINFO_WMI_STREAMTRACE, *PPERFINFO_WMI_STREAMTRACE;
	
	
	typedef struct PERFINFO_DSHOW_AUDIORECV {
LONGLONG    streamTime ;
LONGLONG    sampleStart ;
LONGLONG    sampleStop ;
LONGLONG    hwduration ;
BOOL        discontinuity ;
	} PERFINFO_DSHOW_AUDIORECV, *PPERFINFO_DSHOW_AUDIORECV;
	
	typedef struct PERFINFO_WMI_AUDIORECV {
EVENT_TRACE_HEADER          header;
PERFINFO_DSHOW_AUDIORECV   data;
	} PERFINFO_WMI_AUDIORECV, *PPERFINFO_WMI_AUDIORECV;
	
	typedef struct PERFINFO_DSHOW_AUDIOSLAVE {
LONGLONG    masterClock ;
LONGLONG    slaveClock ;
LONGLONG    errorAccum ;
LONGLONG    lastHighErrorSeen ;
LONGLONG    lastLowErrorSeen ;
	} PERFINFO_DSHOW_AUDIOSLAVE, *PPERFINFO_DSHOW_AUDIOSLAVE;
	
	typedef struct PERFINFO_WMI_AUDIOSLAVE {
EVENT_TRACE_HEADER          header;
PERFINFO_DSHOW_AUDIOSLAVE   data;
	} PERFINFO_WMI_AUDIOSLAVE, *PPERFINFO_WMI_AUDIOSLAVE;
	
	typedef struct PERFINFO_DSHOW_AUDIOADDBREAK {
DWORD   iterNextWrite ;
DWORD   offsetNextWrite ;
DWORD   iterWrite ;
DWORD   offsetWrite ;
	} PERFINFO_DSHOW_AUDIOADDBREAK, *PPERFINFO_DSHOW_AUDIOADDBREAK;
	
	typedef struct PERFINFO_WMI_AUDIOADDBREAK {
EVENT_TRACE_HEADER              header;
PERFINFO_DSHOW_AUDIOADDBREAK    data;
	} PERFINFO_WMI_AUDIOADDBREAK, *PPERFINFO_WMI_AUDIOADDBREAK;
	
	#endif // _PREFSTRUCT_H_
	