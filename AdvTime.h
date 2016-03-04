// AdvTime.h: interface for the CAdvTime class
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

#if !defined(AFX_ADVTIME_H__EF4B5982_BD6E_11D1_8720_444553540000__INCLUDED_)
#define AFX_ADVTIME_H__EF4B5982_BD6E_11D1_8720_444553540000__INCLUDED_

//////////////////////////////////////////////////////////////////////
// CAdvTime Includes
//////////////////////////////////////////////////////////////////////

#include <sys/timeb.h>
#include <sys/types.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////
// CAdvTime Class Definition
//////////////////////////////////////////////////////////////////////

class CAdvTime //: public CObject  
{

// Attributes
private:
	_timeb	m_Value;

// Construction / Destruction
public:
	CAdvTime()										{ SetCurrent(); };
	CAdvTime( const double& nValue )				{ SetValue( nValue ); };
	//virtual ~CAdvTime()								{ };

// Initialization
public:
	void SetCurrent()								{ _ftime( &m_Value ); };

private:
	void Validate();

// Data Manipulation
public:
	long		GetBase() const						{ return m_Value.time; };
	WORD		GetMilli() const					{ return m_Value.millitm; };
	double		GetValue() const;
	void		SetValue( const double& );

// Time Operations
public:
	CAdvTime	Elapsed() const						{ return (CurrentTime() - (*this)); };
	
// String Functions
public:
	void		GetFullString( CString& ) const;
	CString		GetFullString() const;
	void		GetString( CString& ) const;
	CString		GetString() const;

// Overloaded Operators
public:
	// Conversion
	operator	double() const						{ return GetValue(); };
	operator	CString() const						{ return GetString(); };

	// Assignment
	CAdvTime&	operator=( const double& );
	CAdvTime&	operator+=( const double& );
	CAdvTime&	operator-=( const double& );
	CAdvTime&	operator*=( const double& );
	CAdvTime&	operator/=( const double& );
	// Arithmetic
	CAdvTime	operator+( const double& ) const;
	CAdvTime	operator-( const double& ) const;
	CAdvTime	operator*( const double& ) const;
	CAdvTime	operator/( const double& ) const;
	// Equality / Inequality Tests
	BOOL		operator==( const double& ) const;
	BOOL		operator!=( const double& ) const;
	BOOL		operator>( const double& ) const;
	BOOL		operator<( const double& ) const;
	BOOL		operator>=( const double& ) const;
	BOOL		operator<=( const double& ) const;

// Static Functions
public:
	static CAdvTime CurrentTime()					{ return CAdvTime(); };

// Diagnostic Operations
#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext&) const;
#endif // _DEBUG

};

//////////////////////////////////////////////////////////////////////
// Inline Functions
//////////////////////////////////////////////////////////////////////

	inline CAdvTime& CAdvTime::operator=( const double& nOther )
	{
		SetValue( nOther );
		return (*this);
	}

	inline CAdvTime& CAdvTime::operator+=( const double& nOther )
	{
		SetValue( GetValue() + nOther );
		return (*this);
	}

	inline CAdvTime& CAdvTime::operator-=( const double& nOther )
	{
		SetValue( GetValue() - nOther );
		return (*this);
	}

	inline CAdvTime& CAdvTime::operator*=( const double& nOther )
	{
		SetValue( GetValue() * nOther );
		return (*this);
	}

	inline CAdvTime& CAdvTime::operator/=( const double& nOther )
	{
		SetValue( GetValue() / nOther );
		return (*this);
	}

	inline CAdvTime CAdvTime::operator+( const double& nOther ) const
	{
		return CAdvTime( GetValue() + nOther );
	}

	inline CAdvTime CAdvTime::operator-( const double& nOther ) const
	{
		return CAdvTime( GetValue() - nOther );
	}

	inline CAdvTime CAdvTime::operator*( const double& nOther ) const
	{
		return CAdvTime( GetValue() * nOther );
	}

	inline CAdvTime CAdvTime::operator/( const double& nOther ) const
	{
		return CAdvTime( GetValue() / nOther );
	}

	inline BOOL CAdvTime::operator==( const double& nOther ) const
	{
		return ( GetValue() == nOther );
	}

	inline BOOL CAdvTime::operator!=( const double& nOther ) const
	{
		return ( GetValue() != nOther );
	}

	inline BOOL CAdvTime::operator>( const double& nOther ) const
	{
		return ( GetValue() > nOther );
	}

	inline BOOL CAdvTime::operator<( const double& nOther ) const
	{
		return ( GetValue() < nOther );
	}

	inline BOOL CAdvTime::operator>=( const double& nOther ) const
	{
		return ( GetValue() >= nOther );
	}

	inline BOOL CAdvTime::operator<=( const double& nOther ) const
	{
		return ( GetValue() <= nOther );
	}

//////////////////////////////////////////////////////////////////////
// End of Inline Functions
//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_ADVTIME_H__EF4B5982_BD6E_11D1_8720_444553540000__INCLUDED_)

//////////////////////////////////////////////////////////////////////
// End of AdvTime.h
//////////////////////////////////////////////////////////////////////
