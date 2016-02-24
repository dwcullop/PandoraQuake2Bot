//	QuakeSocket.h : interface for the CQuakeSocket								
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

#if !defined(AFX_QUAKESOCKET_H__9C4E6BD1_E0EC_11D0_BDF3_0000C06F1BB9__INCLUDED_)
#define AFX_QUAKESOCKET_H__9C4E6BD1_E0EC_11D0_BDF3_0000C06F1BB9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxsock.h>
#include "QuakePacket.h" 
#include "AdvTime.h"
#include "PandoraDefs.h"

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket Defines

#define PING_HISTORY_SIZE	5

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket class types

class CQuakeConnect;

/////////////////////////////////////////////////////////////////////////////
// CQuakeSocket Definition

class CQuakeSocket : public CAsyncSocket
{
// Attributes
private:
	// Stats for Connectless packets
	UINT				m_nConnectionlessSent;
	UINT				m_nConnectionlessReceived;
	// Stats for Connection Based Packets
	UINT				m_nTotalSent;
	UINT				m_nTotalReceived;
	UINT				m_nSend;
	UINT				m_nReceive;
	UINT				m_nReliableLastSent;
	UINT				m_nReliablesSent;
	UINT				m_nReliablesLost;
	BOOL				m_bLastReliable;
	BOOL				m_bNextReliable;
	BOOL				m_bNeedAck;
	// Other QuakeSocket info
	CQuakePacket*		m_pCurrentReliable;
	CQuakePacket*		m_pNextReliable;
	WORD				m_nQPort;
	CString				m_strRemoteIP;
	CString				m_strLocalIP;
	UINT				m_nRemotePort;
	UINT				m_nLocalPort;
	CAdvTime			m_tLastReceived;
	CAdvTime			m_tLastSent;
	CString				m_strConnectionless;
	CCriticalSection	m_csLock;
	CQuakeConnect*		m_pConnect;
	float				m_nPacketLoss;
	// Used for computing Ping Time
	CAdvTime			m_tCurrentPacket;
	WORD				m_nPingHistory[PING_HISTORY_SIZE];
	BYTE				m_nPingHistoryIndex;
	WORD				m_nPing;

// Construction / Destruction
public:
	CQuakeSocket();
	virtual ~CQuakeSocket()								{ Disconnect(); };

// Data Manipulation
public:
	// Get Data Functions
	const UINT		GetNextSequenceNumber() const		{ return (m_nSend+1); };
	const CString&	GetLocalIP() const					{ return m_strLocalIP; };
	const UINT&		GetLocalPort() const				{ return m_nLocalPort; };
	const CString&	GetRemoteIP() const					{ return m_strRemoteIP; };
	const UINT&		GetRemotePort() const				{ return m_nRemotePort; };
	double			GetLastReceived() const				{ return m_tLastReceived.Elapsed().GetValue(); };
	double			GetLastSent() const					{ return m_tLastSent.Elapsed().GetValue(); };
	const WORD&		GetQPort() const					{ return m_nQPort; };
	const WORD&		GetPing() const						{ return m_nPing; };
	const float&	GetPacketLoss();
	// Set Data Functions
	void			SetConnector(CQuakeConnect* pNew)	{ m_pConnect = pNew; };
	void			SetRemoteInfo(const CString&, const WORD&);
	void			ClearStats();

// Operations
public:
	void	ResendLastConnectionless()					{ SendConnectionless( m_strConnectionless ); };
	void	SkipSequenceNumber()						{ m_nSend++; };
	void	SetClientMode()								{ m_nQPort = (rand() % USHRT_MAX) + 1; };
	void	SetServerMode()								{ m_nQPort = 0; };
	void	CheckReliable();
	void	CheckSend();
	void	Disconnect();
	void	Init( const UINT& nPort );
	void	SendConnectionless( const CString& );
	void	SendReliable( CQuakePacket* );
	void	SendUnreliable( CQuakePacket* );

private:
	void Lock()											{ m_csLock.Lock(); };
	void Unlock()										{ m_csLock.Unlock(); };
	void ResendReliable();
	void ReliableReceived();
	void SendKeepAlive();
	BOOL CreateSocket( const UINT& );
	void Reset();
	void ProcessDataPacket( CQuakePacket* );
	void DisplayError();
	void SendPacket( CQuakePacket*, const BOOL bReliable = TRUE );
	void SendData( CQuakePacket* );

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuakeSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CQuakeSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUAKESOCKET_H__9C4E6BD1_E0EC_11D0_BDF3_0000C06F1BB9__INCLUDED_)
