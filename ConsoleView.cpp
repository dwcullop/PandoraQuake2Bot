// ConsoleView.cpp : implementation file
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
#include "ConsoleView.h"
#include "PandoraDoc.h"
#include "ViewThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConsoleView

IMPLEMENT_DYNCREATE(CConsoleView, CRichEditView)

CConsoleView::CConsoleView()
{
	m_pThread = NULL;
}

CConsoleView::~CConsoleView()
{
}

BEGIN_MESSAGE_MAP(CConsoleView, CRichEditView)
	//{{AFX_MSG_MAP(CConsoleView)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConsoleView Private Operations

void CConsoleView::WriteString( const CString& strText )
{
	GetRichEditCtrl().SetSel( GetTextLength(), GetTextLength() );
	GetRichEditCtrl().ReplaceSel( strText );
}

/////////////////////////////////////////////////////////////////////////////
// CConsoleView Operations

void CConsoleView::DisplayText( const CString& strText, const COLORREF crText, const BYTE nOptions )
{
	CHARFORMAT2 charFormat;
	PARAFORMAT2 pf;

	// Set the font info
	charFormat.crTextColor = crText;
	charFormat.dwEffects = 0;
	charFormat.dwMask = (CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE);
	if (nOptions & TO_BOLD)
	{
		charFormat.dwEffects |= CFE_BOLD;
	}
	if (nOptions & TO_ITALIC)
	{
		charFormat.dwEffects |= CFE_ITALIC;
	}
	if (nOptions & TO_UNDERLINE)
	{
		charFormat.dwEffects |= CFE_UNDERLINE;
	}
	SetCharFormat( charFormat );
	// Set the paragraph info
	pf.dwMask = PFM_ALIGNMENT;
	if (nOptions & TO_CENTER)
	{
		pf.wAlignment = PFA_CENTER;
	}
	else
	{
		pf.wAlignment = PFA_LEFT;
	}
	SetParaFormat( pf );
	// Write the actual text
	WriteString( strText );
	// Skip a newline if necessary
	if (nOptions & TO_NEWLINE)
	{
		WriteString( "\n" );
	}
	// Undo the options
/*	if (nOptions & TO_CENTER)
	{
		pf.wAlignment = PFA_LEFT;
		pf.dwMask = PFM_ALIGNMENT;
		SetParaFormat( pf );
	}
*/
//	charFormat.crTextColor = crText;
	charFormat.dwEffects = 0;
	SetCharFormat( charFormat );
}

/////////////////////////////////////////////////////////////////////////////
// CConsoleView diagnostics

#ifdef _DEBUG
void CConsoleView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CConsoleView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConsoleView message handlers

void CConsoleView::OnReplaceSel( LPCTSTR lpszFind, BOOL bNext, BOOL bCase, BOOL bWord, LPCTSTR lpszReplace )
{
	// Do Nothing
}


BOOL CConsoleView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	// User cannot drop things into the Console Window
	return FALSE;
}

void CConsoleView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CHARFORMAT2 csConsole;

	CRichEditView::OnShowWindow(bShow, nStatus);
	GetRichEditCtrl().LimitText( -1 );	// Prevents the user from adding text
	// Use a fixed width font

		// TODO : Don't hard code Font Name here
	strcpy( csConsole.szFaceName, "Courier New" );
	csConsole.dwEffects = 0;
	csConsole.dwMask = (CFM_FACE | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_PROTECTED);
	csConsole.cbSize = sizeof( csConsole );
	CRichEditView::SetCharFormat( csConsole );
}