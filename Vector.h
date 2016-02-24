// Vector.h: interface for the CVector class
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

#if !defined(AFX_VECTOR_H__7BB23499_BD1E_11D1_8720_444553540000__INCLUDED_)
#define AFX_VECTOR_H__7BB23499_BD1E_11D1_8720_444553540000__INCLUDED_

//////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include <float.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////

#define PI				3.14159265359f		// Value of Pi
#define PI_2			1.570796326795f		// Value of Pi / 2
#define TWO_PI			6.28318530718f		// Value of 2*Pi
#define DEG_PER_RAD		57.2957795131f		// Degrees per Radian
#define CLEAR_POINT		0.0f				// Value of an empty point

//////////////////////////////////////////////////////////////////////
// Class Definition
//////////////////////////////////////////////////////////////////////

class CVector : public CObject  
{
// Allow for serialization
	DECLARE_SERIAL(CVector)

// Attributes
private:
	float	m_nX;
	float	m_nY;
	float	m_nZ;

// Construction / Destruction
public:
	CVector( const CVector& rOther )						{ Copy( rOther ); };
	CVector( const CVector* pOther )						{ Copy( pOther ); };
	CVector()												{ Clear(); };
	CVector( const float&, const float&, const float& );
	CVector( const float pValues[3] );
	virtual ~CVector()										{};

// Initialization
public:
	void Clear();
	BOOL IsClear() const;
	void Randomize();

// Data Manipulation
public:
	const float&	GetX() const							{ return m_nX; };
	const float&	GetY() const							{ return m_nY; };
	const float&	GetZ() const							{ return m_nZ; };
	void			SetX( const float& nNew )				{ m_nX = nNew; };
	void			SetY( const float& nNew )				{ m_nY = nNew; };
	void			SetZ( const float& nNew )				{ m_nZ = nNew; };
	// Updatable References
	float&			GetSetX()								{ return m_nX; };
	float&			GetSetY()								{ return m_nY; };
	float&			GetSetZ()								{ return m_nZ; };

// Operations
public:
	void			Copy( const CVector& );
	void			Copy( const CVector* );

// Vector Math
public:
	void			Length( float& ) const;
	float			Length() const;
	float			DistanceTo( const CVector& ) const;
	void			Normalize();
	void			GetNormalized( CVector& ) const;
	CVector			GetNormalized() const;
	BOOL			IsNormalized() const;
	void			ScaleTo( const float& );
	CVector			CrossProduct( const CVector& ) const;
	float			DotProduct( const CVector& ) const;

// Angle Based Math
public:
	void			GetRollAngle( float& nRoll ) const		{ nRoll = CLEAR_POINT; };
	float			GetRollAngle() const					{ return CLEAR_POINT; };
	void			GetYawAngle( float& ) const;
	float			GetYawAngle() const;
	void			GetPitchAngle( float& ) const;
	float			GetPitchAngle() const;
	void			SetAngles( const float&, const float& );

// String Functions
public:
	void			GetString( CString& ) const;
	CString			GetString() const;

// Overloaded Operators
public:
					operator CString() const				{ return GetString(); };
					operator float() const					{ return Length(); };
	BOOL			operator>( const CVector& ) const;
	BOOL			operator<( const CVector& ) const;
	BOOL			operator>=( const CVector& ) const;
	BOOL			operator<=( const CVector& ) const;
	BOOL			operator==( const CVector& ) const;
	BOOL			operator!=( const CVector& ) const;
	CVector			operator-( const CVector& ) const;
	float			operator*( const CVector& ) const;		// Dot Product
	CVector			operator*( const float& ) const;		// Vector * Scalar
	CVector			operator+( const CVector& ) const;
	CVector&		operator=( const CVector& );
	CVector&		operator+=( const CVector& );
	CVector&		operator-=( const CVector& );
	CVector&		operator/=( const float& );
	CVector&		operator*=( const float& );

// Diagnostic Operations
#ifdef _DEBUG
public:
	virtual void	AssertValid() const;
	virtual void	Dump(CDumpContext&) const;
#endif // _DEBUG

};

//////////////////////////////////////////////////////////////////////
// Inline Functions
//////////////////////////////////////////////////////////////////////

// Vector Math Functions
inline void CVector::Length( float& nLength ) const
{
	nLength = ( (float)sqrt( (m_nX*m_nX) + (m_nY*m_nY) + (m_nZ*m_nZ) ) );
}

inline float CVector::Length() const
{
	float nReturnMe;

	Length(nReturnMe);
	return nReturnMe;
}

inline BOOL CVector::IsNormalized() const
{
	return ( Length() == 1.0f );
}

// Equality Operators
inline BOOL CVector::operator==(const CVector& vOther) const
{
	return ((GetX() == vOther.GetX()) && (GetY() == vOther.GetY()) && (GetZ() == vOther.GetZ()));
}

inline BOOL CVector::operator!=(const CVector& vOther) const
{
	return (!(*this == vOther));
}

inline BOOL CVector::operator>(const CVector& vOther) const
{
	return ((GetX() > vOther.GetX()) && (GetY() > vOther.GetY()) && (GetZ() > vOther.GetZ()));
}

inline BOOL CVector::operator<(const CVector& vOther) const
{
	return ((GetX() < vOther.GetX()) && (GetY() < vOther.GetY()) && (GetZ() < vOther.GetZ()));
}

inline BOOL CVector::operator>=(const CVector& vOther) const
{
	return (!(*this < vOther));
}

inline BOOL CVector::operator<=(const CVector& vOther) const
{
	return (!(*this > vOther));
}

// Dot Product of Two Vectors
inline float CVector::operator*(const CVector& vOther) const
{
	return DotProduct(vOther);
}

// Assignment Operator
inline CVector& CVector::operator=(const CVector& vOther)
{
	Copy(vOther);
	return (*this);
}

// Other Operations
inline void CVector::Copy(const CVector& vCopyMe)
{
	CopyMemory( this, &vCopyMe, sizeof(CVector) );
}

inline void CVector::Copy( const CVector* pCopyMe )
{
	CopyMemory( this, pCopyMe, sizeof(CVector) );
}

//////////////////////////////////////////////////////////////////////
// Inline Utility Functions
//////////////////////////////////////////////////////////////////////

inline void NormalizeAngle( float& nAngle )
{
	ASSERT( !_isnan(nAngle) );
	while ( nAngle > 180.0f )
	{
		nAngle -= 360.0f;
	}
	while ( nAngle < -180.0f )
	{
		nAngle += 360.0f;
	}
}

inline void NormalizeAngle( const float& nAngle, float& nTarget )
{
	nTarget = nAngle;
	NormalizeAngle( nTarget );
}

inline float RadiansToDegrees( const float& nRadians )
{
	return ( nRadians * DEG_PER_RAD );
}

inline float DegreesToRadians( const float& nDegrees )
{
	return ( nDegrees / DEG_PER_RAD );
}

inline void ConvertRadiansToDegrees( float& nRadians )
{
	nRadians *= DEG_PER_RAD;
}

inline void ConvertDegreesToRadians( float& nDegrees )
{
	nDegrees /= DEG_PER_RAD;
}

//////////////////////////////////////////////////////////////////////
// End of Inline Functions
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_VECTOR_H__7BB23499_BD1E_11D1_8720_444553540000__INCLUDED_)

//////////////////////////////////////////////////////////////////////
// End of Vector.h
//////////////////////////////////////////////////////////////////////
