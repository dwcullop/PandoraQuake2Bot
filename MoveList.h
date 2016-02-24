// MoveList.h: interface for the CMoveList class.
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

#if !defined(AFX_MOVELIST_H__1BCFA4C2_D98D_11D1_AF1D_0060080A5FD2__INCLUDED_)
#define AFX_MOVELIST_H__1BCFA4C2_D98D_11D1_AF1D_0060080A5FD2__INCLUDED_

#include "MoveData.h"
#include "BotMove.h"
#include "PandoraDefs.h"
#include <AfxMT.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMoveList  
{
// Attributes
private:
	float				m_nTotalTime;
	UINT				m_nTotalMoves;
	CMoveData*			m_pMoves[MOVE_FRAMES];
	CObList				m_lstSentMoves;
	CVector				m_vDeltaOrigin;
	CAdvTime			m_tLastSent;
	CCriticalSection	m_csLock;

// Construction / Destruction
public:
	CMoveList();
	virtual ~CMoveList();

// Data Manipulation
public:
	CMoveData*		GetMoveFrame( const BYTE );
	const CVector&	GetDeltaOrigin() const						{ return m_vDeltaOrigin; };

// Operations
public:
	float			AverageMoveTime() const						{ return ( (m_nTotalMoves==0) ? 0.0f : (m_nTotalTime / (float)m_nTotalMoves) ); };
	void			ComputeDeltaOrigin( const float& );
	void			NewMove( const CBotMove&, const CVector& );
	void			BeginLevel();
	void			Clear();
	void			Reset();

private:
	void AddFrame( CMoveData* );

// Multithreaded Protection
public:
	void Lock()													{ m_csLock.Lock(); };
	void Unlock()												{ m_csLock.Unlock(); };
};

#endif // !defined(AFX_MOVELIST_H__1BCFA4C2_D98D_11D1_AF1D_0060080A5FD2__INCLUDED_)
