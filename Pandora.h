// Pandora.h : main header file for the Pandora Bot application
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

#if !defined(AFX_PANDORA_H__7BB23485_BD1E_11D1_8720_444553540000__INCLUDED_)
#define AFX_PANDORA_H__7BB23485_BD1E_11D1_8720_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPandoraApp:
// See Pandora.cpp for the implementation of this class
//

class CPandoraApp : public CWinApp
{
// Attributes
private:
	BOOL				m_bShowConsole;
	BOOL				m_bShowBotInfo;
	CMultiDocTemplate*	m_pConsoleTemplate;
//	CMultiDocTemplate*	m_pPandoraTemplate;
	CMultiDocTemplate*	m_pBotInfoTemplate;

// Construction / Destruction
public:
	CPandoraApp();
	virtual ~CPandoraApp()									{};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPandoraApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Operations
private:
	void GoToURL( const UINT& );

public:
	void ShowingConsoleView( const BOOL bShowing )	{ m_bShowConsole = bShowing; };
	void ShowingBotInfoView( const BOOL bShowing )	{ m_bShowBotInfo = bShowing; };

// Implementation
public:
	//{{AFX_MSG(CPandoraApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnWebDarrin();
	afx_msg void OnWebDvc();
	afx_msg void OnWebPandora();
	afx_msg void OnViewBotinfo();
	afx_msg void OnUpdateViewBotinfo(CCmdUI* pCmdUI);
	afx_msg void OnViewConsole();
	afx_msg void OnUpdateViewConsole(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANDORA_H__7BB23485_BD1E_11D1_8720_444553540000__INCLUDED_)
