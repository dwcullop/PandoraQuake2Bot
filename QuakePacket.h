//	QuakePacket.h : interface for the CQuakePacket
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

#ifndef QUAKE_PACKET_H
#define QUAKE_PACKET_H

//////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Includes

#include "StdAfx.h"
#include "SystemObject.h"
#include "Vector.h"

//////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Defines


//////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Class Definition

//class CQuakePacket : public CSystemObject
class CQuakePacket : public CObject
{
	DECLARE_DYNCREATE(CQuakePacket);

// Attributes
private:
	BOOL			m_bReadMode;
	CByteArray		m_arrData;

protected:
	WORD			m_nPosition;

// Construction / Destruction
public:
	CQuakePacket()							{ Clear(); };
	CQuakePacket(const CQuakePacket* pNew)	{ Copy( *pNew ); };
	CQuakePacket(const CQuakePacket& New)	{ Copy( New ); };
	virtual ~CQuakePacket()					{ };

// Data Manipulation Operations
public:
	// Get Data Functions
	const BOOL&			GetReadMode() const				{ return m_bReadMode; };
	const WORD&			GetPosition() const				{ return m_nPosition; };
	const CByteArray&	GetData() const					{ return m_arrData; };
	BYTE*				GetDataPtr()					{ return m_arrData.GetData(); };
	CByteArray&			GetDataArray()					{ return m_arrData; };

// Operations
private:
	void			MergeBuffer(CQuakePacket&, const WORD&);

public:
	void			InsertData(CQuakePacket&);
	void			PrependData(CQuakePacket&);
	BOOL			DataToRead() const;
	void			RemoveData(const WORD&, const WORD&);
	virtual void	SetReadMode();
	virtual void	SetWriteMode();
	virtual void	Clear();
	virtual void	Copy(const CQuakePacket&);
	void			SetSize(int nNew)				{ GetDataArray().SetSize(nNew); GetDataArray().FreeExtra(); m_nPosition = GetSize(); };
	int				GetSize() const					{ return GetData().GetSize(); };
	void			SkipToEnd()						{ m_nPosition = GetSize(); };
	BYTE			PeekNext() const				{ return GetData().GetAt(m_nPosition); };
	void			CheckLength()					{ GetDataArray().SetSize(m_nPosition); GetDataArray().FreeExtra(); };
	void			Insert(BYTE nNew)				{ m_arrData.InsertAt(0, nNew); m_nPosition++; };
	void			SetAt(int nIndex, BYTE nNew)	{ m_arrData.SetAt(nIndex, nNew); };


// Overloaded Operators
	CQuakePacket& operator=(const CQuakePacket&);

// Read / Write Operations
private:
	BYTE	GetByte();
	void	PutByte(const BYTE&);

public:
	// Read Operations
	char	ReadChar()					{ return char(GetByte()); };
	void	ReadChar(char& nGet)		{ nGet = char(GetByte()); };
	BYTE	ReadByte()					{ return (GetByte()); };
	void	ReadByte(BYTE& nGet)		{ nGet = (GetByte()); };
	WORD	ReadWord()					{ return ((WORD)ReadShort()); };
	void	ReadWord(WORD& nGet)		{ ReadShort( (short&)nGet ); };
	UINT	ReadUInt()					{ return ((UINT)ReadLong()); };
	void	ReadUInt(UINT& nGet)		{ ReadLong( (long&)nGet ); };
	short	ReadShort();
	void	ReadShort(short&);
	long	ReadLong();
	void	ReadLong(long&);
	float	ReadFloat();
	void	ReadFloat(float&);
	float	ReadCoord();
	void	ReadCoord(float&);
	float	ReadAngle();
	void	ReadAngle(float&);
	float	ReadAngle16();
	void	ReadAngle16(float&);
	CVector	ReadAngles();
	void	ReadAngles(CVector&);
	CVector	ReadAngles16();
	void	ReadAngles16(CVector&);
	CVector	ReadVector();
	void	ReadVector(CVector&);
	CString	ReadString();
	void	ReadString(CString&);
	// Write Operations
	void	WriteChar(const char& nData)	{ PutByte((BYTE)nData); };
	void	WriteByte(const BYTE& nData)	{ PutByte(nData); };
	void	WriteAngle(const float&);
	void	WriteAngle16(const float&);
	void	WriteShort(const short&);
	void	WriteLong(const long&);
	void	WriteFloat(const float&);
	void	WriteCoord(const float&);
	void	WriteVector(const CVector&);
	void	WriteString(const char*);

// Overrides
public:
	void Serialize(CArchive&);

// Diagnostics
#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG
};

/*
//////////////////////////////////////////////////////////////////////////////////
// CQuakePacket Inline Functions

	///////////////////////////////////////////////////////////////////////////
	// CQuakePacket Operations

	inline void CQuakePacket::RemoveData(const WORD& nPosition, const WORD& nLength)
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

	inline void CQuakePacket::PrependData(CQuakePacket& rOther)
	{
		MergeBuffer(rOther, 0);
	}

	inline void CQuakePacket::InsertData(CQuakePacket& rOther)
	{
		MergeBuffer(rOther, m_nPosition);
	}

	inline void CQuakePacket::Clear()
	{
		SetWriteMode();
		m_nPosition		= 0;
		m_arrData.RemoveAll();
		// Call the base class
		CQuakeSystemObject::Clear();
	}

	inline void CQuakePacket::Copy(const CQuakePacket& rCopyMe)
	{
		m_bReadMode	= rCopyMe.GetReadMode();
		m_nPosition	= rCopyMe.GetPosition();
		m_arrData.RemoveAll();
		m_arrData.SetSize(rCopyMe.GetData().GetSize());
		m_arrData.Append(rCopyMe.GetData());
		// Call the base class
		CQuakeSystemObject::Copy(rCopyMe);
	}

	inline BOOL CQuakePacket::DataToRead() const
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

	inline CQuakePacket& CQuakePacket::operator=(const CQuakePacket& rCopyMe)
	{
		Copy(rCopyMe);
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Private Read/Write Functions

	inline BYTE CQuakePacket::GetByte()
	{
		ASSERT(GetReadMode() == TRUE);
		ASSERT(GetPosition() < GetDataArray().GetSize());
		return GetDataArray().GetAt(m_nPosition++);
	}

	inline void CQuakePacket::PutByte(const BYTE& nData)
	{
		ASSERT(GetReadMode() == FALSE);
		GetDataArray().SetAtGrow(m_nPosition++, nData);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Read Functions

	inline short CQuakePacket::ReadShort()
	{
		short nReturnMe;
		ReadShort(nReturnMe);
		return nReturnMe;
	}

	inline void CQuakePacket::ReadShort(short& nGet)
	{
		BYTE		*pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nGet; 
		for(nCount = 0; nCount < sizeof(short); nCount++)
		{
			pTemp[nCount] = GetByte();
		}
	}

	inline long CQuakePacket::ReadLong()
	{
		long nReturnMe;
		ReadLong(nReturnMe);
		return nReturnMe;
	}

	inline void CQuakePacket::ReadLong(long& nGet)
	{
		BYTE		*pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nGet; 
		for(nCount = 0; nCount < sizeof(long); nCount++)
		{
			pTemp[nCount] = GetByte();
		}
	}

	inline float CQuakePacket::ReadFloat()
	{
		float nReturnMe;
		ReadFloat(nReturnMe);
		return nReturnMe;
	}

	inline void CQuakePacket::ReadFloat(float& nGet)
	{
		BYTE		*pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nGet; 
		for(nCount = 0; nCount < sizeof(float); nCount++)
		{
			pTemp[nCount] = GetByte();
		}
	}

	inline float CQuakePacket::ReadCoord()
	{
		return ((float)((float)ReadShort() / (float)8.0));
	}

	inline void CQuakePacket::ReadCoord(float& nGet)
	{
		nGet = ReadCoord();
	}

	inline float CQuakePacket::ReadAngle()
	// Angles are sent as a single byte (Scaled down from 360 to 256)
	//		NOTE: (360 / 256) = 1.40625
	{
		return ((float)((float)ReadChar() * (float)1.40625));
	}

	inline void CQuakePacket::ReadAngle(float& nGet)
	{
		nGet = ReadAngle();
	}

	inline CVector CQuakePacket::ReadVector()
	{
		CVector	vReturnMe;

		ReadVector(vReturnMe);
		return vReturnMe;
	}

	inline void CQuakePacket::ReadVector(CVector& rReadMe)
	{
		rReadMe.SetX( ReadCoord() );
		rReadMe.SetY( ReadCoord() );
		rReadMe.SetZ( ReadCoord() );
	}

	inline CString CQuakePacket::ReadString()
	{
		CString strReturnMe;

		ReadString(strReturnMe);
		return strReturnMe;
	}

	inline void CQuakePacket::ReadString(CString& strReadMe)
	{
		register int	nCounter = 0;
		BYTE		nTemp;

		strReadMe.Empty();
		nTemp = ReadByte();
		if (nTemp > 128)
		{
			nTemp -= 128;
		}
		strReadMe += nTemp;
		while (strReadMe[nCounter++] != '\0')
		{
			strReadMe += ReadChar();
		}
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Write Operations

	inline void CQuakePacket::WriteShort(const short& nData)
	{
		BYTE*		pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nData;
		for (nCount = 0; nCount < sizeof(short); nCount++)
		{
			PutByte(pTemp[nCount]);
		}
	}

	inline void CQuakePacket::WriteLong(const long& nData)
	{
		BYTE*		pTemp;
		register int	nCount;

		pTemp = (BYTE*)&nData;
		for (nCount = 0; nCount < sizeof(long); nCount++)
		{
			PutByte(pTemp[nCount]);
		}
	}

	inline void CQuakePacket::WriteFloat(const float& nData)
	{
		BYTE*		pTemp;
		register int	nCount;

		pTemp = (BYTE *)&nData;
		for (nCount = 0; nCount < sizeof(float); nCount++)
		{
			PutByte(pTemp[nCount]);
		}
	}

	inline void CQuakePacket::WriteCoord(const float& nData)
	{
		WriteShort( ((short)(nData * 8)) );
	}

	inline void CQuakePacket::WriteAngle(const float& nData)
	//	Angles are sent as a single byte (Scaled down from 360 to 256)
	//		NOTE: (256 / 360) = 0.7111111111111
	{
		WriteByte((BYTE)(nData * 0.7111));
	}

	inline void CQuakePacket::WriteVector(const CVector& rData)
	{
		WriteCoord( rData.GetX() );
		WriteCoord( rData.GetY() );
		WriteCoord( rData.GetZ() );
	}

	inline void CQuakePacket::WriteString(const char* strData)
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
*/
//////////////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////////////
