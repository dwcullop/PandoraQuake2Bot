// ConsoleView.h : header file
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

#if !defined(AFX_CONSOLEVIEW_H__7BB23497_BD1E_11D1_8720_444553540000__INCLUDED_)
#define AFX_CONSOLEVIEW_H__7BB23497_BD1E_11D1_8720_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Pandora.h"
#include <afxrich.h>

// Other Class
class CViewThread;

// CConsoleView Definitions
#define	COLOR_DEFAULT		0x000000	// Black
// Text Options
#define	TO_CENTER			0x01
#define TO_ITALIC			0x02
#define TO_BOLD				0x04
#define TO_UNDERLINE		0x08
#define TO_NEWLINE			0x10

class CConsoleView : public CRichEditView
{
	DECLARE_DYNCREATE(CConsoleView)

// Attributes
private:
	CViewThread* m_pThread;

// Construction / Destruction
protected: // create from serialization only
	CConsoleView();
public:
	virtual ~CConsoleView();

// Data Manipulation
public:
	void SetThread( CViewThread* pNew)			{ m_pThread = pNew; };
 
// Operations
public:
	void DisplayText( const CString& strText, const COLORREF crText = COLOR_DEFAULT, const BYTE nOptions = 0 );
	void StartTimer( const UINT&, const UINT& );
	void StopTimer( const UINT& );

private:
	void WriteString( const CString& );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsoleView)
	public:
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnReplaceSel( LPCTSTR lpszFind, BOOL bNext, BOOL bCase, BOOL bWord, LPCTSTR lpszReplace );
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CConsoleView)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOLEVIEW_H__7BB23497_BD1E_11D1_8720_444553540000__INCLUDED_)
