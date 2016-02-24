// Entity.h: interface for the CEntity class.
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

#if !defined(AFX_ENTITY_H__CA903382_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_ENTITY_H__CA903382_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_

#include "EntityState.h"
#include "BotMsgs.h"
#include "BotSystem.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGameState;

#define BASELINE_REFERENCE_FRAME	0xFFFFFFFF
#define MAX_FRAMES					16

//class CEntity : public CEntityState, public CObject
class CEntity : public CObject
{
	DECLARE_DYNCREATE(CEntity)

// Attributes
private:
	CEntityState*		m_pBaseline;
	CEntityState*		m_pPastFrames[MAX_FRAMES];
	BYTE				m_nMuzzleFlash;
	BYTE				m_nMuzzleFlash2;
	WORD				m_nEntityNumber;
	BOOL				m_bActive;

protected:
	CEntityState*		m_pCurrentFrame;
	UINT				m_nFrameNumber;

// Static
protected:
	static CGameState*	m_pGame;
	static CBotSystem*	m_pBotSys;

// Construction / Destruction
public:
	CEntity()												{ Clear(); };
	virtual ~CEntity()										{ Reset(); };

// Data Manipulation
public:
	void			SetEntityNumber( const WORD& nNew )		{ m_nEntityNumber = nNew; };
	void			SetMuzzleFlash( const BYTE& nNew )		{ m_nMuzzleFlash = nNew; OnMuzzleFlash(); };
	void			SetMuzzleFlash2( const BYTE& nNew )		{ m_nMuzzleFlash2 = nNew; OnMuzzleFlash2(); };

	const WORD&		GetEntityNumber() const					{ return m_nEntityNumber; };
	const BYTE&		GetMuzzleFlash() const					{ return m_nMuzzleFlash; };
	const BYTE&		GetMuzzleFlash2() const					{ return m_nMuzzleFlash2; };
	CEntityState*	GetCurrent()							{ return m_pCurrentFrame; };
	const CVector&	GetOrigin() const						{ ASSERT( m_pCurrentFrame != NULL ); return m_pCurrentFrame->GetOrigin(); };
	CEntityState*	GetBaseline();

private:
	void			SetActiveState( const BOOL& );
	
// Static Data Manipulation
public:
	static void		SetGameState( CGameState* pNew )		{ m_pGame = pNew; };
	static void		SetBotSys( CBotSystem* pNew )			{ m_pBotSys = pNew; };

// Operations
public:
	const BOOL&		IsVisible() const						{ return m_bActive; };
	void			AfterUpdate();
	void			BeforeUpdate( const UINT&, const UINT& );
	void			GetVelocity( CVector& ) const;
	CVector			GetVelocity() const;

private:
	void			CopyEntityState( CEntityState**, CEntityState** );

// Overridables
public:
	virtual void	Clear();
	virtual void	GetModelName( CString& ) const;
	virtual void	NewFrame( const UINT&, const UINT& );
	virtual void	Reset();

private:
	virtual void	OnActive()								{ Post( QB_ENTITY_UPDATE_ACTIVE ); };
	virtual void	OnRemove()								{ Post( QB_ENTITY_UPDATE_REMOVE ); };
	virtual void	OnMuzzleFlash()							{ Post( QB_ENTITY_MUZZLEFLASH ); };
	virtual void	OnMuzzleFlash2()						{ Post( QB_ENTITY_MUZZLEFLASH2 ); };
	virtual void	Post( const UINT& );
};

// Inline Functions

inline void CEntity::Post( const UINT& nMsgID )
{
	ASSERT( m_pBotSys != NULL );
	m_pBotSys->PostSystemMessage( nMsgID, NULL, m_nEntityNumber );
}

inline void CEntity::SetActiveState( const BOOL& bState )
{
	if ( bState != m_bActive )
	{
		if ( m_bActive = bState )
		{
			OnActive();
		}
		else
		{
			OnRemove();
		}
	}
}

#endif // !defined(AFX_ENTITY_H__CA903382_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
