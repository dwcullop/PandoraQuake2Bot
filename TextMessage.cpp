// TextMessage.cpp: implementation of the CTextMessage class.
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
#include "TextMessage.h"
#include "PandoraDefs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CTextMessage
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE( CTextMessage, CSystemObject )

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	// Defined Inline

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

CString CTextMessage::GetFiltered() const
{
	CString strReturnMe;

	GetFiltered( strReturnMe );
	return strReturnMe;
}

void CTextMessage::GetFiltered( CString& strFiltered ) const
{
	BYTE		nCurrent;
	register	nCount;
	WORD		nLength	= m_strText.GetLength();

	strFiltered = m_strText;
	for (nCount = 0; nCount < nLength; nCount++)
	{
		nCurrent = strFiltered.GetAt(nCount);
		if (nCurrent > 127)
		{
			nCurrent -= 128;
		}
		else
		{
			switch (nCurrent)
			{
			case 0x00:
				nCurrent = ((BYTE)(0x20));	// A Space Character In ASCII
				break;
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
				nCurrent = ((BYTE)(0x00));
				break;
			case 0x0B:
			case 0x0E:
			case 0x7F:
				nCurrent = '_';
				break;
			case 0x05:
			case 0x0F:
			case 0x1C:
				nCurrent = '.';
				break;
			case 0x10:
				nCurrent = '[';
				break;
			case 0x11:
				nCurrent = ']';
				break;
			// Conversion of Numerical Characters
			case 0x12:
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1A:
			case 0x1B:
				nCurrent += 0x1E;
				break;
			case 0x1D:
				nCurrent = '<';
				break;
			case 0x1E:
				nCurrent = '=';
				break;
			case 0x1F:
				nCurrent = '>';
				break;
			}
		}
		strFiltered.SetAt( nCount, nCurrent );
	}
}