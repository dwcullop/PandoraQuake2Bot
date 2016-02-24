// MoveData.h: interface for the CMoveData class.
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

#if !defined(AFX_MOVEDATA_H__56D8D833_EF41_11D1_AF23_0060080A5FD2__INCLUDED_)
#define AFX_MOVEDATA_H__56D8D833_EF41_11D1_AF23_0060080A5FD2__INCLUDED_

//////////////////////////////////////////////////////////////////////
// CMoveData Includes
//////////////////////////////////////////////////////////////////////

#include "AdvTime.h"
#include "Vector.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CMoveData Defines
//////////////////////////////////////////////////////////////////////

#define	BM_PITCH			0x01
#define BM_YAW				0x02
#define BM_ROLL				0x04
#define BM_FORWARD			0x08
#define BM_RIGHT			0x10
#define BM_UP				0x20
#define BM_BUTTONS			0x40
#define BM_IMPULSE			0x80
#define DEFAULT_LIGHTING	0x80
#define DEFAULT_BITMASK		(BM_PITCH | BM_YAW | BM_ROLL | BM_FORWARD | BM_RIGHT | BM_UP | BM_BUTTONS | BM_IMPULSE)

//////////////////////////////////////////////////////////////////////
// CMoveData Class Definition
//////////////////////////////////////////////////////////////////////

class CMoveData  
{
// Attributes
private:
	BYTE		m_nBitMask;
	short		m_nPitch;
	short		m_nYaw;
	short		m_nRoll;
	short		m_nForward;
	short		m_nRight;
	short		m_nUp;
	BYTE		m_nButtons;
	BYTE		m_nImpulse;
	BYTE		m_nMilliseconds;
	BYTE		m_nLighting;

// Constructor / Destructor
public:
	CMoveData( const CMoveData* pCopy )						{ Copy( pCopy ); };
	CMoveData();
	virtual ~CMoveData();

// Data Manipulation
public:
	const BYTE&		GetBitMask() const						{ return m_nBitMask; };
	const short&	GetPitch() const						{ return m_nPitch; };
	const short&	GetYaw() const							{ return m_nYaw; };
	const short&	GetRoll() const							{ return m_nRoll; };
	const short&	GetForward() const						{ return m_nForward; };
	const short&	GetRight() const						{ return m_nRight; };
	const short&	GetUp() const							{ return m_nUp; };
	const BYTE&		GetButtons() const						{ return m_nButtons; };
	const BYTE&		GetImpulse() const						{ return m_nImpulse; };
	const BYTE&		GetMilliseconds() const					{ return m_nMilliseconds; };
	const BYTE&		GetLighting() const						{ return m_nLighting; };

	void			SetBitMask( const BYTE& nNew )			{ m_nBitMask		= nNew; };
	void			SetPitch( const short& nNew )			{ m_nPitch			= nNew; };
	void			SetYaw( const short& nNew )				{ m_nYaw			= nNew; };
	void			SetRoll( const short& nNew )			{ m_nRoll			= nNew; };	
	void			SetForward( const short& nNew )			{ m_nForward		= nNew; };
	void			SetRight( const short& nNew )			{ m_nRight			= nNew; };
	void			SetUp( const short& nNew )				{ m_nUp				= nNew; };
	void			SetButtons( const BYTE& nNew )			{ m_nButtons		= nNew; };
	void			SetImpulse( const BYTE& nNew )			{ m_nImpulse		= nNew; };
	void			SetMilliseconds( const BYTE& nNew )		{ m_nMilliseconds	= nNew; };
	void			SetLighting( const BYTE& nNew )			{ m_nLighting		= nNew; };

// Operations
public:
	BOOL			IsFlagSet( const BYTE& nFlag )			{ return ( m_nBitMask & nFlag ); };
	void			Clear();
	void			Copy( const CMoveData* );
	void			CreateBitMask( const CMoveData* = NULL );

private:
	void			SetFlag( const BYTE& nFlag )			{ m_nBitMask |= nFlag; };

};

#endif // !defined(AFX_MOVEDATA_H__56D8D833_EF41_11D1_AF23_0060080A5FD2__INCLUDED_)
