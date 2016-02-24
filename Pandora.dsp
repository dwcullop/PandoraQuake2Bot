# Microsoft Developer Studio Project File - Name="Pandora" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Pandora - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Pandora.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pandora.mak" CFG="Pandora - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pandora - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Pandora - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Pandora - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /o "NUL" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "Pandora - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Pandora - Win32 Release"
# Name "Pandora - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutBox.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvTime.cpp
# End Source File
# Begin Source File

SOURCE=.\AIData.cpp
# End Source File
# Begin Source File

SOURCE=.\AIThread.cpp
# End Source File
# Begin Source File

SOURCE=.\ArmorSpec.cpp
# End Source File
# Begin Source File

SOURCE=.\Bot.cpp
# End Source File
# Begin Source File

SOURCE=.\BotAI.cpp
# End Source File
# Begin Source File

SOURCE=.\BotInfoFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\BotInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\BotMove.cpp
# End Source File
# Begin Source File

SOURCE=.\BotSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\BotTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BotThread.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsoleFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ConsoleView.cpp
# End Source File
# Begin Source File

SOURCE=.\DangerSpec.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\EntityState.cpp
# End Source File
# Begin Source File

SOURCE=.\GameState.cpp
# End Source File
# Begin Source File

SOURCE=.\HealingSpec.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MapPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveData.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveList.cpp
# End Source File
# Begin Source File

SOURCE=.\Pandora.cpp
# End Source File
# Begin Source File

SOURCE=.\Pandora.rc
# End Source File
# Begin Source File

SOURCE=.\PandoraDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\QuakeClient.cpp
# End Source File
# Begin Source File

SOURCE=.\QuakeConnect.cpp
# End Source File
# Begin Source File

SOURCE=.\QuakePacket.cpp
# End Source File
# Begin Source File

SOURCE=.\QuakeRecorder.cpp
# End Source File
# Begin Source File

SOURCE=.\QuakeSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SentMove.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TempEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\TextMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewThread.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponSpec.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutBox.h
# End Source File
# Begin Source File

SOURCE=.\AdvTime.h
# End Source File
# Begin Source File

SOURCE=.\AIData.h
# End Source File
# Begin Source File

SOURCE=.\AIThread.h
# End Source File
# Begin Source File

SOURCE=.\ArmorSpec.h
# End Source File
# Begin Source File

SOURCE=.\Bot.h
# End Source File
# Begin Source File

SOURCE=.\BotAI.h
# End Source File
# Begin Source File

SOURCE=.\BotInfoFrame.h
# End Source File
# Begin Source File

SOURCE=.\BotInfoView.h
# End Source File
# Begin Source File

SOURCE=.\BotMove.h
# End Source File
# Begin Source File

SOURCE=.\BotMsgs.h
# End Source File
# Begin Source File

SOURCE=.\BotSystem.h
# End Source File
# Begin Source File

SOURCE=.\BotTarget.h
# End Source File
# Begin Source File

SOURCE=.\BotThread.h
# End Source File
# Begin Source File

SOURCE=.\ConnectDialog.h
# End Source File
# Begin Source File

SOURCE=.\ConsoleFrame.h
# End Source File
# Begin Source File

SOURCE=.\ConsoleView.h
# End Source File
# Begin Source File

SOURCE=.\DangerSpec.h
# End Source File
# Begin Source File

SOURCE=.\Entity.h
# End Source File
# Begin Source File

SOURCE=.\EntityState.h
# End Source File
# Begin Source File

SOURCE=.\GameState.h
# End Source File
# Begin Source File

SOURCE=.\HealingSpec.h
# End Source File
# Begin Source File

SOURCE=.\m_player.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MapPoint.h
# End Source File
# Begin Source File

SOURCE=.\MoveData.h
# End Source File
# Begin Source File

SOURCE=.\MoveList.h
# End Source File
# Begin Source File

SOURCE=.\NetUtils.h
# End Source File
# Begin Source File

SOURCE=.\Pandora.h
# End Source File
# Begin Source File

SOURCE=.\PandoraDefs.h
# End Source File
# Begin Source File

SOURCE=.\PandoraDoc.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\PlayerInfo.h
# End Source File
# Begin Source File

SOURCE=.\QuakeClient.h
# End Source File
# Begin Source File

SOURCE=.\QuakeConnect.h
# End Source File
# Begin Source File

SOURCE=.\QuakePacket.h
# End Source File
# Begin Source File

SOURCE=.\QuakeRecorder.h
# End Source File
# Begin Source File

SOURCE=.\QuakeSocket.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SentMove.h
# End Source File
# Begin Source File

SOURCE=.\Sound.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemObject.h
# End Source File
# Begin Source File

SOURCE=.\TempEntity.h
# End Source File
# Begin Source File

SOURCE=.\TempEntityNormals.h
# End Source File
# Begin Source File

SOURCE=.\TextMessage.h
# End Source File
# Begin Source File

SOURCE=.\Vector.h
# End Source File
# Begin Source File

SOURCE=.\ViewThread.h
# End Source File
# Begin Source File

SOURCE=.\WeaponSpec.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Pandora.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Pandora_Q2.ICO
# End Source File
# Begin Source File

SOURCE=.\res\terminal.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
