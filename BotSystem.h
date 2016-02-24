//	BotSystem.h : interface of the CBotSystem class	
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

#ifndef BOT_SYSTEM_H
#define BOT_SYSTEM_H

#include "SystemObject.h"

class CBotThread;
class CQuakePacket;

//////////////////////////////////////////////////////////////////////////////////
// CBotSystem Class Definition

class CBotSystem : public CObject
{
	DECLARE_DYNCREATE(CBotSystem);
// Attributes
private:
	CCriticalSection	m_Lock;
	CObList				m_lstThreads;
	CObList				m_lstSysObjects;
	BYTE				m_nThreadCount;

// Constructor / Destructor
public:
	CBotSystem()			{ m_nThreadCount = 0; };
	~CBotSystem()			{ Reset(); } ;

// Operations
private:
	void	Reset();
	void	RecordObjectUse(CSystemObject*);

public:
	void	PostSystemMessage(const UINT& nMsgID, void* pParam = NULL, const UINT nParam = 0);
	void	LockObject( CSystemObject* );
	void	ReleaseObject( CSystemObject* );
	void	IgnoreObject( CSystemObject* );

// Thread Operations
public:
	void	RegisterThread(CBotThread*);
	void	UnregisterThread(CBotThread*);

// Diagnostics
#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG

};

//////////////////////////////////////////////////////////////////////////////////
// CBotSystem Inline Functions
	/////////////////////////////////////////////////////////////////////////////
	// CBotSystem Private Operations

	inline void CBotSystem::RecordObjectUse(CSystemObject* pUsed)
	{
		ASSERT(pUsed != NULL);
		BYTE nUses = pUsed->CheckUsage();
		//TRACE("Object at %p has been used %d times!\n", pUsed, nUses);
		if (nUses >= m_nThreadCount)
		{
			POSITION pUsedSpot;
			if ((pUsedSpot = m_lstSysObjects.Find(pUsed)) != NULL)
			{
				m_lstSysObjects.RemoveAt(pUsedSpot);
#ifdef _DEBUG
				CSingleLock	sLock( pUsed );

				if ( sLock.IsLocked() )
				{
					TRACE("Trying to delete Locked Object!\n");
				}
#endif // _DEBUG
				//TRACE("Object at %p deleted!\n", pUsed);
				delete pUsed;
				pUsed = NULL;
			}
		}
		//TRACE("!!!\tThere are %d undestroyed system objects!\n", m_lstSysObjects.GetCount());
	}

	/////////////////////////////////////////////////////////////////////////////
	// CBotSystem Public Operations

	inline void CBotSystem::LockObject(CSystemObject* pLockMe)
	{
		ASSERT(pLockMe != NULL);
		pLockMe->Lock();
	}

	inline void CBotSystem::ReleaseObject(CSystemObject* pUnlockMe)
	{
		ASSERT(pUnlockMe != NULL);
		pUnlockMe->Unlock();
		RecordObjectUse(pUnlockMe);
	}

	inline void CBotSystem::IgnoreObject(CSystemObject* pIgnore)
	{
		RecordObjectUse(pIgnore);
	}

//////////////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////////////