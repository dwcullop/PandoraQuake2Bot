// TempEntity.h: interface for the CTempEntity class.
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

#if !defined(AFX_TEMPENTITY_H__C90CE462_C11E_11D1_8720_444553540000__INCLUDED_)
#define AFX_TEMPENTITY_H__C90CE462_C11E_11D1_8720_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SystemObject.h"
#include "Vector.h"

#define MAX_NORMALS				162

class CTempEntity : public CSystemObject  
{
	DECLARE_DYNCREATE(CTempEntity);

// Attributes
private:
	BYTE		m_nType;
	CVector		m_vOrigin;
	CVector		m_vEndPosition;
	CVector		m_vOffset;
	BYTE		m_nDirectionIndex;
	BYTE		m_nCount;
	BYTE		m_nColor;
	BYTE		m_nSounds;
	WORD		m_nEntity;

// Statics
private:
	static float	m_nVectors[MAX_NORMALS][3];

// Construction / Destruction
public:
	CTempEntity()								{ Clear(); };
	virtual ~CTempEntity()						{};

// Data Manipulation
public:
	BYTE&			GetSetType()				{ return m_nType; };
	CVector&		GetSetOrigin()				{ return m_vOrigin; };
	CVector&		GetSetEndPosition()			{ return m_vEndPosition; };
	CVector&		GetSetOffset()				{ return m_vOffset; };
	BYTE&			GetSetDirectionIndex()		{ return m_nDirectionIndex; };
	BYTE&			GetSetCount()				{ return m_nCount; };
	BYTE&			GetSetColor()				{ return m_nColor; };
	BYTE&			GetSetSounds()				{ return m_nSounds; };
	WORD&			GetSetEntity()				{ return m_nEntity; };

	const BYTE&		GetType() const				{ return m_nType; };
	const CVector&	GetOrigin() const			{ return m_vOrigin; };
	const CVector&	GetEndPosition() const		{ return m_vEndPosition; };
	const CVector&	GetOffset() const			{ return m_vOffset; };
	const BYTE&		GetDirectionIndex() const	{ return m_nDirectionIndex; };
	const CVector	GetDirection() const		{ return CVector( m_nVectors[m_nDirectionIndex] ); };
	const BYTE&		GetCount() const			{ return m_nCount; };
	const BYTE&		GetColor() const			{ return m_nColor; };
	const BYTE&		GetSounds() const			{ return m_nSounds; };
	const WORD&		GetEntity() const			{ return m_nEntity; };

// Operations
public:
	void Clear();
	void Copy( const CTempEntity& );

// Static Operations
public:
	static BYTE* GetNormalsArray()				{ return ((BYTE*)m_nVectors); };

};

#endif // !defined(AFX_TEMPENTITY_H__C90CE462_C11E_11D1_8720_444553540000__INCLUDED_)
