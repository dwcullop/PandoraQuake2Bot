// Player.cpp: implementation of the CPlayer class.
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
#include "Player.h"
#include "m_player.h"	// This file is from Id software

IMPLEMENT_DYNCREATE( CPlayer, CEntity )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	// Defined inline

//////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////

void CPlayer::AfterUpdate()
{
	CEntity::AfterUpdate();
	if ( IsVisible() )
	{
		if ( IsDeathFrame() )
		{
			if ( !IsDead())
			{
				m_bDead = TRUE;
				OnKilled();
			}
		}
		else
		{
			if ( IsDead() )
			{
				m_bDead = FALSE;
				OnRespawned();
			}
		}
	}
}

void CPlayer::Clear()
{
	m_bDead				= TRUE;
	m_nNextFireFrame	= 0;
	m_pWeapon			= NULL;
	m_nPing				= 0;
	m_nFrags			= 0;
	m_nPlayerNumber		= 0;
	m_strName.Empty();
	m_strSkin.Empty();
	CEntity::Clear();
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

BOOL CPlayer::IsAttacking() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_attack1) && (m_pCurrentFrame->GetFrame() <= FRAME_attack8) )
	{
		return TRUE;
	}
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_crattak1) && (m_pCurrentFrame->GetFrame() <= FRAME_crattak9) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsCrouching() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_crstnd01) && (m_pCurrentFrame->GetFrame() <= FRAME_crpain4) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsDeathFrame() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_crdeath1) && (m_pCurrentFrame->GetFrame() <= FRAME_death308) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsFlippingOff() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_flip01) && (m_pCurrentFrame->GetFrame() <= FRAME_flip12) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsGesturing() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_flip01) && (m_pCurrentFrame->GetFrame() <= FRAME_point12) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsInPain() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_pain101) && (m_pCurrentFrame->GetFrame() <= FRAME_pain304) )
	{
		return TRUE;
	}
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_crpain1) && (m_pCurrentFrame->GetFrame() <= FRAME_crpain4) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsJumping() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_jump1) && (m_pCurrentFrame->GetFrame() <= FRAME_jump6) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsPointing() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_point01) && (m_pCurrentFrame->GetFrame() <= FRAME_point12) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsRunning() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_run1) && (m_pCurrentFrame->GetFrame() <= FRAME_run6) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsSaluting() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_salute01) && (m_pCurrentFrame->GetFrame() <= FRAME_salute11) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsStanding() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_stand01) && (m_pCurrentFrame->GetFrame() <= FRAME_stand40) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsTaunting() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_taunt01) && (m_pCurrentFrame->GetFrame() <= FRAME_taunt17) )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CPlayer::IsWaving() const
{
	ASSERT( m_pCurrentFrame != NULL );
	if ( (m_pCurrentFrame->GetFrame() >= FRAME_wave01) && (m_pCurrentFrame->GetFrame() <= FRAME_wave11) )
	{
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// End of Player.cpp
//////////////////////////////////////////////////////////////////////