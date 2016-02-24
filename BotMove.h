// BotMove.h: interface for the CBotMove class.
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

#if !defined(AFX_BOTMOVE_H__8E577A32_D25A_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_BOTMOVE_H__8E577A32_D25A_11D1_AF1C_0060080A5FD2__INCLUDED_

//////////////////////////////////////////////////////////////////////
// CBotMove Includes
//////////////////////////////////////////////////////////////////////

#include "AdvTime.h"
#include "Vector.h"
#include "MoveData.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CBotMove Definitions
//////////////////////////////////////////////////////////////////////

#define MAX_SPEED		300

//////////////////////////////////////////////////////////////////////
// CBotMove Enumerated Data Types
//////////////////////////////////////////////////////////////////////

enum MoveOption	{ Yes, No, Maybe };

//////////////////////////////////////////////////////////////////////
// CBotMove Class Definition
//////////////////////////////////////////////////////////////////////

class CBotMove
{
// Attributes
private:
	CVector			m_vMove;
	CVector			m_vLook;
	MoveOption		m_moAttack;
	MoveOption		m_moJump;
	MoveOption		m_moCrouch;
	MoveOption		m_moUse;
	BYTE			m_nImpulse;
	CAdvTime		m_tSent;

// Construction / Destruction
public:
	CBotMove()													{ Clear(); };
	virtual ~CBotMove()											{};

// Data Manipulation
public:
	const CVector&		GetMove() const							{ return m_vMove; };
	const CVector&		GetLook() const							{ return m_vLook; };
	const MoveOption&	GetAttack() const						{ return m_moAttack; };
	const MoveOption&	GetJump() const							{ return m_moJump; };
	const MoveOption&	GetCrouch() const						{ return m_moCrouch; };
	const MoveOption&	GetUse() const							{ return m_moUse; };
	const BYTE&			GetImpulse() const						{ return m_nImpulse; };
	const CAdvTime&		GetTimeSent() const						{ return m_tSent; };
	
	void				GetMove( CVector& vNew ) const			{ vNew = m_vMove; };
	void				GetLook( CVector& vNew ) const			{ vNew = m_vLook; };

	void				SetMove( const CVector& vNew )			{ m_vMove		= vNew; };
	void				SetLook( const CVector& vNew )			{ m_vLook		= vNew; };
	void				SetAttack( const MoveOption& moNew )	{ m_moAttack	= moNew; };
	void				SetJump( const MoveOption& moNew )		{ m_moJump		= moNew; };
	void				SetCrouch( const MoveOption& moNew )	{ m_moCrouch	= moNew; };
	void				SetUse( const MoveOption& moNew )		{ m_moUse		= moNew; };

// Operations
public:
	void				MarkTimeSent()							{ m_tSent.SetCurrent(); };
	void				Clear();
	void				PrepareMoveData( CMoveData*, const CVector& ) const;

private:
	void				SetMoveDataSpeeds( CMoveData* ) const;
	void				SetMoveDataUpSpeed( CMoveData* ) const;
	void				SetMoveDataAngles( CMoveData*, const CVector& ) const;
	void				SetMoveDataButtons( CMoveData* ) const;
};

#endif // !defined(AFX_BOTMOVE_H__8E577A32_D25A_11D1_AF1C_0060080A5FD2__INCLUDED_)
