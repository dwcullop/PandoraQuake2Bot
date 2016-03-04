//	QuakePacket.cpp : implementation of the CQuakePacket class
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
#include "QuakePacket.h"
#include "PandoraDefs.h"
#include "NetUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Local Definitions

#ifdef _DEBUG
	// Include this for dumping extended information
	// or comment it out for just the standard stuff
	//#define DUMP_EXTENDED_INFO
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////
// CQuakePacket 

IMPLEMENT_DYNCREATE(CQuakePacket, CObject)

//////////////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Construction / Destruction

	// Defined Inline

//////////////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Operations

// Private Operations
void CQuakePacket::MergeBuffer(CQuakePacket& rOther, const WORD& nInsertPoint)
{
	GetDataArray().InsertAt(nInsertPoint, &rOther.GetDataArray());
	if (m_nPosition >= nInsertPoint)
	{
		m_nPosition += rOther.GetSize();
	}
}

void CQuakePacket::SetReadMode()
{
	m_bReadMode = TRUE;
	m_nPosition = 0;
}

void CQuakePacket::SetWriteMode()
{
	m_bReadMode = FALSE;
	m_nPosition = GetSize();
}

//////////////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Overrides

void CQuakePacket::Serialize(CArchive& ar)
{
	m_arrData.Serialize(ar);
}

//////////////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Diagnostics

#ifdef _DEBUG
void CQuakePacket::AssertValid() const
{
	ASSERT( (GetPosition() < GetSize()) );
	GetData().AssertValid();
	CObject::AssertValid();
}

void CQuakePacket::Dump(CDumpContext& dc) const
{
	// Standard Dumping Format
	dc << "CQuakePacket" << "\n";
	dc << "\tRead Mode:		" << (GetReadMode() ? _T("True") : _T("False") ) << "\n";
	dc << "\tPosition:		" << GetPosition() << "\n";
	// Special Format for displaying data in an easy (easier anyway) to read format

	CString			strTemp;
	CString			strHexData;
	CString			strRawData;
	BYTE			nCurrent;
	register int	nCounter;

#ifdef DUMP_EXTENDED_INFO
	DWORD	nCheckSum = 0;

	for ( nCounter = 0; ( nCounter < GetSize() ); nCounter++ )
	{
		nCheckSum += GetData().GetAt( nCounter );
	}
	strTemp.Format("Length: %d (0x%04X), CheckSum: %d (0x%04X)",
		GetSize(), GetSize(), nCheckSum, nCheckSum);
	dc << "\tData [" << strTemp << "]" << "\n";
#else
	dc << "\tData" << "\n";
#endif // DUMP_EXTENDED_INFO

	for ( nCounter = 0; ( nCounter < GetSize() ); nCounter++ )
	{
		if ((nCounter % 16) == 0)
		{
			// Format the "lead" information at the beginning of each line
			strHexData.Format("%05X:  ", nCounter);
			strRawData.Empty();
		}
		nCurrent = ( (BYTE) ( GetData().GetAt(nCounter) ) );
		strTemp.Format(" %02X", nCurrent);
		strHexData += strTemp;
		// If the current character is non-printable,
		// change it so it displays a decimal point instead
		if ((nCurrent <= 32) || (nCurrent >= 128))
		{
			nCurrent = '.';
		}
		strRawData += ( (char)(nCurrent) );
		// After processing 16 bytes of data, display the output to the screen
		if ( (nCounter % 16) == 15 )
		{
			dc << "\t" << strHexData << "\t\t" << strRawData << "\n";
			strHexData.Empty();
			strRawData.Empty();
		}
	}
	// If we stopped, and the last data set had not been printed out because
	// it was less than 16 bytes long, 
	// then print out the last one.
	if (!(strHexData.IsEmpty()))
	{
		// Make sure the string is as long as the other ones, so everything lines
		// up properly.  Here is where the number 56 comes from:
		//		8 for the lead information (5 digits, plus a colon and two spaces)
		//		3*16 for each byte of data (2 digits plus a space)
		// 8 + 48 = 56
		strTemp.Format("%-56s", strHexData);
		dc << "\t" << strTemp << "\t\t" << strRawData << "\n";
	}

	// Call the base class
		//CSystemObject::Dump(dc);
	CObject::Dump(dc);
}

#endif


//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Inline Functions

	///////////////////////////////////////////////////////////////////////////
	// CQuakePacket Operations

	void CQuakePacket::RemoveData(const WORD& nPosition, const WORD& nLength)
	{
		ASSERT(nPosition < GetSize());
		if (m_nPosition > nPosition)
		{
			if (nLength > m_nPosition)
			{
				m_nPosition = 0;
			}
			else
			{
				m_nPosition -= nLength;
			}
		}
		GetDataArray().RemoveAt(nPosition, nLength);
	}

	void CQuakePacket::PrependData(CQuakePacket& rOther)
	{
		MergeBuffer(rOther, 0);
	}

	void CQuakePacket::InsertData(CQuakePacket& rOther)
	{
		MergeBuffer(rOther, m_nPosition);
	}

	void CQuakePacket::Clear()
	{
		SetWriteMode();
		m_nPosition		= 0;
		m_arrData.RemoveAll();
		m_arrData.SetSize( MAX_PACKET_LENGTH, MAX_PACKET_LENGTH );
	}

	void CQuakePacket::Copy(const CQuakePacket& rCopyMe)
	{
	// TODO: Try and see if CopyMemory works or not
	//	CopyMemory( this, &rCopyMe, sizeof(rCopyMe) );

		m_bReadMode	= rCopyMe.GetReadMode();
		m_nPosition	= rCopyMe.GetSize();
		m_arrData.RemoveAll();
		m_arrData.SetSize(rCopyMe.GetData().GetSize());
		m_arrData.Append(rCopyMe.GetData());

	}

	BOOL CQuakePacket::DataToRead() const
	{
		if ((m_bReadMode) && (m_nPosition < GetSize()))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}	
	}

	//////////////////////////////////////////////////////////////////////////////
	// CQuakePacket Overloaded Operators

	CQuakePacket& CQuakePacket::operator=(const CQuakePacket& rCopyMe)
	{
		Copy(rCopyMe);
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Private Read/Write Functions

	BYTE CQuakePacket::GetByte()
	{
		ASSERT(GetReadMode() == TRUE);
		ASSERT(GetPosition() < GetDataArray().GetSize());
		return GetDataArray().GetAt(m_nPosition++);
	}

	void CQuakePacket::PutByte(const BYTE& nData)
	{
		ASSERT(GetReadMode() == FALSE);
		GetDataArray().SetAtGrow(m_nPosition++, nData);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Read Functions

	short CQuakePacket::ReadShort()
	{
		short nReturnMe;
		ReadShort(nReturnMe);
		return nReturnMe;
	}

	void CQuakePacket::ReadShort(short& nGet)
	{
		BYTE		*pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nGet; 
		for(nCount = 0; nCount < sizeof(short); nCount++)
		{
			pTemp[nCount] = GetByte();
		}
	}

	long CQuakePacket::ReadLong()
	{
		long nReturnMe;
		ReadLong(nReturnMe);
		return nReturnMe;
	}

	void CQuakePacket::ReadLong(long& nGet)
	{
		BYTE		*pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nGet; 
		for(nCount = 0; nCount < sizeof(long); nCount++)
		{
			pTemp[nCount] = GetByte();
		}
	}

	float CQuakePacket::ReadFloat()
	{
		float nReturnMe;
		ReadFloat(nReturnMe);
		return nReturnMe;
	}

	void CQuakePacket::ReadFloat(float& nGet)
	{
		BYTE*			pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nGet; 
		for(nCount = 0; nCount < sizeof(float); nCount++)
		{
			pTemp[nCount] = GetByte();
		}
	}

	float CQuakePacket::ReadCoord()
	{
		float nReturnMe;

		ReadCoord( nReturnMe );
		return nReturnMe;
	}

	void CQuakePacket::ReadCoord(float& nGet)
	{
		nGet = ((float)((float)ReadShort() / (float)8.0));
	}

	float CQuakePacket::ReadAngle()
	{
		float nReturnMe;

		ReadAngle( nReturnMe );
		return nReturnMe;
	}

	void CQuakePacket::ReadAngle(float& nGet)
	// Angles are sent as a single byte (Scaled down from 360 to 256)
	{
		nGet = ((float)((float)ReadChar() * ((float)(360.0 / 256.0))));
	}

	float CQuakePacket::ReadAngle16()
	{
		float nReturnMe;

		ReadAngle16( nReturnMe );
		return nReturnMe;
	}

	void CQuakePacket::ReadAngle16(float& nGet)
	// Some angles are sent as two bytes (Scaled from 360 to 65535)
	{
		nGet = ShortToAngle( ReadShort() );
	}

	CVector CQuakePacket::ReadAngles()
	{
		CVector	vReturnMe;

		ReadAngles(vReturnMe);
		return vReturnMe;
	}

	void CQuakePacket::ReadAngles( CVector& rReadMe )
	{
		ReadAngle( rReadMe.GetSetX() );
		ReadAngle( rReadMe.GetSetY() );
		ReadAngle( rReadMe.GetSetZ() );
	}

	CVector CQuakePacket::ReadAngles16()
	{
		CVector	vReturnMe;

		ReadAngles16(vReturnMe);
		return vReturnMe;
	}

	void CQuakePacket::ReadAngles16( CVector& rReadMe )
	{
		ReadAngle16( rReadMe.GetSetX() );
		ReadAngle16( rReadMe.GetSetY() );
		ReadAngle16( rReadMe.GetSetZ() );
	}

	CVector CQuakePacket::ReadVector()
	{
		CVector	vReturnMe;

		ReadVector(vReturnMe);
		return vReturnMe;
	}

	void CQuakePacket::ReadVector(CVector& rReadMe)
	{
		ReadCoord( rReadMe.GetSetX() );
		ReadCoord( rReadMe.GetSetY() );
		ReadCoord( rReadMe.GetSetZ() );
	}

	CString CQuakePacket::ReadString()
	{
		CString strReturnMe;

		ReadString(strReturnMe);
		return strReturnMe;
	}

	void CQuakePacket::ReadString(CString& strReadMe)
	{
		register int nCounter = 0;
		char	 chrTemp;

		strReadMe.Empty();
		while (DataToRead() && ((chrTemp = ReadChar()) != 0))
		{
			strReadMe += chrTemp;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Write Operations

	void CQuakePacket::WriteAngle(const float& nData)
	//	Angles are sent as a single byte (Scaled down from 360 to 256)
	//		NOTE: (256 / 360) = 0.7111111111111
	{
		WriteByte((BYTE)(nData * 0.7111));
	}

	void CQuakePacket::WriteAngle16(const float& nData)
	{
		WriteShort( AngleToShort(nData) );
	}

	void CQuakePacket::WriteShort(const short& nData)
	{
		BYTE*		pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nData;
		for (nCount = 0; nCount < sizeof(short); nCount++)
		{
			PutByte(pTemp[nCount]);
		}
	}

	void CQuakePacket::WriteLong(const long& nData)
	{
		BYTE*		pTemp;
		register int	nCount;

		pTemp = (BYTE*)&nData;
		for (nCount = 0; nCount < sizeof(long); nCount++)
		{
			PutByte(pTemp[nCount]);
		}
	}

	void CQuakePacket::WriteFloat(const float& nData)
	{
		BYTE*			pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nData;
		for (nCount = 0; nCount < sizeof(float); nCount++)
		{
			PutByte(pTemp[nCount]);
		}
	}

	void CQuakePacket::WriteCoord(const float& nData)
	{
		WriteShort( ((short)(nData * 8)) );
	}

	void CQuakePacket::WriteVector(const CVector& rData)
	{
		WriteCoord( rData.GetX() );
		WriteCoord( rData.GetY() );
		WriteCoord( rData.GetZ() );
	}

	void CQuakePacket::WriteString(const char* strData)
	{
		WORD nTemp;

		VERIFY(strData != NULL);
		nTemp = 0;
		while (strData[nTemp] != '\0')
		{
			PutByte(strData[nTemp++]);
		}
		PutByte('\0');
	}

	//////////////////////////////////////////////////////////////////////////////////