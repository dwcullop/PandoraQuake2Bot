// BotInfoFrame.h : header file
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

#if !defined(AFX_BOTINFOFRAME_H__921C81D3_D8A0_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_BOTINFOFRAME_H__921C81D3_D8A0_11D1_AF1C_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CBotInfoFrame frame

#define BOTINFO_FRAME_WIDTH		630		// Width in Pixels
#define BOTINFO_FRAME_HEIGHT	220		// Height in Pixels

/////////////////////////////////////////////////////////////////////////////
// CBotInfoFrame frame

class CBotInfoFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBotInfoFrame)
// Attributes
private:

// Construction / Destruction
protected:
	CBotInfoFrame();           // protected constructor used by dynamic creation
	virtual ~CBotInfoFrame();

// Operations
public:

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBotInfoFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBotInfoFrame)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOTINFOFRAME_H__921C81D3_D8A0_11D1_AF1C_0060080A5FD2__INCLUDED_)
