// DangerSpec.h: interface for the CDangerSpec class.
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

#if !defined(AFX_DANGERSPEC_H__9C2A0644_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
#define AFX_DANGERSPEC_H__9C2A0644_F18B_11D1_AF24_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDangerSpec : public CObject
{
// Attributes
private:
	WORD	m_nSpeed;
	WORD	m_nDamage;
	WORD	m_nBlastDamage;
	WORD	m_nBlastRadius;
	BOOL	m_bEnergyWeapon;

// Construction / Destruction
public:
	CDangerSpec();
	virtual ~CDangerSpec();

// Data Manipulation
public:
	const WORD&	GetSpeed() const							{ return m_nSpeed; };
	const WORD& GetDamage() const							{ return m_nDamage; };
	const WORD& GetBlastDamage() const						{ return m_nBlastDamage; };
	const WORD&	GetBlastRadius() const						{ return m_nBlastRadius; };
	const BOOL& GetEnergyWeapon() const						{ return m_bEnergyWeapon; };
	void		SetSpeed( const WORD& nNew )				{ m_nSpeed = nNew; };
	void		SetDamage( const WORD& nNew )				{ m_nDamage = nNew; };
	void		SetBlastDamage( const WORD& nNew )			{ m_nBlastDamage = nNew; };
	void		SetBlastRadius( const WORD& nNew )			{ m_nBlastRadius = nNew; };
	void		SetEnergyWeapon( const BOOL& bNew )			{ m_bEnergyWeapon = bNew; };

// Operations
public:
	void Clear();
};

#endif // !defined(AFX_DANGERSPEC_H__9C2A0644_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
