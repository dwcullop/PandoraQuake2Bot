// EntityState.cpp: implementation of the CEntityState class.
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
#include "EntityState.h"

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
// Overridables
//////////////////////////////////////////////////////////////////////

void CEntityState::Clear()
{
	m_bActive = FALSE;
	m_nEffects = 0;
	m_nEvent = 0;
	m_nFrame = 0;
	m_nModelIndex = 0;
	m_nModelIndex2 = 0;
	m_nModelIndex3 = 0;
	m_nModelIndex4 = 0;
	m_nRenderFX = 0;
	m_nSkinNum = 0;
	m_nSolid = 0;
	m_vAngles.Clear();
	m_vOldOrigin.Clear();
	m_vOrigin.Clear();
}

void CEntityState::Copy( const CEntityState* pCopy )
{
	if ( pCopy != NULL )
	{
/*
		m_bActive = pCopy->GetActive();
		m_nEffects = pCopy->GetEffects();
		m_nEvent = pCopy->GetEvent();
		m_nFrame = pCopy->GetFrame();
		m_nModelIndex = pCopy->GetModelIndex();
		m_nModelIndex2 = pCopy->GetModelIndex2();
		m_nModelIndex3 = pCopy->GetModelIndex3();
		m_nModelIndex4 = pCopy->GetModelIndex4();
		m_nRenderFX = pCopy->GetRenderFX();
		m_nSkinNum = pCopy->GetSkinNum();
		m_nSolid = pCopy->GetSolid();
		m_vAngles = pCopy->GetAngles();
		m_vOldOrigin = pCopy->GetOldOrigin();
		m_vOrigin = pCopy->GetOrigin();
*/
		CopyMemory( this, pCopy, sizeof(CEntityState) );
	}
	else
	{
		Clear();
	}
}

//////////////////////////////////////////////////////////////////////
// End of EntityState.cpp
//////////////////////////////////////////////////////////////////////