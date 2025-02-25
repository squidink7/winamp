	﻿!ifndef NULLSOFT_WINAMP_UNINSTALLER_USERDATA_HEADER
	!define NULLSOFT_WINAMP_UNINSTALLER_USERDATA_HEADER
	
	Section "un.$(IDS_UNINSTALL_USER_PREFERENCES)" IDX_UNINSTALL_USER_PREFERENCES
; do we still need this line? If no paths.ini, then $SETTINGSDIR = $INSTDIR anyway
; StrCmp $SETTINGSDIR $INSTDIR skip_removeIniPath
${FrenchRadio_UninstallUserData}
	
Delete "$INSTDIR\install.ini"
Delete "$INSTDIR\paths.ini"
Delete "$SETTINGSDIR\Winamp.ini"
Delete "$SETTINGSDIR\Winamp.lks"
Delete "$SETTINGSDIR\winamp.m3u"
Delete "$SETTINGSDIR\winamp.m3u8"
Delete "$SETTINGSDIR\winamp.log"
Delete "$APPDATA\Winamp\winamp.log"
Delete "$SETTINGSDIR\winamp.pic"
Delete "$SETTINGSDIR\studio.xnf"
Delete "$SETTINGSDIR\Winamp.q1"
Delete "$SETTINGSDIR\Winamp.q2"
Delete "$SETTINGSDIR\Winamp.bm"
Delete "$SETTINGSDIR\Winamp.bm8"
Delete "$SETTINGSDIR\demo.aac"
Delete "$SETTINGSDIR\demo.mp3"
Delete "$SETTINGSDIR\demoedit.aac"
Delete "$SETTINGSDIR\auth.ini"
Delete "$SETTINGSDIR\jsapisec.ini"
Delete "$SETTINGSDIR\links.xml"
Delete "$SETTINGSDIR\jscfg.ini"
Delete "$SETTINGSDIR\Plugins\plugin.ini"
Delete "$SETTINGSDIR\Plugins\in_mp4.ini"
Delete "$SETTINGSDIR\Plugins\feedback.ini"
Delete "$SETTINGSDIR\Plugins\vis_avs.dat"
Delete "$SETTINGSDIR\Plugins\cddiscs.*"
Delete "$SETTINGSDIR\Plugins\cdtracks.*"
Delete "$SETTINGSDIR\Plugins\mudqueue.*"
Delete "$SETTINGSDIR\Plugins\podcasts.*"
Delete "$SETTINGSDIR\Plugins\gen_ml.ini"
Delete "$SETTINGSDIR\Plugins\gen_mud.ini"
Delete "$SETTINGSDIR\Plugins\milk_config.ini"
Delete "$SETTINGSDIR\Plugins\milk_img.ini"
Delete "$SETTINGSDIR\Plugins\milk_msg.ini"
Delete "$SETTINGSDIR\Plugins\milk2.ini"
Delete "$SETTINGSDIR\Plugins\milk2_img.ini"
Delete "$SETTINGSDIR\Plugins\milk2_msg.ini"
Delete "$SETTINGSDIR\Plugins\milk2_adapters.txt"
Delete "$SETTINGSDIR\Plugins\Milkdrop2\milk2.ini"
Delete "$SETTINGSDIR\Plugins\Milkdrop2\milk2_img.ini"
Delete "$SETTINGSDIR\Plugins\Milkdrop2\milk2_msg.ini"
Delete "$SETTINGSDIR\Plugins\Milkdrop2\milk2_adapters.txt"
Delete "$SETTINGSDIR\Plugins\ml_transcode.ini"
Delete "$SETTINGSDIR\Plugins\Gracenote\*.db"
Delete "$SETTINGSDIR\Plugins\Gracenote\cddbplm.*"
Delete "$SETTINGSDIR\Plugins\loginBox\login*.*"
Delete "$SETTINGSDIR\Plugins\omBrowser\*.ini"
Delete "$SETTINGSDIR\Plugins\dropbox\*.ini"
Delete "$SETTINGSDIR\Plugins\ml\omServices\*.ini"
Delete "$SETTINGSDIR\Plugins\ml\cache\*.*"
Delete "$SETTINGSDIR\Plugins\ml\*.vmd"
Delete "$SETTINGSDIR\Plugins\ml\views\*.vmd"
Delete "$SETTINGSDIR\Plugins\ml\*.ini"
;Delete "$SETTINGSDIR\Plugins\ml\*.m3u*" ; maybe don't delete playlists just yet, though the RMDir /r command later probably does this anyway...
;Delete "$SETTINGSDIR\Plugins\ml\playlists\*.m3u*" ; maybe don't delete playlists just yet, though the RMDir /r command later probably does this anyway...
Delete "$SETTINGSDIR\Plugins\ml\*.dat"
Delete "$SETTINGSDIR\Plugins\ml\*.idx"
Delete "$SETTINGSDIR\Plugins\ml\art\*.dat"
Delete "$SETTINGSDIR\Plugins\ml\art\*.idx"
Delete "$SETTINGSDIR\Plugins\ml\art\*.dat.*"
Delete "$SETTINGSDIR\Plugins\ml\art\*.idx.*"
Delete "$SETTINGSDIR\Plugins\ml\*.xml"
Delete "$SETTINGSDIR\Plugins\ml\*.backup"
Delete "$SETTINGSDIR\Plugins\ml\feeds\*.xml"
Delete "$SETTINGSDIR\Plugins\ml\feeds\*.backup"
Delete "$SETTINGSDIR\Plugins\ml\main.dat.*"
Delete "$SETTINGSDIR\Plugins\ml\art.dat.*"
Delete "$SETTINGSDIR\Plugins\ml\main.idx.*"
Delete "$SETTINGSDIR\Plugins\ml\art.idx.*"
Delete "$SETTINGSDIR\Plugins\ml\playlists\*.xml"
Delete "$SETTINGSDIR\Cloud\*.db"
Delete "$SETTINGSDIR\Cloud\views\*.ini"
Delete "$SETTINGSDIR\Cloud\logs\*.*"
RMDir /r "$SETTINGSDIR\Plugins\omBrowser\cache"
RMDir /r "$SETTINGSDIR\Plugins\omBrowser"
RMDir /r "$SETTINGSDIR\Plugins\Gracenote"
RMDir /r "$SETTINGSDIR\Plugins\Milkdrop2"
RMDir /r "$SETTINGSDIR\Plugins\ml\playlists"
RMDir /r "$SETTINGSDIR\Plugins\ml\views"
RMDir /r "$SETTINGSDIR\Plugins\ml\feeds"
RMDir /r "$SETTINGSDIR\Plugins\ml\art"
RMDir /r "$SETTINGSDIR\Plugins\ml\cache"
RMDir /r "$SETTINGSDIR\Plugins\ml\omServices"
RMDir /r "$SETTINGSDIR\Plugins\ml"
RMDir /r "$SETTINGSDIR\Cloud\views"
RMDir /r "$SETTINGSDIR\Cloud\logs"
RMDir /r "$SETTINGSDIR\Cloud"
RMDir /r "$SETTINGSDIR"
	SectionEnd
	!endif ; NULLSOFT_WINAMP_UNINSTALLER_USERDATA_HEADER