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
#if !defined(AFX_BOTINFOVIEW_H__921C81D2_D8A0_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_BOTINFOVIEW_H__921C81D2_D8A0_11D1_AF1C_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BotInfoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView Defines

/////////////////////////////////////////////////////////////////////////////
// CBotInfoView class definition

class CBotInfoView : public CFormView
{
DECLARE_DYNCREATE(CBotInfoView)

// Attributes
private:

// Form Data
private:
	//{{AFX_DATA(CBotInfoView)
	enum { IDD = IDD_BOT_INFO };
	CEdit	m_ctrlWeapon;
	CEdit	m_ctrlMovePos;
	CEdit	m_ctrlMoveName;
	CEdit	m_ctrlMoveDist;
	CEdit	m_ctrlHealth;
	CEdit	m_ctrlFrags;
	CEdit	m_ctrlBotVelocity;
	CEdit	m_ctrlBotPos;
	CEdit	m_ctrlAttackPos;
	CEdit	m_ctrlAttackName;
	CEdit	m_ctrlAttackDist;
	CEdit	m_ctrlAIInfo;
	CEdit	m_ctrlChatText;
	//}}AFX_DATA

// Construction / Destruction
protected:
	CBotInfoView();           // protected constructor used by dynamic creation
	virtual ~CBotInfoView();

// Operations
public:
	void SetWeapon( const CString& strText )	{ m_ctrlWeapon.SetWindowText( strText ); };
	void SetMovePos( const CString& strText )	{ m_ctrlMovePos.SetWindowText( strText ); };
	void SetMoveName( const CString& strText )	{ m_ctrlMoveName.SetWindowText( strText ); };
	void SetMoveDist( const CString& strText )	{ m_ctrlMoveDist.SetWindowText( strText ); };
	void SetHealth( const CString& strText )	{ m_ctrlHealth.SetWindowText( strText ); };
	void SetFrags( const CString& strText )		{ m_ctrlFrags.SetWindowText( strText ); };
	void SetVelocity( const CString& strText )	{ m_ctrlBotVelocity.SetWindowText( strText ); };
	void SetBotPos( const CString& strText )	{ m_ctrlBotPos.SetWindowText( strText ); };
	void SetAttackPos( const CString& strText )	{ m_ctrlAttackPos.SetWindowText( strText ); };
	void SetAttackName( const CString& strText ){ m_ctrlAttackName.SetWindowText( strText ); };
	void SetAttackDist( const CString& strText ){ m_ctrlAttackDist.SetWindowText( strText ); };
	void SetAIInfo( const CString& strText )	{ m_ctrlAIInfo.SetWindowText( strText ); };
	void Clear();

private:
	void SetFieldText( CEdit&, const CString& );

// Overrides
private:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBotInfoView)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Diagnostics
#ifdef _DEBUG
protected:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Message Handlers
protected:
	// Generated message map functions
	//{{AFX_MSG(CBotInfoView)
	afx_msg void OnButtonCmd();
	afx_msg void OnButtonSay();
	afx_msg void OnButtonTeam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOTINFOVIEW_H__921C81D2_D8A0_11D1_AF1C_0060080A5FD2__INCLUDED_)
