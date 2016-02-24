// AdvTime.cpp: implementation of the CAdvTime class
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
#include "AdvTime.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	// All are declared inline

//////////////////////////////////////////////////////////////////////
// Initialization
//////////////////////////////////////////////////////////////////////

// Private
void CAdvTime::Validate()
{
	while ( GetMilli() < 0 )
	{
		m_Value.time	-= 1;
		m_Value.millitm	+= 1000;
	}
	while ( GetMilli() >= 1000 )
	{
		m_Value.time	+= 1;
		m_Value.millitm -= 1000;
	}
}

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

double CAdvTime::GetValue() const
{
	return ( ((double)m_Value.time + ((double)m_Value.millitm / 1000.0)) ); 
}

void CAdvTime::SetValue( const double& nNew )
{
	m_Value.time	= (long)floor( nNew );
	m_Value.millitm = (WORD)floor( (nNew - m_Value.time)*1000 );
}

//////////////////////////////////////////////////////////////////////
// String Functions
//////////////////////////////////////////////////////////////////////

void CAdvTime::GetFullString( CString& strTime ) const
{
	double	nSeconds	= GetValue();
	UINT	nHours;
	BYTE	nMinutes;
	
	nHours		= (UINT)floor(nSeconds / 3600);
	nSeconds	-= nHours*3600;
	nMinutes	= (BYTE)floor(nSeconds / 60);
	nSeconds	-= nMinutes*60;
	strTime.Format("%02d:%02d:%05.3f", nHours, nMinutes, nSeconds);
}

CString CAdvTime::GetFullString() const
{
	CString strReturnMe;

	GetFullString(strReturnMe);
	return strReturnMe;
}

void CAdvTime::GetString( CString& strTime ) const
{
	double	nSeconds	= GetValue();
	WORD	nMinutes;
	UINT	nHours;
	
	nHours		= (UINT)floor(nSeconds / 3600);
	nSeconds	-= nHours*3600;
	nMinutes	= (WORD)floor(nSeconds / 60);
	nSeconds	-= nMinutes*60;
	if (nHours)
	{
		strTime.Format("%3d:%02d:%02d", nHours, nMinutes, (int)(nSeconds) );
	}
	else
	{
		strTime.Format("%2d:%02d", nMinutes, (int)(nSeconds) );
	}
}

CString CAdvTime::GetString() const
{
	CString strReturnMe;

	GetString(strReturnMe);
	return strReturnMe;
}

//////////////////////////////////////////////////////////////////////
// Diagnostics
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CAdvTime::AssertValid() const
{
	CObject::AssertValid();
}

void CAdvTime::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << GetString();
}

#endif // _DEBUG

//////////////////////////////////////////////////////////////////////
// End of AdvTime.cpp
//////////////////////////////////////////////////////////////////////
