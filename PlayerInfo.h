// PlayerInfo.h: interface for the CPlayerInfo class.
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

#if !defined(AFX_PLAYERINFO_H__CA903386_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_PLAYERINFO_H__CA903386_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_

//////////////////////////////////////////////////////////////////////
// CPlayerInfo Includes
//////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include "PandoraDefs.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CPlayerInfo Defines
//////////////////////////////////////////////////////////////////////

#define MAX_BLENDS		4

//////////////////////////////////////////////////////////////////////
// Used Class List
//////////////////////////////////////////////////////////////////////

class CBot;

//////////////////////////////////////////////////////////////////////
// CPlayerInfo Class Definition
//////////////////////////////////////////////////////////////////////

class CPlayerInfo
{
// Attributes
private:
	BYTE				m_nMoveType;
	CVector				m_vOrigin;
	CVector				m_vVelocity;
	BYTE				m_nMoveTime;
	BYTE				m_nMoveFlags;
	WORD				m_nGravity;
	CVector				m_vDeltaAngles;
	CVector				m_vViewOffset;
	CVector				m_vViewAngles;
	CVector				m_vKickAngles;
	BYTE				m_nGunIndex;
	BYTE				m_nGunFrame;
	CVector				m_vGunOffset;
	CVector				m_vGunAngles;
	float				m_nBlend[MAX_BLENDS];
	BYTE				m_nFOV;
	BYTE				m_nRenderFlags;
	short				m_nStats[MAX_STATS];

// Static Attributes
private:
	static CBot*		m_pBot;

// Construction / Destruction
public:
	CPlayerInfo();
	CPlayerInfo( const CPlayerInfo& rCopy )					{ Copy( rCopy ); };
	CPlayerInfo( const CPlayerInfo* pCopy )					{ Copy( pCopy ); };
	virtual ~CPlayerInfo();

// Data Manipulation
public:
	// Read only references
	const BYTE&		GetMoveType() const 					{ return m_nMoveType; };
	const CVector&	GetOrigin() const 						{ return m_vOrigin; };
	const CVector&	GetVelocity() const						{ return m_vVelocity; };
	const BYTE&		GetMoveTime() const						{ return m_nMoveTime; };
	const BYTE&		GetMoveFlags() const					{ return m_nMoveFlags; };
	const WORD&		GetGravity() const						{ return m_nGravity; };
	const CVector&	GetDeltaAngles() const					{ return m_vDeltaAngles; };
	const CVector&	GetViewOffset() const					{ return m_vViewOffset; };
	const CVector&	GetViewAngles() const					{ return m_vViewAngles; };
	const CVector&	GetKickAngles() const					{ return m_vKickAngles; };
	const BYTE&		GetGunIndex() const						{ return m_nGunIndex; };
	const BYTE&		GetGunFrame() const						{ return m_nGunFrame; };
	const CVector&	GetGunOffset() const					{ return m_vGunOffset; };
	const CVector&	GetGunAngles() const					{ return m_vGunAngles; };
	const BYTE&		GetRenderFlags() const					{ return m_nRenderFlags; };
	const BYTE&		GetFOV() const							{ return m_nFOV; };
	const float*	GetBlendPtr() const						{ return m_nBlend; };
	const short*	GetStatPtr() const						{ return m_nStats; };
	const float&	GetBlend( const BYTE ) const;
	const short&	GetStat( const BYTE ) const;
	// Changable References
	BYTE&			GetSetMoveType()						{ return m_nMoveType; };
	BYTE&			GetSetMoveTime()						{ return m_nMoveTime; };
	BYTE&			GetSetMoveFlags()						{ return m_nMoveFlags; };
	WORD&			GetSetGravity()							{ return m_nGravity; };
	CVector&		GetSetDeltaAngles()						{ return m_vDeltaAngles; };
	CVector&		GetSetViewOffset()						{ return m_vViewOffset; };
	CVector&		GetSetViewAngles()						{ return m_vViewAngles; };
	CVector&		GetSetKickAngles()						{ return m_vKickAngles; };
	BYTE&			GetSetGunFrame()						{ return m_nGunFrame; };
	CVector&		GetSetGunOffset()						{ return m_vGunOffset; };
	CVector&		GetSetGunAngles()						{ return m_vGunAngles; };
	BYTE&			GetSetRenderFlags()						{ return m_nRenderFlags; };
	BYTE&			GetSetFOV()								{ return m_nFOV; };
	float&			GetSetBlend( const BYTE );
	// Set Operations
	void			SetGunIndex( const BYTE& );
	void			SetOrigin( const CVector& );
	void			SetStat( const BYTE&, const short& );
	void			SetVelocity( const CVector& );

// Static Data Manipulation
public:
	static void		SetBot( CBot* pBot )					{ m_pBot = pBot; };

// Operations
public:
	void Clear();
	void Copy( const CPlayerInfo& );
	void Copy( const CPlayerInfo* );

};

#endif // !defined(AFX_PLAYERINFO_H__CA903386_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
