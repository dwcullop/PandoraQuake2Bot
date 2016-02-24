// ConsoleFrame.cpp : implementation file
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
#include "ConsoleFrame.h"
#include "BotInfoFrame.h"
#include "MainFrm.h"
#include "PandoraDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConsoleFrame

IMPLEMENT_DYNCREATE(CConsoleFrame, CMDIChildWnd)

CConsoleFrame::CConsoleFrame()
{
}

CConsoleFrame::~CConsoleFrame()
{
}


BEGIN_MESSAGE_MAP(CConsoleFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CConsoleFrame)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConsoleFrame message handlers

BOOL CConsoleFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	CRect rctParentSize;

	(AfxGetMainWnd())->GetClientRect( &rctParentSize );
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~FWS_PREFIXTITLE;
	cs.cx	= BOTINFO_FRAME_WIDTH;								// Width
	cs.cy	= (rctParentSize.Height() - BOTINFO_FRAME_HEIGHT - 55);	// Height
	cs.x	= 0;												// X Coordinate
	cs.y	= 0;												// Y Coordinate
	return CMDIChildWnd::PreCreateWindow(cs);
}

void CConsoleFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CString strTitle;

	CMDIChildWnd::OnShowWindow(bShow, nStatus);
	strTitle.LoadString( IDS_CONSOLE_TITLE );
	SetWindowText( strTitle );
	((CPandoraApp*)AfxGetApp())->ShowingConsoleView( TRUE );
}

void CConsoleFrame::PostNcDestroy() 
{
	((CPandoraApp*)AfxGetApp())->ShowingConsoleView( FALSE );
	((CPandoraDoc*)GetActiveDocument())->SetViewThreadViews();
	CMDIChildWnd::PostNcDestroy();
}

void CConsoleFrame::OnClose() 
{
	if (((CPandoraDoc*)GetActiveDocument())->GetStatus() == csNotConnected)
	{
		CMDIChildWnd::OnClose();
	}
}
