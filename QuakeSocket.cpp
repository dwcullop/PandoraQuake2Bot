//	QuakeSocket.cpp : implementation for the CQuakeSocket						
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

#include "StdAfx.h"
#include "Pandora.h"
#include "QuakeSocket.h"
#include "QuakeConnect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CQuakeSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CQuakeSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket Definitions

#ifdef _DEBUG
	//#define DUMP_PACKETS_IN
	//#define DUMP_PACKETS_OUT
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket Constructor / Destructor

CQuakeSocket::CQuakeSocket()
{
	register int nCount;

	for ( nCount = 0; nCount < PING_HISTORY_SIZE ; nCount++ )
	{
		m_nPingHistory[nCount] = 0;
	}
	m_nPing = 0;
	m_nPingHistoryIndex = 0;
	m_nPacketLoss = 0.0f;
	m_pCurrentReliable = NULL;
	m_pNextReliable = NULL;
	Reset();
	m_pConnect = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket Public member functions

void CQuakeSocket::CheckReliable()
{
	if ( (m_bNeedAck) && (GetLastSent() > 0.2) && (GetLastReceived() > 0.2) )
	{
		SendKeepAlive();
	}
}

void CQuakeSocket::CheckSend()
{
	if ( GetLastSent() > 1.0 )
	{
		SendKeepAlive();
	}
	if ( GetLastReceived() > 2.0 )
	{
		m_pConnect->ProcessTimeOut();
		m_tLastReceived.SetCurrent();
	}
}

void CQuakeSocket::Disconnect()
{
	Close();
	Reset();
}

const float& CQuakeSocket::GetPacketLoss()
{
	if ( m_nReceive || m_nReliablesSent )
	{
		m_nPacketLoss = ( (float)(m_nReceive - m_nTotalReceived + m_nReliablesLost) );
		m_nPacketLoss /= ( (float)(m_nReceive + m_nReliablesSent) );
		m_nPacketLoss *= 100.0f;
		if ( m_nPacketLoss > 100.0f )
		{
			m_nPacketLoss = 100.0f;
		}
	}
	return m_nPacketLoss;
}

void CQuakeSocket::Init( const UINT& nPort )
{
	ASSERT(m_hSocket == INVALID_SOCKET);
	ClearStats();
	if (!CreateSocket(nPort))
	{
		// If the specified port is unavailable, have the OS pick one
		if ((GetLastError() != WSAEADDRINUSE) || (!CreateSocket(0)))
		{
			TRACE("Socket Creation Failed!\n");
			DisplayError();
		}
	}
	if (!( GetSockName(m_strLocalIP, m_nLocalPort) ))
	{
		TRACE("Get Socket Name Failed!\n");
		DisplayError();
	}
}

void CQuakeSocket::OnReceive( int nErrorCode ) 
{
	CQuakePacket*	pNewData = new CQuakePacket;
	WORD			nReceived;

	Lock();
	nReceived = Receive( pNewData->GetDataPtr(), MAX_PACKET_LENGTH );
	if ( nReceived != SOCKET_ERROR )
	{
		m_tLastReceived.SetCurrent();
		pNewData->SetSize( nReceived );
		pNewData->SetReadMode();
#ifdef DUMP_PACKETS_IN
		afxDump << "Data Received: (Processed)\n";
		pNewData->Dump(afxDump);
#endif  // DUMP_PACKETS_IN
		ProcessDataPacket( pNewData );
	}
	else
	{
		DisplayError();
	}
	Unlock();
	CAsyncSocket::OnReceive( nErrorCode );
}

void CQuakeSocket::SendConnectionless( const CString& strMessage )
{
	CQuakePacket*	pConnectionless = new CQuakePacket;
	register int	nCounter = 0;

	pConnectionless->WriteLong( -1 );
	while ( nCounter < strMessage.GetLength() )
	{
		pConnectionless->WriteChar( strMessage[nCounter++] );
	}
	Lock();
	m_tCurrentPacket.SetCurrent();
	SendData( pConnectionless );
	m_strConnectionless = strMessage;
	m_nConnectionlessSent++;
	Unlock();
}

void CQuakeSocket::SendReliable( CQuakePacket* pSendMe )
{
	pSendMe->CheckLength();
	Lock();
	if ( m_pCurrentReliable == NULL )
	{
		m_pCurrentReliable = new CQuakePacket;
		m_pCurrentReliable->InsertData( *pSendMe );
		m_pCurrentReliable->SetSize( pSendMe->GetSize() );

		SendPacket( pSendMe, TRUE );
	}
	else
	{
		if ( m_pNextReliable == NULL )
		{
			m_pNextReliable = pSendMe;
		}
		else
		{
			m_pNextReliable->InsertData( *pSendMe );
			delete pSendMe;
		}
	}
	Unlock();
}

void CQuakeSocket::SendUnreliable( CQuakePacket* pSendMe )
{
	pSendMe->CheckLength();
	SendPacket( pSendMe, FALSE );
}

void CQuakeSocket::SetRemoteInfo( const CString& strRemoteInfo, const WORD& nDefaultPort )
{
	CString strTemp;

	m_strRemoteIP = strRemoteInfo.SpanExcluding(":");
	m_nRemotePort = nDefaultPort;
	strTemp = strRemoteInfo.Right( strRemoteInfo.GetLength() - m_strRemoteIP.GetLength() - 1 );
	if ( strTemp.GetLength() )
	{
		m_nRemotePort = (WORD)atol( strTemp.GetBuffer(7) );
		strTemp.ReleaseBuffer();
	}
	m_tLastSent.SetCurrent();
	m_tLastReceived.SetCurrent();
	Connect( m_strRemoteIP, m_nRemotePort );
}

void CQuakeSocket::ClearStats()
{
	m_nConnectionlessSent		= 0;
	m_nConnectionlessReceived	= 0;
	m_nTotalSent				= 0;
	m_nTotalReceived			= 0;
	m_nSend						= 0;
	m_nReceive					= 0;
	m_nReliableLastSent			= 0;
	m_nReliablesSent			= 0;
	m_nReliablesLost			= 0;
	m_bNeedAck					= FALSE;
	m_bLastReliable				= FALSE;
	m_bNextReliable				= FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket Private member functions

void CQuakeSocket::SendKeepAlive()
{
	CQuakePacket* pNew = new CQuakePacket;

	SendPacket( pNew, FALSE );
}

BOOL CQuakeSocket::CreateSocket(const UINT& nPort)
{
	return Create( nPort, SOCK_DGRAM, (FD_READ | FD_WRITE | FD_CLOSE) );
}

void CQuakeSocket::DisplayError()
{
	TRACE( "Windows Socket Error #%d : ", GetLastError() );
	switch( GetLastError() )
	{
	case WSANOTINITIALISED:
		TRACE("Winsock Not Initialized");
		break;
	case WSAENETDOWN:
		TRACE("Network subsystem failed");
		break;
	case WSAEACCES:
		TRACE("Requested address is a broadcast address, but flag not set");
		break;
	case WSAEAFNOSUPPORT:
		TRACE("Unsupported Address Family");
		break;
	case WSAEFAULT:
		TRACE("lpSockAddrLen argument was too small");
		break;
	case WSAEINPROGRESS:
		TRACE("A Blocking Socket operation is in progress");
		break;
	case WSAENETRESET:
		TRACE("Connect should be reset");
		break;
	case WSAEINVAL:
		TRACE("The socket has not been bound");
		break;
	case WSAENOTCONN:
		TRACE("Socket is not connected");
		break;
	case WSAENOTSOCK:
		TRACE("Descriptor is not a socket");
		break;
	case WSAEOPNOTSUPP:
		TRACE("MSG_OOB was specified, but socket is not SOCK_STREAM");
		break;
	case WSAEWOULDBLOCK:
		TRACE("Socket is non-blocking, ReceiveFrom would block");
		break;
	case WSAEMSGSIZE:
		TRACE("The datagram is too large for the buffer and was truncated");
		break;
	case WSAECONNABORTED:
		TRACE("Virtual circuit was aborted due to timeout or other failure");
		break;
	case WSAECONNRESET:
		TRACE("Virtual circuit was set by the remote side");
		break;
	case WSAEMFILE:
		TRACE("No more file descriptors are available");
		break;
	case WSAENOBUFS:
		TRACE("No Buffer Space is available");
		break;
	case WSAEPROTONOSUPPORT:
		TRACE("Specified port is not supported");
		break;
	case WSAEPROTOTYPE:
		TRACE("Specified port is the wrong type for this socket");
		break;
	case WSAESOCKTNOSUPPORT:
		TRACE("Specified Socket Type is not suppoted in this address family");
		break;
	case WSAEADDRNOTAVAIL:
		TRACE("Address not available from the local machine");
		break;
	case WSAEDESTADDRREQ:
		TRACE("Destination address is required");
		break;
	case WSAENETUNREACH:
		TRACE("The network cannot be reached from this host");
		break;
	case WSAESHUTDOWN:
		TRACE("The socket has been shut down");
		break;
	case WSAEADDRINUSE:
		TRACE("The specified address is already in use.");
		break;
	case WSAEISCONN:
		TRACE("Socket is already connected");
		break;
	case WSAETIMEDOUT:
		TRACE("Connection timed out!");
		break;
	default:
		TRACE("Unknown Error Type!");
		break;
	}
	TRACE("\n");
}

void CQuakeSocket::ResendReliable()
{
	if (m_pCurrentReliable != NULL)
	{
		CQuakePacket* pResendMe;

		if ( m_pNextReliable != NULL )
		{
			m_pCurrentReliable->InsertData( *m_pNextReliable );
			delete m_pNextReliable;
			m_pNextReliable = NULL;
		}
		m_nReliablesLost++;
		pResendMe = new CQuakePacket;
		pResendMe->InsertData( *m_pCurrentReliable );
		pResendMe->SetSize( m_pCurrentReliable->GetSize() );
		SendPacket( pResendMe, TRUE );
	}
}

void CQuakeSocket::ReliableReceived()
{
	if ( m_pCurrentReliable != NULL )
	{
		delete m_pCurrentReliable;
		if ( m_pNextReliable != NULL )
		{
			m_pCurrentReliable = new CQuakePacket;
			m_pCurrentReliable->InsertData( *m_pNextReliable );
			m_pCurrentReliable->SetSize( m_pNextReliable->GetSize() );
			SendPacket( m_pNextReliable, TRUE );
			m_pNextReliable = NULL;
		}
		else
		{
			m_pCurrentReliable = NULL;
		}
	}
}

void CQuakeSocket::ProcessDataPacket( CQuakePacket* pNew )
{
	UINT nSeq1;

	pNew->ReadLong( (long&)nSeq1 );
	// Test to see if it's a connectionless packet
	if (nSeq1 == -1)
	{
		m_nConnectionlessReceived++;
		m_tCurrentPacket = m_tCurrentPacket.Elapsed();
		m_nPingHistory[m_nPingHistoryIndex] = ( (WORD)((m_tCurrentPacket.GetValue() / 2.0) * 1000) );
		if ( m_nPingHistory[ PING_HISTORY_SIZE-1 ] )
		{
			register int	nCount;
			WORD			nSum = 0;

			for ( nCount = 0 ; nCount < PING_HISTORY_SIZE ; nCount++)
			{
				nSum += m_nPingHistory[nCount];
			}
			m_nPing = (nSum / PING_HISTORY_SIZE);
		}
		else
		{
			m_nPing = m_nPingHistory[m_nPingHistoryIndex];
		}
		if ( ++m_nPingHistoryIndex >= PING_HISTORY_SIZE )
		{
			m_nPingHistoryIndex = 0;
		}
		if ( pNew->DataToRead() )
		{
			CString strConnectionless;

			pNew->RemoveData(0, CONNECTIONLESS_HEADER_SIZE);
			pNew->SetReadMode();
			pNew->ReadString( strConnectionless );
			m_pConnect->ProcessConnectionless( strConnectionless );
		}
		delete pNew;
	}
	else
	{
		UINT nSeq2;

		pNew->ReadLong( (long&)nSeq2 );
		m_nTotalReceived++;
		m_nReceive = (nSeq1 & (~RELIABLE_FLAG));
		if (nSeq1 & RELIABLE_FLAG)
		{
			m_bLastReliable = (!m_bLastReliable);
			m_bNeedAck = TRUE;
		}
		else
		{
			m_bNeedAck = FALSE;
		}
		if ( (nSeq2 & (~RELIABLE_FLAG)) >= m_nReliableLastSent )
		{
			// The side should have received the last reliable
			if (m_bNextReliable)
			{
				// Reliable Flag should be set
				if (!( nSeq2 & RELIABLE_FLAG ))
				{
					// It isn't, so the packet was lost
					m_bNextReliable = FALSE;		// Adjust to match other side
					ResendReliable();
				}
				else
				{
					// It is, so the packet arrived safely
					ReliableReceived();
				}
			}
			else
			{
				// Reliable Flag shouldn't be set
				if ( nSeq2 & RELIABLE_FLAG )
				{
					// It is set anyway, so the packet was lost
					m_bNextReliable = TRUE;		// Adjust to match other side
					ResendReliable();
				}
				else
				{
					// It isn't, so the packet arrived safely
					ReliableReceived();
				}
			}
		}
		if ( pNew->DataToRead() )
		{
			pNew->RemoveData( 0, PACKET_HEADER_SIZE );
			pNew->SetReadMode();
			m_pConnect->ProcessDataPacket( pNew );
		}
		delete pNew;
	}
}

void CQuakeSocket::Reset()
{
	Lock();
	ClearStats();
	m_strRemoteIP	= DEFAULT_IP;
	m_strConnectionless.Empty();
	if ( m_pCurrentReliable != NULL )
	{
		delete m_pCurrentReliable;
		m_pCurrentReliable = NULL;
	}
	if ( m_pNextReliable != NULL )
	{
		delete m_pNextReliable;
		m_pNextReliable = NULL;
	}
	Unlock();
}

void CQuakeSocket::SendPacket( CQuakePacket* pSendMe, const BOOL bReliable )
{
	UINT			nSeq1, nSeq2;
	CQuakePacket	qpHeader;

	pSendMe->CheckLength();
	nSeq1 = ++m_nSend;
	if ( bReliable )
	{
		m_nReliableLastSent = nSeq1;
		nSeq1 |= RELIABLE_FLAG;
		m_bNextReliable = (!m_bNextReliable);
		m_nReliablesSent++;
	}
	nSeq2 = m_nReceive;
	if ( m_bLastReliable )
	{
		nSeq2 |= RELIABLE_FLAG;
	}
	qpHeader.WriteLong( nSeq1 );
	qpHeader.WriteLong( nSeq2 );
	if ( GetQPort() )
	{
		qpHeader.WriteShort( GetQPort() );
	}
	qpHeader.CheckLength();
	pSendMe->PrependData( qpHeader );
	m_nTotalSent++;
	SendData(pSendMe);
}

void CQuakeSocket::SendData(CQuakePacket* pSendMe)
{
	ASSERT( m_pConnect != NULL );
	pSendMe->CheckLength();
	if ( Send(pSendMe->GetDataPtr(), pSendMe->GetSize()) == SOCKET_ERROR )
	{
		TRACE("Unable to send datagram!\n");
		DisplayError();
	}
	else
	{
		m_tLastSent.SetCurrent();
	}
#ifdef DUMP_PACKETS_OUT
	afxDump << "Data Sent:\n";
	pSendMe->Dump(afxDump);
#endif
	delete pSendMe;
}


/////////////////////////////////////////////////////////////////////////////