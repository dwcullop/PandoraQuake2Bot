// BotAI.h: interface for the CBotAI class.
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

#if !defined(AFX_BOTAI_H__9C2A0646_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
#define AFX_BOTAI_H__9C2A0646_F18B_11D1_AF24_0060080A5FD2__INCLUDED_

#include "AIData.h"
#include "GameState.h"
#include "QuakeClient.h"
#include "MapPoint.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBotAI  
{
// Attributes
protected:
	UINT			m_nMoveCount;
	CObList			m_lstAmmo;
	CObList			m_lstArmor;
	CObList			m_lstDangerous;
	CObList			m_lstHealing;
	CObList			m_lstItems;
	CObList			m_lstPlayers;
	CObList			m_lstWeapons;
	CGameState*		m_pGame;
	CQuakeClient*	m_pClient;
	CAIData			m_aiGameData;
	CBot*			m_pBot;
	CMapPoint		m_mpTemp;
	CMapPoint		m_mpTemp2;
	BOOL			m_bMoveOkay;
	BYTE			m_nStuckCount;
	CBotMove		m_bmCurrent;
	CVector			m_vBotOrigin;
	CPlayer*		m_pAttackTarget;
	CMapPoint*		m_pMoveTarget;

// Construction / Destruction
public:
	CBotAI();
	virtual ~CBotAI();

// Data Manipulation
public:
	void			SetGameState( CGameState* pNew )				{ m_pGame = pNew; };
	void			SetClient( CQuakeClient* pNew )					{ m_pClient = pNew; };

// General Operations
protected:
	void			ResetAI();

// List Operations
protected:
	CPlayer*		FindBestPlayer( CEntity* (CBotAI::*)(CEntity*, CEntity*) );
	CEntity*		FindBestItem( CObList&, CEntity* (CBotAI::*)(CEntity*, CEntity*) );
	void			AddEntity( CEntity* );
	void			RemoveEntity( CEntity* );
	void			AddPlayer( CPlayer* );
	void			RemovePlayer( CPlayer* );

private:
	void			AddListItem( CObList&, CEntity* );
	void			RemoveListItem( CObList&, CEntity* );

// Move Operations
protected:
	const BOOL		PrepareMove();
	void			SendMove();
	BOOL			AttackPlayer( CPlayer* );
	void			MoveRandomly( const WORD& );
	void			MoveToEntity( const CEntity* );
	void			MoveToMapPoint();
	BOOL			IsBotStuck();

// Item Operations
protected:
	void			UseItem( const CString& );
	void			UseItem( const BYTE& );
	void			DropItem( const CString& );
	void			DropItem( const BYTE& );

// Weapon Selection Operations
protected:
	BOOL			IsWeaponAvailable( const CWeaponSpec* );
	CWeaponSpec*	SelectBestWeapon();

// Targeting Operations
protected:
	BOOL			IsShotClear( const CVector&, const CVector&, const CWeaponSpec* );
	BOOL			IsViableTarget( const CPlayer* );
	void			PredictImpactOrigin( const CVector&, CVector&, const CVector&, const CWeaponSpec* );

// Map Operations
protected:
	BOOL			IsPathClear( const CVector&, const CVector& );

// Sorting Functions
protected:
	CPlayer*		SortPlayer( CPlayer*, CPlayer*, CEntity* (CBotAI::*)(CEntity*, CEntity*) );
	CEntity*		Closest( CEntity*, CEntity* );
};

#endif // !defined(AFX_BOTAI_H__9C2A0646_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
