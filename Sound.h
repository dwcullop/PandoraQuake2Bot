// Sound.h: interface for the CSound class.
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

#if !defined(AFX_SOUND_H__C90CE461_C11E_11D1_8720_444553540000__INCLUDED_)
#define AFX_SOUND_H__C90CE461_C11E_11D1_8720_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SystemObject.h"
#include "Vector.h"

class CSound : public CSystemObject  
{
	DECLARE_DYNCREATE(CSound);

// Attributes
private:
	BYTE			m_nSoundIndex;
	float			m_nVolume;
	BYTE			m_nAttenuation;
	BYTE			m_nTimeOffset;		// Time in milliseconds
	WORD			m_nEntity_Channel;
	CVector			m_vOrigin;

// Construction / Destruction
public:
	CSound()											{ Clear(); };
	virtual ~CSound()									{};

// Data Manipulation
public:
	void			SetVolume(const float& nNew)		{ m_nVolume = nNew; };
	void			SetAttenuation(const BYTE& nNew)	{ m_nAttenuation = nNew; };
	void			SetTimeOffset(const BYTE& nNew)		{ m_nTimeOffset = nNew; };
	void			SetSoundIndex(const BYTE& nNew)		{ m_nSoundIndex = nNew; };
	void			SetEntity_Channel(const WORD& nNew)	{ m_nEntity_Channel = nNew; };
	void			SetOrigin(const CVector& vNew)		{ m_vOrigin = vNew; };

	BYTE&			GetSetSoundIndex()					{ return m_nSoundIndex; };
	float&			GetSetVolume()						{ return m_nVolume; };
	BYTE&			GetSetAttenuation()					{ return m_nAttenuation; };
	BYTE&			GetSetTimeOffset()					{ return m_nTimeOffset; };
	WORD&			GetSetEntity_Channel()				{ return m_nEntity_Channel; };
	CVector&		GetSetOrigin()						{ return m_vOrigin; };

	const BYTE&		GetSoundIndex() const				{ return m_nSoundIndex; };
	const float&	GetVolume() const					{ return m_nVolume; };
	const BYTE&		GetAttenuation() const				{ return m_nAttenuation; };
	const BYTE&		GetTimeOffset() const				{ return m_nTimeOffset; };
	const WORD		GetEntityNumber() const				{ return (m_nEntity_Channel >> 3); };
	const BYTE		GetChannel() const					{ return (m_nEntity_Channel & 0x07); };
	const CVector&	GetOrigin() const					{ return m_vOrigin; };

// Operations
public:
	void Clear();
	void Copy( const CSound& );
	
};

#endif // !defined(AFX_SOUND_H__C90CE461_C11E_11D1_8720_444553540000__INCLUDED_)
