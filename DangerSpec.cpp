// DangerSpec.cpp: implementation of the CDangerSpec class.
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
#include "DangerSpec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDangerSpec::CDangerSpec()
{
	Clear();
}

CDangerSpec::~CDangerSpec()
{

}

//////////////////////////////////////////////////////////////////////
// Public Operations
//////////////////////////////////////////////////////////////////////

void CDangerSpec::Clear()
{
	m_nSpeed = 0;
	m_nDamage = 0;
	m_nBlastRadius = 0;
	m_nBlastDamage = 0;
	m_bEnergyWeapon = FALSE;
}

//////////////////////////////////////////////////////////////////////
// End of DangerSpec.cpp
//////////////////////////////////////////////////////////////////////
