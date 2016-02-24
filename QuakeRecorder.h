// QuakeRecorder.h: interface for the CQuakeRecorder class.
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

#if !defined(AFX_QUAKERECORDER_H__A17626D2_F508_11D1_AF24_0060080A5FD2__INCLUDED_)
#define AFX_QUAKERECORDER_H__A17626D2_F508_11D1_AF24_0060080A5FD2__INCLUDED_

#include "QuakePacket.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CQuakeRecorder  
{
// Attributes
private:
	CString		m_strPath;
	BOOL		m_bFileOpen;
	CFile		m_fDemoFile;

// Construction / Destruction
public:
	CQuakeRecorder();
	virtual ~CQuakeRecorder();

// Data Manipulation
public:
	void	SetPath( const CString& strNew )					{ m_strPath = strNew; };

// Operations
public:
	void	NextFile()											{ CloseFile(); OpenFile(); };
	void	OpenFile();
	void	CloseFile();
	void	WriteBlock( CQuakePacket* );

private:
	void	SetFileName();

};

#endif // !defined(AFX_QUAKERECORDER_H__A17626D2_F508_11D1_AF24_0060080A5FD2__INCLUDED_)
