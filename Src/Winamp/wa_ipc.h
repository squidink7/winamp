					/*
					** Copyright (C) 1997-2014 Winamp SA
					**
					** This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held 
					** liable for any damages arising from the use of this software. 
					**
					** Permission is granted to anyone to use this software for any purpose, including commercial applications, and to 
					** alter it and redistribute it freely, subject to the following restrictions:
					**
					**   1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. 
					**      If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
					**
					**   2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
					**
					**   3. This notice may not be removed or altered from any source distribution.
					**
					*/
					
					#ifndef _WA_IPC_H_
					#define _WA_IPC_H_
					
					#include <windows.h>
					#include <stddef.h>
					#if (_MSC_VER <= 1200)
					typedef int intptr_t;
					#endif
					/*
					** This is the modern replacement for the classic 'frontend.h'. Most of these 
					** updates are designed for in-process use, i.e. from a plugin.
					**
					*/
					
					/* Most of the IPC_* messages involve sending the message in the form of:
					** result = SendMessageW(hwnd_winamp,WM_WA_IPC,(parameter),IPC_*);
					** Where different then this is specified (typically with WM_COPYDATA variants)
					**
					** When you use SendMessageW(hwnd_winamp,WM_WA_IPC,(parameter),IPC_*) and specify a IPC_*
					** which is not currently implemented/supported by the Winamp version being used then it
					** will return 1 for 'result'. This is a good way of helping to check if an api being
					** used which returns a function pointer, etc is even going to be valid.
					*/
					
					
					#define WM_WA_IPC WM_USER
					/* but some of them use WM_COPYDATA. be afraid.
					*/
					
					#define WINAMP_VERSION_MAJOR(winampVersion) ((winampVersion & 0x0000FF00) >> 12)
					#define WINAMP_VERSION_MINOR(winampVersion) (winampVersion & 0x000000FF)  // returns, i.e. 0x12 for 5.12 and 0x10 for 5.1... 
					
					
					#define IPC_GETVERSION 0
					/* int version = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVERSION);
					**
					** The version returned will be 0x20yx for Winamp 2.yx.
					** Versions previous to Winamp 2.0 typically (but not always) use 0x1zyx for 1.zx.
					** Just a bit weird but that's the way it goes.
					**
					** For Winamp 5.x it uses the format 0x50yx for Winamp 5.yx
					** e.g.   5.01 -> 0x5001
					**        5.09 -> 0x5009
					**        5.1  -> 0x5010
					**
					** Notes: For 5.02 this api will return the same value as for a 5.01 build.
					**        For 5.07 this api will return the same value as for a 5.06 build.
					*/
					
					
					#define IPC_GETVERSIONSTRING 1
					
					
					#define IPC_GETREGISTEREDVERSION 770
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETREGISTEREDVERSION);
					**
					** This will open the Winamp Preferences and show the Winamp Pro page.
					*/
					
					
					#define IPC_IS_SAFEMODE 999
					/* (requires Winamp 5.64+)
					** int res = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_IS_SAFEMODE);
					**
					** This will indicate if running in safe mode or not (only applies to native plugins).
					** This returns:
					**   0 if in safe mode
					**   1 if in normal mode
					**   2 if in safe mode and media library plug-ins are to be disabled
					**
					** Safe mode is used to disable 3rd party plugins to determine if they are the cause
					** of stability issues and crashes for users experiencing issues without having to
					** first remove plug-in dlls which is often found 'too hard' to do properly most times.
					*/
					
					
					typedef struct {
                const char *filename;
                const char *title;
                const char *ext;
                int length;
					} enqueueFileWithMetaStruct; // send this to a IPC_PLAYFILE in a non WM_COPYDATA, 
					// and you get the nice desired result. if title is NULL, it is treated as a "thing",
					// otherwise it's assumed to be a file (for speed)
					
					typedef struct {
                const wchar_t *filename;
                const wchar_t *title;
                const wchar_t *ext;
                int length;
					} enqueueFileWithMetaStructW;
					
					#define IPC_PLAYFILE 100  // dont be fooled, this is really the same as enqueufile
					#define IPC_ENQUEUEFILE 100 
					#define IPC_PLAYFILEW 1100
					#define IPC_ENQUEUEFILEW 1100
					/* This is sent as a WM_COPYDATA with IPC_PLAYFILE as the dwData member and the string
					** of the file / playlist to be enqueued into the playlist editor as the lpData member.
					** This will just enqueue the file or files since you can use this to enqueue a playlist.
					** It will not clear the current playlist or change the playback state.
					**
					** COPYDATASTRUCT cds = {0};
					**   cds.dwData = IPC_ENQUEUEFILE;
					**   cds.lpData = (void*)"c:\\test\\folder\\test.mp3";
					**   cds.cbData = lstrlen((char*)cds.lpData)+1;  // include space for null char
					**   SendMessageW(hwnd_winamp,WM_COPYDATA,0,(LPARAM)&cds);
					**
					**
					** With 2.9+ and all of the 5.x versions you can send this as a normal WM_WA_IPC
					** (non WM_COPYDATA) with an enqueueFileWithMetaStruct as the param.
					** If the title member is null then it is treated as a "thing" otherwise it will be
					** assumed to be a file (for speed).
					**
					** enqueueFileWithMetaStruct eFWMS = {0};
					**   eFWMS.filename = "c:\\test\\folder\\test.mp3";
					**   eFWMS.title = "Whipping Good";
					**   eFWMS.length = 300;  // this is the number of seconds for the track
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&eFWMS,IPC_ENQUEUEFILE);
					*/
					
					
					#define IPC_DELETE 101
					#define IPC_DELETE_INT 1101 
					/* SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_DELETE);
					** Use this api to clear Winamp's internal playlist.
					** You should not need to use IPC_DELETE_INT since it is used internally by Winamp when
					** it is dealing with some lame Windows Explorer issues (hard to believe that!).
					*/
					
					
					#define IPC_STARTPLAY 102   
					#define IPC_STARTPLAY_INT 1102 
					/* SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_STARTPLAY);
					** Sending this will start playback and is almost the same as hitting the play button.
					** The IPC_STARTPLAY_INT version is used internally and you should not need to use it
					** since it won't be any fun.
					*/
					
					
					#define IPC_CHDIR 103
					/* This is sent as a WM_COPYDATA type message with IPC_CHDIR as the dwData value and the
					** directory you want to change to as the lpData member.
					**
					** COPYDATASTRUCT cds = {0};
					**   cds.dwData = IPC_CHDIR;
					**   cds.lpData = (void*)"c:\\download";
					**   cds.cbData = lstrlen((char*)cds.lpData)+1; // include space for null char
					**   SendMessageW(hwnd_winamp,WM_COPYDATA,0,(LPARAM)&cds);
					**
					** The above example will make Winamp change to the directory 'C:\download'.
					*/
					
					
					#define IPC_ISPLAYING 104
					/* int res = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_ISPLAYING);
					** This is sent to retrieve the current playback state of Winamp.
					** If it returns 1, Winamp is playing.
					** If it returns 3, Winamp is paused.
					** If it returns 0, Winamp is not playing.
					*/
					
					
					#define IPC_GETOUTPUTTIME 105
					/* int res = SendMessageW(hwnd_winamp,WM_WA_IPC,mode,IPC_GETOUTPUTTIME);
					** This api can return two different sets of information about current playback status.
					**
					** If mode = 0 then it will return the position (in ms) of the currently playing track.
					** Will return -1 if Winamp is not playing.
					**
					** If mode = 1 then it will return the current track length (in seconds).
					** Will return -1 if there are no tracks (or possibly if Winamp cannot get the length).
					**
					** If mode = 2 then it will return the current track length (in milliseconds).
					** Will return -1 if there are no tracks (or possibly if Winamp cannot get the length).
					*/
					
					
					#define IPC_JUMPTOTIME 106
					/* (requires Winamp 1.60+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,ms,IPC_JUMPTOTIME);
					** This api sets the current position (in milliseconds) for the currently playing song.
					** The resulting playback position may only be an approximate time since some playback
					** formats do not provide exact seeking e.g. mp3
					** This returns -1 if Winamp is not playing, 1 on end of file, or 0 if it was successful.
					*/
					
					
					#define IPC_GETMODULENAME 109
					#define IPC_EX_ISRIGHTEXE 666
					/* usually shouldnt bother using these, but here goes:
					** send a WM_COPYDATA with IPC_GETMODULENAME, and an internal
					** flag gets set, which if you send a normal WM_WA_IPC message with
					** IPC_EX_ISRIGHTEXE, it returns whether or not that filename
					** matches. lame, I know.
					*/
					
					
					#define IPC_WRITEPLAYLIST 120
					/* (requires Winamp 1.666+)
					** int cur = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_WRITEPLAYLIST);
					**
					** IPC_WRITEPLAYLIST will write the current playlist to winamp.m3u and on unicode clients
					** it will also write the current playlist to winamp.m3u8. This will also return the
					** current playlist position (see IPC_GETLISTPOS).
					**
					** Where the playlist(s) are saved to depends on the Winamp client version used though it
					** is simple to find the path using the correct location (when working in-process):
					**
					** Pre 2.90 -> '<winampdir>\\Winamp.m3u'
					** From 2.90 to 5.1 -> Use IPC_GETINIDIRECTORY
					** From 5.11 -> Use IPC_GETM3UDIRECTORY
					**
					** If working from an external program then it is possible to work out the location of the
					** playlist by reading relevant values out of paths.ini (if found) otherwise the pre 2.90
					** behaviour is what will be attempted to be used (as Winamp does if there is any failure).
					**
					** This is kinda obsoleted by some of the newer 2.x api items but it still is good for
					** use with a front-end program (instead of a plug-in) and you want to see what is in the
					** current playlist.
					**
					** This api will only save out extended file information in the #EXTINF entry if Winamp
					** has already read the data such as if the file was played of scrolled into view. If
					** Winamp has not read the data then you will only find the file with its filepath entry
					** (as is the base requirements for a m3u playlist).
					*/
					
					
					#define IPC_SETPLAYLISTPOS 121
					/* (requires Winamp 2.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,position,IPC_SETPLAYLISTPOS)
					** IPC_SETPLAYLISTPOS sets the playlist position to the specified 'position'.
					** It will not change playback status or anything else. It will just set the current
					** position in the playlist and will update the playlist view if necessary.
					**
					** If you use SendMessageW(hwnd_winamp,WM_COMMAND,MAKEWPARAM(WINAMP_BUTTON2,0),0);
					** after using IPC_SETPLAYLISTPOS then Winamp will start playing the file at 'position'.
					*/
					
					
					#define IPC_SETVOLUME 122
					/* (requires Winamp 2.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,volume,IPC_SETVOLUME);
					** IPC_SETVOLUME sets the volume of Winamp (between the range of 0 to 255).
					**
					** If you pass 'volume' as -666 then the message will return the current volume.
					** int curvol = SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SETVOLUME);
					*/
					
					
					#define IPC_GETVOLUME(hwnd_winamp) SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SETVOLUME)
					/* (requires Winamp 2.0+)
					** int curvol = IPC_GETVOLUME(hwnd_winamp);
					** This will return the current volume of Winamp (between the range of 0 to 255).
					*/
					
					
					#define IPC_SETPANNING 123
					#define IPC_SETBALANCE 123
					/* (requires Winamp 2.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,panning,IPC_SETPANNING);
					** IPC_SETPANNING sets the panning of Winamp from 0 (left) to 255 (right).
					**
					** At least in 5.x+ this works from -127 (left) to 127 (right).
					**
					** If you pass 'panning' as -666 to this api then it will return the current panning.
					** int curpan = SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SETPANNING);
					*/
					
					
					#define IPC_GETPANNING(hwnd_winamp) SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SETPANNING)
					#define IPC_GETBALANCE(hwnd_winamp) SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SETBALANCE)
					/* (requires Winamp 2.0+)
					** int curpan = IPC_GETPANNING(hwnd_winamp);
					** This will return the current panning level of Winamp (5.x) from -127 (left) to 127 (right)
					** or from 0 (left) to 255 (right) on older client versions.
					*/
					
					
					#define IPC_GETLISTLENGTH 124
					/* (requires Winamp 2.0+)
					** int length = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLISTLENGTH);
					** IPC_GETLISTLENGTH returns the length of the current playlist as the number of tracks.
					*/
					
					
					#define IPC_GETLISTPOS 125
					/* (requires Winamp 2.05+)
					** int pos=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLISTPOS);
					** IPC_GETLISTPOS returns the current playlist position (which is shown in the playlist
					** editor as a differently coloured text entry e.g is yellow for the classic skin).
					**
					** This api is a lot like IPC_WRITEPLAYLIST but a lot faster since it does not have to
					** write out the whole of the current playlist first.
					*/
					
					
					#define IPC_GETNEXTLISTPOS 136
					/* (requires Winamp 5.61+)
					** int pos=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETNEXTLISTPOS);
					** IPC_GETNEXTLISTPOS returns the next playlist position expected to be played from the
					** current playlist and allows for determining the next playlist item to be played even
					** if shuffle mode (see IPC_GET_SHUFFLE) is enabled at the time of using this api.
					**
					** If there is no known next playlist item then this will return -1 i.e. if there's only
					** one playlist item or at the end of the current playlist and repeat is disabled.
					**
					** Notes: If a plug-in (like the JTFE plug-in) uses IPC_GET_NEXT_PLITEM to override the
					**        playlist order then you will need to query the plug-in directly (via api_queue
					**        for the JTFE plug-in) to get the correct next playlist item to be played.
					**
					**        If a change is made to the internal shuffle table, the value returned by prior
					**        use of this api is likely to be different and so will need to be re-queried.
					**
					**        The returned playlist item position is zero-based.
					*/
					
					
					#define IPC_GETINFO 126
					/* (requires Winamp 2.05+)
					** int inf=SendMessageW(hwnd_winamp,WM_WA_IPC,mode,IPC_GETINFO);
					** IPC_GETINFO returns info about the current playing song. The value
					** it returns depends on the value of 'mode'.
					** Mode      Meaning
					** ------------------
					** 0         Samplerate, in kilohertz (i.e. 44)
					** 1         Bitrate  (i.e. 128)
					** 2         Channels (i.e. 2)
					** 3 (5+)    Video LOWORD=w HIWORD=h
					** 4 (5+)    > 65536, string (video description)
					** 5 (5.25+) Samplerate, in hertz (i.e. 44100)
					*/
					
					
					#define IPC_GETEQDATA 127
					/* (requires Winamp 2.05+)
					** int data=SendMessageW(hwnd_winamp,WM_WA_IPC,pos,IPC_GETEQDATA);
					** IPC_GETEQDATA queries the status of the EQ. 
					** The value returned depends on what 'pos' is set to:
					** Value      Meaning
					** ------------------
					** 0-9        The 10 bands of EQ data. 0-63 (+20db - -20db)
					** 10         The preamp value. 0-63 (+20db - -20db)
					** 11         Enabled. zero if disabled, nonzero if enabled.
					** 12         Autoload. zero if disabled, nonzero if enabled.
					*/
					
					
					#define IPC_SETEQDATA 128
					/* (requires Winamp 2.05+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,pos,IPC_GETEQDATA);
					** SendMessageW(hwnd_winamp,WM_WA_IPC,value,IPC_SETEQDATA);
					** IPC_SETEQDATA sets the value of the last position retrieved
					** by IPC_GETEQDATA. This is pretty lame, and we should provide
					** an extended version that lets you do a MAKELPARAM(pos,value).
					** someday...
					
                    new (2.92+): 
                if the high byte is set to 0xDB, then the third byte specifies
                which band, and the bottom word specifies the value.
					*/
					
					
					#define IPC_ADDBOOKMARK 129
					#define IPC_ADDBOOKMARKW 131
					/* (requires Winamp 2.4+)
					** This is sent as a WM_COPYDATA using IPC_ADDBOOKMARK as the dwData value and the
					** directory you want to change to as the lpData member. This will add the specified
					** file / url to the Winamp bookmark list.
					**
					** COPYDATASTRUCT cds = {0};
					**   cds.dwData = IPC_ADDBOOKMARK;
					**   cds.lpData = (void*)"http://www.blah.com/listen.pls";
					**   cds.cbData = lstrlen((char*)cds.lpData)+1; // include space for null char
					**   SendMessageW(hwnd_winamp,WM_COPYDATA,0,(LPARAM)&cds);
					**
					**
					** In Winamp 5.0+ we use this as a normal WM_WA_IPC and the string is null separated as
					** the filename and then the title of the entry.
					**
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(char*)"filename\0title\0",IPC_ADDBOOKMARK);
					**
					** This will notify the library / bookmark editor that a bookmark was added.
					** Note that using this message in this context does not actually add the bookmark.
					** Do not use, it is essentially just a notification type message :)
					**
					** Additional Notes:
					**
					** If IPC_ADDBOOKMARK is called with wParam as zero then it returns the bookmark filepath
					** as an ansi string.
					**
					** As of 5.58+, calling IPC_ADDBOOKMARKW with wParam as zero will return the bookmark
					** filepath as a unicode string and IPC_ADDBOOKMARK will behave as prior to 5.58.
					** Passing wParam as 666 will return the winamp.bm8 filepath and is valid for both apis.
					*/
					
					
					#define IPC_INSTALLPLUGIN 130
					/* This is not implemented (and is very unlikely to be done due to safety concerns).
					** If it was then you could do a WM_COPYDATA with a path to a .wpz and it would then
					** install the plugin for you.
					**
					** COPYDATASTRUCT cds = {0};
					**   cds.dwData = IPC_INSTALLPLUGIN;
					**   cds.lpData = (void*)"c:\\path\\to\\file.wpz";
					**   cds.cbData = lstrlen((char*)cds.lpData)+1; // include space for null char
					**   SendMessageW(hwnd_winamp,WM_COPYDATA,0,(LPARAM)&cds);
					*/
					
					
					#define IPC_RESTARTWINAMP 135
					/* (requires Winamp 2.2+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_RESTARTWINAMP);
					** IPC_RESTARTWINAMP will restart Winamp (isn't that obvious ? :) )
					** If this fails to make Winamp start after closing then there is a good chance one (or
					** more) of the currently installed plugins caused Winamp to crash on exit (either as a
					** silent crash or a full crash log report before it could call itself start again.
					*/
					
					
					#define IPC_RESTARTSAFEWINAMP 1135
					/* (requires Winamp 5.64+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_RESTARTSAFEWINAMP);
					** IPC_RESTARTSAFEWINAMP will restart Winamp (isn't that obvious ? :) ) in safe mode.
					** If this fails to make Winamp start after closing then there is a good chance one (or
					** more) of the currently installed plugins caused Winamp to crash on exit (either as a
					** silent crash or a full crash log report before it could call itself start again.
					*/
					
					
					#define IPC_ISFULLSTOP 400
					/* (requires winamp 2.7+ I think)
					** int ret=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_ISFULLSTOP);
					** This is useful for when you're an output plugin and you want to see if the stop/close
					** happening is a full stop or if you are just between tracks. This returns zero if it is
					** a full stop (such as the user pressing stop) or non-zero if it is just the end of a
					** file or other internal events.
					*/
					
					
					#define IPC_INETAVAILABLE 242
					/* (requires Winamp 2.05+)
					** int val=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_INETAVAILABLE);
					** IPC_INETAVAILABLE will return 1 if an Internet connection is available for Winamp and
					** relates to the internet connection type setting on the main general preferences page
					** in the Winamp preferences.
					*/
					
					
					#define IPC_UPDTITLE 243
					/* (requires Winamp 2.2+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_UPDTITLE);
					** IPC_UPDTITLE will ask Winamp to update the information about the current title and
					** causes GetFileInfo(..) in the input plugin associated with the current playlist entry
					** to be called. This can be called such as when an input plugin is buffering a file so
					** that it can cause the buffer percentage to appear in the playlist.
					*/
					
					
					#define IPC_REFRESHPLCACHE 247
					/* (requires Winamp 2.2+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_REFRESHPLCACHE);
					** IPC_REFRESHPLCACHE will flush the playlist cache buffer and you send this if you want
					** Winamp to go refetch the titles for all of the entries in the current playlist.
					**
					** 5.3+:
					** If you pass a wchar_t * string in wParam then it will be be found using strnicmp() and
					** the cache for that entry only will be cleared unlike passing nothing which clears all.
					*/
					
					
					#define IPC_GET_SHUFFLE 250
					/* (requires Winamp 2.4+)
					** int val=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_SHUFFLE);
					** IPC_GET_SHUFFLE returns the status of the shuffle option.
					** If set then it will return 1 and if not set then it will return 0.
					*/
					
					
					#define IPC_GET_REPEAT 251
					/* (requires Winamp 2.4+)
					** int val=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_REPEAT);
					** IPC_GET_REPEAT returns the status of the repeat option.
					** If set then it will return 1 and if not set then it will return 0.
					*/
					
					
					#define IPC_SET_SHUFFLE 252
					/* (requires Winamp 2.4+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,value,IPC_SET_SHUFFLE);
					** IPC_SET_SHUFFLE sets the status of the shuffle option.
					** If 'value' is 1 then shuffle is turned on.
					** If 'value' is 0 then shuffle is turned off.
					*/
					
					
					#define IPC_SET_REPEAT 253
					/* (requires Winamp 2.4+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,value,IPC_SET_REPEAT);
					** IPC_SET_REPEAT sets the status of the repeat option.
					** If 'value' is 1 then shuffle is turned on.
					** If 'value' is 0 then shuffle is turned off.
					*/
					
					
					#define IPC_ENABLEDISABLE_ALL_WINDOWS 259 // 0xdeadbeef to disable
					/* (requires Winamp 2.9+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(enable?0:0xdeadbeef),IPC_ENABLEDISABLE_ALL_WINDOWS);
					** Sending this message with 0xdeadbeef as the param will disable all winamp windows and
					** any other values will enable all of the Winamp windows again. When disabled you won't
					** get any response on clicking or trying to do anything to the Winamp windows. If the
					** taskbar icon is shown then you may still have control ;)
					*/
					
					
					#define IPC_GETWND 260
					/* (requires Winamp 2.9+)
					** HWND h=SendMessageW(hwnd_winamp,WM_WA_IPC,IPC_GETWND_xxx,IPC_GETWND);
					** returns the HWND of the window specified.
					*/
                    #define IPC_GETWND_EQ 0 // use one of these for the param
                    #define IPC_GETWND_PE 1
                    #define IPC_GETWND_MB 2
                    #define IPC_GETWND_VIDEO 3
					#define IPC_ISWNDVISIBLE 261 // same param as IPC_GETWND
					
					
					/************************************************************************
					***************** in-process only (WE LOVE PLUGINS)
					************************************************************************/
					
					#define IPC_SETSKINW 199
					#define IPC_SETSKIN 200
					/* (requires Winamp 2.04+, only usable from plug-ins (not external apps))
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)"skinname",IPC_SETSKIN);
					** IPC_SETSKIN sets the current skin to "skinname". Note that skinname 
					** can be the name of a skin, a skin .zip file, with or without path. 
					** If path isn't specified, the default search path is the winamp skins 
					** directory.
					*/
					
					
					#define IPC_GETSKIN 201
					#define IPC_GETSKINW 1201
					/* (requires Winamp 2.04+, only usable from plug-ins (not external apps))
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)skinname_buffer,IPC_GETSKIN);
					** IPC_GETSKIN puts the directory where skin bitmaps can be found 
					** into  skinname_buffer.
					** skinname_buffer must be MAX_PATH characters in length.
					** When using a .zip'd skin file, it'll return a temporary directory
					** where the ZIP was decompressed.
					*/
					
					
					#define IPC_EXECPLUG 202
					/* (requires Winamp 2.04+, only usable from plug-ins (not external apps))
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)"vis_file.dll",IPC_EXECPLUG);
					** IPC_EXECPLUG executes a visualization plug-in pointed to by WPARAM.
					** the format of this string can be:
					** "vis_whatever.dll"
					** "vis_whatever.dll,0" // (first mod, file in winamp plug-in dir)
					** "C:\\dir\\vis_whatever.dll,1" 
					*/
					
					
					#define IPC_GETPLAYLISTFILE 211
					#define IPC_GETPLAYLISTFILEW 214
					/* (requires Winamp 2.04+, only usable from plug-ins (not external apps))
					** char *name=SendMessageW(hwnd_winamp,WM_WA_IPC,index,IPC_GETPLAYLISTFILE);
					** IPC_GETPLAYLISTFILE gets the filename of the playlist entry [index].
					** returns a pointer to it. returns NULL on error.
					*/
					
					
					#define IPC_GETPLAYLISTTITLE 212
					#define IPC_GETPLAYLISTTITLEW 213
					/* (requires Winamp 2.04+, only usable from plug-ins (not external apps))
					** char *name=SendMessageW(hwnd_winamp,WM_WA_IPC,index,IPC_GETPLAYLISTTITLE);
					**
					** IPC_GETPLAYLISTTITLE gets the title of the playlist entry [index].
					** returns a pointer to it. returns NULL on error.
					*/
					
					
					#define IPC_GETHTTPGETTER 240
					/* retrieves a function pointer to a HTTP retrieval function.
					** if this is unsupported, returns 1 or 0.
					** the function should be:
					** int (*httpRetrieveFile)(HWND hwnd, char *url, char *file, char *dlgtitle);
					** if you call this function, with a parent window, a URL, an output file, and a dialog title,
					** it will return 0 on successful download, 1 on error.
					*/
					
					
					#define IPC_GETHTTPGETTERW 1240
					/* int (*httpRetrieveFileW)(HWND hwnd, char *url, wchar_t *file, wchar_t *dlgtitle); */
					
					
					#define IPC_MBOPEN 241
					/* (requires Winamp 2.05+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_MBOPEN);
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)url,IPC_MBOPEN);
					** IPC_MBOPEN will open a new URL in the minibrowser. if url is NULL, it will open the Minibrowser window.
					*/
					
					
					#define IPC_CHANGECURRENTFILE 245
					/* (requires Winamp 2.05+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)file,IPC_CHANGECURRENTFILE);
					** IPC_CHANGECURRENTFILE will set the current playlist item.
					*/
					
					
					#define IPC_CHANGECURRENTFILEW 1245
					/* (requires Winamp 5.3+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)file,IPC_CHANGECURRENTFILEW);
					** IPC_CHANGECURRENTFILEW will set the current playlist item.
					*/
					
					
					#define IPC_GETMBURL 246
					/* (requires Winamp 2.2+)
					** char buffer[4096]; // Urls can be VERY long
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)buffer,IPC_GETMBURL);
					** IPC_GETMBURL will retrieve the current Minibrowser URL into buffer.
					** buffer must be at least 4096 bytes long.
					*/
					
					
					#define IPC_MBBLOCK 248
					/* (requires Winamp 2.4+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,value,IPC_MBBLOCK);
					**
					** IPC_MBBLOCK will block the Minibrowser from updates if value is set to 1
					*/
					
					
					#define IPC_MBOPENREAL 249
					/* (requires Winamp 2.4+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)url,IPC_MBOPENREAL);
					**
					** IPC_MBOPENREAL works the same as IPC_MBOPEN except that it will works even if 
					** IPC_MBBLOCK has been set to 1
					*/
					
					
					#define IPC_ADJUST_OPTIONSMENUPOS 280
					/* (requires Winamp 2.9+)
					** int newpos=SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)adjust_offset,IPC_ADJUST_OPTIONSMENUPOS);
					** This moves where Winamp expects the Options menu to be in the main menu.
					** This is useful if you wish to insert a menu item above the options/skins/vis menus for a window.
					** If you pass adjust_offset as zero then it will return the current offset without adjusting it.
					*/
					
					
					#define IPC_GET_HMENU 281
					/* (requires Winamp 2.9+)
					** HMENU hMenu=SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)0,IPC_GET_HMENU);
					**
					** For 2.9x installs the following values are valid:
					** 0 : main popup menu (mapped to -1 in 5.x installs)
					** 1 : main menubar file menu
					** 2 : main menubar options menu
					** 3 : main menubar windows menu
					** 4 : main menubar help menu
					**
					** For 5.x client versions the following values are valid (changed due to Modern skin support):
					** -1 : the main winamp menu resource (same as doing LoadMenu(winamp_module_or_lng_file,101)
					**  0 : main popup menu 
					**  1 : main menubar file menu
					**  2 : main menubar play menu
					**  3 : main menubar options menu
					**  4 : main menubar windows menu
					**  5 : main menubar windows help
					**  6 : playlist editor menubar file menu
					**  7 : playlist editor menubar playlist menu
					**  8 : playlist editor menubar sort menu
					**  9 : media library menubar file menu
					** 10 : media library menubar view menu
					**
					** In all client versions, unsupported values will return NULL.
					**
					** e.g. (psuedo code to add an item to the end of the main window 'view' menu)
					** HMENU windows_menu = (HMENU)SendMessageW(hwnd_winamp,WM_WA_IPC,4,IPC_GET_HMENU);
					** if(windows_menu)
					** {
					**   // WA_MENUITEM_ID is obtained from IPC_REGISTER_WINAMP_IPCMESSAGE or a predefined
					**   // value if that api is not supported on the client version you are working with.
					**
					**   int window_visible = 1; // this would be updated as needed for the window view state
					**   MENUITEMINFO i = {sizeof(i), MIIM_ID | MIIM_STATE | MIIM_TYPE, MFT_STRING,
					**                     window_visible ? MFS_CHECKED : 0, WA_MENUITEM_ID};
					**   i.dwTypeData = "My Menu Item";
					**   InsertMenuItem(windows_menu, GetMenuItemCount(windows_menu), TRUE, &i);
					** }
					*/
					
					
					#define IPC_GET_EXTENDED_FILE_INFO 290 //pass a pointer to the following struct in wParam
					#define IPC_GET_EXTENDED_FILE_INFO_HOOKABLE 296
					/* (requires Winamp 2.9+)
					** to use, create an extendedFileInfoStruct, point the values filename and metadata to the
					** filename and metadata field you wish to query, and ret to a buffer, with retlen to the
					** length of that buffer, and then SendMessageW(hwnd_winamp,WM_WA_IPC,&struct,IPC_GET_EXTENDED_FILE_INFO);
					** the results should be in the buffer pointed to by ret.
					** returns 1 if the decoder supports a getExtendedFileInfo method
					*/
					typedef struct {
                    const char *filename;
                    const char *metadata;
                    char *ret;
                    size_t retlen;
					} extendedFileInfoStruct;
					
					
					#define IPC_GET_BASIC_FILE_INFO 291 //pass a pointer to the following struct in wParam
					typedef struct {
                    const char *filename;
					
                    int quickCheck; // set to 0 to always get, 1 for quick, 2 for default (if 2, quickCheck will be set to 0 if quick wasnot used)
					
                    // filled in by winamp
                    int length;
                    char *title;
                    int titlelen;
					} basicFileInfoStruct;
					
					
					#define IPC_GET_BASIC_FILE_INFOW 1291 //pass a pointer to the following struct in wParam
					typedef struct {
                    const wchar_t *filename;
					
                    int quickCheck; // set to 0 to always get, 1 for quick, 2 for default (if 2, quickCheck will be set to 0 if quick wasnot used)
					
                    // filled in by winamp
                    int length;
                    wchar_t *title;
                    int titlelen;
					} basicFileInfoStructW;
					
					
					#define IPC_GET_EXTLIST 292
					#define IPC_GET_EXTLISTW 1292
					/* (requires Winamp 5.0+)
					** char* ext_list = (char*)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)mode,IPC_GET_EXTLIST);
					** wchar_t* ext_list = (wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)mode,IPC_GET_EXTLISTW);
					** These return a double null delimited string based on the mode passed.
					** Ensure you GlobalFree() the result when done.
					**
					** mode = 0 - returns raw extlist of all loadable formats
					** mode = 1 - returns something suitable for getopenfilename of all loadable formats
					**
					** update 5.66+
					** these now de-duplicate file extensions reported by the input plug-ins as well as capitalising.
					*/
					
					#define IPC_GET_PLAYLIST_EXTLISTW 282
					/* (requires Winamp 5.66+)
					** wchar_t* pl_ext_list = (wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)mode,IPC_GET_PLAYLIST_EXTLISTW);
					** These just return playlist extensions / file types instead of all
					** extensions / file types like the prior IPC_GET_EXTLIST(W) methods.
					** There is no need to GlobalFree() the result unlike the IPC_GET_EXTLIST(W) behaviour.
					**
					** mode = 0 - returns raw extlist of loadable playlist formats
					** mode = 1 - returns something suitable for getopenfilename of loadable playlist formats
					** mode = 2 - returns raw extlist of writeable playlist formats
					** mode = 3 - returns something suitable for getopenfilename of writeable playlist formats
					*/
					
					typedef struct {
                    HWND parent;
                    char *filename;
					} infoBoxParam;
					
					#define IPC_INFOBOX 293
					/* (requires Winamp 5.0+)
					** infoBoxParam infoBox = {parent_hwnd,"c:\\test\\folder\\test.mp3"};
					** int ret_val = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&infoBox,IPC_INFOBOX);
					**
					** ret_val is 0 if OK was pressed and is 1 if CANCEL was pressed
					** The standard behaviour is to abort any loops used with this api if a cancel occurs.
					*/
					
					
					typedef struct {
                    HWND parent;
                    const wchar_t *filename;
					} infoBoxParamW;
					
					#define IPC_INFOBOXW 1293
					/* (requires Winamp 5.3+)
					** infoBoxParamW infoBoxW = {parent_hwnd,L"c:\\test\\folder\\test.mp3"};
					** int ret_val = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&infoBoxW,IPC_INFOBOXW);
					**
					** ret_val is 0 if OK was pressed and is 1 if CANCEL was pressed
					** The standard behaviour is to abort any loops used with this api if a cancel occurs.
					*/
					
					
					#define IPC_SET_EXTENDED_FILE_INFO 294 //pass a pointer to the a extendedFileInfoStruct in wParam
					/* (requires Winamp 2.9+)
					** to use, create an extendedFileInfoStruct, point the values filename and metadata to the
					** filename and metadata field you wish to write in ret. (retlen is not used). and then 
					** SendMessageW(hwnd_winamp,WM_WA_IPC,&struct,IPC_SET_EXTENDED_FILE_INFO);
					** returns 1 if the metadata is supported
					** Call IPC_WRITE_EXTENDED_FILE_INFO once you're done setting all the metadata you want to update
					*/
					
					
					#define IPC_WRITE_EXTENDED_FILE_INFO 295 
					/* (requires Winamp 2.9+)
					** writes all the metadata set thru IPC_SET_EXTENDED_FILE_INFO to the file
					** returns 1 if the file has been successfully updated, 0 if error
					*/
					
					
					#define IPC_FORMAT_TITLE 297
					typedef struct 
					{
                    char *spec; // NULL=default winamp spec
                    void *p;
					
                    char *out;
                    int out_len;
					
                    char * (*TAGFUNC)(const char * tag, void * p); //return 0 if not found
                    void (*TAGFREEFUNC)(char * tag,void * p);
					} waFormatTitle;
					
					
					#define IPC_FORMAT_TITLE_EXTENDED 298 // similiar to IPC_FORMAT_TITLE, but falls back to Winamp's %tags% if your passed tag function doesn't handle it
					typedef struct 
					{
                    const wchar_t *filename;
                    int useExtendedInfo; // set to 1 if you want the Title Formatter to query the input plugins for any tags that your tag function fails on
                    const wchar_t *spec; // NULL=default winamp spec
                    void *p;
					
                    wchar_t *out;
                    int out_len;
					
                    wchar_t * (*TAGFUNC)(const wchar_t * tag, void * p); //return 0 if not found, -1 for empty tag
                    void (*TAGFREEFUNC)(wchar_t *tag, void *p);
					} waFormatTitleExtended;
					
					
					#define IPC_COPY_EXTENDED_FILE_INFO 299 
					typedef struct
					{
                    const char *source;
                    const char *dest;
					} copyFileInfoStruct;
					
					
					#define IPC_COPY_EXTENDED_FILE_INFOW 1299 
					typedef struct
					{
                    const wchar_t *source;
                    const wchar_t *dest;
					} copyFileInfoStructW;
					
					
					typedef struct {
                    int (*inflateReset)(void *strm);
                    int (*inflateInit_)(void *strm,const char *version, int stream_size);
                    int (*inflate)(void *strm, int flush);
                    int (*inflateEnd)(void *strm);
                    unsigned long (*crc32)(unsigned long crc, const unsigned  char *buf, unsigned int len);
					} wa_inflate_struct;
					
					#define IPC_GETUNCOMPRESSINTERFACE 331
					/* returns a function pointer to uncompress().
					** int (*uncompress)(unsigned char *dest, unsigned long *destLen, const unsigned char *source, unsigned long sourceLen);
					** right out of zlib, useful for decompressing zlibbed data.
					** if you pass the parm of 0x10100000, it will return a wa_inflate_struct * to an inflate API.
					*/
					
					
					typedef struct _prefsDlgRec {
                    HINSTANCE hInst;  // dll instance containing the dialog resource
                    int dlgID;        // resource identifier of the dialog
                    void *proc;       // window proceedure for handling the dialog defined as
// LRESULT CALLBACK PrefsPage(HWND,UINT,WPARAM,LPARAM)
					
                    char *name;       // name shown for the prefs page in the treelist
                    intptr_t where;   // section in the treelist the prefs page is to be added to
// 0 for General Preferences
// 1 for Plugins
// 2 for Skins
// 3 for Bookmarks (no longer in the 5.0+ prefs)
// 4 for Prefs     (the old 'Setup' section - no longer in 5.0+)
// 6 for Media Library
					
                    intptr_t _id;
                    struct _prefsDlgRec *next; // no longer implemented as a linked list, now used by Winamp for other means
					} prefsDlgRec;
					
					typedef struct _prefsDlgRecW {
                    HINSTANCE hInst;  // dll instance containing the dialog resource
                    int dlgID;        // resource identifier of the dialog
                    void *proc;       // window proceedure for handling the dialog defined as
// LRESULT CALLBACK PrefsPage(HWND,UINT,WPARAM,LPARAM)
					
                    wchar_t *name;    // name shown for the prefs page in the treelist
                    intptr_t where;   // section in the treelist the prefs page is to be added to
// 0 for General Preferences
// 1 for Plugins
// 2 for Skins
// 3 for Bookmarks (no longer in the 5.0+ prefs)
// 4 for Prefs     (the old 'Setup' section - no longer in 5.0+)
// 6 for Media Library
					
                    intptr_t _id;
                    struct _prefsDlgRec *next; // no longer implemented as a linked list, now used by Winamp for other means
					} prefsDlgRecW;
					
					#define IPC_ADD_PREFS_DLG 332
					#define IPC_ADD_PREFS_DLGW 1332 
					#define IPC_REMOVE_PREFS_DLG 333
					#define IPC_UPDATE_PREFS_DLG 342
					#define IPC_UPDATE_PREFS_DLGW 1342
					/* (requires Winamp 2.9+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&prefsRec,IPC_ADD_PREFS_DLG);
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&prefsRec,IPC_REMOVE_PREFS_DLG);
					**
					** IPC_ADD_PREFS_DLG:
					** To use this you need to allocate a prefsDlgRec structure (either on the heap or with
					** some global data but NOT on the stack) and then initialise the members of the structure
					** (see the definition of the prefsDlgRec structure above).
					**
					**   hInst  -  dll instance of where the dialog resource is located.
					**   dlgID  -  id of the dialog resource.
					**   proc   -  dialog window procedure for the prefs dialog.
					**   name   -  name of the prefs page as shown in the preferences list.
					**   where  -  see above for the valid locations the page can be added.
					**
					** Then you do SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&prefsRec,IPC_ADD_PREFS_DLG);
					**
					** example:
					**
					** prefsDlgRec* prefsRec = 0;
					**   prefsRec = GlobalAlloc(GPTR,sizeof(prefsDlgRec));
					**   prefsRec->hInst = hInst;
					**   prefsRec->dlgID = IDD_PREFDIALOG;
					**   prefsRec->name = "Pref Page";
					**   prefsRec->where = 0;
					**   prefsRec->proc = PrefsPage;
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&prefsRec,IPC_ADD_PREFS_DLG);
					**
					**
					** IPC_REMOVE_PREFS_DLG:
					** To use you pass the address of the same prefsRec you used when adding the prefs page 
					** though you shouldn't really ever have to do this but it's good to clean up after you
					** when you're plugin is being unloaded.
					**
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&prefsRec,IPC_REMOVE_PREFS_DLG);
					**
					** IPC_ADD_PREFS_DLGW
					** requires Winamp 5.53+
					**
					** IPC_UPDATE_PREFS_DLG
					** IPC_UPDATE_PREFS_DLGW
					** requires Winamp 5.64+
					*/
					
					
					#define IPC_OPENPREFSTOPAGE 380
					/* SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&prefsRec,IPC_OPENPREFSTOPAGE);
					**
					** There are two ways of opening a preferences page.
					**
					** The first is to pass an id of a builtin preferences page (see below for ids) or a
					** &prefsDlgRec of the preferences page to open and this is normally done if you are
					** opening a prefs page you added yourself.
					**
					** If the page id does not or the &prefsRec is not valid then the prefs dialog will be
					** opened to the first page available (usually the Winamp Pro page).
					**
					** (requires Winamp 5.04+)
					** Passing -1 for param will open the preferences dialog to the last page viewed.
					**
					** Note: v5.0 to 5.03 had a bug in this api
					**       
					** On the first call then the correct prefs page would be opened to but on the next call
					** the prefs dialog would be brought to the front but the page would not be changed to the
					** specified.
					** In 5.04+ it will change to the prefs page specified if the prefs dialog is already open.
					*/
					
					/* Builtin Preference page ids (valid for 5.0+)
					** (stored in the lParam member of the TVITEM structure from the tree item)
					**
					** These can be useful if you want to detect a specific prefs page and add things to it
					** yourself or something like that ;)
					**
					** Winamp Pro           20
					** General Preferences  0
					** File Types           1
					** Playlist             23
					** Titles               21
					** Playback             42 (added in 5.25)
					** Station Info         41 (added in 5.11 & removed in 5.5)
					** Video                24
					** Localization         25 (added in 5.5)
					** Skins                40
					** Classic Skins        22
					** Plugins              30
					** Input                31
					** Output               32
					** Visualisation        33
					** DSP/Effect           34
					** General Purpose      35
					**
					** Note:
					** Custom page ids begin from 60
					** The value of the normal custom pages (Global Hotkeys, Jump To File, etc) is not
					** guaranteed since it depends on the order in which the plugins are loaded which can
					** change on different systems.
					**
					** Global Hotkeys, Jump To File, Media Library (under General Preferences and child pages),
					** Media Library (under Plugins), Portables, CD Ripping and Modern Skins are custom pages
					** created by the plugins shipped with Winamp.
					*/
					
					
					#define IPC_GETINIFILE 334
					/* (requires Winamp 2.9+)
					** char *ini=(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETINIFILE);
					** This returns a pointer to the full file path of winamp.ini.
					**
					** char ini_path[MAX_PATH] = {0};
					**
					** void GetIniFilePath(HWND hwnd){
					**   if(SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVERSION) >= 0x2900){
					**     // this gets the string of the full ini file path
					**     lstrcpynA(ini_path,(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETINIFILE),sizeof(ini_path)/sizeof(char));
					**   }
					**   else{
					**   char* p = ini_path;
					**     p += GetModuleFileNameA(0,ini_path,sizeof(ini_path)/sizeof(char)) - 1;
					**     while(p && *p != '.' && p != ini_path){p = CharPrevA(ini_path,p);}
					**     lstrcpynA(p+1,"ini",sizeof(ini_path)/sizeof(char));
					**   }
					** }
					*/
					
					
					#define IPC_GETINIFILEW 1334
					/* (requires Winamp 5.58+)
					** wchar_t *ini=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETINIFILEW);
					** This returns a pointer to the full file path of winamp.ini.
					**
					** wchar_t ini_path[MAX_PATH] = {0};
					**
					** void GetIniFilePath(HWND hwnd){
					**   if(SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVERSION) >= 0x5058){
					**     // this gets the string of the full ini file path
					**     lstrcpynW(ini_path,(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETINIFILEW),sizeof(ini_path)/sizeof(wchar_t));
					**   }
					**   else{
					**   wchar_t* p = ini_path;
					**     p += GetModuleFileNameW(0,ini_path,sizeof(ini_path)/sizeof(wchar_t)) - 1;
					**     while(p && *p != '.' && p != ini_path){p = CharPrevW(ini_path,p);}
					**     lstrcpynW(p+1,L"ini",sizeof(ini_path)/sizeof(wchar_t));
					**   }
					** }
					**
					** IPC_GETINIFILEW requires 5.58+
					*/
					
					
					#define IPC_GETINIDIRECTORY 335
					/* (requires Winamp 2.9+)
					** char *dir=(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETINIDIRECTORY);
					** This returns a pointer to the directory where winamp.ini can be found and is
					** useful if you want store config files but you don't want to use winamp.ini.
					*/
					
					
					#define IPC_GETINIDIRECTORYW 1335
					/* (requires Winamp 5.58+)
					** wchar_t *dir=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETINIDIRECTORYW);
					** This returns a pointer to the directory where winamp.ini can be found and is
					** useful if you want store config files but you don't want to use winamp.ini.
					*/
					
					
					#define IPC_GETPLUGINDIRECTORY 336
					/* (requires Winamp 5.11+)
					** char *plugdir=(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETPLUGINDIRECTORY);
					** This returns a pointer to the directory where Winamp has its plugins stored and is
					** useful if you want store config files in plugins.ini in the plugins folder or for
					** accessing any local files in the plugins folder.
					*/
					
					
					#define IPC_GETPLUGINDIRECTORYW 1336
					/* (requires Winamp 5.58+)
					** wchar_t *plugdir=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETPLUGINDIRECTORYW);
					** This returns a pointer to the directory where Winamp has its plugins stored and is
					** useful if you want store config files in plugins.ini in the plugins folder or for
					** accessing any local files in the plugins folder.
					*/
					
					
					#define IPC_GETM3UDIRECTORY 337
					/* (requires Winamp 5.11+)
					** char *m3udir=(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETM3UDIRECTORY);
					** This returns a pointer to the directory where winamp.m3u (and winamp.m3u8 if supported) is stored in.
					*/
					
					
					#define IPC_GETM3UDIRECTORYW 338
					/* (requires Winamp 5.3+)
					** wchar_t *m3udirW=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETM3UDIRECTORYW);
					** This returns a pointer to the directory where winamp.m3u (and winamp.m3u8 if supported) is stored in.
					*/
					
					
					#define IPC_GETVISDIRECTORYW 339
					/* (requires Winamp 5.58+)
					** wchar_t *visdir=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVISDIRECTORYW);
					** This returns a pointer to the directory set to load/store visualization plugins from.
					**
					** This can otherwise be obtained by reading the "VISDir" entry in the winamp section of
					** winamp.ini which if null then you need to assume <winampdir>\plugins
					*/
					
					
					#define IPC_GETSKINDIRECTORYW 340
					/* (requires Winamp 5.58+)
					** wchar_t *skindir=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETSKINDIRECTORYW);
					** This returns a pointer to the directory set to load/store installed skins from.
					**
					** This can otherwise be obtained by reading the "SkinDir" entry in the winamp section of
					** winamp.ini which if null then you need to assume <winampdir>\skins
					*/
					
					
					#define IPC_GETDSPDIRECTORYW 341
					/* (requires Winamp 5.58+)
					** wchar_t *dspdir=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETDSPDIRECTORYW);
					** This returns a pointer to the directory set to load/store installed DSP/effect plugins from.
					**
					** This can otherwise be obtained by reading the "DSPDir" entry in the winamp section of
					** winamp.ini which if null then you need to assume <winampdir>\plugins
					*/
					
					
					#define IPC_GETMLINIFILE 343
					#define IPC_GETMLINIFILEW 1343
					/* (requires Winamp 5.66+)
					** wchar_t *ml_ini=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETMLINIFILEW);
					** This returns a pointer to the full file path of gen_ml.ini.
					*/
					
					
					#define IPC_GETSHAREDDLLDIRECTORYW 1344
					/* (requires Winamp 5.8+)
					** wchar_t *shareddir=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETSHAREDDLLDIRECTORYW);
					** This returns a pointer to the directory set to load/store installed DSP/effect plugins from.
					*/
					
					
					#define IPC_SPAWNBUTTONPOPUP 361 // param =
					// 0 = eject
					// 1 = previous
					// 2 = next
					// 3 = pause
					// 4 = play
					// 5 = stop
					
					
					#define IPC_OPENURLBOX 360
					/* (requires Winamp 5.0+)
					** HGLOBAL hglobal = (HGLOBAL)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)parent,IPC_OPENURLBOX);
					** You pass a hwnd for the dialog to be parented to (which modern skin support uses).
					** This will return a HGLOBAL that needs to be freed with GlobalFree() if this worked.
					*/
					
					
					#define IPC_OPENFILEBOX 362
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)parent,IPC_OPENFILEBOX);
					** You pass a hwnd for the dialog to be parented to (which modern skin support uses).
					*/
					
					
					#define IPC_OPENDIRBOX 363
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)parent,IPC_OPENDIRBOX);
					** You pass a hwnd for the dialog to be parented to (which modern skin support uses).
					*/
					
					
					#define IPC_SETDIALOGBOXPARENT 364
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)parent,IPC_SETDIALOGBOXPARENT);
					** Pass 'parent' as the window which will be used as the parent for a number of the built
					** in Winamp dialogs and is useful when you are taking over the whole of the UI so that
					** the dialogs will not appear at the bottom right of the screen since the main winamp
					** window is located at 3000x3000 by gen_ff when this is used.  Call this again with
					** parent = null to reset the parent back to the orginal Winamp window.
					*/
					
					
					#define IPC_GETDIALOGBOXPARENT 365
					/* (requires Winamp 5.51+)
					** HWND hwndParent = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)0,IPC_GETDIALOGBOXPARENT);
					** hwndParent can / must be passed to all modal dialogs/MessageBoxes when using Winamp as a parent.
					*/
					
					
					#define IPC_UPDATEDIALOGBOXPARENT 366
					/* (requires Winamp 5.53+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)parent,IPC_UPDATEDIALOGBOXPARENT);
					** If you previously called IPC_SETDIALOGBOXPARENT then call this every time your window resizes.
					*/ 
					
					
					#define IPC_DRO_MIN 401 // reserved for DrO
					
					#define IPC_SET_JTF_COMPARATOR 409
					/* (requires Winamp 5.2+)
					/* pass me an int (__cdecl *)(const char *, const char *) in wParam
					** If this is not set or if it is cleared then Winamp reverts to it's own comparator.
					** It is not until Winamp 5.33+ that passing wParam=0 or another function will allow
					** for it to be changed from what was set on the first calling of this api.
					*/
					
					#define IPC_SET_JTF_COMPARATOR_W 410
					/* (requires Winamp 5.55+)
					** pass me an int (__cdecl *)(const wchar_t *, const wchar_t *) in wParam
					** If this is not set or if it is cleared then Winamp will revert to the
					** IPC_SET_JTF_COMPARATOR handler or the native search function if not set.
					*/
					
					#define IPC_SET_JTF_DRAWTEXT 416
					
					#define IPC_SET_JTF_LOAD_MODE 426
					/* (requires Winamp 5.66+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)mode,IPC_SET_JTF_LOAD_MODE);
					** Pass 'mode' to alter the loading mode of the JTF window (default is mode = 0).
					** If 'value' is 1 then disable loading of the full playlist results if no search.
					** If 'value' is 0 then enable loading of the full playlist results if no search.
					**
					** If you pass 'value' as -666 to this api then it will return the current mode.
					** int mode = SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SET_JTF_LOAD_MODE);
					*/
					
					#define IPC_GET_JTF_LOAD_MODE(hwnd_winamp) SendMessageW(hwnd_winamp,WM_WA_IPC,-666,IPC_SET_JTF_LOAD_MODE)
					/* (requires Winamp 5.66+)
					** int curpan = IPC_GETPANNING(hwnd_winamp);
					** This will return the current loading mode of the JTF window.
					*/
					
					
					#define IPC_DRO_MAX 499
					
					
					// pass 0 for a copy of the skin HBITMAP
					// pass 1 for name of font to use for playlist editor likeness
					// pass 2 for font charset
					// pass 3 for font size
					#define IPC_GET_GENSKINBITMAP 503
					
					
					#ifdef __cplusplus
					class ifc_window;
					#endif
					
					typedef struct embedWindowState embedWindowState;
					
					#define FFC_CREATEEMBED   0 // param = (LPARAM)(ifc_window*)windowParent; return 1 to terminate creation.
					#define FFC_DESTROYEMBED  1
					
					typedef int (CALLBACK *FFCALLBACK)(embedWindowState* /*windowState*/, INT /*eventId*/, LPARAM /*param*/);
					
					typedef struct embedWindowState
					{
                    HWND me; //hwnd of the window
					
                    #define EMBED_FLAGS_NORESIZE 0x1
                    // set this bit to keep window from being resizable
					
                    #define EMBED_FLAGS_NOTRANSPARENCY 0x2
                    // set this bit to make gen_ff turn transparency off for this window
					
                    #define EMBED_FLAGS_NOWINDOWMENU 0x4
                    // set this bit to prevent gen_ff from automatically adding your window to the right-click menu
					
                    #define EMBED_FLAGS_GUID 0x8
                    // (5.31+) call SET_EMBED_GUID(yourEmbedWindowStateStruct, GUID) to define a GUID for this window 
					
                    #define EMBED_FLAGS_FFCALLBACK 0x10
                    // 5.55+
					
                    #define EMBED_FLAGS_LEGACY_WND 0x20
                    // 5.66+ set this bit to prevent gen_ff from adding a modern skin frame to the window
                    //       when using the legacy api methods for allowing old plug-ins to be dockable
					
                    #define SET_EMBED_GUID(windowState, windowGUID) { windowState->flags |= EMBED_FLAGS_GUID; *((GUID *)&windowState->extra_data[4])=windowGUID; }
                    #define GET_EMBED_GUID(windowState) (*((GUID *)&windowState->extra_data[4]))
					
                    int flags;  // see above
					
                    RECT r;
                    void *user_ptr;       // for application use
					
                    union
                    {
                    #pragma warning(push)
                    #pragma warning(disable:4201)
                    #pragma pack(push, 1)
                struct
                {
                struct embedWindowState *link;
                intptr_t attached; 
                intptr_t padding1[2]; //2-3
                GUID guid;  // 4-7
                #ifdef _WIN64
                intptr_t guidpadding;
                #endif
                FFCALLBACK callback; // MAKSIM UPDATE HERE
                intptr_t padding2[52]; // 9-60
                intptr_t hostcount; // 61
                intptr_t reparenting; // 62
                #ifdef __cplusplus
                ifc_window *wasabi_window;
                #else
                void *wasabi_window; // ifc_window *	
                #endif
                };
                    #pragma warning(pop)
                    #pragma pack(pop)
                    intptr_t extra_data[64];   // for internal winamp use
                    };
					} embedWindowState;
					
					
					#define IPC_GET_EMBEDIF 505
					/* (requires Winamp 2.9+)
					** HWND myframe = (HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&wa_wnd,IPC_GET_EMBEDIF);
					**
					** or
					**
					** HWND myframe = 0;
					** HWND (*embed)(embedWindowState *params)=0;
					**   *(void**)&embed = (void*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_EMBEDIF);
					**   myframe = embed(&wa_wnd);
					**
					** You pass an embedWindowState* and it will return a hwnd for the frame window or if you
					** pass wParam as null then it will return a HWND embedWindow(embedWindowState *);
					**
					** Embed window can send notification to the first child. 
					** Notifications will come in form of WM_NOTIFY.
					** Notifications:
					*/
					
					#define EWN_FIRST		(0)
					
					typedef struct __EMBEDSHOW
					{
                    NMHDR hdr;
                    BOOL fShow;
                    UINT nStatus;
					} EMBEDSHOW;
					
					#define EWN_SHOWWINDOW	(EWN_FIRST + 0) // lParam = (LPARAM)(EMBEDSHOW*)pnmh. This is preffered way to show hide your chold window
					
					#define IPC_SKINWINDOW	534
					
					#define SWF_NORESIZE EMBED_FLAGS_NORESIZE
					#define SWF_NOTRANSPARENCY EMBED_FLAGS_NOTRANSPARENCY
					#define SWF_NOWINDOWMENU EMBED_FLAGS_NOWINDOWMENU
					
					typedef struct __SKINWINDOWPARAM 
					{
                    INT cbSize; // sizeof(SKINWINDOWPARAM)
                    HWND hwndToSkin;
                    GUID windowGuid;
                    UINT flagsEx;
                    FFCALLBACK callbackFF;
					} SKINWINDOWPARAM;
					
					
					typedef struct embedEnumStruct
					{
                    int (*enumProc)(embedWindowState *ws, struct embedEnumStruct *param); // return 1 to abort
                    int user_data; // or more :)
					} embedEnumStruct; // pass 
					#define IPC_EMBED_ENUM 532
					/* (requires Winamp 2.9+)
					*/
					
					
					#define IPC_EMBED_ISVALID 533
					/* (requires Winamp 2.9+)
					** int valid = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)embedhwnd,IPC_EMBED_ISVALID);
					** Pass a hwnd in the wParam to this to check if the hwnd is a valid embed window or not.
					*/
					
					
					#define IPC_EMBED_ADD_LEGACY 535
					/* (requires Winamp 5.66+)
					** int done = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(embedWindowState*)ws,IPC_EMBED_ADD_LEGACY);
					** You pass an embedWindowState* filled with any appropriate details and ensure you add
					** EMBED_FLAGS_LEGACY_WND to the 'flags' member to ensure it will be handled correctly.
					** Returns 1 if the request was able to be processed.
					*/
					
					
					#define IPC_EMBED_REMOVE_LEGACY 536
					/* (requires Winamp 5.66+)
					** int done = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(embedWindowState*)ws,IPC_EMBED_REMOVE_LEGACY);
					** You pass an embedWindowState* filled with any appropriate details and ensure you add
					** EMBED_FLAGS_LEGACY_WND to the 'flags' member to ensure it will be handled correctly.
					** Returns 1 if the request was able to be processed.
					*/
					
					
					#define IPC_EMBED_UPDATE_LEGACY_POS 537
					/* (requires Winamp 5.66+)
					** int done = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(embedWindowState*)ws,IPC_EMBED_UPDATE_LEGACY_POS);
					** You pass an embedWindowState* filled with an updated position of the window by filling
					** int the 'r' member so Winamp will know the correct position of the window after moving.
					** Returns 1 if the request was able to be processed.
					**
					** Not sending this (ideally at the end of the window being moved) will likely cause issues
					** with the placement and docking of the legacy window when Winamp's naitve and any embedded
					** windows are then moved.
					*/
					
					
					#define IPC_GET_EMBED_SNAPFUNC 538
					/* (requires Winamp 5.66+)
					** SnapToScreen is used to adjust the rect passed so as to keep the window no the screen
					** RECT r;
					** BOOL (*SnapToScreen)(LPRECT outrc)=0;
					**   *(void**)&SnapToScreen = (void*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_EMBED_SNAPFUNC);
					**   SnapToScreen(&r);
					**
					** or
					**
					** SnapWindowToAllWindows is used to allow the window to natively dock to other Winamp windows
					** RECT r;
					** HWND myWnd = 0;
					** void (*SnapWindowToAllWindows)(LPRECT outrc, HWND hwndNoSnap)=0;
					**   *(void**)&SnapWindowToAllWindows = (void*)SendMessageW(hwnd_winamp,WM_WA_IPC,1,IPC_GET_EMBED_SNAPFUNC);
					**   SnapWindowToAllWindows(&r, myWnd);
					*/
					
					
					#define IPC_CONVERTFILE 506
					/* (requires Winamp 2.92+)
					** Converts a given file to a different format (PCM, MP3, etc...)
					** To use, pass a pointer to a waFileConvertStruct struct
					** This struct can be either on the heap or some global
					** data, but NOT on the stack. At least, until the conversion is done.
					**
					** eg: SendMessageW(hwnd_winamp,WM_WA_IPC,&myConvertStruct,IPC_CONVERTFILE);
					**
					** Return value:
					** 0: Can't start the conversion. Look at myConvertStruct->error for details.
					** 1: Conversion started. Status messages will be sent to the specified callbackhwnd.
					**    Be sure to call IPC_CONVERTFILE_END when your callback window receives the
					**    IPC_CB_CONVERT_DONE message.
					*/
					#ifdef __cplusplus
					class ifc_audiostream;
					class AudioCoder;
					#else
					typedef void *ifc_audiostream;
					typedef void *AudioCoder;
					#endif
					typedef struct 
					{
                    char *sourcefile;  // "c:\\source.mp3"
                    char *destfile;    // "c:\\dest.pcm"
                    intptr_t destformat[8]; // like 'PCM ',srate,nch,bps.
                    //hack alert! you can set destformat[6]=mmioFOURCC('I','N','I',' '); and destformat[7]=(int)my_ini_file; (where my_ini_file is a char*)
                    HWND callbackhwnd; // window that will receive the IPC_CB_CONVERT notification messages
                    
                    //filled in by winamp.exe
                    char *error;        //if IPC_CONVERTFILE returns 0, the reason will be here
					
                    int bytes_done;     //you can look at both of these values for speed statistics
                    int bytes_total;
                    int bytes_out;
					
                    int killswitch;     // don't set it manually, use IPC_CONVERTFILE_END
                    	/* everything below is for internal use */
				ifc_audiostream *decoder; // for internal winamp use 
				HANDLE convert_thread;														 
				HANDLE file_handle;			
				AudioCoder *audio_coder;
				HMODULE encoder_mod;			
				int bps;								
				int channels;						
				int sample_rate;				
                    intptr_t extra_data[56]; // for future use
					} convertFileStruct;
					
					
					#define IPC_CONVERTFILEW 515
					// (requires Winamp 5.36+)
					
					typedef struct 
					{
                    wchar_t *sourcefile;  // "c:\\source.mp3"
                    wchar_t *destfile;    // "c:\\dest.pcm"
                    intptr_t destformat[8]; // like 'PCM ',srate,nch,bps.
                    //hack alert! you can set destformat[6]=mmioFOURCC('I','N','I',' '); and destformat[7]=(int)my_ini_file; (where my_ini_file is a char*)
                    HWND callbackhwnd; // window that will receive the IPC_CB_CONVERT notification messages
                    
                    //filled in by winamp.exe
                    wchar_t *error;        //if IPC_CONVERTFILE returns 0, the reason will be here
					
                    int bytes_done;     //you can look at both of these values for speed statistics
                    int bytes_total;
                    int bytes_out;
					
                    int killswitch;     // don't set it manually, use IPC_CONVERTFILE_END
				/* everything below is for internal use */
				ifc_audiostream *decoder; // for internal winamp use 
				HANDLE convert_thread;														 
				HANDLE file_handle;			
				AudioCoder *audio_coder;
				HMODULE encoder_mod;			
				int bps;								
				int channels;						
				int sample_rate;				
                    intptr_t extra_data[56]; // for future use
					} convertFileStructW;
					
					
					#define IPC_CONVERTFILE_END 507
					/* (requires Winamp 2.92+)
					** Stop/ends a convert process started from IPC_CONVERTFILE
					** You need to call this when you receive the IPC_CB_CONVERTDONE message or when you
					** want to abort a conversion process
					**
					** eg: SendMessageW(hwnd_winamp,WM_WA_IPC,&myConvertStruct,IPC_CONVERTFILE_END);
					**
					** No return value
					*/
					
					
					#define IPC_CONVERTFILEW_END 516
					// (requires Winamp 5.36+)
					
					
					typedef struct {
                    HWND hwndParent;
                    int format;
					
                    //filled in by winamp.exe
                    HWND hwndConfig;
                    int extra_data[8];
                    //hack alert! you can set extra_data[6]=mmioFOURCC('I','N','I',' '); and extra_data[7]=(int)my_ini_file; (where my_ini_file is a char*)
					} convertConfigStruct;
					
					#define IPC_CONVERT_CONFIG 508
					#define IPC_CONVERT_CONFIG_END 509
					
					
					typedef struct
					{
                    void (*enumProc)(intptr_t user_data, const char *desc, int fourcc);
                    intptr_t user_data;
					} converterEnumFmtStruct;
					
					#define IPC_CONVERT_CONFIG_ENUMFMTS 510
					/* (requires Winamp 2.92+)
					*/
					
					
					typedef struct
					{
                    char cdletter;
                    char *playlist_file;
                    HWND callback_hwnd;
					
                    //filled in by winamp.exe
                    char *error;
					} burnCDStruct;
					#define IPC_BURN_CD 511
					/* (requires Winamp 5.0+)
					*/
					
					
					typedef struct
					{
                    convertFileStruct *cfs;
                    int priority;
					} convertSetPriority;
					
					#define IPC_CONVERT_SET_PRIORITY 512
					
					
					typedef struct
					{
                    convertFileStructW *cfs;
                    int priority;
					} convertSetPriorityW;
					
					#define IPC_CONVERT_SET_PRIORITYW 517
					// (requires Winamp 5.36+)
					
					
					#define IPC_CONVERT_TEST 518
					/* requires Winamp 5.55+
					* pass a convertFileStructW and it will verify that you are able to transcode
					* checks: 
					* - valid input file
					* - valid destination format / encoder type (including winamp pro authorization for mp3)
					* - valid destination file (not that as a side-effect, this function will create a 0 byte destination file!)
					*/
					
					
					typedef struct
					{
                    unsigned int format; //fourcc value
                    char *item; // config item, eg "bitrate"
                    char *data; // buffer to recieve, or buffer that contains the data
                    int len; // length of the data buffer (only used when getting a config item)
                    char *configfile; // config file to read from
					} convertConfigItem;
					
					#define IPC_CONVERT_CONFIG_SET_ITEM 513 // returns TRUE if successful
					#define IPC_CONVERT_CONFIG_GET_ITEM 514 // returns TRUE if successful
					
					
					typedef struct
					{
                    const char *filename;
                    char *title; // 2048 bytes
                    int length;
                    int force_useformatting; // can set this to 1 if you want to force a url to use title formatting shit
					} waHookTitleStruct;
					
					#define IPC_HOOK_TITLES 850
					/* (requires Winamp 5.0+)
					** If you hook this message and modify the information then make sure to return TRUE.
					** If you don't hook the message then make sure you pass it on through the subclass chain.
					**
					** LRESULT CALLBACK WinampWndProc(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam)
					** {
					**   LRESULT ret = CallWindowProc((WNDPROC)WinampProc,hwnd,umsg,wParam,lParam);
					**
					**   if(message==WM_WA_IPC && lParam==IPC_HOOK_TITLES)
					**   {
					**     waHookTitleStruct *ht = (waHookTitleStruct *) wParam;
					**     // Doing ATF stuff with ht->title, whatever...
					**     return TRUE;
					**   }
					**   return ret;
					** }
					*/
					
					
					typedef struct
					{
                    const wchar_t *filename;
                    wchar_t *title; // 2048 characters
                    int length;
                    int force_useformatting; // can set this to 1 if you want to force a url to use title formatting shit
					} waHookTitleStructW;
					
					#define IPC_HOOK_TITLESW 851
					/* (requires Winamp 5.3+)
					** See information on IPC_HOOK_TITLES for how to process this.
					*/
					
					
					#define IPC_GETSADATAFUNC 800
					/* (requires Winamp 5.0+)
					** <returned_function_pointer> = SendMessageW(hwnd_winamp,WM_WA_IPC,param,IPC_GETSADATAFUNC);
					** where param can be 0 , 1 or 2.  A param == 2 is meant to replace param == 0 as of 5.5+
					**
					** void (*export_sa_setreq)(int want);
					** *(void **)&export_sa_setreq=(void *)SendMessageW(hwnd_winamp,WM_WA_IPC,1,IPC_GETSADATAFUNC);
					** This can called as either want = 0 -> use user setting (ie classic skin mode)
					**                        or want = 1 -> just obtain data (ie modern skin mode)
					**
					** (replaces passing wParam == 0 and if not present then this call will return a null function pointer)
					** char * (*export_sa_get)(char data[75*2 + 8]);
					** *(void **)&export_sa_get=(void*)SendMessageW(hwnd_winamp,WM_WA_IPC,2,IPC_GETSADATAFUNC);
					**
					** When called this will fill the passed buffer with 150 bytes of data and return a pointer to it.
					** char data[75*2 + 8];
					** char *p = export_sa_get(data);
					**
					**
					** (deprecated as of at least 5.5+ but should still work)
					** char * (*export_sa_get_deprecated)();
					** *(void **)&export_sa_get_deprecated=(void*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETSADATAFUNC);
					**
					** When called this will return 150 bytes of data as a static buffer inside Winamp.
					** char *data = export_sa_get_deprecated();
					*/
					
					
					#define IPC_GETVUDATAFUNC 801
					/* (requires Winamp 5.0+)
					**
					** int (*export_vu_get)(int channel);
					** *(void **)&export_vu_get=(void*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVUDATAFUNC);
					**
					**
					** This returns a function pointer of int export_vu_get(int channel) and when called it
					** will return values between 0 - 255 or or it will return -1 for a bad channel / value.
					**
					** Calling export_vu_get(0) will return the left channel.
					** Calling export_vu_get(1) will return the right channel.
					*/
					
					
					#define IPC_ISMAINWNDVISIBLE 900
					/* (requires Winamp 5.0+)
					** int visible=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_ISMAINWNDVISIBLE);
					** You send this to Winamp to query if the main window is visible or not such as by
					** unchecking the option in the main right-click menu. If the main window is visible then
					** this will return 1 otherwise it returns 0.
					*/
					
					
					typedef struct
					{
                    int numElems;
                    int *elems;
                    HBITMAP bm; // set if you want to override
					} waSetPlColorsStruct;
					
					#define IPC_SETPLEDITCOLORS 920
					/* (requires Winamp 5.0+)
					** This is sent by gen_ff when a modern skin is being loaded to set the colour scheme for
					** the playlist editor. When sent numElems is usually 6 and matches with the 6 possible
					** colours which are provided be pledit.txt from the classic skins. The elems array is
					** defined as follows:
					**
					** elems = 0  =>  normal text
					** elems = 1  =>  current text
					** elems = 2  =>  normal background
					** elems = 3  =>  selected background
					** elems = 4  =>  minibroswer foreground
					** elems = 5  =>  minibroswer background
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_SETPLEDITCOLORS)
					** {
					**   waSetPlColorsStruct* colStr = (waSetPlColorsStruct*)wp;
					**   if(colStr)
					**   {
					**      // set or inspect the colours being used (basically for gen_ff's benefit)
					**   }
					** }
					*/
					
					
					typedef struct
					{
                    HWND wnd;
                    int xpos; // in screen coordinates
                    int ypos;
					} waSpawnMenuParms;
					
					// waSpawnMenuParms2 is used by the menubar submenus
					typedef struct
					{
                    HWND wnd;
                    int xpos; // in screen coordinates
                    int ypos;
                    int width;
                    int height;
					} waSpawnMenuParms2;
					
					// the following IPC use waSpawnMenuParms as parameter
					#define IPC_SPAWNEQPRESETMENU 933
					#define IPC_SPAWNFILEMENU 934 //menubar
					#define IPC_SPAWNOPTIONSMENU 935 //menubar
					#define IPC_SPAWNWINDOWSMENU 936 //menubar
					#define IPC_SPAWNHELPMENU 937 //menubar
					#define IPC_SPAWNPLAYMENU 938 //menubar
					#define IPC_SPAWNPEFILEMENU 939 //menubar
					#define IPC_SPAWNPEPLAYLISTMENU 940 //menubar
					#define IPC_SPAWNPESORTMENU 941 //menubar
					#define IPC_SPAWNPEHELPMENU 942 //menubar
					#define IPC_SPAWNMLFILEMENU 943 //menubar
					#define IPC_SPAWNMLVIEWMENU 944 //menubar
					#define IPC_SPAWNMLHELPMENU 945 //menubar
					#define IPC_SPAWNPELISTOFPLAYLISTS 946
					
					
					#define WM_WA_SYSTRAY WM_USER+1
					/* This is sent by the system tray when an event happens (you might want to simulate it).
					**
					** if(uMsg == WM_WA_SYSTRAY)
					** {
					**   switch(lParam)
					**   {
					**     // process the messages sent from the tray
					**   }
					** }
					*/
					
					
					#define WM_WA_MPEG_EOF WM_USER+2
					/* Input plugins send this when they are done playing back the current file to inform
					** Winamp or anyother installed plugins that the current
					**
					** if(uMsg == WM_WA_MPEG_EOF)
					** {
					**   // do what is needed here
					** }
					*/
					
					
					//// video stuff
					
					#define IPC_IS_PLAYING_VIDEO 501 // returns >1 if playing, 0 if not, 1 if old version (so who knows):)
					#define IPC_GET_IVIDEOOUTPUT 500 // see below for IVideoOutput interface
					#define VIDEO_MAKETYPE(A,B,C,D) ((A) | ((B)<<8) | ((C)<<16) | ((D)<<24))
					#define VIDUSER_SET_INFOSTRING 0x1000
					#define VIDUSER_GET_VIDEOHWND  0x1001
					#define VIDUSER_SET_VFLIP      0x1002
					#define VIDUSER_SET_TRACKSELINTERFACE 0x1003 // give your ITrackSelector interface as param2
					#define VIDUSER_OPENVIDEORENDERER 0x1004
					#define VIDUSER_CLOSEVIDEORENDERER 0x1005
					#define VIDUSER_GETPOPUPMENU 0x1006
					#define VIDUSER_SET_INFOSTRINGW 0x1007
					#define VIDUSER_SET_THREAD_SAFE 0x1008 // set param2 = 1 if open(), draw() and close() will be called on the same thread 
					#define VIDUSER_SET_PALETTE 0x1010
					
					#define IPC_HAS_VIDEO_SUPPORT 502
					/* (requires Winamp 5.666+)
					** int has_video_support=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_HAS_VIDEO_SUPPORT);
					** indicates if video support is enabled or not
					** This returns 0 if video support is disabled (no compatible input plug-ins or via
					** the no_video=1 winamp.ini configuration option) and 1 if enabled (so will return
					** 1 on all older Winamp clients where this API method is not available).
					*/
					
					typedef struct
					{
                    int w;
                    int h;
                    int vflip;
                    double aspectratio;
                    unsigned int fmt;
					} VideoOpenStruct;
					
					#ifndef NO_IVIDEO_DECLARE
					#ifdef __cplusplus
					
					class VideoOutput;
					class SubsItem;
					
					#ifndef _NSV_DEC_IF_H_
					struct YV12_PLANE {
                    unsigned char* baseAddr;
                    long rowBytes;
					} ;
					
					struct YV12_PLANES {
                    YV12_PLANE y;
                    YV12_PLANE u;
                    YV12_PLANE v;
					};
					#endif
					
					class IVideoOutput
					{
                    public:
                virtual ~IVideoOutput() { }
                virtual int open(int w, int h, int vflip, double aspectratio, unsigned int fmt)=0;
                virtual void setcallback(LRESULT (*msgcallback)(void *token, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam), void *token) { (void)token; (void)msgcallback; /* to eliminate warning C4100 */ }
                virtual void close()=0;
                virtual void draw(void *frame)=0;
                virtual void drawSubtitle(SubsItem *item) {UNREFERENCED_PARAMETER(item);  }
                virtual void showStatusMsg(const char *text) {UNREFERENCED_PARAMETER(text);  }
                virtual int get_latency() { return 0; }
                virtual void notifyBufferState(int bufferstate) { UNREFERENCED_PARAMETER(bufferstate); } /* 0-255*/
				virtual INT_PTR extended(INT_PTR param1, INT_PTR param2, INT_PTR param3) { UNREFERENCED_PARAMETER(param1); UNREFERENCED_PARAMETER(param2); UNREFERENCED_PARAMETER(param3); return 0; } // Dispatchable, eat this!
					};
					
					class ITrackSelector 
					{
                    public:
                virtual int getNumAudioTracks()=0;
                virtual void enumAudioTrackName(int n, char *buf, int size)=0;
                virtual int getCurAudioTrack()=0;
                virtual int getNumVideoTracks()=0;
                virtual void enumVideoTrackName(int n, char *buf, int size)=0;
                virtual int getCurVideoTrack()=0;
					
                virtual void setAudioTrack(int n)=0;
                virtual void setVideoTrack(int n)=0;
					};
					
					#endif //cplusplus
					#endif//NO_IVIDEO_DECLARE
					
					// these messages are callbacks that you can grab by subclassing the winamp window
					
					// wParam = 
					#define IPC_CB_WND_EQ 0 // use one of these for the param
					#define IPC_CB_WND_PE 1
					#define IPC_CB_WND_MB 2
					#define IPC_CB_WND_VIDEO 3
					#define IPC_CB_WND_MAIN 4
					
					#define IPC_CB_ONSHOWWND 600 
					#define IPC_CB_ONHIDEWND 601 
					
					#define IPC_CB_GETTOOLTIP 602
					#define IPC_CB_GETTOOLTIPW 1602
					
					#define IPC_CB_MISC 603
					#define IPC_CB_MISC_TITLE 0  // start of playing/stop/pause
					#define IPC_CB_MISC_VOLUME 1 // volume/pan
					#define IPC_CB_MISC_STATUS 2 // start playing/stop/pause/ffwd/rwd
					#define IPC_CB_MISC_EQ 3
					#define IPC_CB_MISC_INFO 4
					#define IPC_CB_MISC_VIDEOINFO 5
					#define IPC_CB_MISC_TITLE_RATING 6 // (5.5+ for when the rating is changed via the songticker menu on current file)
					#define IPC_CB_MISC_PAUSE 7	// 5.65+
					#define IPC_CB_MISC_UNPAUSE 8 // 5.65+
					
					/* Example of using IPC_CB_MISC_STATUS to detect the start of track playback with 5.x
					**
					** if(lParam == IPC_CB_MISC && wParam == IPC_CB_MISC_STATUS)
					** {
					**   if(SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_ISPLAYING) == 1 &&
					**      !SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETOUTPUTTIME))
					**   {
					**     char* file = (char*)SendMessageW(hwnd_winamp,WM_WA_IPC,
					**                  SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLISTPOS),IPC_GETPLAYLISTFILE);
					**     // only output if a valid file was found
					**     if(file)
					**     {
					**       MessageBox(hwnd_winamp,file,"starting",0);
					**       // or do something else that you need to do
					**     }
					**   }
					** }
					*/
					
					
					#define IPC_CB_CONVERT_STATUS 604 // param value goes from 0 to 100 (percent)
					#define IPC_CB_CONVERT_DONE   605
					
					
					#define IPC_ADJUST_FFWINDOWSMENUPOS 606
					/* (requires Winamp 2.9+)
					** int newpos=SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)adjust_offset,IPC_ADJUST_FFWINDOWSMENUPOS);
					** This will move where Winamp expects the freeform windows in the menubar windows main
					** menu. This is useful if you wish to insert a menu item above extra freeform windows.
					*/
					
					
					#define IPC_ISDOUBLESIZE 608
					/* (requires Winamp 5.0+)
					** int dsize=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_ISDOUBLESIZE);
					** You send this to Winamp to query if the double size mode is enabled or not.
					** If it is on then this will return 1 otherwise it will return 0.
					*/
					
					
					#define IPC_ADJUST_FFOPTIONSMENUPOS 609
					/* (requires Winamp 2.9+)
					** int newpos=SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)adjust_offset,IPC_ADJUST_FFOPTIONSMENUPOS);
					** moves where winamp expects the freeform preferences item in the menubar windows main
					** menu. This is useful if you wish to insert a menu item above the preferences item.
					** If you pass adjust_offset as zero then it will return the current offset without adjusting it.
					**
					** Note: This setting was ignored by gen_ff until it was fixed in 5.1
					**       gen_ff would assume that the menu position was 11 in all cases and so when you
					**       had two plugins attempting to add entries into the main right click menu it
					**       would cause the 'colour themes' submenu to either be incorrectly duplicated or
					**       to just disappear instead.
					*/
					
					
					#define IPC_GETTIMEDISPLAYMODE 610
					/* (requires Winamp 5.0+)
					** int mode=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETTIMEDISPLAYMODE);
					** This will return the status of the time display i.e. shows time elapsed or remaining.
					** This returns 0 if Winamp is displaying time elapsed or 1 for the time remaining.
					*/
					
					
					#define IPC_SETVISWND 611
					/* (requires Winamp 5.0+)
					** int viswnd=(HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)viswnd,IPC_SETVISWND);
					** This allows you to set a window to receive the following message commands (which are
					** used as part of the modern skin integration).
					** When you have finished or your visualisation is closed then send wParam as zero to
					** ensure that things are correctly tidied up.
					*/
					
					/* The following messages are received as the LOWORD(wParam) of the WM_COMMAND message.
					** See %SDK%\winamp\wa5vis.txt for more info about visualisation integration in Winamp.
					*/
					#define ID_VIS_NEXT                     40382
					#define ID_VIS_PREV                     40383
					#define ID_VIS_RANDOM                   40384
					#define ID_VIS_FS                       40389
					#define ID_VIS_CFG                      40390
					#define ID_VIS_MENU                     40391
					
					
					#define IPC_GETVISWND 612
					/* (requires Winamp 5.0+)
					** int viswnd=(HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVISWND);
					** This returns a HWND to the visualisation command handler window if set by IPC_SETVISWND.
					*/
					
					
					#define IPC_ISVISRUNNING 613
					/* (requires Winamp 5.0+)
					** int visrunning=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_ISVISRUNNING);
					** This will return 1 if a visualisation is currently running and 0 if one is not running.
					*/
					
					
					#define IPC_CB_VISRANDOM 628 // param is status of random
					
					
					#define IPC_SETIDEALVIDEOSIZE 614
					/* (requires Winamp 5.0+)
					** This is sent by Winamp back to itself so it can be trapped and adjusted as needed with
					** the desired width in HIWORD(wParam) and the desired height in LOWORD(wParam).
					**
					** if(uMsg == WM_WA_IPC){
					**   if(lParam == IPC_SETIDEALVIDEOSIZE){
					**      wParam = MAKEWPARAM(height,width);
					**   }
					** }
					*/
					
					
					#define IPC_GETSTOPONVIDEOCLOSE 615
					/* (requires Winamp 5.0+)
					** int sovc=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETSTOPONVIDEOCLOSE);
					** This will return 1 if 'stop on video close' is enabled and 0 if it is disabled.
					*/
					
					
					#define IPC_SETSTOPONVIDEOCLOSE 616
					/* (requires Winamp 5.0+)
					** int sovc=SendMessageW(hwnd_winamp,WM_WA_IPC,enabled,IPC_SETSTOPONVIDEOCLOSE);
					** Set enabled to 1 to enable and 0 to disable the 'stop on video close' option.
					*/
					
					
					typedef struct {
                    HWND hwnd;
                    int uMsg;
                    WPARAM wParam;
                    LPARAM lParam;
					} transAccelStruct;
					
					#define IPC_TRANSLATEACCELERATOR 617
					/* (requires Winamp 5.0+)
					** (deprecated as of 5.53x+)
					*/
					
					
					typedef struct {
                    int cmd;
                    int x;
                    int y;
                    int align;
					} windowCommand; // send this as param to an IPC_PLCMD, IPC_MBCMD, IPC_VIDCMD
					
					
					#define IPC_CB_ONTOGGLEAOT 618 
					
					
					#define IPC_GETPREFSWND 619
					/* (requires Winamp 5.0+)
					** HWND prefs = (HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETPREFSWND);
					** This will return a handle to the preferences dialog if it is open otherwise it will
					** return zero. A simple check with the OS api IsWindow(..) is a good test if it's valid.
					**
					** e.g.  this will open (or close if already open) the preferences dialog and show if we
					**       managed to get a valid 
					** SendMessageW(hwnd_winamp,WM_COMMAND,MAKEWPARAM(WINAMP_OPTIONS_PREFS,0),0);
					** MessageBox(hwnd_winamp,(IsWindow((HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETPREFSWND))?"Valid":"Not Open"),0,MB_OK);
					*/
					
					
					#define IPC_SET_PE_WIDTHHEIGHT 620
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&point,IPC_SET_PE_WIDTHHEIGHT);
					** You pass a pointer to a POINT structure which holds the width and height and Winamp
					** will set the playlist editor to that size (this is used by gen_ff on skin changes).
					** There does not appear to be any bounds limiting with this so it is possible to create
					** a zero size playlist editor window (which is a pretty silly thing to do).
					*/
					
					
					#define IPC_GETLANGUAGEPACKINSTANCE 621
					/* (requires Winamp 5.0+)
					** HINSTANCE hInst = (HINSTANCE)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLANGUAGEPACKINSTANCE);
					** This will return the HINSTANCE to the currently used language pack file for winamp.exe
					**
					** (5.5+)
					** If you pass 1 in wParam then you will have zero returned if a language pack is in use.
					** if(!SendMessageW(hwnd_winamp,WM_WA_IPC,1,IPC_GETLANGUAGEPACKINSTANCE)){
					**   // winamp is currently using a language pack
					** }
					**
					** If you pass 2 in wParam then you will get the path to the language pack folder.
					** wchar_t* lngpackfolder = (wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,2,IPC_GETLANGUAGEPACKINSTANCE);
					**
					** If you pass 3 in wParam then you will get the path to the currently extracted language pack.
					** wchar_t* lngpack = (wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,3,IPC_GETLANGUAGEPACKINSTANCE);
					**
					** If you pass 4 in wParam then you will get the name of the currently used language pack.
					** wchar_t* lngname = (char*)SendMessageW(hwnd_winamp,WM_WA_IPC,4,IPC_GETLANGUAGEPACKINSTANCE);
					*/
					#define LANG_IDENT_STR 0
					#define LANG_LANG_CODE 1
					#define LANG_COUNTRY_CODE 2
					/*
					** (5.51+)
					** If you pass 5 in LOWORD(wParam) then you will get the ident string/code string
					** (based on the param passed in the HIWORD(wParam) of the currently used language pack.
					** The string returned with LANG_IDENT_STR is used to represent the language that the
					** language pack is intended for following ISO naming conventions for consistancy.
					**
					** wchar_t* ident_str = (wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,MAKEWPARAM(5,LANG_XXX),IPC_GETLANGUAGEPACKINSTANCE);
					**
					** e.g.
					** For the default language it will return the following for the different LANG_XXX codes
					**    LANG_IDENT_STR ->     "en-US" (max buffer size of this is 9 wchar_t)
					**    LANG_LANG_CODE ->     "en"    (language code)
					**    LANG_COUNTRY_CODE ->  "US"    (country code)
					**
					** On pre 5.51 installs you can get LANG_IDENT_STR using the following method
					** (you'll have to custom process the string returned if you want the langugage or country but that's easy ;) )
					**
					** #define LANG_PACK_LANG_ID 65534 (if you don't have lang.h)
					** HINSTANCE hInst = (HINSTANCE)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLANGUAGEPACKINSTANCE);
					** wchar_t buffer[9] = {0};
					** LoadStringW(hInst,LANG_PACK_LANG_ID,buffer,sizeof(buffer)/sizeof(wchar_t));
					**
					**
					**
					** The following example shows how using the basic api will allow you to load the playlist
					** context menu resource from the currently loaded language pack or it will fallback to
					** the default winamp.exe instance.
					**
					** HINSTANCE lang = (HINSTANCE)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLANGUAGEPACKINSTANCE);
					** HMENU popup = GetSubMenu(GetSubMenu((LoadMenu(lang?lang:GetModuleHandle(0),MAKEINTRESOURCE(101))),2),5);
					**   // do processing as needed on the menu before displaying it
					**   TrackPopupMenuEx(orig,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,rc.left,rc.bottom,hwnd_owner,0);
					**   DestroyMenu(popup);
					**
					** If you need a specific menu handle then look at IPC_GET_HMENU for more information.
					*/
					
					
					#define IPC_CB_PEINFOTEXT 622 // data is a string, ie: "04:21/45:02"
					
					
					#define IPC_CB_OUTPUTCHANGED 623 // output plugin was changed in config
					
					
					#define IPC_GETOUTPUTPLUGIN 625
					/* (requires Winamp 5.0+)
					** char* outdll = (char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETOUTPUTPLUGIN);
					** This returns a string of the current output plugin's dll name.
					** e.g. if the directsound plugin was selected then this would return 'out_ds.dll'.
					*/
					
					
					#define IPC_SETDRAWBORDERS 626
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,enabled,IPC_SETDRAWBORDERS);
					** Set enabled to 1 to enable and 0 to disable drawing of the playlist editor and winamp
					** gen class windows (used by gen_ff to allow it to draw its own window borders).
					*/
					
					
					#define IPC_DISABLESKINCURSORS 627
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,enabled,IPC_DISABLESKINCURSORS);
					** Set enabled to 1 to enable and 0 to disable the use of skinned cursors.
					*/
					
					
					#define IPC_GETSKINCURSORS 628
					/* (requires Winamp 5.36+)
					** data = (WACURSOR)cursorId. (check wa_dlg.h for values)
					*/
					
					
					#define IPC_CB_RESETFONT 629
					
					
					#define IPC_IS_FULLSCREEN 630
					/* (requires Winamp 5.0+)
					** int val=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_IS_FULLSCREEN);
					** This will return 1 if the video or visualisation is in fullscreen mode or 0 otherwise.
					*/
					
					
					#define IPC_SET_VIS_FS_FLAG 631
					/* (requires Winamp 5.0+)
					** A vis should send this message with 1/as param to notify winamp that it has gone to or has come back from fullscreen mode
					*/
					
					
					#define IPC_SHOW_NOTIFICATION 632
					/* (requires Winamp 5.0+ & Modern skin support - gen_ff.dll present)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_SHOW_NOTIFICATION);
					** If a Modern skin is loaded and this message is sent/received then it will
					** trigger the Modern skin notifier to appear (subject to user settings).
					*/
					
					
					#define IPC_GETSKININFO 633
					#define IPC_GETSKININFOW 1633
					/* (requires Winamp 5.0+)
					** This is a notification message sent to the main Winamp window by itself whenever it
					** needs to get information to be shown about the current skin in the 'Current skin
					** information' box on the main Skins page in the Winamp preferences.
					**
					** When this notification is received and the current skin is one you are providing the
					** support for then you return a valid buffer for Winamp to be able to read from with
					** information about it such as the name of the skin file.
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_GETSKININFO){
					**   if(is_our_skin()){
					**      return is_our_skin_name();
					**   }
					** }
					*/
					
					
					#define IPC_GET_MANUALPLADVANCE 634
					/* (requires Winamp 5.03+)
					** int val=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_MANUALPLADVANCE);
					** IPC_GET_MANUALPLADVANCE returns the status of the Manual Playlist Advance.
					** If enabled this will return 1 otherwise it will return 0.
					*/
					
					
					#define IPC_SET_MANUALPLADVANCE 635
					/* (requires Winamp 5.03+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,value,IPC_SET_MANUALPLADVANCE);
					** IPC_SET_MANUALPLADVANCE sets the status of the Manual Playlist Advance option.
					** Set value = 1 to turn it on and value = 0 to turn it off.
					*/
					
					
					#define IPC_GET_NEXT_PLITEM 636
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_NEXT_PLITEM);
					**
					** Sent to Winamp's main window when an item has just finished playback or the next
					** button has been pressed and requesting the new playlist item number to go to.
					**
					** Subclass this message in your application to return the new item number.
					** Return -1 for normal Winamp operation (default) or the new item number in
					** the playlist to be played instead of the originally selected next track.
					*/
					
					
					#define IPC_GET_PREVIOUS_PLITEM 637
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_PREVIOUS_PLITEM);
					**
					** Sent to Winamp's main window when the previous button has been pressed and Winamp is
					** requesting the new playlist item number to go to.
					**
					** Return -1 for normal Winamp operation (default) or the new item number in
					** the playlist to be played instead of the originally selected previous track.
					*/
					
					
					#define IPC_IS_WNDSHADE 638
					/* (requires Winamp 5.04+)
					** int is_shaded=SendMessageW(hwnd_winamp,WM_WA_IPC,wnd,IPC_IS_WNDSHADE);
					** Pass 'wnd' as an id as defined for IPC_GETWND or pass -1 to query the status of the
					** main window. This returns 1 if the window is in winshade mode and 0 if it is not.
					** Make sure you only test for this on a 5.04+ install otherwise you get a false result.
					** (See the notes about unhandled WM_WA_IPC messages).
					*/
					
					
					#define IPC_SETRATING 639 
					/* (requires Winamp 5.04+ with ML)
					** int rating=SendMessageW(hwnd_winamp,WM_WA_IPC,rating,IPC_SETRATING);
					** This will allow you to set the 'rating' on the current playlist entry where 'rating'
					** is an integer value from 0 (no rating) to 5 (5 stars).
					**
					** The following example should correctly allow you to set the rating for any specified
					** playlist entry assuming of course that you're trying to get a valid playlist entry.
					**
					** void SetPlaylistItemRating(int item_to_set, int rating_to_set){
					** int cur_pos=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLISTPOS);
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,item_to_set,IPC_SETPLAYLISTPOS);
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,rating_to_set,IPC_SETRATING);
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,cur_pos,IPC_SETPLAYLISTPOS);
					** }
					**
					** Note: Winamp 5.6+ allows you to save the rating directly into the file as long as the
					**       file being rated supports the rating metadata field via a supporting input plug-in
					**       to process the tag save as appropriate. If not then the rating will not be saved.
					*/
					
					
					#define IPC_GETRATING 640 
					/* (requires Winamp 5.04+ with ML)
					** int rating=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETRATING);
					** This returns the current playlist entry's rating between 0 (no rating) to 5 (5 stars).
					**
					** The following example should correctly allow you to get the rating for any specified
					** playlist entry assuming of course that you're trying to get a valid playlist entry.
					**
					** int GetPlaylistItemRating(int item_to_get, int rating_to_set){
					** int cur_pos=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETLISTPOS), rating = 0;
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,item_to_get,IPC_SETPLAYLISTPOS);
					**   rating = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETRATING);
					**   SendMessageW(hwnd_winamp,WM_WA_IPC,cur_pos,IPC_SETPLAYLISTPOS);
					**   return rating;
					** }
					*/
					
					
					#define IPC_GETNUMAUDIOTRACKS 641
					/* (requires Winamp 5.04+)
					** int n = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETNUMAUDIOTRACKS);
					** This will return the number of audio tracks available from the currently playing item.
					*/
					
					
					#define IPC_GETNUMVIDEOTRACKS 642
					/* (requires Winamp 5.04+)
					** int n = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETNUMVIDEOTRACKS);
					** This will return the number of video tracks available from the currently playing item.
					*/
					
					
					#define IPC_GETAUDIOTRACK 643
					/* (requires Winamp 5.04+)
					** int cur = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETAUDIOTRACK);
					** This will return the id of the current audio track for the currently playing item.
					*/
					
					
					#define IPC_GETVIDEOTRACK 644
					/* (requires Winamp 5.04+)
					** int cur = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVIDEOTRACK);
					** This will return the id of the current video track for the currently playing item.
					*/
					
					
					#define IPC_SETAUDIOTRACK 645
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,track,IPC_SETAUDIOTRACK);
					** This allows you to switch to a new audio track (if supported) in the current playing file.
					*/
					
					
					#define IPC_SETVIDEOTRACK 646
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,track,IPC_SETVIDEOTRACK);
					** This allows you to switch to a new video track (if supported) in the current playing file.
					*/
					
					
					#define IPC_PUSH_DISABLE_EXIT 647
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_PUSH_DISABLE_EXIT);
					** This will let you disable or re-enable the UI exit functions (close button, context
					** menu, alt-f4). Remember to call IPC_POP_DISABLE_EXIT when you are done doing whatever
					** was required that needed to prevent exit otherwise you have to kill the Winamp process.
					*/
					
					
					#define IPC_POP_DISABLE_EXIT  648
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_POP_DISABLE_EXIT);
					** See IPC_PUSH_DISABLE_EXIT
					*/
					
					
					#define IPC_IS_EXIT_ENABLED 649
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_IS_EXIT_ENABLED);
					** This will return 0 if the 'exit' option of Winamp's menu is disabled and 1 otherwise.
					*/
					
					
					#define IPC_IS_AOT 650
					/* (requires Winamp 5.04+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_IS_AOT);
					** This will return the status of the always on top flag.
					** Note: This may not match the actual TOPMOST window flag while another fullscreen
					** application is focused if the user has the 'Disable always on top while fullscreen
					** applications are focused' option under the  General Preferences page is checked.
					*/
					
					
					#define IPC_USES_RECYCLEBIN 651
					/* (requires Winamp 5.09+)
					** int use_bin=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_USES_RECYCLEBIN);
					** This will return 1 if the deleted file should be sent to the recycle bin or
					** 0 if deleted files should be deleted permanently (default action for < 5.09).
					**
					** Note: if you use this on pre 5.09 installs of Winamp then it will return 1 which is
					** not correct but is due to the way that SendMessageW(..) handles un-processed messages.
					** Below is a quick case for checking if the returned value is correct.
					**
					** if(SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_USES_RECYCLEBIN) &&
					**    SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETVERSION)>=0x5009)
					** {
					**   // can safely follow the option to recycle the file
					** }
					** else
					*  {
					**   // need to do a permanent delete of the file
					** }
					*/
					
					
					//#define IPC_FLUSHAUDITS 652
					
					
					#define IPC_GETPLAYITEM_START 653
					#define IPC_GETPLAYITEM_END   654
					
					
					#define IPC_GETVIDEORESIZE 655
					#define IPC_SETVIDEORESIZE 656
					
					
					#define IPC_INITIAL_SHOW_STATE 657
					/* (requires Winamp 5.36+)
					** int show_state = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_INITIAL_SHOW_STATE);
					** returns the processed value of nCmdShow when Winamp was started
					** (see MSDN documentation the values passed to WinMain(..) for what this should be)
					**
					** e.g.
					** if(SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_INITIAL_SHOW_STATE) == SW_SHOWMINIMIZED){
					**   // we are starting minimised so process as needed (keep our window hidden)
					** }
					**
					** Useful for seeing if winamp was run minimised on startup so you can act accordingly.
					** On pre-5.36 versions this will effectively return SW_NORMAL/SW_SHOWNORMAL due to the
					** handling of unknown apis returning 1 from Winamp.
					*/
					
					
					#define IPC_GET_STOP_AFTER_CURRENT 658
					/* (requires Winamp 5.58+)
					** int stopping=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_STOP_AFTER_CURRENT);
					** IPC_GET_STOP_AFTER_CURRENT returns the status of the Stop After Current state.
					** If enabled this will return 0 otherwise it will return 1 (see the notes about
					** SendMessageW(WM_WA_IPC) handling with unsupported apis for why this is inverted).
					*/
					
					// >>>>>>>>>>> Next is 659
					
					#define IPC_PLCMD  1000 
					
					#define PLCMD_ADD  0
					#define PLCMD_REM  1
					#define PLCMD_SEL  2
					#define PLCMD_MISC 3
					#define PLCMD_LIST 4
					
					//#define IPC_MBCMD  1001 
					
					#define MBCMD_BACK    0
					#define MBCMD_FORWARD 1
					#define MBCMD_STOP    2
					#define MBCMD_RELOAD  3
					#define MBCMD_MISC    4
					
					#define IPC_VIDCMD 1002 
					
					#define VIDCMD_FULLSCREEN 0
					#define VIDCMD_1X         1
					#define VIDCMD_2X         2
					#define VIDCMD_LIB        3
					#define VIDPOPUP_MISC     4
					#define VIDCMD_EXIT_FS    5
					
					//#define IPC_MBURL       1003 //sets the URL
					//#define IPC_MBGETCURURL 1004 //copies the current URL into wParam (have a 4096 buffer ready)
					//#define IPC_MBGETDESC   1005 //copies the current URL description into wParam (have a 4096 buffer ready)
					//#define IPC_MBCHECKLOCFILE 1006 //checks that the link file is up to date (otherwise updates it). wParam=parent HWND
					//#define IPC_MBREFRESH   1007 //refreshes the "now playing" view in the library
					//#define IPC_MBGETDEFURL 1008 //copies the default URL into wParam (have a 4096 buffer ready)
					
					#define IPC_STATS_LIBRARY_ITEMCNT 1300 // updates library count status
					
					/*
					** IPC's in the message range 2000 - 3000 are reserved internally for freeform messages.
					** These messages are taken from ff_ipc.h which is part of the Modern skin integration.
					*/
					
					#define IPC_FF_FIRST 2000
					
					#define IPC_FF_COLOURTHEME_CHANGE IPC_FF_ONCOLORTHEMECHANGED
					#define IPC_FF_ONCOLORTHEMECHANGED IPC_FF_FIRST + 3
					/*
					** This is a notification message sent when the user changes the colour theme in a Modern
					** skin and can also be detected when the Modern skin is first loaded as the gen_ff plugin
					** applies relevant settings and styles (like the colour theme).
					**
					** The value of wParam is the name of the new color theme being switched to.
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(const char*)colour_theme_name,IPC_FF_ONCOLORTHEMECHANGED);
					**
					** (IPC_FF_COLOURTHEME_CHANGE is the name i (DrO) was using before getting a copy of
					** ff_ipc.h with the proper name in it).
					*/
					
					
					#define IPC_FF_ISMAINWND IPC_FF_FIRST + 4
					/*
					** int ismainwnd = (HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)test_wnd,IPC_FF_ISMAINWND);
					**
					** This allows you to determine if the window handle passed to it is a modern skin main
					** window or not. If it is a main window or any of its windowshade variants then it will
					** return 1.
					**
					** Because of the way modern skins are implemented, it is possible for this message to
					** return a positive test result for a number of window handles within the current Winamp
					** process. This appears to be because you can have a visible main window, a compact main
					** window and also a winshaded version.
					**
					** The following code example below is one way of seeing how this api works since it will
					** enumerate all windows related to Winamp at the time and allows you to process as
					** required when a detection happens.
					**
					**
					** EnumThreadWindows(GetCurrentThreadId(),enumWndProc,0);
					**
					** BOOL CALLBACK enumWndProc(HWND hwnd, LPARAM lParam){
					**
					**   if(SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)hwnd,IPC_FF_ISMAINWND)){
					**     // do processing in here 
					**     // or continue the enum for other main windows (if they exist)
					**     // and just comment out the line below
					**     return 0;
					**   }
					**   return 1;
					** }
					*/
					
					
					#define IPC_FF_GETCONTENTWND IPC_FF_FIRST + 5
					/*
					** HWND wa2embed = (HWND)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(HWND)test_wnd,IPC_FF_GETCONTENTWND);
					**
					** This will return the Winamp 2 window that is embedded in the window's container
					** i.e. if hwnd is the playlist editor windowshade hwnd then it will return the Winamp 2
					**      playlist editor hwnd.
					**
					** If no content is found such as the window has nothing embedded then this will return
					** the hwnd passed to it.
					*/
					
					
					#define IPC_FF_NOTIFYHOTKEY IPC_FF_FIRST + 6
					/*
					** This is a notification message sent when the user uses a global hotkey combination
					** which had been registered with the gen_hotkeys plugin.
					**
					** The value of wParam is the description of the hotkey as passed to gen_hotkeys.
					** SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(const char*)hotkey_desc,IPC_FF_NOTIFYHOTKEY);
					*/
					
					#define IPC_FF_LAST  3000
					
					
					/*
					** General IPC messages in Winamp
					**
					** All notification messages appear in the lParam of the main window message proceedure.
					*/
					
					
					#define IPC_GETDROPTARGET 3001
					/* (requires Winamp 5.0+)
					** IDropTarget* IDrop = (IDropTarget*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GETDROPTARGET);
					**
					** You call this to retrieve a copy of the IDropTarget interface which Winamp created for
					** handling external drag and drop operations on to it's Windows. This is only really
					** useful if you're providing an alternate interface and want your Windows to provide the
					** same drag and drop support as Winamp normally provides the user. Check out MSDN or
					** your prefered search facility for more information about the IDropTarget interface and
					** what's needed to handle it in your own instance.
					*/
					
					
					#define IPC_PLAYLIST_MODIFIED 3002
					/* (requires Winamp 5.0+)
					** This is a notification message sent to the main Winamp window whenever the playlist is
					** modified in any way e.g. the addition/removal of a playlist entry.
					**
					** It is not a good idea to do large amounts of processing in this notification since it
					** will slow down Winamp as playlist entries are modified (especially when you're adding
					** in a large playlist).
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_PLAYLIST_MODIFIED)
					** {
					**   // do what you need to do here
					** }
					*/
					
					
					#define IPC_PLAYING_FILE 3003
					/* (requires Winamp 5.0+)
					** This is a notification message sent to the main Winamp window when playback begins for
					** a file. This passes the full filepath in the wParam of the message received.
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_PLAYING_FILE)
					** {
					**   // do what you need to do here, e.g.
					**   process_file((char*)wParam);
					** }
					*/
					
					
					#define IPC_PLAYING_FILEW 13003
					/* (requires Winamp 5.3+)
					** This is a notification message sent to the main Winamp window when playback begins for
					** a file. This passes the full filepath in the wParam of the message received.
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_PLAYING_FILEW)
					** {
					**   // do what you need to do here, e.g.
					**   process_file((wchar_t*)wParam);
					** }
					*/
					
					#define IPC_FILE_TAG_MAY_UPDATEW 3046
					/* (requires Winamp 5.66+)
					** This is a notification message sent to the main Winamp window when a file is about to
					** be opened in the file info editor and so may have it's tag (e.g. id3) updated.
					**
					** The wParam value holds a copy of the filepath of the file which may update and this
					** can be sent without a matching IPC_FILE_TAG_MAY_HAVE_UPDATED(W) message if the user
					** does not make any changes or the file being edited does not support tagging updates.
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_FILE_TAG_MAY_UPDATEW)
					** {
					**   // do what you need to do here, e.g.
					** }
					*/
					
					#define IPC_FILE_TAG_MAY_HAVE_UPDATED 3004
					#define IPC_FILE_TAG_MAY_HAVE_UPDATEDW 3005
					/* (requires Winamp 5.0+)
					** This is a notification message sent to the main Winamp window when a file's tag
					** (e.g. id3) may have been updated. This appears to be sent when the InfoBox(..) function
					** of the associated input plugin returns a 1 (which is the file information dialog/editor
					** call normally).
					**
					** The wParam value holds a copy of the filepath of the file which was updated.
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_FILE_TAG_MAY_HAVE_UPDATED)
					** {
					**   // do what you need to do here, e.g.
					**   update_info_on_file_update((char*)wParam);
					** }
					*/
					
					
					#define IPC_ALLOW_PLAYTRACKING 3007
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,allow,IPC_ALLOW_PLAYTRACKING);
					** Send allow as nonzero to allow play tracking and zero to disable the mode.
					** This is useful if you're an input plugin and need to edit a tag in a file
					** whilst playing that track so this can be sent to Winamp so it appears like
					** there wasn't a stop in the playback of the file (as far as the UI display).
					*/
					
					
					#define IPC_HOOK_OKTOQUIT 3010
					/* (requires Winamp 5.0+)
					** This is a notification message sent to the main Winamp window asking if it's okay to
					** close or not. Return zero to prevent Winamp from closing or return anything non-zero
					** to allow Winamp to close.
					**
					** The best implementation of this option is to let the message pass through to the
					** original window proceedure since another plugin may want to have a say in the matter
					** with regards to Winamp closing.
					**
					** if(uMsg == WM_WA_IPC && lParam == IPC_HOOK_OKTOQUIT)
					** {
					**   // do what you need to do here, e.g.
					**   if(no_shut_down())
					**   {
					**     return 0;
					**   }
					** }
					*/
					
					
					#define IPC_WRITECONFIG 3011
					/* (requires Winamp 5.0+)
					** SendMessageW(hwnd_winamp,WM_WA_IPC,write_type,IPC_WRITECONFIG);
					**
					** Send write_type as 2 to write all config settings and the current playlist.
					**
					** Send write_type as 1 to write the playlist and common settings.
					** This won't save the following ini settings::
					**
					**   defext, titlefmt, proxy, visplugin_name, dspplugin_name, check_ft_startup,
					**   visplugin_num, pe_fontsize, visplugin_priority, visplugin_autoexec, dspplugin_num,
					**   sticon, splash, taskbar, dropaotfs, ascb_new, ttips, riol, minst, whichicon,
					**   whichicon2, addtolist, snap, snaplen, parent, hilite, disvis, rofiob, shownumsinpl,
					**   keeponscreen, eqdsize, usecursors, fixtitles, priority, shuffle_morph_rate,
					**   useexttitles, bifont, inet_mode, ospb, embedwnd_freesize, no_visseh
					** (the above was valid for 5.1)
					**
					** Send write_type as 0 to write the common and less common settings and no playlist.
					*/
					
					
					#define IPC_UPDATE_URL 3012
					// pass the URL (char *) in lparam, will be free()'d on done. 
					
					
					#define IPC_GET_RANDFUNC 3015 // returns a function to get a random number
					/* (requires Winamp 5.1+)
					** int (*randfunc)(void) = (int(*)(void))SendMessageW(plugin.hwndParent,WM_WA_IPC,0,IPC_GET_RANDFUNC);
					** if(randfunc && randfunc != 1){
					**   randfunc();
					** }
					**
					** This will return a positive 32-bit number (essentially 31-bit).
					** The check for a returned value of 1 is because that's the default return value from
					** SendMessageW(..) when it is not handled so is good to check for it in this situation.
					*/
					
					
					#define IPC_METADATA_CHANGED 3017
					/* (requires Winamp 5.1+)
					** int changed=SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)(char*)field,IPC_METADATA_CHANGED);
					** a plugin can SendMessageW this to winamp if internal metadata has changes.
					** wParam should be a char * of what field changed
					**
					** Currently used for internal actions (and very few at that) the intent of this api is
					** to allow a plugin to call it when metadata has changed in the current playlist entry
					** e.g.a new id3v2 tag was found in a stream
					**
					** The wparam value can either be NULL or a pointer to an ansi string for the metadata
					** which has changed. This can be thought of as an advanced version of IPC_UPDTITLE and
					** could be used to allow for update of the current title when a specific tag changed.
					**
					** Not recommended to be used since there is not the complete handling implemented in
					** Winamp for it at the moment.
					*/
					
					
					#define IPC_SKIN_CHANGED 3018
					/* (requires Winamp 5.1+)
					** This is a notification message sent to the main Winamp window by itself whenever
					** the skin in use is changed. There is no information sent by the wParam for this.
					**
					** if(message == WM_WA_IPC && lparam == IPC_SKIN_CHANGED)
					** {
					**   // do what you need to do to handle skin changes, e.g. call WADlg_init(hwnd_winamp);
					** }
					*/
					
					
					#define IPC_REGISTER_LOWORD_COMMAND 3019
					/* (requires Winamp 5.1+)
					** WORD id = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_REGISTER_LOWORD_COMMAND);
					** This will assign you a unique id for making your own commands such as for extra menu
					** entries. The starting value returned by this message will potentially change as and
					** when the main resource file of Winamp is updated with extra data so assumptions cannot
					** be made on what will be returned and plugin loading order will affect things as well.
					
					** 5.33+
					** If you want to reserve more than one id, you can pass the number of ids required in wParam
					*/
					
					
					typedef struct 
					{
                    wchar_t *name; // filled in by plugin, make sure it's a unicode string!! (i.e. L"myObject" instead of "myObject).
                    struct IDispatch *dispatch; // filled in by plugin 
                    DWORD id; // filled in by winamp on return
					} DispatchInfo;
					
					#define IPC_GET_DISPATCH_OBJECT 3020  // gets winamp main IDispatch * (for embedded webpages)
					#define IPC_GET_UNIQUE_DISPATCH_ID 3021 // gives you a unique dispatch ID that won't conflict with anything in winamp's IDispatch *
					#define IPC_ADD_DISPATCH_OBJECT 3022 // add your own dispatch object into winamp's.  This lets embedded webpages access your functions
					// pass a pointer to DispatchInfo (see below).  Winamp makes a copy of all this data so you can safely delete it later
					
					#define IPC_REMOVE_DISPATCH_OBJECT 3038 
					/* (requires Winamp 5.56+)
					** remove registered IDispatch. pass (DWORD)dispatchId ad parameter
					*/
					
					// see IPC_JSAPI2_GET_DISPATCH_OBJECT for version 2 of the Dispatchable scripting interface
					
					
					#define IPC_GET_PROXY_STRING 3023
					/* (requires Winamp 5.11+)
					** char* proxy_string=(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_PROXY_STRING);
					** This will return the same string as is shown on the General Preferences page.
					*/
					
					
					#define IPC_USE_REGISTRY 3024 
					/* (requires Winamp 5.11+)
					** int reg_enabled=SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_USE_REGISTRY);
					** This will return 0 if you should leave your grubby hands off the registry (i.e. for
					** lockdown mode). This is useful if Winamp is run from a USB drive and you can't alter
					** system settings, etc.
					*/
					
					
					#define IPC_GET_API_SERVICE 3025 
					/* (requires Winamp 5.12+)
					** api_service* api_service = (api_service*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_API_SERVICE);
					** This api will return Winamp's api_service pointer (which is what Winamp3 used, heh).
					** If this api is not supported in the Winamp version that is being used at the time then
					** the returned value from this api will be 1 which is a good version check.
					**
					** As of 5.12 there is support for .w5s plugins which reside in %WinampDir%\System and
					** are intended for common code that can be shared amongst other plugins e.g. jnetlib.w5s
					** which contains jnetlib in one instance instead of being duplicated multiple times in
					** all of the plugins which need internet access.
					**
					** Details on the .w5s specifications will come at some stage (possibly).
					*/
					
					
					typedef struct {
                    const wchar_t *filename;
                    const wchar_t *metadata;
                    wchar_t *ret;
                    size_t retlen;
					} extendedFileInfoStructW;
					
					#define IPC_GET_EXTENDED_FILE_INFOW 3026 
					/* (requires Winamp 5.13+)
					** Pass a pointer to the above struct in wParam
					*/
					
					
					#define IPC_GET_EXTENDED_FILE_INFOW_HOOKABLE 3027
					#define IPC_SET_EXTENDED_FILE_INFOW 3028 
					/* (requires Winamp 5.13+)
					** Pass a pointer to the above struct in wParam
					*/
					
					
					#define IPC_PLAYLIST_GET_NEXT_SELECTED 3029
					/* (requires 5.2+)
					** int pl_item = SendMessageW(hwnd_winamp,WM_WA_IPC,start,IPC_PLAYLIST_GET_NEXT_SELECTED);
					**
					** This works just like the ListView_GetNextItem(..) macro for ListView controls.
					** 'start' is the index of the playlist item that you want to begin the search after or
					** set this as -1 for the search to begin with the first item of the current playlist.
					**
					** This will return the index of the selected playlist according to the 'start' value or
					** it returns -1 if there is no selection or no more selected items according to 'start'.
					**
					** Quick example:
					**
					** int sel = -1;
					** // keep incrementing the start of the search so we get all of the selected entries
					** while((sel = SendMessageW(hwnd_winamp,WM_WA_IPC,sel,IPC_PLAYLIST_GET_NEXT_SELECTED))!=-1){
					**   // show the playlist file entry of the selected item(s) if there were any
					**   MessageBox(hwnd_winamp,(char*)SendMessageW(hwnd_winamp,WM_WA_IPC,sel,IPC_GETPLAYLISTFILE),0,0);
					** }
					*/
					
					
					#define IPC_PLAYLIST_GET_SELECTED_COUNT 3030
					/* (requires 5.2+)
					** int selcnt = SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_PLAYLIST_GET_SELECTED_COUNT);
					** This will return the number of selected playlist entries.
					*/
					
					
					#define IPC_GET_PLAYING_FILENAME 3031
					/* (requires Winamp 5.?+)
					** wchar_t* fn=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_PLAYING_FILENAME);
					** This will return the currently playing filename string as held by Winamp.
					*/
					
					
					#define IPC_OPEN_URL 3032
					// send either ANSI or Unicode string (it'll figure it out, but it MUST start with "h"!, so don't send ftp:// or anything funny)
					// you can also send this one from another process via WM_COPYDATA (unicode only)
					
					
					#define IPC_USE_UXTHEME_FUNC 3033
					/* (requires Winamp 5.35+)
					** int ret = SendMessageW(hwnd_winamp,WM_WA_IPC,param,IPC_USE_UXTHEME_FUNC);
					** param can be IPC_ISWINTHEMEPRESENT or IPC_ISAEROCOMPOSITIONACTIVE or a valid hwnd.
					**
					** If you pass a hwnd then it will apply EnableThemeDialogTexture(ETDT_ENABLETAB)
					** so your tabbed dialogs can use the correct theme (on supporting OSes ie XP+).
					**
					** Otherwise this will return a value based on the param passed (as defined below).
					** For compatability, the return value will be zero on success (as 1 is returned
					** for unsupported ipc calls on older Winamp versions)
					*/
                    #define IPC_ISWINTHEMEPRESENT 0
					/* This will return 0 if uxtheme.dll is present
					** int isthemethere = !SendMessageW(hwnd_winamp,WM_WA_IPC,IPC_ISWINTHEMEPRESENT,IPC_USE_UXTHEME_FUNC);
					*/
                    #define IPC_ISAEROCOMPOSITIONACTIVE 1
					/* This will return 0 if aero composition is active
					** int isaero = !SendMessageW(hwnd_winamp,WM_WA_IPC,IPC_ISAEROCOMPOSITIONACTIVE,IPC_USE_UXTHEME_FUNC);
					*/
					
					
					#define IPC_GET_PLAYING_TITLE 3034
					/* (requires Winamp 5.5+)
					** wchar_t* title=(wchar_t*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_PLAYING_TITLE);
					** This will return the currently playing file title string as displayed in Winamp's window.
					*/
					
					
					#define IPC_CANPLAY 3035
					/* (requires Winamp 5.5+)
					** In_Module *in_mod=(In_Module*)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)fn,IPC_CANPLAY);
					** This api will return either a In_Module* for plugin associated with the file passed or
					** it will return 0 to indicate there is not a supporting input plugin.
					** Pass a unicode (wchar_t) filepath.
					**
					** In_Module *in_mod=(In_Module*)SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)fn,IPC_CANPLAY);
					** if(in_mod && (in_mod != (In_Module*)1){
					**   // we got a valid In_Module *
					** }
					*/
					
					
					typedef struct {
                    // fill these in...
                    size_t size; // init to sizeof(artFetchData)
                    HWND parent; // parent window of the dialogue
					
                    // fill as much of these in as you can, otherwise leave them 0
                    const wchar_t *artist;
                    const wchar_t *album;
                    int year, amgArtistId, amgAlbumId;
					
                    int showCancelAll; // if set to 1, this shows a "Cancel All" button on the dialogue
					
                    // winamp will fill these in if the call returns successfully:
                    void* imgData; // a buffer filled with compressed image data. free with WASABI_API_MEMMGR->sysFree()
                    int imgDataLen; // the size of the buffer
                    wchar_t type[10]; // eg: "jpg"
                    const wchar_t *gracenoteFileId; // if you know it
					} artFetchData;
					
					#define IPC_FETCH_ALBUMART 3036
					/* pass an artFetchData*. This will show a dialog guiding the use through choosing art, and return when it's finished
					** return values:
					** 1: error showing dialog
					** 0: success
					** -1: cancel was pressed
					** -2: cancel all was pressed
					*/
					
					
					#define IPC_JSAPI2_GET_DISPATCH_OBJECT 3037
					/* pass your service's unique ID, as a wchar_t * string, in wParam
					** Winamp will copy the string, so don't worry about keeping it around
					** An IDispatch * object will be returned (cast the return value from SendMessageW)
					** This IDispatch can be used for scripting/automation/VB interaction
					** Pass to IE via IDocHostUIHandler::GetExternal and it will become window.external in javscript
					*/
					
					// #define IPC_REMOVE_DISPATCH_OBJECT	3038   /* this id already in use */ 
					
					
					#define IPC_HANDLE_URI 3039 /* only for use in WM_COPYDATA, passes Winamp a filename that will get handled by svc_urihandler */
					
					
					#define IPC_PLAYFILEW_NDE 3040 /* just like IPC_PLAYFILEW, but the filename is an NDE reference-counted string (but not the title!!) */
					#define IPC_PLAYFILEW_NDE_TITLE 3041 /* use this if the title is reference counted also */
					
					
					#define IPC_OUTPUT_STARTED 3042
					/* (requires Winamp 5.57+)
					** This is a notification message sent to the main Winamp window by an output plugin
					** when the pre-buffer has been filled and output has started which is useful if you
					** want to wait until playback has buffered before doing something on song transition.
					** 
					** It is not guaranteed that this message is implemented in all output plugins (with
					** only out_ds supporting it as of 5.57) so is recommended to wait for 5 seconds or
					** until you receive this notification message before handling the song transition.
					**
					** if(message == WM_WA_IPC && lparam == IPC_OUTPUT_STARTED)
					** {
					**   // do what you need to do
					** }
					*/
					
					
					typedef struct {
                    int last_time;
                    int g_fullstop;
					} stopPlayingInfoStruct;
					
					#define IPC_STOPPLAYING 3043
					/* (requires Winamp 5.57+)
					** This is a notification message sent to the main Winamp window by itself whenever
					** playback is stopped either when file playback ends or the user stops playing.
					**
					** if(message == WM_WA_IPC && lparam == IPC_STOPPLAYING)
					** {
					**   // do what you need to do such as logging where playback was
					** }
					*/
					
					
					#define IPC_GET_D3DX9 3044
					/* (requires Winamp 5.57+)
					** HMODULE d3dx9 = (HMODULE)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_D3DX9);
					**
					** This will return the module handle of a d3dx9_*.dll based against the version
					** internally required by Winamp and it's supporting plug-ins (version can change).
					**
					** HMODULE d3dx9 = (HMODULE)SendMessageW(hwnd_winamp,WM_WA_IPC, 0, IPC_GET_D3DX9);
					** if (!d3dx9 || d3dx9 == (HMODULE)1) {
					**   // if here then loading failed and you'll need to manually load the library
					** }
					*/
					
					
					#define IPC_GET_FILEREGISTRAR_OBJECT 3045
					/* (requires Winamp 5.58+)
					** IFileTypeRegistrar* registrar = (IFileTypeRegistrar*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_FILEREGISTRAR_OBJECT);
					**
					** You call this to retrieve a copy of a IFileTypeRegistrar object which Winamp will
					** create which provides some commonly used functions for registry and file access
					** which will be automatically elevated on Vista / Window 7 depending on the user's
					** permissions as required.
					**
					** // it is best to call this everytime that the object is required as there is no
					** // guarantee it will already have been created or if it's already been released
					** IFileTypeRegistrar *registrar = (IFileTypeRegistrar*)SendMessageW(hwnd_winamp,WM_WA_IPC,0,IPC_GET_FILEREGISTRAR_OBJECT);
					** // make sure that we've got a valid object (as 1 is an unsupported api return)
					** if(registrar && (registrar != (IFileTypeRegistrar*)1)){
					**   // we got a valid copy of the object (automatically elevated as required)
					**   // so now we can start using the IFileTypeRegistrar object as required
					**
					**   // once we're done using the IFileTypeRegistrar object for the immediate moment
					**   // then we should release the object so everything is kept as clean as possible
					**   registrar->Release();
					** }
					**
					** 5.66+:
					** If you pass 1 in wParam then it will skip trying to provide a fallback instance
					** which is helpful for batch processing and you need to know if elevation failed.
					*/
					
					
					#define IPC_SHELL_ACTION_START 3047
					#define IPC_SHELL_ACTION_END 3048
					/* (requires Winamp 5.66+)
					** This is a notification message sent to the main Winamp window by itself whenever
					** there is an action generated by the Windows shell which may change the playlist.
					**
					** if(message == WM_WA_IPC && lparam == IPC_SHELL_ACTION_START)
					** {
					** }
					*/
					
					
					#define IPC_REGISTER_WINAMP_IPCMESSAGE 65536 
					/* (requires Winamp 5.0+)
					** DWORD id = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)name,IPC_REGISTER_WINAMP_IPCMESSAGE);
					** e.g. DWORD id = SendMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)&"enter_a_different_string",IPC_REGISTER_WINAMP_IPCMESSAGE);
					**
					** The value 'id' returned is > 65536 and is incremented on subsequent calls for unique
					** 'name' values passed to it. By using the same 'name' in different plugins will allow a
					** common runtime api to be provided for the currently running instance of Winamp
					** e.g.
					**   PostMessageW(hwnd_winamp,WM_WA_IPC,(WPARAM)my_param,registered_ipc);
					** Have a look at wa_hotkeys.h for an example on how this api is used in practice for a
					** custom WM_WA_IPC message.
					**
					**
					** if(uMsg == WM_WA_IPC && lParam == id_from_register_winamp_ipcmessage){
					**   // do things
					** }
					*/
					
					/**************************************************************************/
					
					/*
					** Finally there are some WM_COMMAND messages that you can use to send 
					** Winamp misc commands.
					** 
					** To send these, use:
					**
					** SendMessageW(hwnd_winamp, WM_COMMAND,command_name,0);
					*/
					
					#ifndef _WA_IPC_LEAN_H_
					#define WINAMP_OPTIONS_EQ               40036 // toggles the EQ window
					#define WINAMP_OPTIONS_PLEDIT           40040 // toggles the playlist window
					#define WINAMP_VOLUMEUP                 40058 // turns the volume up a little
					#define WINAMP_VOLUMEDOWN               40059 // turns the volume down a little
					#define WINAMP_FFWD5S                   40060 // fast forwards 5 seconds
					#define WINAMP_REW5S                    40061 // rewinds 5 seconds
					
					// the following are the five main control buttons, with optionally shift 
					// or control pressed
					// (for the exact functions of each, just try it out)
					#define WINAMP_BUTTON1                  40044
					#define WINAMP_BUTTON2                  40045
					#define WINAMP_BUTTON3                  40046
					#define WINAMP_BUTTON4                  40047
					#define WINAMP_BUTTON5                  40048
					#define WINAMP_BUTTON1_SHIFT            40144
					#define WINAMP_BUTTON2_SHIFT            40145
					#define WINAMP_BUTTON3_SHIFT            40146
					#define WINAMP_BUTTON4_SHIFT            40147
					#define WINAMP_BUTTON5_SHIFT            40148
					#define WINAMP_BUTTON1_CTRL             40154
					#define WINAMP_BUTTON2_CTRL             40155
					#define WINAMP_BUTTON3_CTRL             40156
					#define WINAMP_BUTTON4_CTRL             40157
					#define WINAMP_BUTTON5_CTRL             40158
					
					#define WINAMP_FILE_PLAY                40029 // pops up the load file(s) box
					#define WINAMP_FILE_DIR                 40187 // pops up the load directory box
					#define WINAMP_OPTIONS_PREFS            40012 // pops up the preferences
					#define WINAMP_OPTIONS_AOT              40019 // toggles always on top
					#define WINAMP_HELP_ABOUT               40041 // pops up the about box :)
					
					#define ID_MAIN_PLAY_AUDIOCD1           40323 // starts playing the audio CD in the first CD reader
					#define ID_MAIN_PLAY_AUDIOCD2           40324 // plays the 2nd
					#define ID_MAIN_PLAY_AUDIOCD3           40325 // plays the 3rd
					#define ID_MAIN_PLAY_AUDIOCD4           40326 // plays the 4th
					#define ID_MAIN_PLAY_AUDIOCD_SEP        40327
					
					// IDs 42000 to 45000 are reserved for gen_ff
					// IDs from 45000 to 57000 are reserved for library 
					#endif
					
					#endif//_WA_IPC_H_