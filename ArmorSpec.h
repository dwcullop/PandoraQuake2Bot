// ArmorSpec.h: interface for the CArmorSpec class.
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

#if !defined(AFX_ARMORSPEC_H__9C2A0643_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
#define AFX_ARMORSPEC_H__9C2A0643_F18B_11D1_AF24_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CArmorSpec : public CObject
{
// Attributes
private:
	BYTE	m_nItemIndex;
	BYTE	m_nUnitsItemIndex;
	float	m_nNormalMax;
	float	m_nEnergyMax;
	BYTE	m_nPointsPerUnit;

// Construction / Destruction
public:
	CArmorSpec();
	virtual ~CArmorSpec();

// Data Manipulation
public:
	const BYTE&		GetItemIndex() const					{ return m_nItemIndex; };
	const BYTE&		GetUnitsItemIndex() const				{ return m_nUnitsItemIndex; };
	const float&	GetNormalMax() const					{ return m_nNormalMax; };
	const float&	GetEnergyMax() const					{ return m_nEnergyMax; };
	const BYTE&		GetPointsPerUnit() const				{ return m_nPointsPerUnit; };
	void			SetItemIndex( const BYTE& nNew )		{ m_nItemIndex = nNew; };
	void			SetUnitsItemIndex( const BYTE& nNew )	{ m_nUnitsItemIndex = nNew; };
	void			SetNormalMax( const float& nNew )		{ m_nNormalMax = nNew; };
	void			SetEnergyMax( const float& nNew )		{ m_nEnergyMax = nNew; };
	void			SetPointsPerUnit( const BYTE& nNew )	{ m_nPointsPerUnit = nNew; };

// Operations
public:
	void			Clear();
};

#endif // !defined(AFX_ARMORSPEC_H__9C2A0643_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
