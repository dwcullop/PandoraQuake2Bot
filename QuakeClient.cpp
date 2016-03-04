// QuakeClient.cpp: implementation of the CQuakeClient class.
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
#include "QuakeClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
	#define PACKET_TYPE_DEBUG
#endif

#ifdef PACKET_TYPE_DEBUG
	#define PACKET_TYPE_TRACE	::AfxTrace
#else
	#define PACKET_TYPE_TRACE	(void)0
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuakeClient::CQuakeClient()
{
	m_tTotalConnect.SetValue( 0.0 );
	m_qsSocket.SetClientMode();
	m_nRefFrame = 0;
	m_nFrameNumber = 0;
	m_nRetries = 0;
	m_nRetriesMax = 0;
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CQuakeClient::Connect(const CString& strConnectInfo)
{
	m_strRemoteInfo = strConnectInfo;
	OnPreConnect();
	SendChallengeRequest();
}

void CQuakeClient::DisplayText( const UINT& nResID )
{
	DisplayText( CString((LPCSTR)nResID) );
}

void CQuakeClient::DisplayText( const CString& strText )
{
	CTextMessage* pDisplay = new CTextMessage;

	pDisplay->SetText( strText );
	ProcessDisplayText( pDisplay );
}

void CQuakeClient::GetConnectTime( CString& strTime ) const
{
	if ( m_csStatus == csConnected )
	{
		CAdvTime tTemp( m_tCurrentConnect.Elapsed() + m_tTotalConnect );

		tTemp.GetString( strTime );
	}
	else
	{
		m_tTotalConnect.GetString( strTime );
	}
}

void CQuakeClient::Say(const CString& strSayText)
{
	CString strMessage;

	strMessage.Format( CString((LPCSTR)IDS_CMD_SAY), strSayText );
	SendStringCmd( strMessage );
}

void CQuakeClient::SayTeam(const CString& strSayText)
{
	CString strMessage;

	strMessage.Format( CString((LPCSTR)IDS_CMD_SAYTEAM), strSayText );
	SendStringCmd( strMessage );
}

void CQuakeClient::SendMove( const CBotMove& rNewMove )
{
	m_mlMoves.NewMove( rNewMove, GetBot()->GetPlayerInfo().GetDeltaAngles() );
	SendMove();
}

void CQuakeClient::Wave( const BYTE nWaveType )
{
	CString strFormat;
	CString strWaveCmd;

	strFormat.LoadString( IDS_FMT_CMD_WAVE );
	strWaveCmd.Format( strFormat, nWaveType );
	SendStringCmd( strWaveCmd );
}

//////////////////////////////////////////////////////////////////////
// Overrides
//////////////////////////////////////////////////////////////////////

void CQuakeClient::OnDisconnected()
{
	CQuakeConnect::OnDisconnected();
	m_tTotalConnect += m_tCurrentConnect.Elapsed();
	Reset();
	m_nRetries = 0;
}

void CQuakeClient::ProcessConnectionless( const CString& strMessage )
{
	CString strCommand = strMessage.SpanExcluding(" ");

	if ( m_csStatus != csConnected )
	{
		CString strTemp;

		strTemp.LoadString( IDS_CMD_CHALLENGE_ACCEPT );
		if ( strCommand == strTemp )
		{
			strCommand = strMessage.Right( strMessage.GetLength() - strCommand.GetLength() - 1 );
			SendConnectRequest( strCommand );
		}
		else
		{
			strTemp.LoadString( IDS_CMD_CONNECT_RESPONSE );
			if ( strCommand == strTemp )
			{
				SendStringCmd( IDS_CMD_NEW );
			}
			else
			{
				if ( m_csStatus != csLevelChange )
				{
					DisplayText( strMessage );
					if (m_nRetries < m_nRetriesMax)
					{
						m_nRetries++;
						m_qsSocket.ResendLastConnectionless();
					}
					else
					{
						Disconnect();
					}
				}
			}
		}
	}
	else
	{
		// TODO: Write code to parse the "Status" responses
	}
}

void CQuakeClient::ProcessDataPacket( CQuakePacket* pData )
{
	BYTE nMessageID;

	PACKET_TYPE_TRACE("*** Begin Server Data Decode ***\n");
	Lock();
	while ( pData->DataToRead() )
	{
		nMessageID = pData->ReadByte();
		switch( nMessageID )
		{
		case SVC_BAD:
			ProcessErrorMessage( IDS_ERR_SVC_BAD );
			OnServerReadError( pData );
			break;
		case SVC_MUZZLEFLASH:
			PACKET_TYPE_TRACE("\tGot a SVC_MUZZLEFLASH!\n");
			DecodeMuzzleFlash( pData );
			break;
		case SVC_MUZZLFLASH2:
			PACKET_TYPE_TRACE("\tGot a SVC_MUZZLFLASH2!\n");
			DecodeMuzzleFlash2( pData );
			break;
		case SVC_TEMP_ENTITY:
			PACKET_TYPE_TRACE("\tGot a SVC_TEMP_ENTITY!\n");
			DecodeTempEntity( pData );
			break;
		case SVC_LAYOUT:
			PACKET_TYPE_TRACE("\tGot a SVC_LAYOUT!\n");
			DecodeLayout( pData );
			break;
		case SVC_INVENTORY:
			PACKET_TYPE_TRACE("\tGot a SVC_INVENTORY!\n");
			DecodeInventory( pData );
			break;
		case SVC_NOP:
			PACKET_TYPE_TRACE("\tGot a SVC_NOP!\n");
			OnServerNoOp();
			break;
		case SVC_DISCONNECT:
			PACKET_TYPE_TRACE("\tGot a SVC_DISCONNECT!\n");
			OnServerDisconnect();
			pData->SkipToEnd();
			break;
		case SVC_RECONNECT:
			PACKET_TYPE_TRACE("\tGot a SVC_RECONNECT!\n");
			OnServerReconnect();
			pData->SkipToEnd();
			break;
		case SVC_SOUND:
			PACKET_TYPE_TRACE("\tGot a SVC_SOUND!\n");
			DecodeSound( pData );
			break;
		case SVC_PRINT:
			PACKET_TYPE_TRACE("\tGot a SVC_PRINT!\n");
			DecodePrint( pData );
			break;
		case SVC_STUFFTEXT:
			PACKET_TYPE_TRACE("\tGot a SVC_STUFFTEXT!\n");
			DecodeStuffText( pData );
			break;
		case SVC_SERVERDATA:
			PACKET_TYPE_TRACE("\tGot a SVC_SERVERDATA!\n");
			DecodeServerData( pData );
			break;
		case SVC_CONFIGSTRING:
			PACKET_TYPE_TRACE("\tGot a SVC_CONFIGSTRING!\n");
			DecodeConfigString( pData );
			break;
		case SVC_SPAWNBASELINE:
			PACKET_TYPE_TRACE("\tGot a SVC_SPAWNBASELINE!\n");
			DecodeSpawnBaseline( pData );
			break;
		case SVC_CENTERPRINT:
			PACKET_TYPE_TRACE("\tGot a SVC_CENTERPRINT!\n");
			DecodeCenterPrint( pData );
			break;
		case SVC_DOWNLOAD:
			PACKET_TYPE_TRACE("\tGot a SVC_DOWNLOAD!\n");
			DecodeDownload( pData );
			break;
		case SVC_PLAYERINFO:
			PACKET_TYPE_TRACE("\tGot a SVC_PLAYERINFO!\n");
			DecodePlayerInfo( pData );
			break;
		case SVC_PACKETENTITIES:
			PACKET_TYPE_TRACE("\tGot a SVC_PACKETENTITIES!\n");
			DecodePacketEntities( pData );
			break;
		case SVC_DELTAPACKETENTITIES:
			PACKET_TYPE_TRACE("\tGot a SVC_DELTAPACKETENTITIES!\n");
			DecodeDeltaPacketEntities( pData );
			break;
		case SVC_FRAME:
			PACKET_TYPE_TRACE("\tGot a SVC_FRAME!\n");
			DecodeFrame( pData );
			break;
		default:
			ProcessErrorMessage( IDS_ERR_UNKNOWN_MESSAGE );
			OnServerReadError( pData );
			break;
		}
	}
	PACKET_TYPE_TRACE("*** End Server Data Decode ***\n");
	Unlock();
}

void CQuakeClient::SendDisconnect()
{
	SendStringCmd( IDS_CMD_DISCONNECT );
}

//////////////////////////////////////////////////////////////////////
// Overridables
//////////////////////////////////////////////////////////////////////

void CQuakeClient::OnLevelChange()
{
	m_csStatus = csLevelChange;
	Reset();
	SendStringCmd( IDS_CMD_NEW );
	m_tTotalConnect += m_tCurrentConnect.Elapsed();
	m_nFrameNumber = -1;
	//OnServerBeginLevel();
}

void CQuakeClient::OnPreConnect()
{
	if ( m_csStatus == csConnected )
	{
		Disconnect();
	}
	Reset();
	m_qsSocket.Disconnect();
	m_qsSocket.Init( DEFAULT_CLIENT_PORT );
	m_qsSocket.SetRemoteInfo( m_strRemoteInfo, DEFAULT_SERVER_PORT );
}

void CQuakeClient::OnServerBeginLevel()
{
	m_csStatus = csConnected;
	DisplayText( IDS_CONNECTED );
	m_mlMoves.BeginLevel();
//	BeginLevel();
	m_tCurrentConnect.SetCurrent();
}

void CQuakeClient::OnServerDisconnect()
{
	DisplayText( IDS_DISCONNECTED );
	OnDisconnected();
}

void CQuakeClient::OnServerReadError( CQuakePacket* pData )
{
	ProcessErrorMessage( IDS_ERR_NETWORK_READ );
	pData->SkipToEnd();
	SendDisconnect();
}

void CQuakeClient::OnServerReconnect()
{
	DisplayText( IDS_RECONNECT );
	OnPreConnect();
	SendChallengeRequest();
}

void CQuakeClient::ProcessCenterText( const CString& strCenter )
{
	TRACE("Center: %s\n", strCenter);
}

void CQuakeClient::ProcessDisplayText( CTextMessage* pDisplay )
{
	ASSERT( pDisplay != NULL );
	TRACE("Display Message: %s\n", pDisplay->GetText());
	delete pDisplay;
}

void CQuakeClient::ProcessLayout( const CString& strLayout )
{
	TRACE("Layout: %s\n", strLayout);
}

void CQuakeClient::ProcessPrint( CTextMessage* pPrintMe )
{
	ASSERT( pPrintMe != NULL );
	TRACE("Print Message: %s\n", pPrintMe->GetText());
	delete pPrintMe;
}

void CQuakeClient::ProcessSound( CSound* pSound )
{
	ASSERT( pSound != NULL );
	delete pSound;
}

void CQuakeClient::ProcessStuffText( const CString& strCmd )
{
	CString strTemp;

	strTemp.LoadString( IDS_CMD_RECONNECT );
	if ( strCmd.Left(strTemp.GetLength()) == strTemp )
	{
		OnLevelChange();
	}
	else
	{
		strTemp.LoadString( IDS_CMD_PRECACHE );
		if ( strCmd.Left(strTemp.GetLength()) == strTemp )
		{
			CString strTemp2;

			strTemp2 = strCmd.Right( strCmd.GetLength() - strTemp.GetLength() );
			strTemp.LoadString( IDS_CMD_BEGIN );
			SendStringCmd( strTemp + strTemp2 );
			OnServerBeginLevel();
		}
		else
		{
			strTemp.LoadString( IDS_CMD_CONSOLE );
			if ( strCmd.Left(strTemp.GetLength()) == strTemp )
			{
				CString strTemp2;
				
				strTemp2 = strCmd.Right( strCmd.GetLength() - strTemp.GetLength() );
				//strTemp2.TrimRight();
				//strTemp2.TrimLeft();
				SendStringCmd( strTemp2 );
			}
		}
	}
}

void CQuakeClient::ProcessTempEntity( CTempEntity* pTempEnt )
{
	ASSERT( pTempEnt != NULL );
	delete pTempEnt;
}

/////////////////////////////////////////////////////////////////////////////
// CQuakeClient private operations

// Send Functions
void CQuakeClient::SendChallengeRequest()
{
	CString strConnect;

	m_csStatus = csConnecting;
	strConnect.LoadString( IDS_CMD_CHALLENGE_REQUEST );
	m_qsSocket.SendConnectionless( strConnect );
}

void CQuakeClient::SendConnectRequest(const CString& strChallengeID)
{
	CString strConnect;

	strConnect.Format( "%s %d %d %s \"%s\"\n", 
		CString( (LPCSTR)IDS_CMD_CONNECT_REQUEST ), PROTOCOL_VERSION,
		m_qsSocket.GetQPort(), strChallengeID, GetClientStats());
	m_qsSocket.SendConnectionless( strConnect );
}

void CQuakeClient::SendNoOp()
{
	CQuakePacket* pNoOp = new CQuakePacket;

	pNoOp->WriteByte( CLC_NOP );
	m_qsSocket.SendUnreliable( pNoOp );
}

void CQuakeClient::SendStringCmd(const CString& strCmd)
{
	CQuakePacket* pStringCmd = new CQuakePacket;

	pStringCmd->WriteByte( CLC_STRINGCMD );
	pStringCmd->WriteString( strCmd );
	m_qsSocket.SendReliable( pStringCmd );
}

void CQuakeClient::SendStringCmd(const UINT& nResID)
{
	CString strTemp;

	strTemp.LoadString( nResID );
	SendStringCmd( strTemp );
}

void CQuakeClient::SendUserInfo(const CString& strInfo)
{
	CQuakePacket* pUserInfo = new CQuakePacket;

	pUserInfo->WriteByte( CLC_USERINFO );
	pUserInfo->WriteString( strInfo );
	m_qsSocket.SendReliable( pUserInfo );
}

void CQuakeClient::SendMove()
{
	if (m_csStatus == csConnected)
	{
		CQuakePacket*	pSendMove;
		CMoveData*		pToSend;
		BYTE			nCheckSum;
		BYTE			nRenderTime;
		register int	nCount;

		pSendMove = new CQuakePacket;
		pSendMove->WriteLong( GetFrameNumber() );
		m_mlMoves.Lock();
		for (nCount = 0; nCount < MOVE_FRAMES ; nCount++)
		{
			pToSend = m_mlMoves.GetMoveFrame( nCount );
			ASSERT( pToSend != NULL );
			pSendMove->WriteByte( pToSend->GetBitMask() );
			if ( pToSend->IsFlagSet(BM_PITCH) )
			{
				pSendMove->WriteShort( pToSend->GetPitch() );
			}
			if ( pToSend->IsFlagSet(BM_YAW) )
			{
				pSendMove->WriteShort( pToSend->GetYaw() );
			}
			if ( pToSend->IsFlagSet(BM_ROLL) )
			{
				pSendMove->WriteShort( pToSend->GetRoll() );
			}
			if ( pToSend->IsFlagSet(BM_FORWARD) )
			{
				pSendMove->WriteShort( pToSend->GetForward() );
			}
			if ( pToSend->IsFlagSet(BM_RIGHT) )
			{
				pSendMove->WriteShort( pToSend->GetRight() );
			}
			if ( pToSend->IsFlagSet(BM_UP) )
			{
				pSendMove->WriteShort( pToSend->GetUp() );
			}
			if ( pToSend->IsFlagSet(BM_BUTTONS) )
			{
				pSendMove->WriteByte( pToSend->GetButtons() );
			}
			if ( pToSend->IsFlagSet(BM_IMPULSE) )
			{
				pSendMove->WriteByte( pToSend->GetImpulse() );
			}
			nRenderTime = pToSend->GetMilliseconds();
			if ( nRenderTime == 0 )
			{
				TRACE( "Zero Render Time\n" );
				nRenderTime = ((BYTE)((double)m_tLastMove.Elapsed() * 1000));
				m_tLastMove.SetCurrent();
				pToSend->SetMilliseconds( nRenderTime );
			}
			pSendMove->WriteByte( nRenderTime );
			pSendMove->WriteByte( pToSend->GetLighting() );
		}
		m_mlMoves.Unlock();
		UINT nSeqNum = m_qsSocket.GetNextSequenceNumber();
		while ((nSeqNum % 0x798) > 0x794)
		{
			m_qsSocket.SkipSequenceNumber();
			nSeqNum = m_qsSocket.GetNextSequenceNumber();
		}
		nCheckSum = ComputeChecksum( pSendMove, nSeqNum );
		pSendMove->Insert( nCheckSum );
		pSendMove->Insert( CLC_MOVE );
		m_qsSocket.SendUnreliable( pSendMove );
		OnMoveSent();
	}
}

// Receive Functions
void CQuakeClient::DecodeMuzzleFlash( CQuakePacket* pData )
{
	WORD		nPlayer = pData->ReadShort();
	BYTE		nEffect = pData->ReadByte();
	CEntity*	pEntity = GetEntity( nPlayer );

	if (pEntity == NULL)
	{
		ProcessErrorMessage( IDS_ERR_MUZZLEFLASH );
	}
	else
	{
		pEntity->SetMuzzleFlash( nEffect );
		OnMuzzleFlash( nPlayer );
	}
}

void CQuakeClient::DecodeMuzzleFlash2( CQuakePacket* pData )
{
	WORD		nEntity = pData->ReadShort();
	BYTE		nEffect = pData->ReadByte();
	CEntity*	pEntity = GetEntity( nEntity );

	if (pEntity == NULL)
	{
		ProcessErrorMessage( IDS_ERR_MUZZLEFLASH2 );
	}
	else
	{
		pEntity->SetMuzzleFlash2( nEffect );
		OnMuzzleFlash2( nEntity );
	}
}

void CQuakeClient::DecodeTempEntity( CQuakePacket* pData )
{
	CTempEntity*	pNew = new CTempEntity;

	pData->ReadByte( pNew->GetSetType() );
	switch( pNew->GetType() )
	{
	// point entity
	case TE_EXPLOSION1:
	case TE_EXPLOSION2:
	case TE_ROCKET_EXPLOSION:
	case TE_GRENADE_EXPLOSION:
	case TE_ROCKET_EXPLOSION_WATER:
	case TE_GRENADE_EXPLOSION_WATER:
	case TE_BFG_EXPLOSION:
	case TE_BFG_BIGEXPLOSION:
	case TE_BOSSTPORT:
		pData->ReadVector( pNew->GetSetOrigin() );
		break;
	// impact entity
	case TE_GUNSHOT:
	case TE_BLOOD:
	case TE_BLASTER:
	case TE_SHOTGUN:
	case TE_SPARKS:
	case TE_SCREEN_SPARKS:
	case TE_SHIELD_SPARKS:
	case TE_BULLET_SPARKS:
	case TE_GREENBLOOD:
		pData->ReadVector( pNew->GetSetOrigin() );
		pData->ReadByte( pNew->GetSetDirectionIndex() );
		break;
	// line entity
	case TE_RAILTRAIL:
	case TE_BUBBLETRAIL:
	case TE_BFG_LASER:
	case TE_PLASMATRAIL:
		pData->ReadVector( pNew->GetSetOrigin() );
		pData->ReadVector( pNew->GetSetEndPosition() );
		break;
	// special entity
	case TE_SPLASH:
		pData->ReadByte( pNew->GetSetCount() );
		pData->ReadVector( pNew->GetSetOrigin() );
		pData->ReadByte( pNew->GetSetDirectionIndex() );
		pData->ReadByte( pNew->GetSetSounds() );
		break;
	case TE_LASER_SPARKS:
	case TE_WELDING_SPARKS:
		pData->ReadByte( pNew->GetSetCount() );
		pData->ReadVector( pNew->GetSetOrigin() );
		pData->ReadByte( pNew->GetSetDirectionIndex() );
		pData->ReadByte( pNew->GetSetColor() );
		break;
	case TE_PARASITE_ATTACK:
	case TE_MEDIC_CABLE_ATTACK:
		pData->ReadWord( pNew->GetSetEntity() );
		pData->ReadVector( pNew->GetSetOrigin() );
		pData->ReadVector( pNew->GetSetEndPosition() );
		break;  
	case TE_GRAPPLE_CABLE:
		pData->ReadWord( pNew->GetSetEntity() );
		pData->ReadVector( pNew->GetSetOrigin() );
		pData->ReadVector( pNew->GetSetEndPosition() );
		pData->ReadVector( pNew->GetSetOffset() );
		break;
	default:
		TRACE("UNKNOWN TEMP ENTITY: %d\r\n", pNew->GetType());
		ProcessErrorMessage( IDS_ERR_UNKNOWN_TEMP_ENTITY );
		delete pNew;
		pNew = NULL;
		OnServerReadError( pData );
		break;
	}
	if ( pNew != NULL )
	{
		ProcessTempEntity( pNew );
	}
}

void CQuakeClient::DecodeLayout( CQuakePacket* pData )
{
	CString strTemp;

	pData->ReadString( strTemp );
	ProcessLayout( strTemp );
}

void CQuakeClient::DecodeInventory( CQuakePacket* pData )
{
	CBot*		pBot = GetBot();
	register int	nCount;
	WORD		nAmount;

	for (nCount = 0; nCount < MAX_ITEMS; nCount++)
	{
		nAmount = pData->ReadShort();
		pBot->SetItemCount( nCount, nAmount );
	}
	OnUpdateInventory();
}

void CQuakeClient::DecodeSound( CQuakePacket* pData )
{
	CSound*	pNew = new CSound;
	BYTE	nBitMask;
	
	pData->ReadByte( nBitMask );
	pData->ReadByte( pNew->GetSetSoundIndex() );
	// Read the volume level
	if (nBitMask & 0x01)
	{
		pNew->SetVolume( ((float)pData->ReadByte() / ((float)255.0)) );
	}
	else
	{
		pNew->SetVolume( 1.0 );
	}
	// Read the Attenuation
	if (nBitMask & 0x02)
	{
		pNew->SetAttenuation( pData->ReadByte() >> 6 );
	}
	else
	{
		pNew->SetAttenuation( 1 );
	}
	// Read the TimeOffset
	if (nBitMask & 0x10)
	{
		pData->ReadByte( pNew->GetSetTimeOffset() );
	}
	if (nBitMask & 0x08)
	{
		pData->ReadWord( pNew->GetSetEntity_Channel() );
	}
	if (nBitMask & 0x04)
	{
		pData->ReadVector( pNew->GetSetOrigin() );
	}
	ProcessSound( pNew );
}

void CQuakeClient::DecodePrint( CQuakePacket* pData )
{
	CTextMessage* pPrint = new CTextMessage;

	pData->ReadByte( pPrint->GetSetType() );
	pData->ReadString( pPrint->GetSetText() );
	ProcessPrint( pPrint );
}

void CQuakeClient::DecodeStuffText( CQuakePacket* pData )
{
	CString			strTemp;
	CString			strCmd;

	pData->ReadString( strTemp );
	while ( strTemp.GetLength() )
	{
		strCmd = strTemp.SpanExcluding(";");
		strTemp = strTemp.Right( strTemp.GetLength() - strCmd.GetLength() - 1 );
		strCmd.TrimRight();
		strCmd.TrimLeft();
		ProcessStuffText( strCmd );
		if ( strTemp.GetLength() )
		{
			strCmd = strTemp.SpanIncluding(";");
			strTemp = strTemp.Right( strTemp.GetLength() - strCmd.GetLength() );
			strTemp.TrimRight();
			strTemp.TrimLeft();
		}
	}
}

void CQuakeClient::DecodeServerData( CQuakePacket* pData )
{
	pData->ReadLong( m_nServerVersion );
	if ( m_nServerVersion != PROTOCOL_VERSION )
	{
		TRACE("Incorrect server version: %d\r\n", m_nServerVersion);
		ProcessErrorMessage( IDS_ERR_INCORRECT_SERVER_VERSION );
		OnServerDisconnect();
	}
	else
	{
		pData->ReadLong( m_nLevelKey );
		pData->ReadByte( m_nIsDemo );
		pData->ReadString( m_strGameDir );
		pData->ReadWord( GetSetBotNumber() );
		pData->ReadString( m_strMapName );
		OnUpdateServerData();
	}
}

void CQuakeClient::DecodeConfigString( CQuakePacket* pData )
{
	WORD	nIndex		= pData->ReadShort();
	CString	strConfig	= pData->ReadString();

	SetConfigString( nIndex, strConfig );
}

void CQuakeClient::DecodeSpawnBaseline( CQuakePacket* pData )
{
	UINT nBitMask;
	WORD nEntity;

	DecodeEntityHeader( pData, nEntity, nBitMask );
	DecodeEntityState( pData, (GetEntity(nEntity))->GetBaseline(), nBitMask );
}

void CQuakeClient::DecodeCenterPrint( CQuakePacket* pData )
{
	CString strTemp;

	pData->ReadString( strTemp );
	ProcessCenterText( strTemp );
}

void CQuakeClient::DecodeDownload( CQuakePacket* pData )
{
	TRACE("Received Download Message!\r\n");
	ProcessErrorMessage( IDS_ERR_SVC_DOWNLOAD );
	OnServerReadError( pData );
}

void CQuakeClient::DecodePlayerInfo( CQuakePacket* pData )
{
	CPlayerInfo*	pCurrent = GetBot()->GetPlayerInfoPtr();
	UINT			nBitMask = pData->ReadShort();
	register int	nCount;

	// TODO: #define the bitmask values
	if (nBitMask & 0x0001)
	{
		pData->ReadByte( pCurrent->GetSetMoveType() );
	}
	if (nBitMask & 0x0002)
	{
		pCurrent->SetOrigin( pData->ReadVector() );
	}
	if (nBitMask & 0x0004)
	{
		pCurrent->SetVelocity( pData->ReadVector() );
	}
	if (nBitMask & 0x0008)
	{
		pData->ReadByte( pCurrent->GetSetMoveTime() );
	}
	if (nBitMask & 0x0010)
	{
		pData->ReadByte( pCurrent->GetSetMoveFlags() );
	}
	if (nBitMask & 0x0020)
	{
		pData->ReadWord( pCurrent->GetSetGravity() );
	}
	if (nBitMask & 0x0040)
	{
		pData->ReadAngles16( pCurrent->GetSetDeltaAngles() );
	}
	if (nBitMask & 0x0080)
	{
		pCurrent->GetSetViewOffset().SetX( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetViewOffset().SetY( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetViewOffset().SetZ( pData->ReadChar() / ((float)4.0) );
	}
	if (nBitMask & 0x0100)
	{
		pData->ReadAngles16( pCurrent->GetSetViewAngles() );
	}
	if (nBitMask & 0x0200)
	{
		pCurrent->GetSetKickAngles().SetX( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetKickAngles().SetY( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetKickAngles().SetZ( pData->ReadChar() / ((float)4.0) );
	}
	if (nBitMask & 0x1000)
	{
		pCurrent->SetGunIndex( pData->ReadByte() );
	}
	if (nBitMask & 0x2000)
	{
		pData->ReadByte( pCurrent->GetSetGunFrame() );
		pCurrent->GetSetGunOffset().SetX( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetGunOffset().SetY( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetGunOffset().SetZ( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetGunAngles().SetX( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetGunAngles().SetY( pData->ReadChar() / ((float)4.0) );
		pCurrent->GetSetGunAngles().SetZ( pData->ReadChar() / ((float)4.0) );
	}
	if (nBitMask & 0x0400)
	{
		for (nCount = 0 ; nCount < MAX_BLENDS ; nCount++)
		{
			pCurrent->GetSetBlend(nCount) = ( pData->ReadByte() / ((float)255.0) );
		}
	}
	if (nBitMask & 0x0800)
	{
		pData->ReadByte( pCurrent->GetSetFOV() );
	}
	if (nBitMask & 0x4000)
	{
		pData->ReadByte( pCurrent->GetSetRenderFlags() );
	}
	// Read in the Stat Fields
	pData->ReadLong( (long&)nBitMask );
	for (nCount = 0 ; nCount < MAX_STATS ; nCount++)
	{
		if (nBitMask & (0x00000001 << nCount))
		{
			pCurrent->SetStat( nCount, pData->ReadShort() );
		}
	}
}

void CQuakeClient::DecodePacketEntities( CQuakePacket* pData )
{
	CEntityState*	pCurrent;
	CEntity*		pEntity;
	UINT			nBitMask;
	WORD			nEntity;

	DecodeEntityHeader( pData, nEntity, nBitMask);
	while ( nEntity )
	{
		pEntity = GetEntity( nEntity );
		ASSERT( pEntity != NULL );
		pEntity->BeforeUpdate( m_nFrameNumber, m_nRefFrame );
		pCurrent = pEntity->GetCurrent();
		DecodeEntityState( pData, pCurrent, nBitMask );
		if ( pCurrent->GetActive() )
		{
			OnUpdateEntityActive( nEntity );
		}
		else
		{
			OnUpdateEntityRemove( nEntity );
		}
		pEntity->AfterUpdate();
		DecodeEntityHeader( pData, nEntity, nBitMask );
	}
}

void CQuakeClient::DecodeDeltaPacketEntities( CQuakePacket* pData )
{
	ProcessErrorMessage( IDS_ERR_SVC_DELTAPACKETENTITIES );
	OnServerReadError( pData );
}

void CQuakeClient::DecodeFrame( CQuakePacket* pData )
{
	BYTE	nCount;

	pData->ReadUInt( m_nFrameNumber );
	pData->ReadUInt( m_nRefFrame );
	// Skip the odd byte added in protocol version 31
	pData->ReadByte();
	// Read in the visibility list
		// TODO : Store / use this information
		pData->ReadByte( nCount );
		while ( nCount-- )
		{
			pData->ReadByte();
		}
	// Process the new frame information
	if (!NewFrame( m_nFrameNumber, m_nRefFrame ))
	{
		ProcessErrorMessage( IDS_ERR_NEW_FRAME );
		OnServerReadError( pData );
	}
	//	m_mlMoves.ComputeDeltaOrigin( 2.0f * (m_qsSocket.GetPing() / 1000.0f) );
	//		The above line has been changed to:
	m_mlMoves.ComputeDeltaOrigin( (m_qsSocket.GetPing() / 500.0f) );
	TRACE("\tNew DeltaOrigin: %s\n", GetDeltaOrigin().GetString() );
}

void CQuakeClient::DecodeEntityHeader( CQuakePacket* pData, WORD& nEntity, UINT& nBitMask )
{
	nBitMask = pData->ReadByte();
	if (nBitMask & 0x00000080)
	{
		nBitMask |= (pData->ReadByte() <<  8);
	}
	if (nBitMask & 0x00008000)
	{
		nBitMask |= (pData->ReadByte() << 16);
	}
	if (nBitMask & 0x00800000)
	{
		nBitMask |= (pData->ReadByte() << 24);
	}
	nEntity = (nBitMask & 0x00000100) ? pData->ReadShort() : pData->ReadByte();
}

void CQuakeClient::DecodeEntityState( CQuakePacket* pData, CEntityState* pNew, const UINT& nBitMask )
{
	if (nBitMask & 0x00000040)
	{
		pNew->SetActive( FALSE );
	}
	else
	{
		pNew->SetActive( TRUE );
	}
	if (nBitMask & 0x00000800)
	{
		pNew->SetModelIndex( pData->ReadByte() );
	}
	if (nBitMask & 0x00100000)
	{
		pData->ReadByte( pNew->GetSetModelIndex2() );
	}
	if (nBitMask & 0x00200000)
	{
		pData->ReadByte( pNew->GetSetModelIndex3() );
	}
	if (nBitMask & 0x00400000)
	{
		pData->ReadByte( pNew->GetSetModelIndex4() );
	}
	if (nBitMask & 0x00000010)
	{
		pNew->SetFrame( pData->ReadByte() );
	}
	if (nBitMask & 0x00020000)
	{
		pNew->SetFrame( pData->ReadWord() );
	}
	if (nBitMask & 0x00010000)
	{
		if (nBitMask & 0x02000000)
		{
			pData->ReadUInt( pNew->GetSetSkinNum() );
		}
		else
		{
			pNew->SetSkinNum( pData->ReadByte() );
		}
	}
	else
	{
		if (nBitMask & 0x02000000)
		{
			pNew->SetSkinNum( pData->ReadShort() );
		}
	}
	if (nBitMask & 0x00004000)
	{
		if (nBitMask & 0x00080000)
		{
			pNew->SetEffects( pData->ReadLong() );
		}
		else
		{
			pNew->SetEffects( pData->ReadByte() );
		}
	}
	else
	{
		if (nBitMask & 0x00080000)
		{
			pNew->SetEffects( pData->ReadShort() );
		}
	}
	if (nBitMask & 0x00001000)
	{
		if (nBitMask & 0x00040000)
		{
			pNew->SetRenderFX( pData->ReadLong() );
		}
		else
		{
			pNew->SetRenderFX( pData->ReadByte() );
		}
	}
	else
	{
		if (nBitMask & 0x00040000)
		{
			pNew->SetRenderFX( pData->ReadShort() );
		}
	}

	CVector vTemp = pNew->GetOrigin();
	
	if (nBitMask & 0x00000001)
	{
		pData->ReadCoord( vTemp.GetSetX() );
	}
	if (nBitMask & 0x00000002)
	{
		pData->ReadCoord( vTemp.GetSetY() );
	}
	if (nBitMask & 0x00000200)
	{
		pData->ReadCoord( vTemp.GetSetZ() );
	}
	if ( nBitMask & (0x00000001 | 0x00000002 | 0x00000200) )
	{
		pNew->SetOrigin( vTemp );
	}
	if (nBitMask & 0x00000400)
	{
		pData->ReadAngle( pNew->GetSetAngles().GetSetX() );
	}
	if (nBitMask & 0x00000004)
	{
		pData->ReadAngle( pNew->GetSetAngles().GetSetY() );
	}
	if (nBitMask & 0x00000008)
	{
		pData->ReadAngle( pNew->GetSetAngles().GetSetZ() );
	}
	if (nBitMask & 0x01000000)
	{
		pData->ReadVector( pNew->GetSetOldOrigin() );
	}
	if (nBitMask & 0x04000000)
	{
		pData->ReadByte( pNew->GetSetSound() );
	}
	if (nBitMask & 0x00000020)
	{
		pNew->SetEvent( pData->ReadByte() );
	}
	if (nBitMask & 0x08000000)
	{
		pData->ReadWord( pNew->GetSetSolid() );
	}
}

CString CQuakeClient::GetClientStats() const
{
	CString strFormat;
	CString strReturnMe;

	strFormat.LoadString( IDS_FMT_CLIENT_INFO );
	strReturnMe.Format( strFormat, m_nMsgLevel, m_nRate, m_nFOV, m_strSkin, m_strName, m_nHand );
	return strReturnMe;
}
