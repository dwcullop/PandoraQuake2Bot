// MainFrm.cpp : implementation of the CMainFrame class
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

#include "stdafx.h"
#include "Pandora.h"

#include "MainFrm.h"
#include "PandoraDoc.h"
#include "AdvTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI( ID_INDICATOR_GAME_TIME, OnUpdateGameTime )
	ON_UPDATE_COMMAND_UI( ID_INDICATOR_PING, OnUpdatePing )
	ON_UPDATE_COMMAND_UI( ID_INDICATOR_TOTAL_TIME, OnUpdateTotalTime )
	ON_UPDATE_COMMAND_UI( ID_INDICATOR_CONN, OnUpdateConn )
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_PING,
	ID_INDICATOR_CONN,
	ID_INDICATOR_GAME_TIME,
	ID_INDICATOR_TOTAL_TIME,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pDoc = NULL;
}

CMainFrame::~CMainFrame()
{
}

////////////////////////////////////////////////////////////////////////////
// CMainFrame Overrides

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	CRect rctDesktopSize;

	cs.style &= ~FWS_PREFIXTITLE;
	cs.cx	= MAIN_FRAME_WIDTH;							// Width
	cs.cy	= MAIN_FRAME_HEIGHT;						// Height
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Operations

void CMainFrame::DisplayView(CDocTemplate* pTemplate, CRuntimeClass* pViewClass)
{
    CMDIChildWnd*	pMDIActive;
	CDocument*		pDoc;
	CView*			pView;

	pMDIActive = MDIGetActive();
	ASSERT(pMDIActive != NULL);
	pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);

	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ActivateFrame();
			return;
		}
	}

	CMDIChildWnd* pNewFrame	= (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));
	if (pNewFrame != NULL)
	{
		ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)));
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
		pNewFrame->EnableWindow(TRUE);
	}
	else
	{
		TRACE("Unable to create that view!");
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if (m_pDoc != NULL)
	{
		m_pDoc->OnTimer( nIDEvent );
	}
	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnUpdateGameTime( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	if ( m_pDoc != NULL )
	{
		CString		strTime;
		CAdvTime	tGame;

		tGame.SetValue( m_pDoc->GetFrameNumber() / 10.0 );
		strTime.Format( CString((LPCSTR)IDS_FMT_IND_GAME_TIME), tGame.GetString() );
		pCmdUI->SetText( strTime );
	}
}

void CMainFrame::OnUpdateConn( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	if ( m_pDoc != NULL )
	{
		CString strPL;

		strPL.Format( CString((LPCSTR)IDS_FMT_IND_PACKET_LOSS), m_pDoc->GetSocket()->GetPacketLoss() );
		pCmdUI->SetText( strPL );
	}
}

void CMainFrame::OnUpdatePacketLoss( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
/*	if ( m_pDoc != NULL )

	{
		CString strPL;

		strPL.Format( "Loss: %d%%", (int)(m_pDoc->GetSocket()->GetPacketLoss()) );
		pCmdUI->SetText( strPL );
	}
	else
	{
		pCmdUI->SetText("Hello");
	}
*/
}

void CMainFrame::OnUpdatePing( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	if ( m_pDoc != NULL )
	{
		CString strPing;

		strPing.Format( CString((LPCSTR)IDS_FMT_IND_PING), m_pDoc->GetSocket()->GetPing() );
		pCmdUI->SetText( strPing );
	}
}

void CMainFrame::OnUpdateTotalTime( CCmdUI* pCmdUI )
{
	pCmdUI->Enable();
	if ( m_pDoc != NULL )
	{
		CString		strTime;
		CString		strFormat;

		m_pDoc->GetConnectTime( strTime );
		strFormat.Format( CString((LPCSTR)IDS_FMT_IND_TOTAL_TIME), strTime );
		pCmdUI->SetText( strFormat );
	}
}