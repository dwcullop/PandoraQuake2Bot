// ConnectDialog.cpp : implementation file
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
#include "ConnectDialog.h"
#include <AfxAdv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDialog dialog


CConnectDialog::CConnectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDialog)
	m_strServerAddress = _T("");
	//}}AFX_DATA_INIT
}

void CConnectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDialog)
	DDX_Text(pDX, IDC_SERVER_ADDRESS, m_strServerAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDialog, CDialog)
	//{{AFX_MSG_MAP(CConnectDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDialog message handlers

