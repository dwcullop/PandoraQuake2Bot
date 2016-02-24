// Bot.h: interface for the CBot class.
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

#if !defined(AFX_BOT_H__CA903384_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_BOT_H__CA903384_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_

#include "Player.h"
#include "PlayerInfo.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWeaponSpec;
class CMapPoint;

class CBot : public CPlayer
{
	DECLARE_DYNCREATE(CBot)
// Attributes
private:
	const CPlayer*		m_pAttackTarget;
	const CMapPoint*	m_pMoveTarget;
	CPlayerInfo*		m_pPastInfos[MAX_FRAMES];
	CPlayerInfo			m_piCurrentInfo;
	WORD				m_nItems[MAX_ITEMS];
	WORD				m_nDeaths;
	UINT				m_nAIInfo;

// Construction / Destruction
public:
	CBot()															{ Clear(); };
	virtual ~CBot()													{ Reset(); };

// Data Manipulation
public:
	// Get Functions
	const CPlayer*		GetAttackTarget()							{ return m_pAttackTarget; };
	const CMapPoint*	GetMoveTarget()								{ return m_pMoveTarget; };
	const WORD&			GetItemCount( const BYTE nIndex ) const		{ return m_nItems[nIndex]; };
	const CVector&		GetOrigin() const							{ return m_piCurrentInfo.GetOrigin(); };
	const CVector&		GetVelocity() const							{ return m_piCurrentInfo.GetVelocity(); };
	const WORD&			GetDeaths() const							{ return m_nDeaths; };
	const UINT&			GetAIInfo()	const							{ return m_nAIInfo; };
	CPlayerInfo&		GetPlayerInfo()								{ return m_piCurrentInfo; };
	CPlayerInfo*		GetPlayerInfoPtr()							{ return &m_piCurrentInfo; };
	// Set Functions
	void				SetAttackTarget( const CPlayer* pNew )		{ if ( pNew != m_pAttackTarget) { m_pAttackTarget = pNew; OnUpdateAttackTarget(); } };
	void				SetMoveTarget( const CMapPoint* pNew )		{ if ( pNew != m_pMoveTarget ) { m_pMoveTarget = pNew; OnUpdateMoveTarget(); } };
	void				SetAIInfo( const UINT& nNew )				{ if ( nNew != m_nAIInfo ) { m_nAIInfo = nNew; OnUpdateAIInfo(); } };
	void				SetItemCount( const BYTE , const WORD );

// Overrides
public:
	virtual void		AfterUpdate();
	virtual void		BeforeUpdate( const UINT&, const UINT& );
	virtual void		Clear();
	virtual void		NewFrame( const UINT&, const UINT& );
	virtual void		Reset();

private:
	virtual void		Post( const UINT& );

// Overridable Update Events
private:
	virtual void		OnActive()									{ Post( QB_BOT_UPDATE_ACTIVE ); };
	virtual void		OnRemove()									{ Post( QB_BOT_UPDATE_REMOVE ); };
	virtual void		OnMuzzleFlash()								{ Post( QB_BOT_MUZZLEFLASH ); };
	virtual void		OnMuzzleFlash2()							{ Post( QB_BOT_MUZZLEFLASH2 ); };
	virtual void		OnRespawned()								{ Post( QB_BOT_RESPAWNED ); };
	virtual void		OnUpdateSkin()								{ Post( QB_BOT_UPDATE_SKIN ); };
	virtual void		OnUpdateName()								{ Post( QB_BOT_UPDATE_NAME ); };
	virtual void		OnUpdateWeapon()							{ Post( QB_BOT_UPDATE_WEAPON ); };
	virtual void		OnUpdateFrags();
	virtual void		OnKilled();
	// Added for CBot
	virtual void		OnPickupItem()								{ Post( QB_BOT_PICKUP_ITEM ); };
	virtual void		OnUpdateAttackTarget();
	virtual void		OnUpdateMoveTarget();
	virtual void		OnUpdateAIInfo();
	virtual void		OnUpdateHealth();
	virtual void		OnUpdateAmmo();

	// Added for CPlayerInfo
public:
	virtual void		OnUpdateGunIndex()							{ Post( QB_BOT_UPDATE_GUN_INDEX ); };
	virtual void		OnUpdateOrigin()							{ Post( QB_BOT_UPDATE_ORIGIN ); };
	virtual void		OnUpdateVelocity()							{ Post( QB_BOT_UPDATE_VELOCITY ); };
	virtual void		OnUpdateStat( const BYTE& );
};

//////////////////////////////////////////////////////////////////////
// Inline Functions
//////////////////////////////////////////////////////////////////////

inline void CBot::Post( const UINT& nMsgID )
{
	ASSERT( m_pBotSys != NULL );
	m_pBotSys->PostSystemMessage( nMsgID, NULL, 0 );
}

inline void CBot::OnUpdateStat( const BYTE& nIndex )
{
	switch( nIndex )
	{
	case STAT_HEALTH:
		OnUpdateHealth();
		break;
	case STAT_FRAGS:
		OnUpdateFrags();
		break;
	case STAT_AMMO:
		OnUpdateAmmo();
		break;
	case STAT_PICKUP_STRING:
		OnPickupItem();
		break;
	}
}

inline void CBot::OnUpdateFrags()
{
	m_pBotSys->PostSystemMessage( QB_BOT_UPDATE_FRAGS, NULL, m_piCurrentInfo.GetStat(STAT_FRAGS) );
}

inline void CBot::OnKilled()
{
	SetAttackTarget( NULL );
	SetMoveTarget( NULL );
	m_pBotSys->PostSystemMessage( QB_BOT_KILLED, NULL, m_nDeaths );
}

inline void CBot::OnUpdateAttackTarget()
{
	m_pBotSys->PostSystemMessage( QB_BOT_UPDATE_ATTACK_TARGET, NULL, (UINT)m_pAttackTarget );
}

inline void CBot::OnUpdateMoveTarget()
{
	m_pBotSys->PostSystemMessage( QB_BOT_UPDATE_MOVE_TARGET, NULL, (UINT)m_pMoveTarget );
}

inline void CBot::OnUpdateAIInfo()
{
	m_pBotSys->PostSystemMessage( QB_BOT_UPDATE_AI_INFO, NULL, m_nAIInfo );
}

inline void CBot::OnUpdateHealth()
{
	if ( m_piCurrentInfo.GetStat(STAT_HEALTH) > 0 )
	{
		if ( IsDead() )
		{
			m_bDead = FALSE;
			OnRespawned();
		}
	}
	else
	{
		if (! IsDead() )
		{
			m_bDead = TRUE;
			m_nDeaths++;
			OnKilled();
		}
	}
	m_pBotSys->PostSystemMessage( QB_BOT_UPDATE_HEALTH, NULL, m_piCurrentInfo.GetStat(STAT_HEALTH) );
}

inline void CBot::OnUpdateAmmo()
{
	m_pBotSys->PostSystemMessage( QB_BOT_UPDATE_AMMO, NULL, m_piCurrentInfo.GetStat(STAT_AMMO) );
}

#endif // !defined(AFX_BOT_H__CA903384_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
