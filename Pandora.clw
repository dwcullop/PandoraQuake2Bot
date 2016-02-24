; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBotInfoView
LastTemplate=CMDIChildWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Pandora.h"
LastPage=0

ClassCount=9
Class1=CPandoraApp
Class2=CPandoraDoc
Class3=CBotInfoFrame
Class4=CMainFrame
Class7=CConsoleView

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_CONNECT_DIALOG
Class5=CConnectDialog
Class6=CBotInfoView
Class8=CAboutBox
Class9=CConsoleFrame
Resource4=IDR_PANDORTYPE
Resource5=IDD_BOT_INFO

[CLS:CPandoraApp]
Type=0
HeaderFile=Pandora.h
ImplementationFile=Pandora.cpp
Filter=N
LastObject=CPandoraApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CPandoraDoc]
Type=0
HeaderFile=PandoraDoc.h
ImplementationFile=PandoraDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPandoraDoc

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutBox
ControlCount=10
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_THANK_YOU,edit,1342179332
Control6=IDC_GREETINGS,edit,1342179332
Control7=IDC_GRAPHICS_INFO,static,1342308352
Control8=IDC_GRAPHICS_INFO2,static,1342308352
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_WEB_PANDORA
Command6=ID_WEB_DARRIN
Command7=ID_WEB_DVC
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_CONNECT
Command3=ID_FILE_DISCONNECT
Command4=ID_EDIT_COPY
Command5=ID_COMMANDS_FLIPOFF
Command6=ID_COMMANDS_SALUTE
Command7=ID_COMMANDS_TAUNT
Command8=ID_COMMANDS_WAVE
Command9=ID_COMMANDS_POINT
Command10=ID_COMMANDS_SUICIDE
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_PANDORTYPE]
Type=1
Class=?
Command1=ID_FILE_CONNECT
Command2=ID_FILE_DISCONNECT
Command3=ID_APP_EXIT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_CLEAR
Command6=ID_COMMANDS_FLIPOFF
Command7=ID_COMMANDS_SALUTE
Command8=ID_COMMANDS_TAUNT
Command9=ID_COMMANDS_WAVE
Command10=ID_COMMANDS_POINT
Command11=ID_COMMANDS_SUICIDE
Command12=ID_VIEW_BOTINFO
Command13=ID_VIEW_CONSOLE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_WINDOW_CASCADE
Command17=ID_WINDOW_TILE_HORZ
Command18=ID_WEB_PANDORA
Command19=ID_WEB_DARRIN
Command20=ID_WEB_DVC
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_COMMANDS_FLIPOFF
Command3=ID_COMMANDS_SUICIDE
Command4=ID_FILE_NEW
Command5=ID_COMMANDS_POINT
Command6=ID_COMMANDS_SALUTE
Command7=ID_COMMANDS_TAUNT
Command8=ID_NEXT_PANE
Command9=ID_PREV_PANE
Command10=ID_EDIT_COPY
Command11=ID_COMMANDS_WAVE
CommandCount=11

[CLS:CConsoleView]
Type=0
HeaderFile=ConsoleView.h
ImplementationFile=ConsoleView.cpp
BaseClass=CRichEditView
Filter=C
VirtualFilter=VWC
LastObject=CConsoleView

[DLG:IDD_CONNECT_DIALOG]
Type=1
Class=CConnectDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CONNECT_PROMPT,static,1342308352
Control4=IDC_SERVER_ADDRESS,edit,1350631552

[CLS:CConnectDialog]
Type=0
HeaderFile=ConnectDialog.h
ImplementationFile=ConnectDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CConnectDialog
VirtualFilter=dWC

[CLS:CAboutBox]
Type=0
HeaderFile=AboutBox.h
ImplementationFile=AboutBox.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutBox
VirtualFilter=dWC

[CLS:CConsoleFrame]
Type=0
HeaderFile=ConsoleFrame.h
ImplementationFile=ConsoleFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=CConsoleFrame

[DLG:IDD_BOT_INFO]
Type=1
Class=CBotInfoView
ControlCount=31
Control1=IDC_CHATTEXT,edit,1350635520
Control2=IDC_BUTTON_SAY,button,1342242817
Control3=IDC_BUTTON_TEAM,button,1342242816
Control4=IDC_BUTTON_CMD,button,1342242816
Control5=IDC_HEALTH,edit,1350568065
Control6=IDC_WEAPON,edit,1350568065
Control7=IDC_FRAGS,edit,1350568065
Control8=IDC_HEALTH_LABEL,static,1342308864
Control9=IDC_FRAG_LABEL,static,1342308864
Control10=IDC_WEAPON_LABEL,static,1342308864
Control11=IDC_ATTACK_NAME,edit,1350568065
Control12=IDC_ATTACK_DIST,edit,1350568065
Control13=IDC_ATTACK_POS,edit,1350568065
Control14=IDC_ATTACK_NAME_LABEL,static,1342308864
Control15=IDC_ATTACK_POS_LABEL,static,1342308864
Control16=IDC_ATTACK_DIST_LABEL,static,1342308864
Control17=IDC_ATTACK_GROUP,button,1342177287
Control18=IDC_MOVE_NAME,edit,1350568065
Control19=IDC_MOVE_DIST,edit,1350568065
Control20=IDC_MOVE_POS,edit,1350568065
Control21=IDC_MOVE_NAME_LABEL,static,1342308864
Control22=IDC_MOVE_POS_LABEL,static,1342308864
Control23=IDC_MOVE_DIST_LABEL,static,1342308864
Control24=IDC_MOVE_GROUP,button,1342177287
Control25=IDC_BOT_VELOCITY,edit,1350568065
Control26=IDC_BOT_POS,edit,1350568065
Control27=IDC_BOT_POS_LABEL,static,1342308864
Control28=IDC_BOT_VELOCITY_LABEL,static,1342308864
Control29=IDC_BOTINFO_GROUP,button,1342177287
Control30=IDC_BOT_AI_INFO_GROUP,button,1342177287
Control31=IDC_AI_INFO_TEXT,edit,1350567936

[CLS:CBotInfoView]
Type=0
HeaderFile=BotInfoView.h
ImplementationFile=BotInfoView.cpp
BaseClass=CFormView
Filter=D
LastObject=IDC_ATTACK_DIST
VirtualFilter=VWC

[CLS:CBotInfoFrame]
Type=0
HeaderFile=BotInfoFrame.h
ImplementationFile=BotInfoFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
LastObject=CBotInfoFrame
VirtualFilter=mfWC

