// QuakeClient.h: interface for the CQuakeClient class.
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

#if !defined(AFX_QUAKECLIENT_H__3F622862_D2DB_11D1_AF1C_0060080A5FD2__INCLUDED_)
#define AFX_QUAKECLIENT_H__3F622862_D2DB_11D1_AF1C_0060080A5FD2__INCLUDED_

#include "GameState.h"
#include "QuakeConnect.h"
#include "AdvTime.h"
#include "TextMessage.h"
#include "TempEntity.h"
#include "Sound.h"
#include "MoveList.h"
#include "BotMove.h"
#include "MoveData.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define WAVE_FLIPOFF	0
#define WAVE_SALUTE		1
#define WAVE_TAUNT		2
#define WAVE_WAVE		3
#define WAVE_POINT		4

class CEntityState;

class CQuakeClient : public CQuakeConnect, public CGameState
{
// Attributes
protected:
	CMoveList		m_mlMoves;
	long			m_nServerVersion;
	long			m_nLevelKey;
	BYTE			m_nIsDemo;
	CString			m_strGameDir;
	CString			m_strMapName;
	UINT			m_nFrameNumber;
	UINT			m_nRefFrame;
	CString			m_strRemoteInfo;
	// Bot Settings
	BYTE			m_nRetriesMax;
	BYTE			m_nFPS;
	BYTE			m_nMsgLevel;
	UINT			m_nRate;
	BYTE			m_nFOV;
	BYTE			m_nHand;
	CString			m_strSkin;
	CString			m_strName;

private:
	CAdvTime		m_tCurrentConnect;
	CAdvTime		m_tTotalConnect;
	CAdvTime		m_tLastMove;
	BYTE			m_nRetries;

// Construction / Destruction
public:
	CQuakeClient();
	virtual ~CQuakeClient()										{ Disconnect(); };

// Data Manipulation
public:
	const CString&	GetBotName()								{ return m_strName; };
	const UINT&		GetFrameNumber()							{ return m_nFrameNumber; };

// Overrides
public:
	virtual void	ProcessConnectionless( const CString& );
	virtual void	ProcessDataPacket( CQuakePacket* );

protected:
	virtual void ProcessErrorMessage( const UINT& nResID )		{ CQuakeConnect::ProcessErrorMessage( nResID ); };
	virtual void OnDisconnected();
	virtual void SendDisconnect();

// Overridables
protected:
	virtual void OnMoveSent()									{};
	virtual void OnMuzzleFlash( const WORD )					{};
	virtual void OnMuzzleFlash2( const WORD )					{};
	virtual void OnServerNoOp()									{ SendNoOp(); };
	virtual void OnUpdateEntityActive( const WORD )				{};
	virtual void OnUpdateEntityRemove( const WORD )				{};
	virtual void OnUpdateInventory()							{};
	virtual void OnUpdatePlayerInfo( const UINT )				{};
	virtual void OnUpdatePlayerInfoStats( const UINT )			{};
	virtual void OnUpdateServerData()							{};

	virtual void OnLevelChange();
	virtual void OnPreConnect();
	virtual void OnServerBeginLevel();
	virtual void OnServerDisconnect();
	virtual void OnServerReadError( CQuakePacket* );
	virtual void OnServerReconnect();
	virtual void ProcessDisplayText( CTextMessage* );
	virtual void ProcessPrint( CTextMessage* );
	virtual void ProcessCenterText( const CString& );
	virtual void ProcessStuffText( const CString& );
	virtual void ProcessLayout( const CString& );
	virtual void ProcessTempEntity( CTempEntity* );
	virtual void ProcessSound( CSound* );

// Operations
public:
	float			GetAverageMoveTime() const							{ return m_mlMoves.AverageMoveTime(); };
	const CVector&	GetDeltaOrigin() const								{ return m_mlMoves.GetDeltaOrigin(); };
	// Communications Functions
	void ConsoleCommand( const CString& strC )					{ SendStringCmd( strC ); };
	void WaveFlipoff()											{ Wave( WAVE_FLIPOFF ); };
	void WavePoint()											{ Wave( WAVE_POINT ); };
	void WaveSalute()											{ Wave( WAVE_SALUTE ); };
	void WaveTaunt()											{ Wave( WAVE_TAUNT ); };
	void WaveWave()												{ Wave( WAVE_WAVE ); };
	void DisplayText( const UINT& );
	void DisplayText( const CString& );
	void GetConnectTime( CString& ) const;
	void Say( const CString& );
	void SayTeam( const CString& );
	void SendMove( const CBotMove& );
	void SendMove( CMoveData* );
	void Wave( const BYTE );

protected:
	void Connect( const CString& );
	void SendStringCmd( const CString& );
	void SendStringCmd( const UINT& );

private:
	// Send Functions
	void SendChallengeRequest();
	void SendConnectRequest( const CString& );
	void SendNoOp();
	void SendUserInfo( const CString& );
	void SendMove();
	// Receive Functions
	void DecodeMuzzleFlash( CQuakePacket* );
	void DecodeMuzzleFlash2( CQuakePacket* );
	void DecodeTempEntity( CQuakePacket* );
	void DecodeLayout( CQuakePacket* );
	void DecodeInventory( CQuakePacket* );
	void DecodeSound( CQuakePacket* );
	void DecodePrint( CQuakePacket* );
	void DecodeStuffText( CQuakePacket* );
	void DecodeServerData( CQuakePacket* );
	void DecodeConfigString( CQuakePacket* );
	void DecodeSpawnBaseline( CQuakePacket* );
	void DecodeCenterPrint( CQuakePacket* );
	void DecodeDownload( CQuakePacket* );
	void DecodePlayerInfo( CQuakePacket* );
	void DecodePacketEntities( CQuakePacket* );
	void DecodeDeltaPacketEntities( CQuakePacket* );
	void DecodeFrame( CQuakePacket* );
	void DecodeEntityHeader( CQuakePacket*, WORD&, UINT& );
	void DecodeEntityState( CQuakePacket*, CEntityState*, const UINT& );
	// Other Functions
	CString GetClientStats() const;
};

#endif // !defined(AFX_QUAKECLIENT_H__3F622862_D2DB_11D1_AF1C_0060080A5FD2__INCLUDED_)
