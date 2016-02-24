// Entity.cpp: implementation of the CEntity class.
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
#include "Entity.h"
#include "GameState.h"
#include "BotSystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE( CEntity, CObject )

//////////////////////////////////////////////////////////////////////
// Static Variables
//////////////////////////////////////////////////////////////////////

CGameState* CEntity::m_pGame = NULL;
CBotSystem* CEntity::m_pBotSys = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	// Defined Inline

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

CEntityState* CEntity::GetBaseline()
{
	if (m_pBaseline == NULL)
	{
		m_pBaseline = new CEntityState;
	}
	return m_pBaseline;
}

//////////////////////////////////////////////////////////////////////
// Public Operations
//////////////////////////////////////////////////////////////////////

void CEntity::AfterUpdate()
{
	ASSERT( m_pCurrentFrame != NULL );
	SetActiveState( m_pCurrentFrame->GetActive() );
	if ( m_bActive == FALSE )
	{
		delete m_pCurrentFrame;
		m_pCurrentFrame = NULL;
	}
}

void CEntity::BeforeUpdate( const UINT& nCurrent, const UINT& nRef )
{
	// If the previous frame isn't the reference, we have to create a copy
	// of the one that is.
	if ( nRef != m_nFrameNumber )
	{
		ASSERT( m_pCurrentFrame == NULL );
		if ( nRef == BASELINE_REFERENCE_FRAME )
		{
			m_pCurrentFrame = new CEntityState( m_pBaseline );
		}
		else
		{
			if ( m_pPastFrames[nRef % MAX_FRAMES] == NULL )
			{
				m_pCurrentFrame = new CEntityState( m_pBaseline );
			}
			else
			{
				CopyEntityState( &(m_pPastFrames[nRef % MAX_FRAMES]), &m_pCurrentFrame );
			}
		}
	}
	else
	{
		if ( m_pCurrentFrame == NULL )
		{
			m_pCurrentFrame = new CEntityState;
		}
	}
	m_nFrameNumber = nCurrent;
}

void CEntity::GetVelocity( CVector& vVel ) const
{
	ASSERT( m_pCurrentFrame != NULL );
	vVel = m_pCurrentFrame->GetOrigin() - m_pCurrentFrame->GetOldOrigin();
}

CVector CEntity::GetVelocity() const
{
	CVector vReturn;

	GetVelocity( vReturn );
	return vReturn;
}

//////////////////////////////////////////////////////////////////////
// Private Operations
//////////////////////////////////////////////////////////////////////

void CEntity::CopyEntityState( CEntityState** pSource, CEntityState** pTarget )
{
	ASSERT( pSource != NULL );
	ASSERT( pTarget != NULL );
	if ( *pSource == NULL )
	{
		if ( *pTarget != NULL )
		{
			delete *pTarget;
			*pTarget = NULL;
		}
	}
	else
	{
		if ( *pTarget != NULL )
		{
			(*pTarget)->Copy( *pSource );
		}
		else
		{
			(*pTarget) = new CEntityState( *pSource );
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Overridables
//////////////////////////////////////////////////////////////////////

void CEntity::Clear()
{
	ZeroMemory( m_pPastFrames, MAX_FRAMES*sizeof(CEntityState*) );
	m_pCurrentFrame = NULL;
	m_pBaseline = NULL;
	m_bActive = FALSE;
	m_nMuzzleFlash	= 0;
	m_nMuzzleFlash2	= 0;
	m_nFrameNumber = 0;
	m_nEntityNumber = 0;
}

void CEntity::GetModelName( CString& strNew ) const
{
	ASSERT( m_pGame != NULL );
	ASSERT( m_pCurrentFrame != NULL );
	strNew = m_pGame->GetModelName( m_pCurrentFrame->GetModelIndex() );
}

void CEntity::NewFrame( const UINT& nCurrent, const UINT& nRef )
{
	if ( m_nFrameNumber )
	{
		CopyEntityState( &m_pCurrentFrame, &(m_pPastFrames[m_nFrameNumber % MAX_FRAMES]) );
	}
	// If the reference for the new frame is the "current" frame,
	// don't delete the current frame because we'll just have to recopy it over
	// later.  This saves that step.
	if ( nRef != m_nFrameNumber )
	{
		if ( m_pCurrentFrame != NULL )
		{
			delete m_pCurrentFrame;
			m_pCurrentFrame = NULL;
		}
	}
	m_nMuzzleFlash	= 0;
	m_nMuzzleFlash2 = 0;
}

void CEntity::Reset()
{
	register nCount;

	for ( nCount = 0; nCount < MAX_FRAMES; nCount++ )
	{
		if ( m_pPastFrames[nCount] != NULL )
		{
			delete m_pPastFrames[nCount];
		}
	}
	if ( m_pBaseline != NULL )
	{
		delete m_pBaseline;
	}
	if ( m_pCurrentFrame != NULL )
	{
		delete m_pCurrentFrame;
	}
	Clear();
}

//////////////////////////////////////////////////////////////////////
// End of Entity.cpp
//////////////////////////////////////////////////////////////////////