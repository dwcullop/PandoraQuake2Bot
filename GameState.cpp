// GameState.cpp: implementation of the CGameState class.
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
#include "GameState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Defines
//////////////////////////////////////////////////////////////////////

#define NAME_SKIN_DIVIDER			"\\"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameState::CGameState()
{
	CEntity::SetGameState( this );
	CPlayerInfo::SetBot( &m_botClient );
	Clear();
}

CGameState::~CGameState()
{
	Reset();
}

//////////////////////////////////////////////////////////////////////
// Data Manipulation
//////////////////////////////////////////////////////////////////////

void CGameState::SetConfigString( const WORD& nIndex, const CString& strConfig )
{
	ASSERT( nIndex < MAX_CONFIGSTRINGS );
	m_arrConfigStrings[nIndex] = strConfig;
	// If it is a player info string, parse it for the name and skin
	// and update the appropriate player object
	if ( (nIndex >= CS_PLAYERSKINS) && (m_bReady) )
	{
		ParsePlayerInfo( nIndex-CS_PLAYERSKINS );
	}
}

const CString& CGameState::GetConfigString( const WORD& nIndex ) const
{
	// This generates a warning, but as far as I can tell, it works just fine.
	ASSERT( nIndex < MAX_CONFIGSTRINGS );
	return m_arrConfigStrings.GetAt(nIndex);
}

const CString& CGameState::GetModelName( const BYTE& nModel ) const
{
	ASSERT( nModel < MAX_MODELS );
	return m_arrConfigStrings.GetAt( CS_MODELS + nModel );
}

const CString& CGameState::GetSoundName( const BYTE& nSound ) const
{
	ASSERT( nSound < MAX_SOUNDS );
	return m_arrConfigStrings.GetAt( CS_SOUNDS + nSound );
}

const CString& CGameState::GetImageName( const BYTE& nImage ) const
{
	ASSERT( nImage < MAX_IMAGES );
	return m_arrConfigStrings.GetAt( CS_IMAGES + nImage );
}

const CString& CGameState::GetLightStyle( const BYTE& nStyle ) const
{
	ASSERT( nStyle < MAX_LIGHTSTYLES );
	return m_arrConfigStrings.GetAt( CS_LIGHTS + nStyle );
}

const CString& CGameState::GetItemName( const BYTE& nItem ) const
{
	ASSERT( nItem < MAX_ITEMS );
	return m_arrConfigStrings.GetAt( CS_ITEMS + nItem );
}

const CString& CGameState::GetPlayerSkin( const BYTE& nPlayer ) const
{
	ASSERT( nPlayer < MAX_CLIENTS );
	return m_arrConfigStrings.GetAt( CS_PLAYERSKINS + nPlayer );
}

void CGameState::GetConfigString( const WORD& nIndex, CString& strTarget ) const
{
	ASSERT( nIndex < MAX_CONFIGSTRINGS );
	strTarget = m_arrConfigStrings.GetAt(nIndex);
}

void CGameState::GetModelName( const BYTE& nModel, CString& strTarget ) const
{
	ASSERT( nModel < MAX_MODELS );
	strTarget = m_arrConfigStrings.GetAt( CS_MODELS + nModel );
}

void CGameState::GetSoundName( const BYTE& nSound, CString& strTarget ) const
{
	ASSERT( nSound < MAX_SOUNDS );
	strTarget = m_arrConfigStrings.GetAt( CS_SOUNDS + nSound );
}

void CGameState::GetImageName( const BYTE& nImage, CString& strTarget ) const
{
	ASSERT( nImage < MAX_IMAGES );
	strTarget = m_arrConfigStrings.GetAt( CS_IMAGES + nImage );
}

void CGameState::GetLightStyle( const BYTE& nStyle, CString& strTarget ) const
{
	ASSERT( nStyle < MAX_LIGHTSTYLES );
	strTarget = m_arrConfigStrings.GetAt( CS_LIGHTS + nStyle );
}

void CGameState::GetItemName( const BYTE& nItem, CString& strTarget ) const
{
	ASSERT( nItem < MAX_ITEMS );
	strTarget = m_arrConfigStrings.GetAt( CS_ITEMS + nItem );
}

void CGameState::GetPlayerSkin( const BYTE& nPlayer, CString& strTarget ) const
{
	ASSERT( nPlayer < MAX_CLIENTS );
	strTarget = m_arrConfigStrings.GetAt( CS_PLAYERSKINS + nPlayer );
}

CEntity* CGameState::GetEntity( const WORD nEntity )
{
	ASSERT( nEntity < MAX_EDICTS );
	if ( m_pEdicts[nEntity] == NULL )
	{
		//m_pEdicts[nEntity] = new CEntity;
		BeginLevel();
	}
	return (m_pEdicts[nEntity]);
}

CPlayer* CGameState::GetPlayer( const WORD nPlayer )
{
	ASSERT( nPlayer <= m_nClients );
	if ( m_bReady )
	{
		return ((CPlayer*)(m_pEdicts[nPlayer+1]));
	}
	return NULL;
}

CBot* CGameState::GetBot()
{
	return &m_botClient;
}

//////////////////////////////////////////////////////////////////////
// Reverse Lookup Operations
//////////////////////////////////////////////////////////////////////

BOOL CGameState::FindImageName( const CString& strFindMe, BYTE& nIndex ) const
{
	register nCount;

	for (nCount = 0; nCount < MAX_IMAGES; nCount++)
	{
		CString& strCurrent = m_arrConfigStrings.GetAt( CS_IMAGES + nCount );
		if ( strCurrent == strFindMe )
		{
			nIndex = nCount;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameState::FindItemName( const CString& strFindMe, BYTE& nIndex ) const
{
	register nCount;

	for (nCount = 0; nCount < MAX_ITEMS; nCount++)
	{
		CString& strCurrent = m_arrConfigStrings.GetAt( CS_ITEMS + nCount );
		if ( strCurrent == strFindMe )
		{
			nIndex = nCount;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameState::FindModelName( const CString& strFindMe, BYTE& nIndex ) const
{
	register nCount;

	for (nCount = 0; nCount < MAX_MODELS; nCount++)
	{
		CString& strCurrent = m_arrConfigStrings.GetAt( CS_MODELS + nCount );
		if ( strCurrent == strFindMe )
		{
			nIndex = nCount;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameState::FindSoundName( const CString& strFindMe, BYTE& nIndex ) const
{
	register nCount;

	for (nCount = 0; nCount < MAX_SOUNDS; nCount++)
	{
		CString& strCurrent = m_arrConfigStrings.GetAt( CS_SOUNDS + nCount );
		if ( strCurrent == strFindMe )
		{
			nIndex = nCount;
			return TRUE;
		}
	}
	return FALSE;
}


//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CGameState::ParsePlayerInfo( const BYTE nPlayer )
{
	CPlayer*	pInfo	= GetPlayer( nPlayer );
	CString		strInfo	= m_arrConfigStrings.GetAt( CS_PLAYERSKINS + nPlayer );

	ASSERT( pInfo != NULL );
	if ( strInfo.GetLength() )
	{
		CString	strTemp	= strInfo.SpanExcluding( NAME_SKIN_DIVIDER );

		pInfo->SetName( strTemp );
		strTemp = strInfo.Right( strInfo.GetLength() - strTemp.GetLength() -  strlen(NAME_SKIN_DIVIDER) );
		pInfo->SetSkin( strTemp );
	}
	else
	{
		pInfo->SetName( _T("") );
		pInfo->SetSkin( _T("") );
	}
}

BOOL CGameState::NewFrame( const UINT& nFrameNum, const UINT& nOldFrame )
{
	if ( !m_bReady )
	{
		return FALSE;
	}
	else
	{
		register	nCount;
	
		for ( nCount = 0 ; nCount < MAX_EDICTS ; nCount++ )
		{
			(m_pEdicts[nCount])->NewFrame( nFrameNum, nOldFrame );
		}
		m_nFrameNumber = nFrameNum;
		return TRUE;
	}
}

void CGameState::Clear()
{
	register nCount;

	m_nClients = 0;
	m_nBotNumber = 0;
	for (nCount = 0; nCount < MAX_EDICTS ; nCount++)
	{
		m_pEdicts[nCount] = NULL;
	}
	m_arrConfigStrings.RemoveAll();
	m_arrConfigStrings.SetSize( MAX_CONFIGSTRINGS );
	m_bReady = FALSE;
}

void CGameState::Reset()
{
	register nCount;

	for ( nCount = 0; nCount < MAX_EDICTS ; nCount++ )
	{
		if ( (m_pEdicts[nCount] != NULL) && (m_pEdicts[nCount] != &m_botClient) )
		{
			delete m_pEdicts[nCount];
		}
	}
	m_botClient.Reset();
	Clear();
}

void CGameState::BeginLevel()
{
	register	nCount;
	CString		strTemp;
	CEntity*	pTemp = NULL;

	ASSERT( m_bReady == FALSE );
	// GameState is now ready  to be used
	m_bReady = TRUE;
	// Decode the Max Number of clients
	strTemp = m_arrConfigStrings.GetAt( CS_MAXCLIENTS );
	m_nClients = ((BYTE)(atoi( strTemp.GetBuffer(strTemp.GetLength()) )));
	ASSERT( m_nClients > 0 );

	// Create the "world" entity
	ASSERT( m_pEdicts[0] == NULL );
	m_pEdicts[0] = new CEntity;
	(m_pEdicts[0])->SetEntityNumber( 0 );
	// Create the player entities
	for (nCount = 1; nCount <= m_nClients; nCount++)
	{
		ASSERT( m_pEdicts[nCount] == NULL );
		if ( nCount == m_nBotNumber+1 )
		{
			m_pEdicts[nCount] = &m_botClient;
		}
		else
		{
			m_pEdicts[nCount] = new CPlayer;
		}
		(m_pEdicts[nCount])->SetEntityNumber( nCount );
		((CPlayer*)(m_pEdicts[nCount]))->SetPlayerNumber( nCount-1 );
		ParsePlayerInfo( nCount-1 );
	}
	// Create the rest of the game objects
	for (nCount = m_nClients+1; nCount < MAX_EDICTS; nCount++)
	{
		ASSERT( m_pEdicts[nCount] == NULL );
		m_pEdicts[nCount] = new CEntity;
		(m_pEdicts[nCount])->SetEntityNumber( nCount );
	}
}