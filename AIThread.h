//	AIThread.h : header file
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

#if !defined(AFX_AITHREAD_H__81F028E1_D8AA_11D0_97F8_000000000000__INCLUDED_)
#define AFX_AITHREAD_H__81F028E1_D8AA_11D0_97F8_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BotThread.h"
#include "AdvTime.h"
#include "BotMove.h"
#include "GameState.h"
#include "BotAI.h"

/////////////////////////////////////////////////////////////////////////////
// CAIThread Defines

/////////////////////////////////////////////////////////////////////////////
// CAIThread class definition

class CAIThread : public CBotThread, public CBotAI
{
	DECLARE_DYNCREATE(CAIThread)

// Attributes
private:
	void		(CAIThread::*m_pDoMove)();

// Construction / Destruction
public:
	CAIThread();
	virtual ~CAIThread();

// Standard Programmed Moves
private:
	void	RespawnOne();
	void	RespawnTwo();
	void	NewInventoryMove();
	void	NormalMove();
	void	RandomMove();

// Operations
private:
	void	GetAttackTarget();
	void	GetMoveTarget();
	void	SelectMove();
	void	UpdateInfo( const UINT& );
	void	ComputeMove();

// Overrides

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnNetworkBeginLevel();
	virtual void OnNetworkEndLevel();
	virtual void OnTimerSendMove()							{ ComputeMove(); };
	virtual void OnEntityUpdateActive( const WORD );
	virtual void OnEntityUpdateRemove( const WORD );
	virtual void OnPlayerUpdateActive( const BYTE );
	virtual void OnPlayerUpdateRemove( const BYTE );
	virtual void OnPlayerUpdateFrame( const BYTE );
	virtual void OnPlayerKilled( const BYTE );
	virtual void OnBotKilled( const WORD );
	virtual void OnBotRespawned();
	virtual void OnBotUpdateAttackTarget();
	virtual void OnBotUpdateInventory();
	virtual void OnBotUpdateGunIndex();
	virtual void OnBotUpdateOrigin();
	virtual void OnBotUpdateVelocity();
	virtual void OnBotPickupItem();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAIThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

	/////////////////////////////////////////////////////////////////////////////
	// CAIThread Overrides

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIThread_H__81F028E1_D8AA_11D0_97F8_000000000000__INCLUDED_)
