// ViewThread.h: interface for the CViewThread class
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

#if !defined(AFX_VIEWTHREAD_H__D05094A1_CE42_11D1_AF1A_0060080A5FD2__INCLUDED_)
#define AFX_VIEWTHREAD_H__D05094A1_CE42_11D1_AF1A_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BotThread.h"
#include "ConsoleView.h"
#include "BotInfoView.h"
#include "TextMessage.h"
#include "Player.h"
#include "MapPoint.h"

class CViewThread : public CBotThread  
{
	DECLARE_DYNCREATE(CViewThread)

// Attributes
private:
	CConsoleView*		m_pConsole;
	CBotInfoView*		m_pBotInfo;
	// Bot Stats to be displayed
	WORD				m_nDeaths;
	short				m_nAmmo;
	short				m_nFrags;
	short				m_nHealth;
	const CPlayer*		m_pAttackTarget;
	const CMapPoint*	m_pMoveTarget;
	CVector				m_vBotPos;
	CVector				m_vBotVelocity;
	CString				m_strWeapon;
	CString				m_strMoveName;
	CVector				m_vMovePos;
	CVector				m_vMoveDist;
	CString				m_strAttackName;
	CVector				m_vAttackPos;
	CVector			 	m_vAttackDist;

// Construction / Destruction
public:
	CViewThread();
	virtual ~CViewThread();

// Data Manipulation
public:
	void SetConsoleView( CConsoleView* pNew )				{ m_pConsole = pNew; };
	void SetBotInfoView( CBotInfoView* pNew )				{ m_pBotInfo = pNew; };

// Operations
private:
	void Clear();
	BOOL UpdateOkay();
	void UpdateAmmoAndWeapon();
	void UpdateAttackName();
	void UpdateAttackPos();
	void UpdateAttackDist();
	void UpdateBotOrigin();
	void UpdateBotVelocity();
	void UpdateDeathsAndFrags();
	void UpdateHealth();
	void UpdateMoveName();
	void UpdateMovePos();
	void UpdateMoveDist();
	void AddPrefix( const CString& );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBotThread)
	public:
		virtual BOOL InitInstance();
		virtual int ExitInstance();
		virtual	void OnTextMessage( CTextMessage* );
		virtual void OnStuffText( CTextMessage* );
		virtual void OnCenterMessage( CTextMessage* );
		virtual void OnInfoErrorMessage( const UINT );
		virtual void OnNetworkBeginLevel();
		virtual void OnNetworkEndLevel();
		// Player Update Info
		virtual void OnPlayerUpdateOrigin( const BYTE );
		// Bot Update Info
		virtual void OnBotUpdateVelocity();
		virtual void OnBotUpdateOrigin();
		virtual void OnBotKilled( const WORD );
		virtual void OnBotUpdateFrags( const short );
		virtual void OnBotUpdateAttackTarget( CPlayer* );
		virtual void OnBotUpdateMoveTarget( CMapPoint* );
		virtual void OnBotUpdateHealth( const short );
		virtual void OnBotUpdateAmmo( const short );
		virtual void OnBotUpdateAIInfo( const UINT );
		virtual void OnBotUpdateWeapon();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CBotThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_VIEWTHREAD_H__D05094A1_CE42_11D1_AF1A_0060080A5FD2__INCLUDED_)
