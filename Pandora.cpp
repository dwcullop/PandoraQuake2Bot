// Pandora.cpp : Defines the class behaviors for the application.
//
// Pandora Bot v2.0
// By Darrin W. Cullop (dcullop@arizona.edu)
//
// Copyright (c) 1998-1999 by Darrin W. Cullop.  All Rights Reserved.		
//																			
// Permission to use, copy and distribute unedited copies of this whole
// document is hereby granted, provided that no fee is charged for the
// use or availability	of this document (other than the normal connection
// costs for on-line services, if applicable). The above copyright notice
// and this permission notice must be left intact in all copies of this
// document. Short excerpts of this document may be quoted in discussion
// groups or mailing list articles, as long as a reference to the full
// document is given.
//																			
// Commercial distribution of this document, in whole or in part,
// requires prior agreement with the author. Commercial distribution
// includes any means by which the user has to pay either for the support
// (e.g. book, newsletter or CD-ROM) or for the document itself.
//
// Unauthorized commercial distribution is prohibited.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Pandora.h"

#include "MainFrm.h"
//#include "ChildFrm.h"
#include "ConsoleFrame.h"
#include "PandoraDoc.h"
//#include "PandoraView.h"
#include "ConsoleView.h"
#include "AboutBox.h"
#include "AIThread.h"
#include "ViewThread.h"
#include "BotInfoFrame.h"
#include "BotInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPandoraApp

BEGIN_MESSAGE_MAP(CPandoraApp, CWinApp)
	//{{AFX_MSG_MAP(CPandoraApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_WEB_DARRIN, OnWebDarrin)
	ON_COMMAND(ID_WEB_DVC, OnWebDvc)
	ON_COMMAND(ID_WEB_PANDORA, OnWebPandora)
	ON_COMMAND(ID_VIEW_BOTINFO, OnViewBotinfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOTINFO, OnUpdateViewBotinfo)
	ON_COMMAND(ID_VIEW_CONSOLE, OnViewConsole)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONSOLE, OnUpdateViewConsole)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPandoraApp construction

CPandoraApp::CPandoraApp()
{
	m_bShowConsole = FALSE;
	m_bShowBotInfo = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPandoraApp object

CPandoraApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPandoraApp initialization

BOOL CPandoraApp::InitInstance()
{
	if (! AfxSocketInit() )
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Seed the random number generator
	srand( (unsigned)time( NULL ) );

	// Standard initialization
	Enable3dControls();			// Call this when using MFC in a shared DLL
	SetRegistryKey( _T("QuakeBots") );
	LoadStdProfileSettings(0);
	AfxEnableControlContainer();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pConsoleTemplate = new CMultiDocTemplate(
		IDR_PANDORTYPE,
		RUNTIME_CLASS(CPandoraDoc),
		RUNTIME_CLASS(CConsoleFrame),
		RUNTIME_CLASS(CConsoleView));
/*
	m_pPandoraTemplate = new CMultiDocTemplate(
		IDR_PANDORTYPE2,
		RUNTIME_CLASS(CPandoraDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CPandoraView));
*/
	m_pBotInfoTemplate = new CMultiDocTemplate(
		IDR_BOTINFO_TYPE,
		RUNTIME_CLASS(CPandoraDoc),
		RUNTIME_CLASS(CBotInfoFrame),
		RUNTIME_CLASS(CBotInfoView));

	// Add the document templates
	AddDocTemplate(m_pConsoleTemplate);
		//AddDocTemplate(m_pPandoraTemplate);
	AddDocTemplate(m_pBotInfoTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (! pMainFrame->LoadFrame(IDR_MAINFRAME) )
	{
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	// The main window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow( m_nCmdShow );
	m_pMainWnd->UpdateWindow();

	// Display the BotInfo Window
		//OnViewBotinfo();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraApp Operations

void CPandoraApp::GoToURL( const UINT& nResID )
{
	CString strURL;

	if ( strURL.LoadString(nResID) )
	{
		ShellExecute( AfxGetMainWnd()->m_hWnd, "open", strURL, NULL, "", SW_SHOW );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraApp commands

void CPandoraApp::OnAppAbout()
{
	CAboutBox aboutDlg;
	aboutDlg.DoModal();
}

int CPandoraApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}

void CPandoraApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	if (!m_pDocManager->GetOpenDocumentCount())
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraApp::OnWebDarrin() 
{
	GoToURL( IDS_WEB_DARRIN );	
}

void CPandoraApp::OnWebDvc() 
{
	GoToURL( IDS_WEB_DVC );		
}

void CPandoraApp::OnWebPandora() 
{
	GoToURL( IDS_WEB_PANDORA );	
}

void CPandoraApp::OnViewBotinfo() 
{
	if (! m_bShowBotInfo )
	{
		((CMainFrame*)m_pMainWnd)->DisplayView( m_pBotInfoTemplate, RUNTIME_CLASS(CBotInfoView) );
		m_bShowBotInfo = TRUE;
	}
}

void CPandoraApp::OnUpdateViewBotinfo(CCmdUI* pCmdUI) 
{
	if ( m_bShowBotInfo )
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}

void CPandoraApp::OnViewConsole() 
{
	if (! m_bShowConsole )
	{
		((CMainFrame*)m_pMainWnd)->DisplayView( m_pConsoleTemplate, RUNTIME_CLASS(CConsoleView) );
		m_bShowConsole = TRUE;
	}
}

void CPandoraApp::OnUpdateViewConsole(CCmdUI* pCmdUI) 
{
	if ( m_bShowConsole )
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
}
