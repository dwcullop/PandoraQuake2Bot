// SystemObject.h : interface of the CSystemObject class
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

#ifndef SYSTEM_OBJECT_H
#define SYSTEM_OBJECT_H

//////////////////////////////////////////////////////////////////////////////////
// CSystemObject Includes

#include <AfxMT.h>
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// CSystemObject Class Definition

//class CSystemObject : public CObject, private CCriticalSection
class CSystemObject : public CCriticalSection
{
	DECLARE_DYNCREATE(CSystemObject);

// Attributes
protected:
	//CCriticalSection	m_Lock;
	BYTE				m_nUsage;

// Constructor Functions
public:
	CSystemObject()									{ Clear(); };
	virtual ~CSystemObject()						{};

// Operations
public:
	BYTE CheckUsage()								{ return (++m_nUsage); };
	const BYTE& PeekUsage() const					{ return m_nUsage; };
	//void Lock()										{ m_Lock.Lock(); };
	//void Unlock()									{ m_Lock.Unlock(); };
	virtual void Clear();
	virtual void Copy(const CSystemObject&);

// Overloaded Operators
public:
	virtual CSystemObject& operator=(const CSystemObject&);

// Static Functions
public:
	static void Post();

// Diagnostics
#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG

};

///////////////////////////////////////////////////////////////////////////////
// CSystemObject Inline Functions

	///////////////////////////////////////////////////////////////////////////
	// CSystemObject Operations

	inline void CSystemObject::Clear()
	{
		m_nUsage = 0;
	}

	inline void CSystemObject::Copy(const CSystemObject& rCopyMe)
	{
		m_nUsage = rCopyMe.PeekUsage();
	}

	//////////////////////////////////////////////////////////////////////////////
	// CSystemObject Overloaded Operators

	inline CSystemObject& CSystemObject::operator=(const CSystemObject& rCopyMe)
	{
		Copy(rCopyMe);
		return (*this);
	}

//////////////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////////////
