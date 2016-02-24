// Player.h: interface for the CPlayer class.
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

#if !defined(AFX_PLAYER_H__CA903383_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_PLAYER_H__CA903383_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_

//////////////////////////////////////////////////////////////////////
// CPlayer Includes
//////////////////////////////////////////////////////////////////////

#include "Entity.h"
#include "WeaponSpec.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CPlayer Defines
//////////////////////////////////////////////////////////////////////

#define PLAYER_MODEL_WIDTH				(20.0f)
#define PLAYER_MODEL_DEPTH				(20.0f)
#define PLAYER_MODEL_HEIGHT				(32.0f)
#define PLAYER_MODEL_CROUCH_HEIGHT		(16.0f)
#define PLAYER_CROUCH_HEIGHT_OFFSET		(PLAYER_MODEL_HEIGHT-PLAYER_MODEL_CROUCH_HEIGHT)

//////////////////////////////////////////////////////////////////////
// CPlayer Class Definition
//////////////////////////////////////////////////////////////////////

class CPlayer : public CEntity  
{
	DECLARE_DYNCREATE(CPlayer)
// Attributes
private:
	CString				m_strName;
	CString				m_strSkin;
	short				m_nPing;
	BYTE				m_nPlayerNumber;

protected:
	const CWeaponSpec*	m_pWeapon;
	UINT				m_nNextFireFrame;
	short				m_nFrags;
	BOOL				m_bDead;

// Construction / Destruction
public:
	CPlayer()														{ Clear(); };
	virtual ~CPlayer()												{ Reset(); };

// Data Manipulation
public:
	const short			GetFrags() const							{ return m_nFrags; };
	const CString&		GetName() const								{ return m_strName; };
	const short			GetPing() const								{ return m_nPing; };
	const BYTE&			GetPlayerNumber() const						{ return m_nPlayerNumber; };
	const CString&		GetSkin() const								{ return m_strSkin; };
	const CWeaponSpec*	GetWeapon()	const							{ return m_pWeapon; };

	void				SetFrags( const short& nNew )				{ m_nFrags = nNew; };
	void				SetName( const CString& strNew )			{ m_strName = strNew; };
	void				SetNextFireFrame( const UINT& nNew )		{ m_nNextFireFrame = nNew; };
	void				SetPing( const short& nNew )				{ m_nPing = nNew; };
	void				SetPlayerNumber( const BYTE& nNew )			{ m_nPlayerNumber = nNew; };
	void				SetSkin( const CString& strNew )			{ m_strSkin = strNew; };
	void				SetWeapon( const CWeaponSpec* pNew )		{ if ( pNew != m_pWeapon ) { m_pWeapon = pNew; OnUpdateWeapon(); } };

// Overrides
public:
	virtual void		GetModelName( CString& strName ) const		{ strName = GetName(); };
	virtual void		Reset()										{ CEntity::Reset(); };
	virtual void		BeforeUpdate( const UINT&, const UINT& );
	virtual void		AfterUpdate();
	virtual void		Clear();
	virtual void		NewFrame( const UINT&, const UINT& );

private:
	virtual void		Post( const UINT& );

// Operations
public:
	// Can Fire
	BOOL				CanFire( const UINT& nFrame ) const			{ return ( nFrame > m_nNextFireFrame); };
	// Test for death
	const BOOL&			IsDead() const								{ return m_bDead; };
	// Basic Animation States
	BOOL				IsStanding() const;
	BOOL				IsRunning() const;
	BOOL				IsAttacking() const;
	BOOL				IsInPain() const;
	BOOL				IsCrouching() const;
	BOOL				IsJumping() const;
	BOOL				IsDeathFrame() const;
	// Gesture Animation States
	BOOL				IsPointing() const;
	BOOL				IsWaving() const;
	BOOL				IsFlippingOff() const;
	BOOL				IsTaunting() const;
	BOOL				IsSaluting() const;
	// Generalized "Gesture"
	BOOL				IsGesturing() const;

// Overridable Update Events
private:
	virtual void		OnActive()									{ Post( QB_PLAYER_UPDATE_ACTIVE ); };
	virtual void		OnRemove()									{ Post( QB_PLAYER_UPDATE_REMOVE ); };
	virtual void		OnMuzzleFlash()								{ Post( QB_PLAYER_MUZZLEFLASH ); };
	virtual void		OnMuzzleFlash2()							{ Post( QB_PLAYER_MUZZLEFLASH2 ); };
	// Added for CPlayer
	virtual void		OnKilled()									{ Post( QB_PLAYER_KILLED ); m_pWeapon = NULL; m_nNextFireFrame = 0; };
	virtual void		OnRespawned()								{ Post( QB_PLAYER_RESPAWNED ); };
	virtual void		OnUpdateSkin()								{ Post( QB_PLAYER_UPDATE_SKIN ); };
	virtual void		OnUpdateName()								{ Post( QB_PLAYER_UPDATE_NAME ); };
	virtual void		OnUpdateFrags()								{ Post( QB_PLAYER_UPDATE_FRAGS ); };
	virtual void		OnUpdateWeapon()							{ Post( QB_PLAYER_UPDATE_WEAPON ); };

};

//////////////////////////////////////////////////////////////////////
// Inline Functions
//////////////////////////////////////////////////////////////////////

inline void CPlayer::BeforeUpdate( const UINT& nCurrent, const UINT& nRef )
{
	CEntity::BeforeUpdate( nCurrent, nRef );
}

inline void CPlayer::NewFrame( const UINT& nCurrent, const UINT& nRef )
{
	CEntity::NewFrame( nCurrent, nRef );
}

inline void CPlayer::Post( const UINT& nMsgID )
{
	ASSERT( m_pBotSys != NULL );
	m_pBotSys->PostSystemMessage( nMsgID, NULL, m_nPlayerNumber );
}


#endif // !defined(AFX_PLAYER_H__CA903383_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
