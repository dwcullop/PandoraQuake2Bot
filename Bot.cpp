// Bot.cpp: implementation of the CBot class.
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
#include "Bot.h"
#include "WeaponSpec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE( CBot, CPlayer )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	// Defined inline

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

void CBot::SetItemCount( const BYTE nIndex, const WORD nAmount )
{
	ASSERT( nIndex < MAX_ITEMS );
	m_nItems[nIndex] = nAmount;
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CBot::AfterUpdate()
{
	CPlayer::AfterUpdate();
}

void CBot::BeforeUpdate( const UINT& nCurrent, const UINT& nRef )
{
	CPlayer::BeforeUpdate( nCurrent, nRef );
}

void CBot::Clear()
{
	ZeroMemory( m_pPastInfos, (MAX_FRAMES * sizeof(CPlayerInfo*)) );
	ZeroMemory( m_nItems, (MAX_ITEMS*sizeof(WORD)) );
	m_piCurrentInfo.Clear();
	m_nDeaths = 0;
	m_pAttackTarget = NULL;
	m_pMoveTarget = NULL;
	m_pWeapon = NULL;
	CPlayer::Clear();
}

void CBot::Reset()
{
	register int nCount;

	for (nCount = 0; nCount < MAX_FRAMES; nCount++)
	{
		if ( m_pPastInfos[nCount] != NULL )
		{
			delete m_pPastInfos[nCount];
		}
	}
	CPlayer::Reset();
}

void CBot::NewFrame( const UINT& nCurrent, const UINT& nRef )
{
	if ( m_pPastInfos[m_nFrameNumber % MAX_FRAMES] == NULL )
	{
		m_pPastInfos[m_nFrameNumber % MAX_FRAMES] = new CPlayerInfo( &m_piCurrentInfo );
	}
	else
	{
		(m_pPastInfos[m_nFrameNumber % MAX_FRAMES])->Copy( &m_piCurrentInfo );
	}
	if ( nRef == BASELINE_REFERENCE_FRAME )
	{
		m_piCurrentInfo.Clear();
	}
	else
	{
		if ( nRef != m_nFrameNumber )
		{
			if ( m_pPastInfos[nRef % MAX_FRAMES] == NULL )
			{
				m_piCurrentInfo.Clear();
			}
			else
			{
				m_piCurrentInfo.Copy( m_pPastInfos[nRef % MAX_FRAMES] );
			}
		}
	}
	m_piCurrentInfo.SetStat( STAT_FLASHES, 0 );
	CPlayer::NewFrame( nCurrent, nRef );
}

//////////////////////////////////////////////////////////////////////
// End of Bot.cpp
//////////////////////////////////////////////////////////////////////