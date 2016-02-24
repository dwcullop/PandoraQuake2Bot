// AIData.cpp: implementation of the CAIData class.
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
#include "AIData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CAIData Defines
//////////////////////////////////////////////////////////////////////

#define DATAFILE_COMMENTS		";#'"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAIData::CAIData()
{
	Clear();
}

CAIData::~CAIData()
{
	Reset();
}

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

const CArmorSpec* CAIData::GetArmorData( const BYTE& nIndex )
{
	POSITION pPos = m_lstArmorData.FindIndex( nIndex );

	if ( pPos != NULL )
	{
		return ( (const CArmorSpec*) m_lstArmorData.GetAt(pPos) );
	}
	else
	{
		return NULL;
	}
}

const CDangerSpec* CAIData::GetDangerData( const BYTE& nIndex )
{
	POSITION pPos = m_lstDangerData.FindIndex( nIndex );

	if ( pPos != NULL )
	{
		return ( (const CDangerSpec*) m_lstDangerData.GetAt(pPos) );
	}
	else
	{
		return NULL;
	}
}

const CHealingSpec* CAIData::GetHealingData( const BYTE& nIndex )
{
	POSITION pPos = m_lstHealingData.FindIndex( nIndex );

	if ( pPos != NULL )
	{
		return ( (const CHealingSpec*) m_lstHealingData.GetAt(pPos) );
	}
	else
	{
		return NULL;
	}
}

const CWeaponSpec* CAIData::GetWeaponData( const BYTE& nIndex )
{
	POSITION pPos = m_lstWeaponData.FindIndex( nIndex );

	if ( pPos != NULL )
	{
		return ( (const CWeaponSpec*) m_lstWeaponData.GetAt(pPos) );
	}
	else
	{
		return NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// Data Lookup Operations
//////////////////////////////////////////////////////////////////////

const CWeaponSpec* CAIData::FindWeaponByMuzzleFlash( const BYTE& nMZ )
{
	register			nCount;
	const CWeaponSpec*	pReturn = NULL;

	for ( nCount = 0 ; ( (nCount < GetWeaponCount()) && (pReturn == NULL) ) ; nCount++ )
	{
		if ( GetWeaponData(nCount)->GetMuzzleFlash() == nMZ )
		{
			pReturn = GetWeaponData(nCount);
		}
	}
	return pReturn;
}

const CWeaponSpec* CAIData::FindWeaponByViewModel( const BYTE& nModelIndex )
{
	register			nCount;
	BYTE				nViewType;
	const CWeaponSpec*	pReturn = NULL;

	nViewType = GetSubType( nModelIndex );
	for ( nCount = 0 ; ( (nCount < GetWeaponCount()) && (pReturn == NULL) ) ; nCount++ )
	{
		if ( GetWeaponData(nCount)->GetViewType() == nViewType )
		{
			pReturn = GetWeaponData(nCount);
		}
	}
	return pReturn;
}

//////////////////////////////////////////////////////////////////////
// Public Operations
//////////////////////////////////////////////////////////////////////

void CAIData::Clear()
{
	ClearTypeInfo();
}

void CAIData::Reset()
{
	CObject*	pTemp;

	m_mapModelTypes.RemoveAll();
	while ( !m_lstArmorData.IsEmpty() )
	{
		pTemp = m_lstArmorData.RemoveHead();
		delete pTemp;
	}
	while ( !m_lstDangerData.IsEmpty() )
	{
		pTemp = m_lstDangerData.RemoveHead();
		delete pTemp;
	}
	while ( !m_lstHealingData.IsEmpty() )
	{
		pTemp = m_lstHealingData.RemoveHead();
		delete pTemp;
	}
	while ( !m_lstWeaponData.IsEmpty() )
	{
		pTemp = m_lstWeaponData.RemoveHead();
		delete pTemp;
	}
	Clear();
}

BOOL CAIData::ReadDataFile( const CString& strFilename )
{
	CStdioFile	fDataFile;
	CString		strCurrentLine;
	void		(CAIData::*pHandler)(const CString&);

	if ( !fDataFile.Open(strFilename, CFile::modeRead | CFile::typeText) )
	{
		TRACE("Cannot open AIData file: %s\n", strFilename);
		return FALSE;
	}
	Reset();
	pHandler = NULL;
	while ( fDataFile.ReadString(strCurrentLine) )
	{
		if ( strCurrentLine.FindOneOf(DATAFILE_COMMENTS) && strCurrentLine.GetLength() )
		{
			if ( !strCurrentLine.CompareNoCase("[ModelTypes]") )
			{
				pHandler = ParseModelTypes;
			}
			else if ( !strCurrentLine.CompareNoCase("[Armor]") )
			{
				pHandler = ParseArmorData;
			}
			else if ( !strCurrentLine.CompareNoCase("[Danger]") )
			{
				pHandler = ParseDangerData;
			}
			else if ( !strCurrentLine.CompareNoCase("[Healing]") )
			{
				pHandler = ParseHealingData;
			}
			else if ( !strCurrentLine.CompareNoCase("[Weapons]") )
			{
				pHandler = ParseWeaponData;
			}
			else
			{
				if ( pHandler != NULL )
				{
					(this->*pHandler)( strCurrentLine );
				}
			}
		}
	}
//	m_mapModelTypes.Dump( afxDump );
	return TRUE;
}

void CAIData::ProcessNewConfigStrings( CGameState* pGame )
{
	register	nCount;
	BYTE		nValue;

	ASSERT( pGame != NULL );
	ClearTypeInfo();
	for ( nCount = 0; nCount < MAX_MODELS; nCount++ )
	{
		if ( m_mapModelTypes.Lookup(pGame->GetModelName(nCount), nValue) )
		{
			m_nTypeInfo[nCount] = nValue;
		}
	}

}

//////////////////////////////////////////////////////////////////////
// Private Operations
//////////////////////////////////////////////////////////////////////

void CAIData::ClearTypeInfo()
{
	ZeroMemory( m_nTypeInfo, sizeof(BYTE)*MAX_MODELS );
}

void CAIData::ParseArmorData( const CString& strData )
{
}

void CAIData::ParseDangerData( const CString& strData )
{
	// # Format is Speed, Damage, BlastDamage, BlastRadius, EnergyWeapon
	CString			strTemp;
	UINT			nSpeed;
	UINT			nDamage;
	UINT			nBlastDamage;
	UINT			nBlastRadius;
	UINT			nEnergyWeapon;
	CDangerSpec*	pNew;

	strTemp = strData;
	if ( !ReadData(nSpeed, strTemp) )
	{
		return;
	}
	if ( !ReadData(nDamage,strTemp) )
	{
		return;
	}
	if ( !ReadData(nBlastDamage, strTemp) )
	{
		return;
	}
	if ( !ReadData(nBlastRadius, strTemp) )
	{
		return;
	}
	if ( !ReadData(nEnergyWeapon, strTemp) )
	{
		return;
	}
	pNew = new CDangerSpec;
	pNew->SetSpeed( nSpeed );
	pNew->SetBlastDamage( nBlastDamage );
	pNew->SetBlastRadius( nBlastRadius );
	pNew->SetDamage( nDamage );
	pNew->SetEnergyWeapon( nEnergyWeapon );
	m_lstDangerData.AddTail( pNew );
}

void CAIData::ParseHealingData( const CString& strData )
{
}

void CAIData::ParseModelTypes( const CString& strData )
{
	UINT	nData;
	CString	strModelName;

	strModelName = strData;
	if ( ReadData(nData, strModelName) )
	{
		BYTE nType;

		nType = ( (BYTE)nData );
		m_mapModelTypes.SetAt( strModelName, nType );
	}
}

void CAIData::ParseWeaponData( const CString& strData )
{
	// # Format is ViewType, InvIndex, AmmoInvIndex, AmmoType, DangerIndex, MinRange
	// #	IdealRange, MaxRange, AmmoUsed, FramesPerShot
	CString				strTemp;
	UINT				nViewType;
	UINT				nInvIndex;
	UINT				nAmmoInvIndex;
	UINT				nAmmoType;
	UINT				nDangerIndex;
	UINT				nMinRange;
	UINT				nIdealRange;
	UINT				nMaxRange;
	UINT				nAmmoUsed;
	UINT				nFramesPerShot;
	UINT				nMuzzleFlash;
	CWeaponSpec*		pNew;
	const CDangerSpec*	pDanger;

	strTemp = strData;
	if ( !ReadData(nViewType, strTemp) )
	{
		return;
	}
	if ( !ReadData(nInvIndex, strTemp) )
	{
		return;
	}
	if ( !ReadData(nAmmoInvIndex, strTemp) )
	{
		return;
	}
	if ( !ReadData(nAmmoType, strTemp) )
	{
		return;
	}
	if ( !ReadData(nDangerIndex, strTemp) )
	{
		return;
	}
	if ( !ReadData(nMinRange, strTemp) )
	{
		return;
	}
	if ( !ReadData(nIdealRange, strTemp) )
	{
		return;
	}
	if ( !ReadData(nMaxRange, strTemp) )
	{
		return;
	}
	if ( !ReadData(nAmmoUsed, strTemp) )
	{
		return;
	}
	if ( !ReadData(nFramesPerShot, strTemp) )
	{
		return;
	}
	if ( !ReadData(nMuzzleFlash, strTemp) )
	{
		return;
	}
	pDanger = GetDangerData( nDangerIndex );
	if ( pDanger == NULL )
	{
		TRACE("NULL DangerSpec reading CWeaponSpec!\n");
		return;
	}
	pNew = new CWeaponSpec;

	pNew->SetAmmoInventoryIndex( nAmmoInvIndex );
	pNew->SetAmmoPerShot( nAmmoUsed );
	pNew->SetAmmoType( nAmmoType );
	pNew->SetDangerSpec( pDanger );
	pNew->SetFramesPerShot( nFramesPerShot );
	pNew->SetIdealRange( nIdealRange );
	pNew->SetInventoryIndex( nInvIndex );
	pNew->SetMaxRange( nMaxRange );
	pNew->SetMinRange( nMinRange );
	pNew->SetMuzzleFlash( nMuzzleFlash );
	pNew->SetViewType( nViewType );
	m_lstWeaponData.AddTail( pNew );
}

BOOL CAIData::ReadData( UINT& nData, CString& strData ) const
{
	CString strTemp;

	strTemp = strData.SpanExcluding(",");
	strData = strData.Right( strData.GetLength() - strTemp.GetLength() - 1 );
	strTemp.TrimRight();
	strTemp.TrimLeft();
	strData.TrimRight();
	strData.TrimLeft();
	if ( strTemp.GetLength() )
	{
		nData = atoi( strTemp.GetBuffer(0) );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////
// End of AIData.cpp
//////////////////////////////////////////////////////////////////////


