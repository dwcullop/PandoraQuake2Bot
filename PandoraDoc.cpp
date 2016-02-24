// PandoraDoc.cpp : implementation of the CPandoraDoc class
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
#include "PandoraDoc.h"
#include "ConnectDialog.h"
#include <AfxAdv.h>
#include "PandoraDefs.h"
#include "MainFrm.h"
#include "Entity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc

IMPLEMENT_DYNCREATE(CPandoraDoc, CDocument)

BEGIN_MESSAGE_MAP(CPandoraDoc, CDocument)
	//{{AFX_MSG_MAP(CPandoraDoc)
	ON_COMMAND(ID_FILE_CONNECT, OnFileConnect)
	ON_COMMAND(ID_FILE_DISCONNECT, OnFileDisconnect)
	ON_COMMAND(ID_COMMANDS_FLIPOFF, OnCommandsFlipoff)
	ON_COMMAND(ID_COMMANDS_POINT, OnCommandsPoint)
	ON_COMMAND(ID_COMMANDS_SALUTE, OnCommandsSalute)
	ON_COMMAND(ID_COMMANDS_SUICIDE, OnCommandsSuicide)
	ON_COMMAND(ID_COMMANDS_TAUNT, OnCommandsTaunt)
	ON_COMMAND(ID_COMMANDS_WAVE, OnCommandsWave)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONNECT, OnUpdateFileConnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_DISCONNECT, OnUpdateFileDisconnect)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_FLIPOFF, OnUpdateCommandsFlipoff)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_POINT, OnUpdateCommandsPoint)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_SALUTE, OnUpdateCommandsSalute)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_SUICIDE, OnUpdateCommandsSuicide)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_TAUNT, OnUpdateCommandsTaunt)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_WAVE, OnUpdateCommandsWave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc Definitions

// Expires After June 30, 1998
#define EXPIRES_MONTH						6
#define EXPIRES_YEAR						1998
// Timer Delays (Times in milliseconds)
#define TIMER_DELAY_SEND					1000
#define TIMER_DELAY_RELIABLE				100
#define TIMER_DELAY_MOVE					( 1000 / m_nFPS )
#define TIMER_DELAY_STATUS					6000
#define TIMER_DELAY_COMPUTE_MOVE			200

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc construction/destruction

CPandoraDoc::CPandoraDoc()
{
}

CPandoraDoc::~CPandoraDoc()
{
}

BOOL CPandoraDoc::OnNewDocument()
{
#ifdef DOES_EXPIRE
	if ( CheckExpired() )
	{
		return FALSE;
	}
#endif
	CBotThread::SetBotDoc( this );
	CBotThread::SetBotSys( &m_bsSystem );
	CEntity::SetBotSys( &m_bsSystem );
	// Begin running the threads
	m_threadThink.StartThread();
	m_threadView.StartThread();
	// TODO: Make this user configurable (read / write to the registry)
	m_nRetriesMax	= 10;
	m_nFPS			= 20;
	m_nMsgLevel		= 0;
	m_nRate			= 50000;
	m_nFOV			= 180;
	m_nHand			= 1;
	m_strSkin.LoadString( IDS_BOT_SKIN );
	m_strName.LoadString( IDS_BOT_NAME );
	( (CMainFrame*)AfxGetMainWnd() )->SetDoc( this );

	SetBlankTitle();
	if ( !CDocument::OnNewDocument() )
		return FALSE;

	return TRUE;
}

void CPandoraDoc::OnCloseDocument() 
{
	// Stop running the threads
	m_threadThink.SuspendThread();
	m_threadView.SuspendThread();
	CBotThread::SetBotDoc( NULL );
	CBotThread::SetBotSys( NULL );
	CDocument::OnCloseDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc public operations

CView* CPandoraDoc::GetView( const CRuntimeClass* pViewClass )
{
	CView* pView;

	POSITION pos = GetFirstViewPosition();
	while ( pos != NULL )
	{
		pView = GetNextView( pos );
		if ( pView->IsKindOf(pViewClass) )
		{
			return pView;
		}
	}
	return NULL;
}

void CPandoraDoc::SetViewThreadViews()
{
	if ( this != NULL )
	{
		CConsoleView* pConsole = (CConsoleView*)GetView( RUNTIME_CLASS(CConsoleView) );
		CBotInfoView* pBotInfo = (CBotInfoView*)GetView( RUNTIME_CLASS(CBotInfoView) );

		( (CMDIChildWnd*) pConsole->GetParent() )->MDIRestore();
		( (CMDIChildWnd*) pBotInfo->GetParent() )->MDIRestore();
		m_threadView.SetConsoleView( pConsole );
		m_threadView.SetBotInfoView( pBotInfo );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc private operations

#ifdef DOES_EXPIRE
BOOL CPandoraDoc::CheckExpired() const
{
	CTime tCurrent = CTime::GetCurrentTime();

	if ((tCurrent.GetMonth() > EXPIRES_MONTH) || (tCurrent.GetYear() > EXPIRES_YEAR))
	{
		if ( AfxMessageBox(IDS_EXPIRED_NOTICE, MB_YESNO|MB_ICONQUESTION) == IDYES )
		{
			CString strURL;

			if ( strURL.LoadString(IDS_WEB_PANDORA) )
			{
				ShellExecute( AfxGetMainWnd()->m_hWnd, "open", strURL, NULL, "", SW_SHOW );
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
#endif

void CPandoraDoc::SetBlankTitle()
{
	CString strTitle;

	if ( strTitle.LoadString(IDS_FMT_NEWTITLE) )
	{
		SetTitle( strTitle );
	}
}

void CPandoraDoc::SetConnectedTitle()
{
	CString strServerInfo;
	CString strFormat;

	if ( strFormat.LoadString(IDS_FMT_MAINTITLE) )
	{
		strServerInfo.Format( strFormat, m_strMapName, m_strRemoteInfo );
		SetTitle( strServerInfo );
	}
}

void CPandoraDoc::SetDisconnectedTitle()
{
	CString strServerInfo;
	CString strFormat;

	if ( strFormat.LoadString(IDS_FMT_DISCONNECT_TITLE) )
	{
		strServerInfo.Format( strFormat, m_strRemoteInfo );
		SetTitle( strServerInfo );
	}
}

void CPandoraDoc::StartTimer( const UINT& nMsg, const UINT& nTimer )
{
	AfxGetMainWnd()->SetTimer( nMsg, nTimer, NULL );
}

void CPandoraDoc::StopTimer( const UINT& nMsg )
{
	AfxGetMainWnd()->KillTimer( nMsg );
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc Overridables

void CPandoraDoc::OnTimer( const UINT& nMsg )
{
	m_bsSystem.PostSystemMessage( nMsg );
	switch( nMsg )
	{
	case QB_TIMER_CHECK_SEND:
		m_qsSocket.CheckSend();
		break;
	case QB_TIMER_CHECK_RELIABLE:
		m_qsSocket.CheckReliable();
		break;
	case QB_TIMER_SEND_STATUS:
		if ( m_csStatus == csConnected )
		{
			m_qsSocket.SendConnectionless( "status" );
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc Overrides for CQuakeClient

void CPandoraDoc::OnDisconnected()
{
	if ( m_csStatus == csConnected )
	{
		StopTimer( QB_TIMER_SEND_STATUS );
		StopTimer( QB_TIMER_SEND_MOVE );
		m_bsSystem.PostSystemMessage( QB_NETWORK_END_LEVEL );
	}
	//m_qrDemo.CloseFile();
	StopTimer( QB_TIMER_CHECK_SEND );
	StopTimer( QB_TIMER_CHECK_RELIABLE );
	SetDisconnectedTitle();
	CQuakeClient::OnDisconnected();
}

void CPandoraDoc::OnMoveSent()
{
	m_bsSystem.PostSystemMessage( QB_NETWORK_MOVE_SENT );
}

void CPandoraDoc::OnMuzzleFlash( const WORD nPlayer )
{
	CQuakeClient::OnMuzzleFlash( nPlayer );
}

void CPandoraDoc::OnMuzzleFlash2( const WORD nMonster )
{
	CQuakeClient::OnMuzzleFlash2( nMonster );
}

void CPandoraDoc::OnUpdateEntityActive( const WORD nEntity )
{
	CQuakeClient::OnUpdateEntityActive( nEntity );
}

void CPandoraDoc::OnUpdateEntityRemove( const WORD nEntity ) 
{
	CQuakeClient::OnUpdateEntityRemove( nEntity );
}

void CPandoraDoc::OnUpdateInventory()
{
	m_bsSystem.PostSystemMessage( QB_INFO_INVENTORY );
	CQuakeClient::OnUpdateInventory();
}

void CPandoraDoc::OnUpdatePlayerInfo( const UINT nBitMask )
{
	CQuakeClient::OnUpdatePlayerInfo( nBitMask );
}

void CPandoraDoc::OnUpdatePlayerInfoStats( const UINT nBitMask )
{
	CQuakeClient::OnUpdatePlayerInfoStats( nBitMask );
}

void CPandoraDoc::OnUpdateServerData()
{
	SetConnectedTitle();
	m_bsSystem.PostSystemMessage( QB_INFO_SERVER_DATA );
	CQuakeClient::OnUpdateServerData();
}

void CPandoraDoc::OnPreConnect()
{
	SetViewThreadViews();
	StartTimer( QB_TIMER_CHECK_SEND, TIMER_DELAY_SEND );
	StartTimer( QB_TIMER_CHECK_RELIABLE, TIMER_DELAY_RELIABLE );
	CQuakeClient::OnPreConnect();
}

void CPandoraDoc::OnServerBeginLevel()
{
	m_bsSystem.PostSystemMessage( QB_NETWORK_BEGIN_LEVEL );
	StartTimer( QB_TIMER_SEND_MOVE, TIMER_DELAY_MOVE );
	StartTimer( QB_TIMER_SEND_STATUS, TIMER_DELAY_STATUS );
	CQuakeClient::OnServerBeginLevel();
}

void CPandoraDoc::OnServerReadError( CQuakePacket* pData )
{
	CQuakeClient::OnServerReadError( pData );
	m_bsSystem.PostSystemMessage( QB_SYSTEM_ERROR_NETWORK );
}

void CPandoraDoc::ProcessCenterText( const CString& strCenter )
{
	CTextMessage* pCenter = new CTextMessage;

	pCenter->SetText( strCenter );
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_CENTER_MESSAGE, pCenter );
}

void CPandoraDoc::ProcessDisplayText( CTextMessage* pDisplay )
{
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_TEXTMESSAGE, pDisplay );
}

void CPandoraDoc::ProcessErrorMessage( const UINT& nResID )
{
	m_bsSystem.PostSystemMessage( QB_INFO_ERR_MESSAGE, NULL, nResID );
	CQuakeClient::ProcessErrorMessage( nResID );
}

void CPandoraDoc::ProcessLayout( const CString& strLayout )
{
	CTextMessage* pNew = new CTextMessage;

	pNew->SetText( strLayout );
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_LAYOUT, pNew );
}

void CPandoraDoc::ProcessPrint( CTextMessage* pPrint )
{
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_TEXTMESSAGE, pPrint );
}

void CPandoraDoc::ProcessDataPacket( CQuakePacket* pData )
{
	//m_qrDemo.WriteBlock( pData );
	CQuakeClient::ProcessDataPacket( pData );
	m_bsSystem.PostSystemMessage( QB_NETWORK_PACKET_DONE );
}

void CPandoraDoc::ProcessSound( CSound* pSound )
{
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_SOUND, pSound );
}

void CPandoraDoc::ProcessStuffText( const CString& strCmd )
{
	CTextMessage*	pStuffText = new CTextMessage;

	pStuffText->SetText( strCmd );
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_STUFFED_TEXT, pStuffText );
	CQuakeClient::ProcessStuffText( strCmd );
}

void CPandoraDoc::ProcessTempEntity( CTempEntity* pTempEnt )
{
	m_bsSystem.PostSystemMessage( QB_SYSOBJ_TEMP_ENT, pTempEnt );
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc serialization

void CPandoraDoc::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc diagnostics

#ifdef _DEBUG
void CPandoraDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPandoraDoc::Dump( CDumpContext& dc ) const
{
	CDocument::Dump( dc );
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPandoraDoc Message Handlers

void CPandoraDoc::OnFileConnect() 
{
	CConnectDialog		dlgConnect;
	CRecentFileList*	pServers = new CRecentFileList( 0, "Servers", "Server%d", 10, 20 );

	pServers->ReadList();
	dlgConnect.m_strServerAddress = (*pServers)[0];
	if ( dlgConnect.DoModal() == IDOK )
	{
		pServers->Add( dlgConnect.m_strServerAddress );
		pServers->WriteList();
		// Display the BotInfo View
		( (CPandoraApp*)AfxGetApp() )->OnViewBotinfo();
		Connect( dlgConnect.m_strServerAddress );
		//m_qrDemo.OpenFile();
	}
	delete pServers;
}

void CPandoraDoc::OnFileDisconnect() 
{
	if ( m_csStatus == csConnected )
	{
		CString strURL;

		strURL.LoadString( IDS_WEB_PANDORA );
		Say( strURL );
		Sleep( 300 );
	}
	Disconnect();
}

void CPandoraDoc::OnUpdateFileConnect( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csNotConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraDoc::OnUpdateFileDisconnect( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus != csNotConnected )
	{
		pCmdUI->Enable();
	}	
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

BOOL CPandoraDoc::CanCloseFrame( CFrameWnd* pFrame ) 
{
	if ( m_csStatus != csNotConnected )
	{
		return FALSE;
	}
	else
	{
		return CDocument::CanCloseFrame( pFrame );
	}
}

void CPandoraDoc::OnUpdateCommandsFlipoff( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraDoc::OnUpdateCommandsPoint( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraDoc::OnUpdateCommandsSalute( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraDoc::OnUpdateCommandsSuicide( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraDoc::OnUpdateCommandsTaunt( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void CPandoraDoc::OnUpdateCommandsWave( CCmdUI* pCmdUI ) 
{
	if ( m_csStatus == csConnected )
	{
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}
