// AboutBox.cpp : implementation file
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
#include "AboutBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutBox dialog


CAboutBox::CAboutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutBox)
	//}}AFX_DATA_INIT
}


void CAboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutBox)
	DDX_Control(pDX, IDC_THANK_YOU, m_ctrlThankYou);
	DDX_Control(pDX, IDC_GREETINGS, m_ctrlGreetings);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutBox, CDialog)
	//{{AFX_MSG_MAP(CAboutBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutBox message handlers

BOOL CAboutBox::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrlGreetings.SetWindowText( CString((LPCSTR)IDS_ABOUT_GREETING_LIST) );
	m_ctrlThankYou.SetWindowText( CString((LPCSTR)IDS_ABOUT_THANKYOU_LIST) );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
