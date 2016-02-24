// WeaponSpec.h: interface for the CWeaponSpec class.
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

#if !defined(AFX_WEAPONSPEC_H__E1210262_DE14_11D1_AF21_0060080A5FD2__INCLUDED_)
#define AFX_WEAPONSPEC_H__E1210262_DE14_11D1_AF21_0060080A5FD2__INCLUDED_

#include "DangerSpec.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWeaponSpec : public CObject
{
// Attributes
private:
	BYTE				m_nViewType;
	BYTE				m_nInventoryIndex;
	BYTE				m_nAmmoType;
	BYTE				m_nAmmoInventoryIndex;
	const CDangerSpec*	m_pDanger;
	WORD				m_nMinRange;
	WORD				m_nIdealRange;
	WORD				m_nMaxRange;
	BYTE				m_nAmmoPerShot;
	BYTE				m_nFramesPerShot;
	BYTE				m_nMuzzleFlash;

// Construction / Destruction
public:
	CWeaponSpec();
	virtual ~CWeaponSpec();

// Data Manipulation
public:
	const BYTE&			GetViewType() const							{ return m_nViewType; };
	const BYTE&			GetInventoryIndex() const					{ return m_nInventoryIndex; };
	const BYTE&			GetAmmoType() const							{ return m_nAmmoType; };
	const BYTE&			GetAmmoInventoryIndex() const				{ return m_nAmmoInventoryIndex; };
	const CDangerSpec*	GetDangerSpec() const						{ return m_pDanger; };
	const WORD&			GetMinRange() const							{ return m_nMinRange; };
	const WORD&			GetIdealRange() const						{ return m_nIdealRange; };
	const WORD&			GetMaxRange() const							{ return m_nMaxRange; };
	const BYTE&			GetAmmoPerShot() const						{ return m_nAmmoPerShot; };
	const BYTE&			GetFramesPerShot() const					{ return m_nFramesPerShot; };
	const BYTE&			GetMuzzleFlash() const						{ return m_nMuzzleFlash; };

	void				SetViewType( const BYTE& nNew )				{ m_nViewType = nNew; };
	void				SetInventoryIndex( const BYTE& nNew )		{ m_nInventoryIndex = nNew; };
	void				SetAmmoType( const BYTE& nNew )				{ m_nAmmoType = nNew; };
	void				SetAmmoInventoryIndex( const BYTE& nNew )	{ m_nAmmoInventoryIndex = nNew; };
	void				SetDangerSpec( const CDangerSpec* pNew )	{ m_pDanger = pNew; };
	void				SetMinRange( const WORD& nNew )				{ m_nMinRange = nNew; };
	void				SetIdealRange( const WORD& nNew )			{ m_nIdealRange = nNew; };
	void				SetMaxRange( const WORD& nNew )				{ m_nMaxRange = nNew; };
	void				SetAmmoPerShot( const BYTE& nNew )			{ m_nAmmoPerShot = nNew; };
	void				SetFramesPerShot( const BYTE& nNew )		{ m_nFramesPerShot = nNew; };
	void				SetMuzzleFlash( const BYTE& nNew )			{ m_nMuzzleFlash = nNew; };

// Operations
public:
	BOOL				CheckRange( const float& ) const;
	void				Clear();
};

#endif // !defined(AFX_WEAPONSPEC_H__E1210262_DE14_11D1_AF21_0060080A5FD2__INCLUDED_)
