// TextMessage.h: interface for the CTextMessage class.
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

#if !defined(AFX_TEXTMESSAGE_H__D05094A3_CE42_11D1_AF1A_0060080A5FD2__INCLUDED_)
#define AFX_TEXTMESSAGE_H__D05094A3_CE42_11D1_AF1A_0060080A5FD2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SystemObject.h"
#include "PandoraDefs.h"

class CTextMessage : public CSystemObject  
{
	DECLARE_DYNCREATE(CTextMessage);

// Attributes
private:
	CString		m_strText;
	BYTE		m_nType;

// Construction / Destruction
public:
	CTextMessage()							{ m_nType = PRINT_OTHER; };
	virtual ~CTextMessage()					{};

// Data Manipulation
public:
	const CString& GetText() const			{ return m_strText; };
	const BYTE& GetType() const				{ return m_nType; };
	void SetText(const CString& strNew)		{ m_strText = strNew; };
	void SetType(const BYTE& nNew)			{ m_nType = nNew; };
	CString& GetSetText()					{ return m_strText; };
	BYTE& GetSetType()						{ return m_nType; };
	void GetFiltered( CString& ) const;
	CString GetFiltered() const;

};

#endif // !defined(AFX_TEXTMESSAGE_H__D05094A3_CE42_11D1_AF1A_0060080A5FD2__INCLUDED_)
