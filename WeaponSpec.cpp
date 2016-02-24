// WeaponSpec.cpp: implementation of the CWeaponSpec class.
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
#include "WeaponSpec.h"
#include "GameState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeaponSpec::CWeaponSpec()
{
	Clear();
}

CWeaponSpec::~CWeaponSpec()
{

}

//////////////////////////////////////////////////////////////////////
// Public Operations
//////////////////////////////////////////////////////////////////////

BOOL CWeaponSpec::CheckRange( const float& nRange ) const
{
	// Check Minimum Ranges
	if ( (!m_nMinRange) || (nRange >= m_nMinRange) )
	{
		if ( (!m_nMaxRange) || (nRange <= m_nMaxRange) )
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CWeaponSpec::Clear()
{
	m_nAmmoInventoryIndex	= 0;
	m_nAmmoPerShot			= 0;
	m_nAmmoType				= 0;
	m_nFramesPerShot		= 0;
	m_nIdealRange			= 0;
	m_nInventoryIndex		= 0;
	m_nMaxRange				= 0;
	m_nMinRange				= 0;
	m_nMuzzleFlash			= 0;
	m_nViewType				= 0;
	m_pDanger				= NULL;
}

//////////////////////////////////////////////////////////////////////
// End of WeaponSpec.cpp
//////////////////////////////////////////////////////////////////////