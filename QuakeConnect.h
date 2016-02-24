// QuakeConnect.h: interface for the CQuakeConnect class.
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

#if !defined(AFX_QUAKECONNECT_H__DFA0B5F2_DAD8_11D1_AF1D_0060080A5FD2__INCLUDED_)
#define AFX_QUAKECONNECT_H__DFA0B5F2_DAD8_11D1_AF1D_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "QuakeSocket.h"
#include "QuakePacket.h"
#include "PandoraDefs.h"

enum ConnectStatus	{ csNotConnected, csConnecting, csConnected, csLevelChange };

class CQuakeConnect  
{
// Attributes
protected:
	BYTE			m_nTimeOuts;
	CQuakeSocket	m_qsSocket;
	ConnectStatus	m_csStatus;

// Construction / Destruction
public:
	CQuakeConnect();
	virtual ~CQuakeConnect()									{};

// Data Manipulation
public:
	CQuakeSocket*			GetSocket()							{ return &m_qsSocket; };
	const ConnectStatus&	GetStatus()							{ return m_csStatus; };

// Overridables
public:
	virtual void ProcessConnectionless( const CString& )		{ m_nTimeOuts = 0; };
	virtual void ProcessDataPacket( CQuakePacket* )				{ m_nTimeOuts = 0; };

protected:
	virtual void ProcessErrorMessage( const UINT& )				{};
	virtual void OnDisconnected();
	virtual void SendDisconnect() = 0;

// Operations
public:
	void ProcessTimeOut();

protected:
	BYTE	ComputeChecksum( CQuakePacket*, const UINT& ) const;
	void	Disconnect();

private:
	WORD	DoChecksumCRC( BYTE*, BYTE ) const;

};

#endif // !defined(AFX_QUAKECONNECT_H__DFA0B5F2_DAD8_11D1_AF1D_0060080A5FD2__INCLUDED_)
