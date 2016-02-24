// Vector.cpp: implementation of the CVector class
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
#include "Vector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CVector Class
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CVector, CObject, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector( const float& nX, const float& nY, const float& nZ )
{
	m_nX = nX;
	m_nY = nY;
	m_nZ = nZ;
}

CVector::CVector( const float* pValues )
{
	m_nX = pValues[0];
	m_nY = pValues[1];
	m_nZ = pValues[2];
}

//////////////////////////////////////////////////////////////////////
// Initialization
//////////////////////////////////////////////////////////////////////

void CVector::Clear()
{
	m_nX = CLEAR_POINT;
	m_nY = CLEAR_POINT;
	m_nZ = CLEAR_POINT;
}

BOOL CVector::IsClear() const
{
	return ((m_nX == CLEAR_POINT) && (m_nY == CLEAR_POINT) && (m_nZ == CLEAR_POINT));
}

void CVector::Randomize()
{
	SetX( ( (short) (rand() - rand()) ) );
	SetY( ( (short) (rand() - rand()) ) );
	SetZ( ( (short) (rand() - rand()) ) );
}

//////////////////////////////////////////////////////////////////////
// Vector Math
//////////////////////////////////////////////////////////////////////

float CVector::DistanceTo( const CVector& vOther ) const
{
	return ( *this - vOther );
}

void CVector::Normalize()
{
	float nLength;
	
	Length( nLength );
	if ( nLength != CLEAR_POINT )
	{
		m_nX /= nLength;
		m_nY /= nLength;
		m_nZ /= nLength;
	}
}

void CVector::GetNormalized( CVector& rNormalized ) const
{
	rNormalized.Copy( this );
	rNormalized.Normalize();
}

CVector CVector::GetNormalized() const
{
	CVector vReturnMe;

	GetNormalized( vReturnMe );
	return vReturnMe;
}

void CVector::ScaleTo( const float& nScalar )
{
	Normalize();
	(*this) *= nScalar;
}

CVector CVector::CrossProduct( const CVector& vOther ) const
{
	CVector vReturnMe;

	vReturnMe.SetX( (m_nY * vOther.GetZ()) - (m_nZ * vOther.GetY()) );
	vReturnMe.SetY( (-1)*((m_nX * vOther.GetZ()) - (m_nZ * vOther.GetX())) );
	vReturnMe.SetZ( (m_nX * vOther.GetY()) - (m_nY * vOther.GetX()) );
	return vReturnMe;
}

float CVector::DotProduct( const CVector& vOther ) const
{
	float nReturnMe = CLEAR_POINT;

	nReturnMe += ( m_nX * vOther.GetX() );
	nReturnMe += ( m_nY * vOther.GetY() );
	nReturnMe += ( m_nZ * vOther.GetZ() );
	return nReturnMe;
}

//////////////////////////////////////////////////////////////////////
// Angle Based Math
//////////////////////////////////////////////////////////////////////

void CVector::GetYawAngle( float& nYaw ) const
{
	if ( m_nY || m_nX )
	{
		nYaw = (float)atan2( m_nY, m_nX );
		ConvertRadiansToDegrees( nYaw );
	}
	else
	{
		nYaw = 0.0f;
	}
}

float CVector::GetYawAngle() const
{
	float nReturnMe;
	
	GetYawAngle( nReturnMe );
	return nReturnMe;
}

void CVector::GetPitchAngle( float& nPitch ) const
{
	float nLength;

	Length( nLength );
	if ( nLength )
	{
		nPitch = (float)asin( m_nZ / nLength );
		ConvertRadiansToDegrees( nPitch );
		nPitch *= -1;
	}
	else
	{
		nPitch = 0.0f;
	}
}

float CVector::GetPitchAngle() const
{
	float nReturnMe;
	
	GetPitchAngle( nReturnMe );
	return nReturnMe;
}

void CVector::SetAngles( const float& nPitch, const float& nYaw )
{
	float	nTemp;
	float	nPitchCos;
	
	NormalizeAngle( nPitch, nTemp );
	// Use nPitch, and then use nYaw so there is no need for two variables
	nPitchCos = ((float)cos(nTemp));
	SetZ( (float)(sin(nTemp)) );
	// Now use nYaw
	NormalizeAngle( nYaw, nTemp );
	SetX( (float)(cos( (double)(nTemp) ) * nPitchCos) );
	SetY( (float)(sin( (double)(nTemp) ) * nPitchCos) );
}

//////////////////////////////////////////////////////////////////////
// String Functions
//////////////////////////////////////////////////////////////////////

void CVector::GetString( CString& strVector ) const
{
	strVector.Format( "(%5.1f, %5.1f, %5.1f)", m_nX, m_nY, m_nZ );
}

CString CVector::GetString() const
{
	CString strReturnMe;
	
	GetString(strReturnMe);
	return strReturnMe;
}

//////////////////////////////////////////////////////////////////////
// Overloaded Operators
//////////////////////////////////////////////////////////////////////

// Subtraction Operator
CVector CVector::operator-( const CVector& vOther ) const
{
	CVector vReturnMe;

	vReturnMe.SetX( GetX() - vOther.GetX() );
	vReturnMe.SetY( GetY() - vOther.GetY() );
	vReturnMe.SetZ( GetZ() - vOther.GetZ() );
	return vReturnMe;
}

// Product of a Vector and a Scalar
CVector CVector::operator*( const float& nScalar ) const
{
	CVector vReturnMe;

	vReturnMe.SetX( GetX() * nScalar );
	vReturnMe.SetY( GetY() * nScalar );
	vReturnMe.SetZ( GetZ() * nScalar );
	return vReturnMe;
}

// Assignment Operators
CVector& CVector::operator+=( const CVector& vOther )
{
	m_nX += vOther.GetX();
	m_nY += vOther.GetY();
	m_nZ += vOther.GetZ();
	return ( *this );
}

CVector& CVector::operator-=( const CVector& vOther )
{
	m_nX -= vOther.GetX();
	m_nY -= vOther.GetY();
	m_nZ -= vOther.GetZ();
	return ( *this );
}

CVector& CVector::operator/=( const float& nScalar )
{
	if ( nScalar != CLEAR_POINT )
	{
		m_nX /= nScalar;
		m_nY /= nScalar;
		m_nZ /= nScalar;
	}
	return ( *this );
}

CVector& CVector::operator*=( const float& nScalar )
{
	m_nX *= nScalar;
	m_nY *= nScalar;
	m_nZ *= nScalar;
	return ( *this );
}

//////////////////////////////////////////////////////////////////////
// Diagnostics
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CVector::AssertValid() const
{
	ASSERT( IsKindOf(RUNTIME_CLASS(CVector)) );
	ASSERT( !(_isnan(m_nX)) );
	ASSERT( !(_isnan(m_nY)) );
	ASSERT( !(_isnan(m_nZ)) );
	CObject::AssertValid();
}

void CVector::Dump(CDumpContext& dc) const
{
	dc << GetString() << " [" << Length() << "]";
	// Don't call the base class (for now), so it can be dumped on one line
	// and objects that have CVector as an attribute will have nice looking
	// dumps <insert "Beavis and Butthead" laughter here>
		// CObject::Dump(dc);
}
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////
// End of Vector.cpp
//////////////////////////////////////////////////////////////////////
