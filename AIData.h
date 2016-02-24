// AIData.h: interface for the CAIData class.
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

#if !defined(AFX_AIDATA_H__9C2A0642_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
#define AFX_AIDATA_H__9C2A0642_F18B_11D1_AF24_0060080A5FD2__INCLUDED_

//////////////////////////////////////////////////////////////////////
// AIData Includes
//////////////////////////////////////////////////////////////////////

#include "GameState.h"
#include "ArmorSpec.h"
#include "DangerSpec.h"
#include "HealingSpec.h"
#include "WeaponSpec.h"
#include <afxtempl.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CAIData Defines
//////////////////////////////////////////////////////////////////////

#define	ENTITY_TYPE_OTHER						0
#define ENTITY_TYPE_AMMO						1
#define ENTITY_TYPE_ARMOR						2
#define ENTITY_TYPE_DANGEROUS					3
#define ENTITY_TYPE_HEALING						4
#define ENTITY_TYPE_ITEMS						5
#define ENTITY_TYPE_VISIBLE						6
#define ENTITY_TYPE_WEAPONS						7
#define	GET_TYPE(x)								( ((x)>>5) & (0x07) )
#define GET_SUBTYPE(x)							( (x) & (0x1F) )

//////////////////////////////////////////////////////////////////////
// CAIData TypeDefs
//////////////////////////////////////////////////////////////////////

typedef CMap< CString, LPCSTR, BYTE, BYTE& >	CMapStringToByte;

//////////////////////////////////////////////////////////////////////
// CAIData Class Definitions
//////////////////////////////////////////////////////////////////////

class CAIData  
{
// Attributes
private:
	BYTE				m_nTypeInfo[MAX_MODELS];
	CMapStringToByte	m_mapModelTypes;
	CObList				m_lstArmorData;
	CObList				m_lstDangerData;
	CObList				m_lstWeaponData;
	CObList				m_lstHealingData;

// Construction / Destruction
public:
	CAIData();
	virtual ~CAIData();

// Data Manipulation
public:
	// Type Info
	const BYTE&			GetTypeInfo( const BYTE& nIndex ) const		{ return m_nTypeInfo[nIndex]; };
	BYTE				GetSubType( const BYTE& nIndex ) const		{ return GET_SUBTYPE( m_nTypeInfo[nIndex] ); };
	BYTE				GetType( const BYTE& nIndex ) const			{ return GET_TYPE( m_nTypeInfo[nIndex] ); };
	// Spec Arrays Sizes
	int					GetArmorCount() const						{ return m_lstArmorData.GetCount(); };
	int					GetDangerCount() const						{ return m_lstDangerData.GetCount(); };
	int					GetWeaponCount() const						{ return m_lstWeaponData.GetCount(); };
	int					GetHealingCount() const						{ return m_lstHealingData.GetCount(); };
	// Spec Arrays Data
	const CArmorSpec*	GetArmorData( const BYTE& );
	const CDangerSpec*	GetDangerData( const BYTE& );
	const CWeaponSpec*	GetWeaponData( const BYTE& );
	const CHealingSpec*	GetHealingData( const BYTE& );

// Data Lookup Operations
public:
	const CWeaponSpec*	FindWeaponByMuzzleFlash( const BYTE& );
	const CWeaponSpec*	FindWeaponByViewModel( const BYTE& );

// Operations
public:
	void				Clear();
	void				Reset();
	BOOL				ReadDataFile( const CString& );
	void				ProcessNewConfigStrings( CGameState* );

private:
	void				ClearTypeInfo();
	void				ParseArmorData( const CString& );
	void				ParseDangerData( const CString& );
	void				ParseHealingData( const CString& );
	void				ParseModelTypes( const CString& );
	void				ParseWeaponData( const CString& );
	BOOL				ReadData( UINT&, CString& ) const;
};

#endif // !defined(AFX_AIData_H__9C2A0642_F18B_11D1_AF24_0060080A5FD2__INCLUDED_)
