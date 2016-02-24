// GameState.h: interface for the CGameState class.
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

#if !defined(AFX_GAMESTATE_H__CA903385_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_GAMESTATE_H__CA903385_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_

#include "Bot.h"
#include "Player.h"
#include "Entity.h"
//#include "EntityState.h"
#include "PandoraDefs.h"
#include <AfxMT.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGameState  
{
// Attributes
private:
	BYTE				m_nClients;
	WORD				m_nBotNumber;
	UINT				m_nFrameNumber;
	CBot				m_botClient;
	CEntity*			m_pEdicts[MAX_EDICTS];
	CStringArray		m_arrConfigStrings;
	BOOL				m_bReady;

	CCriticalSection	m_csLock;

// Construction / Destruction
public:
	CGameState();
	virtual ~CGameState();

// Data Manipulation
public:
	const BYTE		GetClientCount() const							{ return m_nClients; };
	const UINT&		GetFrameNumber() const							{ return m_nFrameNumber; };
	WORD&			GetSetBotNumber()								{ return m_nBotNumber; };
	BOOL			IsReady() const									{ return m_bReady; };
	void			SetConfigString(const WORD&, const CString&);
	const CString&	GetConfigString( const WORD& ) const;
	const CString&	GetModelName( const BYTE& ) const;
	const CString&	GetSoundName( const BYTE& ) const;
	const CString&	GetImageName( const BYTE& ) const;
	const CString&	GetLightStyle( const BYTE& ) const;
	const CString&	GetItemName( const BYTE& ) const;
	const CString&	GetPlayerSkin( const BYTE& ) const;
	void			GetConfigString( const WORD&, CString& ) const;
	void			GetModelName( const BYTE&, CString& ) const;
	void			GetSoundName( const BYTE&, CString& ) const;
	void			GetImageName( const BYTE&, CString& ) const;
	void			GetLightStyle( const BYTE&, CString& ) const;
	void			GetItemName( const BYTE&, CString& ) const;
	void			GetPlayerSkin( const BYTE&, CString& ) const;
	CEntity*		GetEntity( const WORD );
	CPlayer*		GetPlayer( const WORD );
	CBot*			GetBot();

// Reverse Lookup Operations
public:
	BOOL			FindModelName( const CString&, BYTE& ) const;
	BOOL			FindSoundName( const CString&, BYTE& ) const;
	BOOL			FindImageName( const CString&, BYTE& ) const;
	BOOL			FindItemName( const CString&, BYTE& ) const;

// Operations
public:
	void BeginLevel();
	void Clear();
	BOOL NewFrame( const UINT&, const UINT& );
	void ParsePlayerInfo( const BYTE );
	void Reset();

// Multithreaded Protection
public:
	void Lock()					{ m_csLock.Lock(); };
	void Unlock()				{ m_csLock.Unlock(); };
};

#endif // !defined(AFX_GAMESTATE_H__CA903385_CF11_11D1_AF1C_0060080A5FD2__INCLUDED_)
