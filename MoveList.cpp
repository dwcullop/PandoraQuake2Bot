// MoveList.cpp: implementation of the CMoveList class.
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

#include "stdafx.h"
#include "Pandora.h"
#include "MoveList.h"
#include "PandoraDefs.h"
#include "SentMove.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoveList::CMoveList()
{
	Clear();
}

CMoveList::~CMoveList()
{
	Reset();
}

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

CMoveData* CMoveList::GetMoveFrame( const BYTE nFrame )
{
	ASSERT( nFrame < MOVE_FRAMES );
	ASSERT( m_pMoves[nFrame] != NULL );
	return m_pMoves[nFrame];
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CMoveList::ComputeDeltaOrigin( const float& nPing )
{
	POSITION	pPos, pPos2;
	CSentMove*	pCurrent;
	CVector		vTemp;

	m_vDeltaOrigin.Clear();
	pPos = m_lstSentMoves.GetHeadPosition();
	while ( (pPos2=pPos) != NULL )
	{
		pCurrent = ( (CSentMove*) m_lstSentMoves.GetNext(pPos) );
		if ( (double)pCurrent->GetSentTime().Elapsed() > nPing )
		{
			delete pCurrent;
			m_lstSentMoves.RemoveAt( pPos2 );
		}
		else
		{
			pCurrent->Delta( vTemp );
			m_vDeltaOrigin += vTemp;
		}
	}
}

void CMoveList::NewMove( const CBotMove& rMove, const CVector& vDelta )
{
	CMoveData*	pNewMoveData;
	double		nRenderTime;
	CVector		vTemp;

	// Deal with the rendering time
	nRenderTime = m_tLastSent.Elapsed();
	m_tLastSent.SetCurrent();
	m_nTotalTime += (float)nRenderTime;
	m_nTotalMoves++;
	// Prepare the new CMoveData object
	pNewMoveData = new CMoveData;
	rMove.PrepareMoveData( pNewMoveData, vDelta );
	pNewMoveData->SetMilliseconds( (BYTE)(nRenderTime * 1000) );
	AddFrame( pNewMoveData );
	// If this CBotMove moves the bot, record with a CSentMove
	if ( rMove.GetMove().Length() )
	{
		CSentMove*	pNewSentMove = new CSentMove( rMove );
		pNewSentMove->SetDuration( nRenderTime );
		pNewSentMove->Delta( vTemp );
		m_vDeltaOrigin += vTemp;
		m_lstSentMoves.AddTail( pNewSentMove );
	}
}

void CMoveList::BeginLevel()
{
	Lock();
	Reset();
	for ( register nCount = 0 ; nCount < MOVE_FRAMES ; nCount++ )
	{
		m_pMoves[nCount] = new CMoveData;
	}
	Unlock();
}

void CMoveList::Reset()
{
	register nCount;

	for ( nCount = 0 ; nCount < MOVE_FRAMES ; nCount++ )
	{
		if ( m_pMoves[nCount] != NULL )
		{
			delete m_pMoves[nCount];
		}
	}
	Clear();
}

void CMoveList::Clear()
{
	register nCount;

	for ( nCount = 0 ; nCount < MOVE_FRAMES ; nCount++ )
	{
		m_pMoves[nCount] = NULL;
	}
	while ( !m_lstSentMoves.IsEmpty() )
	{
		delete m_lstSentMoves.RemoveHead();
	}
	m_nTotalTime = 0.0f;
	m_nTotalMoves = 0;
	m_tLastSent.SetCurrent();
}

//////////////////////////////////////////////////////////////////////
// Private Operations
//////////////////////////////////////////////////////////////////////

void CMoveList::AddFrame( CMoveData* pNew )
{
	register nCount;

	Lock();
	ASSERT( m_pMoves[MOVE_FRAMES - 1] != NULL );	// This should never happen
	delete m_pMoves[MOVE_FRAMES - 1];
	for ( nCount = MOVE_FRAMES - 1 ; nCount > 0; nCount-- )
	{
		m_pMoves[nCount] = m_pMoves[nCount-1];
	}
	pNew->CreateBitMask();
	m_pMoves[0] = pNew;
	for ( nCount = 1 ; nCount < MOVE_FRAMES ; nCount++ )
	{
		m_pMoves[nCount]->CreateBitMask( m_pMoves[nCount-1] );
	}
	Unlock();
}

//////////////////////////////////////////////////////////////////////
// End of MoveList.cpp
//////////////////////////////////////////////////////////////////////