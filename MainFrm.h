// MainFrm.h : interface of the CMainFrame class
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

#if !defined(AFX_MAINFRM_H__7BB23489_BD1E_11D1_8720_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__7BB23489_BD1E_11D1_8720_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BotInfoFrame.h"

#define MAIN_FRAME_WIDTH	(BOTINFO_FRAME_WIDTH+15)
#define MAIN_FRAME_HEIGHT	600

class CPandoraDoc;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
private:

protected:
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	CPandoraDoc*	m_pDoc;

// Construction / Destruction
public:
	CMainFrame();

// Operations
public:
	void DisplayView(CDocTemplate*, CRuntimeClass*);
	void SetDoc( CPandoraDoc* pNew )					{ m_pDoc = pNew; };

// Overrides
private:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnUpdateConn( CCmdUI* );
	afx_msg void OnUpdatePing( CCmdUI* );
	afx_msg void OnUpdateGameTime( CCmdUI* );
	afx_msg void OnUpdateTotalTime( CCmdUI* );
	afx_msg void OnUpdatePacketLoss( CCmdUI* );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7BB23489_BD1E_11D1_8720_444553540000__INCLUDED_)
