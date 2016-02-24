// MoveData.cpp: implementation of the CMoveData class.
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
#include "MoveData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoveData::CMoveData()
{

}

CMoveData::~CMoveData()
{

}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CMoveData::Clear()
{
	m_nPitch		= 0;
	m_nYaw			= 0;
	m_nRoll			= 0;
	m_nForward		= 0;
	m_nRight		= 0;
	m_nUp			= 0;
	m_nButtons		= 0;
	m_nImpulse		= 0;
	m_nMilliseconds	= 0;
	m_nLighting		= DEFAULT_LIGHTING;
	m_nBitMask		= DEFAULT_BITMASK;
}

void CMoveData::Copy( const CMoveData* pCopy )
{
	CopyMemory( this, pCopy, sizeof(CMoveData) );
}

void CMoveData::CreateBitMask( const CMoveData* pRef )
{
	m_nBitMask = 0;
	if ( pRef != NULL )
	{
		if ( GetPitch() != pRef->GetPitch() )
		{
			SetFlag( BM_PITCH );
		}
		if ( GetYaw() != pRef->GetYaw() )
		{
			SetFlag( BM_YAW );
		}
		if ( GetRoll() != pRef->GetRoll() )
		{
			SetFlag( BM_ROLL );
		}
		if ( GetForward() != pRef->GetForward() )
		{
			SetFlag( BM_FORWARD );
		}
		if ( GetRight() != pRef->GetRight() )
		{
			SetFlag( BM_RIGHT );
		}
		if ( GetUp() != pRef->GetUp() )
		{
			SetFlag( BM_UP );
		}
		if ( GetButtons() != pRef->GetButtons() )
		{
			SetFlag( BM_BUTTONS );
		}
		if ( GetImpulse() != pRef->GetImpulse() )
		{
			SetFlag( BM_IMPULSE );
		}
	}
	else
	{
		if ( GetPitch() != 0 )
		{
			SetFlag( BM_PITCH );
		}
		if ( GetYaw() != 0 )
		{
			SetFlag( BM_YAW );
		}
		if ( GetRoll() != 0 )
		{
			SetFlag( BM_ROLL );
		}
		if ( GetForward() != 0 )
		{
			SetFlag( BM_FORWARD );
		}
		if ( GetRight() != 0 )
		{
			SetFlag( BM_RIGHT );
		}
		if ( GetUp() != 0 )
		{
			SetFlag( BM_UP );
		}
		if ( GetButtons() != 0 )
		{
			SetFlag( BM_BUTTONS );
		}
		if ( GetImpulse() != 0 )
		{
			SetFlag( BM_IMPULSE );
		}
	}
}

