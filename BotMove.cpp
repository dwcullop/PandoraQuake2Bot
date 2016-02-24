// BotMove.cpp: implementation of the CBotMove class.
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
#include "BotMove.h"
#include "NetUtils.h"
#include "PandoraDefs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	// Defined Inline

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CBotMove::Clear()
{
	m_vMove.Clear();
	m_vLook.Clear();
	m_tSent.SetCurrent();
	m_moAttack	= Maybe;
	m_moJump	= Maybe;
	m_moCrouch	= Maybe;
	m_moUse		= Maybe;
	m_nImpulse	= 0;
}

void CBotMove::PrepareMoveData( CMoveData* pNew, const CVector& vDelta ) const
{
	ASSERT( pNew != NULL );
	// Set the velocities
	SetMoveDataSpeeds( pNew );
	// Set the UpSpeed
	SetMoveDataUpSpeed( pNew );
	// Set the angles
	SetMoveDataAngles( pNew, vDelta );
	// Set the buttons
	SetMoveDataButtons( pNew );
	// Set the impulse
	pNew->SetImpulse( m_nImpulse );
}

//////////////////////////////////////////////////////////////////////
// Private Operations
//////////////////////////////////////////////////////////////////////

void CBotMove::SetMoveDataSpeeds( CMoveData* pNew ) const
{
	if ( m_vMove.GetX() || m_vMove.GetY() )
	{
		if ( m_vMove == m_vLook )
		{
			pNew->SetForward( MAX_SPEED );
			pNew->SetRight( 0 );
		}
		else
		{
			CVector		vForward;
			CVector		vRight;
			float		nYaw, nPitch;

			m_vLook.GetNormalized( vForward );
			vForward.GetYawAngle( nYaw );
			vForward.GetPitchAngle( nPitch );
			nYaw += 90.0f;
			vRight.SetAngles( nPitch, nYaw );
			vRight.Normalize();
			// Compute the velocities
				// m_vMove = A*vForward + B*vRight
				// Solve for A and B
			float nTemp1, nTemp2;
			short nA, nB;

			nTemp1 = ( m_vMove.GetX()*vRight.GetY() - m_vMove.GetY()*vRight.GetX() );
			nTemp2 = ( vForward.GetX()*vRight.GetY() - vForward.GetY()*vRight.GetX() );
			nA = ( (short)( nTemp1 / nTemp2 ) );
			nTemp1 = ( m_vMove.GetX()*vForward.GetY() - m_vMove.GetY()*vForward.GetX() );
			nTemp2 = ( vRight.GetX()*vForward.GetY() - vRight.GetY()*vForward.GetX() );
			nB = ( (short)( nTemp1 / nTemp2 ) );
			pNew->SetForward( nA );
			pNew->SetRight( nB );
		}
	}
	else
	{
		pNew->SetForward( 0 );
		pNew->SetRight( 0 );
	}
}

void CBotMove::SetMoveDataUpSpeed( CMoveData* pNew ) const
{
	short nUpSpeed;

	switch( m_moJump )
	{
	case No:
		nUpSpeed = 0;
		break;
	case Yes:
		nUpSpeed = MAX_SPEED;
		break;
	case Maybe:
		switch( m_moCrouch )
		{
		case No:
			nUpSpeed = 0;
			break;
		case Yes:
			nUpSpeed = -MAX_SPEED;
			break;
		case Maybe:
			if ( m_vMove.GetZ() )
			{
				nUpSpeed = ( (m_vMove.GetZ() > 0) ? MAX_SPEED : -MAX_SPEED );
			}
			else
			{
				nUpSpeed = 0;
			}
			break;
		}
		break;
	}
	pNew->SetUp( nUpSpeed );
}

void CBotMove::SetMoveDataAngles( CMoveData* pNew, const CVector& vDelta ) const
{
	float nTemp;

	// Pitch Angle
	m_vLook.GetPitchAngle( nTemp );
	nTemp -= vDelta.GetX();
	NormalizeAngle( nTemp );
	pNew->SetPitch( AngleToShort(nTemp) );
	// Yaw Angle
	m_vLook.GetYawAngle( nTemp );
	nTemp -= vDelta.GetY();
	NormalizeAngle( nTemp );
	pNew->SetYaw( AngleToShort(nTemp) );
	// Roll Angle
	m_vLook.GetRollAngle( nTemp );
	nTemp -= vDelta.GetZ();
	NormalizeAngle( nTemp );
	pNew->SetRoll( AngleToShort(nTemp) );
}

void CBotMove::SetMoveDataButtons( CMoveData* pNew ) const
{
	BYTE nButtons = 0;

	if ( m_moAttack == Yes )
	{
		nButtons |= BUTTON_ATTACK;
	}
	if ( m_moUse == Yes )
	{
		nButtons |= BUTTON_USE;
	}
	if ( nButtons )
	{
		nButtons |= BUTTON_ANY;
	}
	pNew->SetButtons( nButtons );
}

