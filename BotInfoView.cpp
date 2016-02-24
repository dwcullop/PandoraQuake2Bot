// BotInfoView.cpp : implementation file
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
#include "BotInfoView.h"
#include "PandoraDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView

IMPLEMENT_DYNCREATE(CBotInfoView, CFormView)

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView Construction / Destruction

CBotInfoView::CBotInfoView()
	: CFormView(CBotInfoView::IDD)
{
	//{{AFX_DATA_INIT(CBotInfoView)
	//}}AFX_DATA_INIT
}

CBotInfoView::~CBotInfoView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView Operations

void CBotInfoView::Clear()
{
	SetAIInfo( _T("") );
	SetAttackDist( _T("") );
	SetAttackName( _T("") );
	SetAttackPos( _T("") );
	SetBotPos( _T("") );
	SetFrags( _T("") );
	SetHealth( _T("") );
	SetMoveDist( _T("") );
	SetMoveName( _T("") );
	SetMovePos( _T("") );
	SetVelocity( _T("") );
	SetWeapon( _T("") );
}

void CBotInfoView::SetFieldText( CEdit& ctrl, const CString& strText )
{
	ctrl.SetSel( 0, -1 );
	ctrl.ReplaceSel( strText );
}

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView Overrides

void CBotInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBotInfoView)
	DDX_Control(pDX, IDC_WEAPON, m_ctrlWeapon);
	DDX_Control(pDX, IDC_MOVE_POS, m_ctrlMovePos);
	DDX_Control(pDX, IDC_MOVE_NAME, m_ctrlMoveName);
	DDX_Control(pDX, IDC_MOVE_DIST, m_ctrlMoveDist);
	DDX_Control(pDX, IDC_HEALTH, m_ctrlHealth);
	DDX_Control(pDX, IDC_FRAGS, m_ctrlFrags);
	DDX_Control(pDX, IDC_BOT_VELOCITY, m_ctrlBotVelocity);
	DDX_Control(pDX, IDC_BOT_POS, m_ctrlBotPos);
	DDX_Control(pDX, IDC_ATTACK_POS, m_ctrlAttackPos);
	DDX_Control(pDX, IDC_ATTACK_NAME, m_ctrlAttackName);
	DDX_Control(pDX, IDC_ATTACK_DIST, m_ctrlAttackDist);
	DDX_Control(pDX, IDC_AI_INFO_TEXT, m_ctrlAIInfo);
	DDX_Control(pDX, IDC_CHATTEXT, m_ctrlChatText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBotInfoView, CFormView)
	//{{AFX_MSG_MAP(CBotInfoView)
	ON_BN_CLICKED(IDC_BUTTON_CMD, OnButtonCmd)
	ON_BN_CLICKED(IDC_BUTTON_SAY, OnButtonSay)
	ON_BN_CLICKED(IDC_BUTTON_TEAM, OnButtonTeam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView diagnostics

#ifdef _DEBUG
void CBotInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBotInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView message handlers

void CBotInfoView::OnButtonCmd() 
{
	CString strText;

	m_ctrlChatText.GetWindowText( strText );
	((CPandoraDoc*)GetDocument())->ConsoleCommand( strText );
	m_ctrlChatText.SetWindowText( _T("") );
	m_ctrlChatText.SetFocus();
}

void CBotInfoView::OnButtonSay() 
{
	CString strText;

	m_ctrlChatText.GetWindowText( strText );
	((CPandoraDoc*)GetDocument())->Say( strText );
	m_ctrlChatText.SetWindowText( _T("") );
	m_ctrlChatText.SetFocus();
}

void CBotInfoView::OnButtonTeam() 
{
	CString strText;

	m_ctrlChatText.GetWindowText( strText );
	((CPandoraDoc*)GetDocument())->SayTeam( strText );
	m_ctrlChatText.SetWindowText( _T("") );
	m_ctrlChatText.SetFocus();
}
