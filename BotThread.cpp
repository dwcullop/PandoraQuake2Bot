//	BotThread.cpp : implementation of the CBotThread class
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

#include "StdAfx.h"
#include "Pandora.h"
#include "BotThread.h"
#include "PandoraDoc.h"
#include "BotSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBotThread

IMPLEMENT_DYNCREATE(CBotThread, CWinThread)

/////////////////////////////////////////////////////////////////////////////
// CBotThread Static Members

	// NOTE: These static values must be changed before instantiating
	// a object of type "CBotThread" (or a derived class)

CPandoraDoc* CBotThread::m_pBotDoc	= NULL;
CBotSystem* CBotThread::m_pBotSys	= NULL;

/////////////////////////////////////////////////////////////////////////////
// CBotThread Construction / Destruction

CBotThread::CBotThread()
{
}

CBotThread::~CBotThread()
{
	UnregisterThread();
}

/////////////////////////////////////////////////////////////////////////////
// CBotThread Operations

void CBotThread::StartThread()
{
	RegisterThread();
	CreateThread();
}

void CBotThread::RegisterThread()
{
	ASSERT( m_pBotDoc != NULL );
	ASSERT( m_pBotSys != NULL );
	m_pBotSys->RegisterThread( this );
}

void CBotThread::UnregisterThread()
{
	if ( m_pBotSys != NULL )
	{
		m_pBotSys->UnregisterThread( this );
	}
}

BOOL CBotThread::PreTranslateMessage( MSG* pMsg )
{
	BOOL bProcessed = TRUE;

	switch( pMsg->message )
	{
	// System Messages
	case QB_SYSTEM_ERROR_NETWORK:
		OnNetworkError();
		break;
	case QB_SYSTEM_ERROR_OTHER:
		OnOtherError();
		break;
	case QB_SYSTEM_SHUTDOWN:
		OnSystemShutdown();
		break;
	// System Objects
	case QB_SYSOBJ_TEXTMESSAGE:
		OnTextMessage( (CTextMessage*)pMsg->wParam);
		break;
	case QB_SYSOBJ_SOUND:
		OnSound( (CSound*)pMsg->wParam );
		break;
	case QB_SYSOBJ_TEMP_ENT:
		OnTempEnt( (CTempEntity*)pMsg->wParam );
		break;
	case QB_SYSOBJ_CENTER_MESSAGE:
		OnCenterMessage( (CTextMessage*)pMsg->wParam );
		break;
	case QB_SYSOBJ_STUFFED_TEXT:
		OnStuffText( (CTextMessage*)pMsg->wParam );
		break;
	case QB_SYSOBJ_LAYOUT:
		OnLayout( (CTextMessage*)pMsg->wParam );
		break;
	// Timer Based
	case QB_TIMER_CHECK_SEND:
		OnTimerCheckSend();
		break;
	case QB_TIMER_CHECK_RELIABLE:
		OnTimerCheckReliable();
		break;
	case QB_TIMER_SEND_MOVE:
		OnTimerSendMove();
		break;
	case QB_TIMER_SEND_STATUS:
		OnTimerSendStatus();
		break;
	case QB_TIMER_COMPUTE_MOVE:
		OnTimerComputeMove();
		break;
	// Network Info
	case QB_NETWORK_MOVE_SENT:
		OnNetworkMoveSent();
		break;
	case QB_NETWORK_PACKET_DONE:
		OnNetworkPacketDone();
		break;
	case QB_NETWORK_BEGIN_LEVEL:
		OnNetworkBeginLevel();
		break;
	case QB_NETWORK_END_LEVEL:
		OnNetworkEndLevel();
		break;
	// Update Info
	case QB_INFO_ERR_MESSAGE:
		OnInfoErrorMessage( (UINT)pMsg->lParam );
		break;
	case QB_INFO_SERVER_DATA:
		OnInfoServerData();
		break;
	case QB_INFO_INVENTORY:
		OnInfoInventory( (UINT)pMsg->lParam );
		break;
	// Entity Update Messages
	case QB_ENTITY_UPDATE_ACTIVE:
		OnEntityUpdateActive( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_UPDATE_REMOVE:
		OnEntityUpdateRemove( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_UPDATE_ORIGIN:
		OnEntityUpdateOrigin( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_UPDATE_MODEL:
		OnEntityUpdateModel( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_UPDATE_FRAME:
		OnEntityUpdateFrame( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_UPDATE_EFFECTS:
		OnEntityUpdateEffects( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_UPDATE_EVENT:
		OnEntityUpdateEvent( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_MUZZLEFLASH:
		OnEntityMuzzleFlash( (WORD)pMsg->lParam );
		break;
	case QB_ENTITY_MUZZLEFLASH2:
		OnEntityMuzzleFlash2( (WORD)pMsg->lParam );
		break;
	// Player Update Messages
	case QB_PLAYER_UPDATE_ACTIVE:
		OnPlayerUpdateActive( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_REMOVE:
		OnPlayerUpdateRemove( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_ORIGIN:
		OnPlayerUpdateOrigin( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_MODEL:
		OnPlayerUpdateModel( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_FRAME:
		OnPlayerUpdateFrame( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_EFFECTS:
		OnPlayerUpdateEffects( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_EVENT:
		OnPlayerUpdateEvent( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_MUZZLEFLASH:
		OnPlayerMuzzleFlash( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_MUZZLEFLASH2:
		OnPlayerMuzzleFlash2( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_KILLED:
		OnPlayerKilled( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_RESPAWNED:
		OnPlayerKilled( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_SKIN:
		OnPlayerUpdateSkin( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_NAME:
		OnPlayerUpdateName( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_FRAGS:
		OnPlayerUpdateFrags( (BYTE)pMsg->lParam );
		break;
	case QB_PLAYER_UPDATE_WEAPON:
		OnPlayerUpdateWeapon( (BYTE)pMsg->lParam );
		break;
	// Bot Update Messages
	case QB_BOT_UPDATE_ACTIVE:
		OnBotUpdateActive();
		break;
	case QB_BOT_UPDATE_REMOVE:
		OnBotUpdateRemove();
		break;
	case QB_BOT_UPDATE_ORIGIN:
		OnBotUpdateOrigin();
		break;
	case QB_BOT_UPDATE_MODEL:
		OnBotUpdateModel();
		break;
	case QB_BOT_UPDATE_FRAME:
		OnBotUpdateFrame();
		break;
	case QB_BOT_UPDATE_EFFECTS:
		OnBotUpdateEffects();
		break;
	case QB_BOT_UPDATE_EVENT:
		OnBotUpdateEvent();
		break;
	case QB_BOT_MUZZLEFLASH:
		OnBotMuzzleFlash();
		break;
	case QB_BOT_MUZZLEFLASH2:
		OnBotMuzzleFlash2();
		break;
	case QB_BOT_KILLED:
		OnBotKilled( (WORD)pMsg->lParam );
		break;
	case QB_BOT_RESPAWNED:
		OnBotRespawned();
		break;
	case QB_BOT_UPDATE_SKIN:
		OnBotUpdateSkin();
		break;
	case QB_BOT_UPDATE_NAME:
		OnBotUpdateName();
		break;
	case QB_BOT_UPDATE_FRAGS:
		OnBotUpdateFrags( (short)pMsg->lParam );
		break;
	case QB_BOT_UPDATE_WEAPON:
		OnBotUpdateWeapon();
		break;
	case QB_BOT_UPDATE_ATTACK_TARGET:
		OnBotUpdateAttackTarget( (CPlayer*)pMsg->lParam );
		break;
	case QB_BOT_UPDATE_MOVE_TARGET:
		OnBotUpdateMoveTarget( (CMapPoint*)pMsg->lParam );
		break;
	case QB_BOT_UPDATE_AI_INFO:
		OnBotUpdateAIInfo( (UINT)pMsg->lParam );
		break;
	case QB_BOT_UPDATE_HEALTH:
		OnBotUpdateHealth( (short)pMsg->lParam );
		break;
	case QB_BOT_UPDATE_AMMO:
		OnBotUpdateAmmo( (short)pMsg->lParam );
		break;
	case QB_BOT_UPDATE_VELOCITY:
		OnBotUpdateVelocity();
		break;
	case QB_BOT_UPDATE_GUN_INDEX:
		OnBotUpdateGunIndex();
		break;
	case QB_BOT_PICKUP_ITEM:
		OnBotPickupItem();
		break;
// If the message is none of the above ...
	default:
		bProcessed = FALSE;
		break;
	}
	return (bProcessed ? TRUE : CWinThread::PreTranslateMessage(pMsg));
}

BOOL CBotThread::InitInstance()
{
	return TRUE;
}

int CBotThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CBotThread Message Map

BEGIN_MESSAGE_MAP(CBotThread, CWinThread)
	//{{AFX_MSG_MAP(CBotThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CBotThread::OnSystemShutdown()
{
	delete this;
	ExitThread(0);
}