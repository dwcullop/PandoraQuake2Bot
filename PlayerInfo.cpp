// PlayerInfo.cpp: implementation of the CPlayerInfo class.
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
#include "PlayerInfo.h"
#include "Bot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Static Variables
//////////////////////////////////////////////////////////////////////

CBot* CPlayerInfo::m_pBot = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayerInfo::CPlayerInfo()
{
	Clear();
}

CPlayerInfo::~CPlayerInfo()
{

}

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

const float& CPlayerInfo::GetBlend( const BYTE nIndex ) const
{
	ASSERT( nIndex < MAX_BLENDS );
	return ( m_nBlend[nIndex] );
}

const short& CPlayerInfo::GetStat( const BYTE nIndex ) const
{
	ASSERT( nIndex < MAX_STATS );
	return ( m_nStats[nIndex] );
}

float& CPlayerInfo::GetSetBlend( const BYTE nIndex )
{
	ASSERT( nIndex < MAX_BLENDS );
	return ( m_nBlend[nIndex] );
}

void CPlayerInfo::SetGunIndex( const BYTE& nNew )
{
	if ( nNew != m_nGunIndex )
	{
		m_nGunIndex = nNew;
		m_pBot->OnUpdateGunIndex();
	}
}

void CPlayerInfo::SetStat( const BYTE& nIndex, const short& nValue )
{
	ASSERT( nIndex < MAX_STATS );
	if ( m_nStats[nIndex] != nValue )
	{
		m_nStats[nIndex] = nValue;
		m_pBot->OnUpdateStat( nIndex );
	}
}

void CPlayerInfo::SetVelocity( const CVector& vNew )
{
	if ( vNew != m_vVelocity )
	{
		m_vVelocity = vNew;
		m_pBot->OnUpdateVelocity();
	}
}

void CPlayerInfo::SetOrigin( const CVector& vNew )
{
	if ( vNew != m_vOrigin )
	{
		m_vOrigin = vNew;
		m_pBot->OnUpdateOrigin();
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CPlayerInfo::Clear()
{
	m_nFOV			= 0;
	m_nGravity		= 0;
	m_nGunFrame		= 0;
	m_nGunIndex		= 0;
	m_nMoveFlags	= 0;
	m_nMoveTime		= 0;
	m_nRenderFlags	= 0;
	m_vDeltaAngles.Clear();
	m_vGunAngles.Clear();
	m_vGunOffset.Clear();
	m_vKickAngles.Clear();
	m_vOrigin.Clear();
	m_vViewAngles.Clear();
	m_vViewOffset.Clear();
	ZeroMemory( m_nBlend, MAX_BLENDS*sizeof(float) );
	ZeroMemory( m_nStats, MAX_STATS*sizeof(short) );
}

void CPlayerInfo::Copy( const CPlayerInfo* pCopy )
{
/*
	m_nFOV			= pCopy->GetFOV();
	m_nGravity		= pCopy->GetGravity();
	m_nGunFrame		= pCopy->GetGunFrame();
	m_nGunIndex		= pCopy->GetGunIndex();
	m_nMoveFlags	= pCopy->GetMoveFlags();
	m_nMoveTime		= pCopy->GetMoveTime();
	m_nRenderFlags	= pCopy->GetRenderFlags();
	m_vDeltaAngles	= pCopy->GetDeltaAngles();
	m_vGunAngles	= pCopy->GetGunAngles();
	m_vGunOffset	= pCopy->GetGunOffset();
	m_vKickAngles	= pCopy->GetKickAngles();
	m_vOrigin		= pCopy->GetOrigin();
	m_vViewAngles	= pCopy->GetViewAngles();
	m_vViewOffset	= pCopy->GetViewOffset();
	CopyMemory( m_nBlend, pCopy->GetBlendPtr(), MAX_BLENDS*sizeof(float) );
	CopyMemory( m_nStats, pCopy->GetStatPtr(), MAX_STATS*sizeof(short) );
*/
	CopyMemory( this, pCopy, sizeof(CPlayerInfo) );
}

void CPlayerInfo::Copy( const CPlayerInfo& rCopy )
{
	Copy( &rCopy );
}

//////////////////////////////////////////////////////////////////////
// End of PlayerInfo.cpp
//////////////////////////////////////////////////////////////////////