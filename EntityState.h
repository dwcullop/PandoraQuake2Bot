// EntityState.h: interface for the CEntityState class.
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

#if !defined(AFX_ENTITYSTATE_H__7BB23498_BD1E_11D1_8720_444553540000__INCLUDED_)
#define AFX_ENTITYSTATE_H__7BB23498_BD1E_11D1_8720_444553540000__INCLUDED_

//////////////////////////////////////////////////////////////////////
// CEntityState Includes
//////////////////////////////////////////////////////////////////////

#include "PandoraDefs.h"
#include "Vector.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CEntityState Class Definition
//////////////////////////////////////////////////////////////////////

class CEntityState
{
// Attributes
private:
	BYTE			m_nModelIndex;
	BYTE			m_nModelIndex2;
	BYTE			m_nModelIndex3;
	BYTE			m_nModelIndex4;
	WORD			m_nFrame;
	UINT			m_nSkinNum;
	UINT			m_nEffects;
	UINT			m_nRenderFX;
	CVector			m_vAngles;
	CVector			m_vOldOrigin;
	BYTE			m_nSound;
	BYTE			m_nEvent;
	WORD			m_nSolid;
	BOOL			m_bActive;
	CVector			m_vOrigin;

// Construction / Destruction
public:
	CEntityState()											{ Clear(); };
	CEntityState( const CEntityState* pNew )				{ Copy( pNew ); };
	virtual ~CEntityState()									{ };

// Data Manipulation
public:
	// Get Operators
	const BYTE&		GetSound() const						{ return m_nSound; };
	const BYTE&		GetEvent() const						{ return m_nEvent; };
	const BYTE&		GetModelIndex() const					{ return m_nModelIndex; };
	const BYTE&		GetModelIndex2() const					{ return m_nModelIndex2; };
	const BYTE&		GetModelIndex3() const					{ return m_nModelIndex3; };
	const BYTE&		GetModelIndex4() const					{ return m_nModelIndex4; };
	const WORD&		GetFrame() const						{ return m_nFrame; };
	const UINT&		GetSkinNum() const						{ return m_nSkinNum; };
	const UINT&		GetEffects() const						{ return m_nEffects; };
	const UINT&		GetRenderFX() const						{ return m_nRenderFX; };
	const CVector&	GetOrigin() const						{ return m_vOrigin; };
	const CVector&	GetAngles() const						{ return m_vAngles; };
	const CVector&	GetOldOrigin() const					{ return m_vOldOrigin; };
	const WORD		GetSolid() const						{ return m_nSolid; };
	const BOOL&		GetActive() const						{ return m_bActive; };
	// Set Operators
	void			SetSound( const BYTE& nNew )			{ m_nSound = nNew; };
	void			SetEvent( const BYTE& nNew )			{ m_nEvent = nNew; };
	void			SetModelIndex( const BYTE& nNew )		{ m_nModelIndex = nNew; };
	void			SetModelIndex2( const BYTE& nNew )		{ m_nModelIndex2 = nNew; };
	void			SetModelIndex3( const BYTE& nNew )		{ m_nModelIndex3 = nNew; };
	void			SetModelIndex4( const BYTE& nNew )		{ m_nModelIndex4 = nNew; };
	void			SetFrame( const WORD& nNew )			{ m_nFrame = nNew; };
	void			SetSkinNum( const UINT& nNew )			{ m_nSkinNum = nNew; };
	void			SetEffects( const UINT& nNew )			{ m_nEffects = nNew; };
	void			SetRenderFX( const UINT& nNew )			{ m_nRenderFX = nNew; };
	void			SetOrigin( const CVector& vNew )		{ m_vOrigin = vNew; };
	void			SetAngles( const CVector& vNew )		{ m_vAngles = vNew; };
	void			SetOldOrigin( const CVector& vNew )		{ m_vOldOrigin = vNew; };
	void			SetSolid( const WORD& nNew )			{ m_nSolid = nNew; };
	void			SetActive( const BOOL& bNew )			{ m_bActive = bNew; };
	// Updatable Get Operators
	BYTE&			GetSetSound()							{ return m_nSound; };
	BYTE&			GetSetEvent()							{ return m_nEvent; };
	BYTE&			GetSetModelIndex()						{ return m_nModelIndex; };
	BYTE&			GetSetModelIndex2()						{ return m_nModelIndex2; };
	BYTE&			GetSetModelIndex3()						{ return m_nModelIndex3; };
	BYTE&			GetSetModelIndex4()						{ return m_nModelIndex4; };
	WORD&			GetSetFrame()							{ return m_nFrame; };
	UINT&			GetSetSkinNum()							{ return m_nSkinNum; };
	UINT&			GetSetEffects()							{ return m_nEffects; };
	UINT&			GetSetRenderFX()						{ return m_nRenderFX; };
	CVector&		GetSetOrigin()							{ return m_vOrigin; };
	CVector&		GetSetAngles()							{ return m_vAngles; };
	CVector&		GetSetOldOrigin()						{ return m_vOldOrigin; };
	WORD&			GetSetSolid()							{ return m_nSolid; };

// Operations
public:
	void		Clear();
	void		Copy( const CEntityState* );
};

#endif // !defined(AFX_ENTITYSTATE_H__7BB23498_BD1E_11D1_8720_444553540000__INCLUDED_)
