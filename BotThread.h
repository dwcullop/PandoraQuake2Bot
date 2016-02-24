//	BotThread.h : interface of the CBotThread class							
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

#if !defined(AFX_BOTTHREAD_H__9C4E6BD2_E0EC_11D0_BDF3_0000C06F1BB9__INCLUDED_)
#define AFX_BOTTHREAD_H__9C4E6BD2_E0EC_11D0_BDF3_0000C06F1BB9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StdAfx.h"
#include "PandoraDefs.h"
#include "SystemObject.h"
#include "QuakePacket.h"
#include "BotSystem.h"
#include "BotMsgs.h"
#include "TextMessage.h"
#include "Sound.h"
#include "TempEntity.h"
#include "Player.h"
#include "MapPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CBotThread Class Declarations

class CPandoraDoc;

/////////////////////////////////////////////////////////////////////////////
// CBotThread thread

class CBotThread : public CWinThread
{
	DECLARE_DYNCREATE(CBotThread)

// Attributes
public:

// Static Attributes
protected:
	static CPandoraDoc*	m_pBotDoc;
	static CBotSystem*	m_pBotSys;

// Construction / Destruction 
public:
	CBotThread();
	virtual ~CBotThread();

// Operations
public:
	virtual BOOL PreTranslateMessage( MSG* );
	void	StartThread();

private:
	void RegisterThread();
	void UnregisterThread();

protected:
	void Post(const UINT& nMsgID, void* pParam = NULL, const UINT& nParam = 0);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBotThread)
	public:
		virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CBotThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Custom Message Handlers
protected:
	// System Messages
	virtual void OnNetworkError()							{ };
	virtual void OnOtherError()								{ };
	// System Object Messages
	virtual void OnTextMessage( CTextMessage* pTemp )		{ m_pBotSys->IgnoreObject(pTemp); };
	virtual void OnSound( CSound* pTemp )					{ m_pBotSys->IgnoreObject(pTemp); };
	virtual void OnTempEnt( CTempEntity* pTemp )			{ m_pBotSys->IgnoreObject(pTemp); };
	virtual void OnCenterMessage( CTextMessage* pTemp )		{ m_pBotSys->IgnoreObject(pTemp); };
	virtual void OnStuffText( CTextMessage* pTemp )			{ m_pBotSys->IgnoreObject(pTemp); };
	virtual void OnLayout( CTextMessage* pTemp )			{ m_pBotSys->IgnoreObject(pTemp); };
	// Timer Based Messages
	virtual void OnTimerCheckSend()							{ };
	virtual void OnTimerCheckReliable()						{ };
	virtual void OnTimerSendMove()							{ };
	virtual void OnTimerSendStatus()						{ };
	virtual void OnTimerComputeMove()						{ };
	// Network Info Messages
	virtual void OnNetworkMoveSent()						{ };
	virtual void OnNetworkPacketDone()						{ };
	virtual void OnNetworkBeginLevel()						{ };
	virtual void OnNetworkEndLevel()						{ };
	// Update Info
	virtual void OnInfoErrorMessage( const UINT )			{ };
	virtual void OnInfoServerData()							{ };
	virtual void OnInfoInventory( const UINT )				{ };
	// Entity Update Messages
	virtual void OnEntityUpdateActive( const WORD )			{ };
	virtual void OnEntityUpdateRemove( const WORD )			{ };
	virtual void OnEntityUpdateOrigin( const WORD )			{ };
	virtual void OnEntityUpdateModel( const WORD )			{ };
	virtual void OnEntityUpdateFrame( const WORD )			{ };
	virtual void OnEntityUpdateEffects( const WORD )		{ };
	virtual void OnEntityUpdateEvent( const WORD )			{ };
	virtual void OnEntityMuzzleFlash( const WORD )			{ };
	virtual void OnEntityMuzzleFlash2( const WORD )			{ };
	// Player Update Messages
	virtual void OnPlayerUpdateActive( const BYTE )			{ };
	virtual void OnPlayerUpdateRemove( const BYTE )			{ };
	virtual void OnPlayerUpdateOrigin( const BYTE )			{ };
	virtual void OnPlayerUpdateModel( const BYTE )			{ };
	virtual void OnPlayerUpdateFrame( const BYTE )			{ };
	virtual void OnPlayerUpdateEffects( const BYTE )		{ };
	virtual void OnPlayerUpdateEvent( const BYTE )			{ };
	virtual void OnPlayerMuzzleFlash( const BYTE )			{ };
	virtual void OnPlayerMuzzleFlash2( const BYTE )			{ };
	virtual void OnPlayerKilled( const BYTE )				{ };
	virtual void OnPlayerRespawned( const BYTE )			{ };
	virtual void OnPlayerUpdateSkin( const BYTE )			{ };
	virtual void OnPlayerUpdateName( const BYTE )			{ };
	virtual void OnPlayerUpdateFrags( const BYTE )			{ };
	virtual void OnPlayerUpdateWeapon( const BYTE )			{ };
	// Bot Update Messages
	virtual void OnBotUpdateActive()						{ };
	virtual void OnBotUpdateRemove()						{ };
	virtual void OnBotUpdateOrigin()						{ };
	virtual void OnBotUpdateModel()							{ };
	virtual void OnBotUpdateFrame()							{ };
	virtual void OnBotUpdateEffects()						{ };
	virtual void OnBotUpdateEvent()							{ };
	virtual void OnBotMuzzleFlash()							{ };
	virtual void OnBotMuzzleFlash2()						{ };
	virtual void OnBotKilled( const WORD )					{ };
	virtual void OnBotRespawned()							{ };
	virtual void OnBotUpdateSkin()							{ };
	virtual void OnBotUpdateName()							{ };
	virtual void OnBotUpdateFrags( const short )			{ };
	virtual void OnBotUpdateWeapon()						{ };
	virtual void OnBotUpdateAttackTarget( CPlayer* )		{ };
	virtual void OnBotUpdateMoveTarget( CMapPoint* )		{ };
	virtual void OnBotUpdateAIInfo( const UINT )			{ };
	virtual void OnBotUpdateHealth( const short )			{ };
	virtual void OnBotUpdateAmmo( const short )				{ };
	virtual void OnBotUpdateVelocity()						{ };
	virtual void OnBotUpdateGunIndex()						{ };
	virtual void OnBotPickupItem()							{ };

private:
	void OnSystemShutdown();	// Not virtual

// Static Operators
public:
	static void	SetBotDoc(CPandoraDoc* pNew)			{ m_pBotDoc	= pNew; };
	static void SetBotSys(CBotSystem* pNew)				{ m_pBotSys = pNew; };

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBotThread Inline Functions

inline void CBotThread::Post(const UINT& nMsgID, void* pParam, const UINT& nParam)
{
	ASSERT( m_pBotSys != NULL );
	m_pBotSys->PostSystemMessage( nMsgID, pParam, nParam );
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


/////////////////////////////////////////////////////////////////////////////



#endif // !defined(AFX_BOTTHREAD_H__9C4E6BD2_E0EC_11D0_BDF3_0000C06F1BB9__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
