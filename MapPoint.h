// MapPoint.h: interface for the CMapPoint class.
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

#if !defined(AFX_MAPPOINT_H__C0A94C83_E775_11D1_AF21_0060080A5FD2__INCLUDED_)
#define AFX_MAPPOINT_H__C0A94C83_E775_11D1_AF21_0060080A5FD2__INCLUDED_

#include "Vector.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMapPoint
{
// Attributes
private:
	CString		m_strName;
	CVector		m_vOrigin;

// Construction / Destruction
public:
	CMapPoint();
	virtual ~CMapPoint();

// Data Manipulation
public:
	const CString&	GetName() const							{ return m_strName; };
	const CVector&	GetOrigin() const						{ return m_vOrigin; };
	void			SetName( const CString& strNew )		{ m_strName = strNew; };
	void			SetOrigin( const CVector& vNew )		{ m_vOrigin = vNew; };

// Operations
public:
	void			SetRandomOrigin()						{ m_vOrigin.Randomize(); };

};

#endif // !defined(AFX_MAPPOINT_H__C0A94C83_E775_11D1_AF21_0060080A5FD2__INCLUDED_)
