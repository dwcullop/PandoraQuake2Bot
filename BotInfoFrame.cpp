// BotInfoFrame.cpp : implementation file
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
#include "BotInfoFrame.h"
#include "MainFrm.h"
#include "PandoraDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBotInfoFrame

IMPLEMENT_DYNCREATE(CBotInfoFrame, CMDIChildWnd)

CBotInfoFrame::CBotInfoFrame()
{
}

CBotInfoFrame::~CBotInfoFrame()
{
}


BEGIN_MESSAGE_MAP(CBotInfoFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CBotInfoFrame)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBotInfoFrame message handlers

BOOL CBotInfoFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	CRect rctParentSize;

	AfxGetMainWnd()->GetClientRect( &rctParentSize );
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~FWS_PREFIXTITLE;
	cs.style &= ~WS_THICKFRAME;
	cs.style |= WS_BORDER;
	cs.cx	= BOTINFO_FRAME_WIDTH;								// Width
	cs.cy	= BOTINFO_FRAME_HEIGHT;								// Height
	cs.x	= 0;												// X Coordinate
	cs.y	= (rctParentSize.Height() - BOTINFO_FRAME_HEIGHT - 55);	// Y Coordinate
	return CMDIChildWnd::PreCreateWindow(cs);
}

void CBotInfoFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CString strTitle;

	CMDIChildWnd::OnShowWindow(bShow, nStatus);
	strTitle.LoadString( IDS_BOT_INFO_TITLE );
	SetWindowText( strTitle );
	((CPandoraApp*)AfxGetApp())->ShowingBotInfoView( TRUE );
}

void CBotInfoFrame::PostNcDestroy() 
{
	((CPandoraApp*)AfxGetApp())->ShowingBotInfoView( FALSE );
	((CPandoraDoc*)GetActiveDocument())->SetViewThreadViews();
	CMDIChildWnd::PostNcDestroy();
}

void CBotInfoFrame::OnClose() 
{
	if (((CPandoraDoc*)GetActiveDocument())->GetStatus() == csNotConnected)
	{
		CMDIChildWnd::OnClose();
	}
}
