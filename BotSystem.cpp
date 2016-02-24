//	BotSystem.cpp : implementation of the CBotSystem
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
#include "BotSystem.h"
#include "BotThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBotSystem

IMPLEMENT_DYNCREATE(CBotSystem, CObject)

/////////////////////////////////////////////////////////////////////////////
// CBotSystem construction/destruction

	// Defined Inline

/////////////////////////////////////////////////////////////////////////////
// CBotSystem operations

void CBotSystem::PostSystemMessage(const UINT& nMsgID, void* pParam, const UINT nParam)
{
	POSITION	pList;
	CWinThread*	pThread;

	if ( pParam != NULL )
	{
		m_lstSysObjects.AddTail(((CObject*)(pParam)));
	}
	m_Lock.Lock();
	pList = m_lstThreads.GetHeadPosition();
	while (pList != NULL)
	{
		pThread = (CWinThread*)m_lstThreads.GetNext(pList);
		pThread->PostThreadMessage(nMsgID, ((UINT)(pParam)), nParam);
	}
	m_Lock.Unlock();
}

void CBotSystem::Reset()
{
   CSystemObject*	pTemp;

	//TRACE("!!! BotSystem is being cleared!\n");
	while(m_lstSysObjects.GetCount())
	{
		TRACE("!!!\tThere are %d undestroyed system objects!\n", m_lstSysObjects.GetCount());
		pTemp = (CSystemObject*)m_lstSysObjects.RemoveHead();
		delete pTemp;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBotSystem Thread operations

void CBotSystem::RegisterThread(CBotThread* pNew)
{
	m_Lock.Lock();
	m_lstThreads.AddTail(pNew);
	m_nThreadCount++;
	m_Lock.Unlock();
}

void CBotSystem::UnregisterThread(CBotThread* pKill)
{
	POSITION pRemoved;

	m_Lock.Lock();
	if ((pRemoved = m_lstThreads.Find(pKill)) != NULL)
	{
		m_lstThreads.RemoveAt(pRemoved);
		m_nThreadCount--;
	}
	m_Lock.Unlock();
}

/////////////////////////////////////////////////////////////////////////////
// CBotSystem diagnostics

#ifdef _DEBUG
void CBotSystem::AssertValid() const
{
}

void CBotSystem::Dump(CDumpContext& dc) const
{
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
/*
	/////////////////////////////////////////////////////////////////////////////
	// CBotSystem Private Operations

	void CBotSystem::RecordObjectUse(CSystemObject* pUsed)
	{
		ASSERT(pUsed != NULL);
		AfxMessageBox("Recording Object Use!");
		BYTE nUses = pUsed->CheckUsage();
		AfxMessageBox("Usage Checked");
		//TRACE("Object at %p has been used %d times!\n", pUsed, nUses);
		if (nUses >= m_nThreadCount)
		{
			POSITION pUsedSpot;
			if ((pUsedSpot = m_lstSysObjects.Find(pUsed)) != NULL)
			{
				m_lstSysObjects.RemoveAt(pUsedSpot);
				//TRACE("Object at %p deleted!\n", pUsed);
				delete pUsed;
				pUsed = NULL;
			}
		}
		//TRACE("!!!\tThere are %d undestroyed system objects!\n", m_lstSysObjects.GetCount());
	}

	/////////////////////////////////////////////////////////////////////////////
	// CBotSystem Public Operations

	void CBotSystem::LockObject(CSystemObject* pLockMe)
	{
		ASSERT(pLockMe != NULL);
		pLockMe->Lock();
	}

	void CBotSystem::ReleaseObject(CSystemObject* pUnlockMe)
	{
		ASSERT(pUnlockMe != NULL);
		pUnlockMe->Unlock();
		RecordObjectUse(pUnlockMe);
	}

	void CBotSystem::IgnoreObject(CSystemObject* pIgnore)
	{
		AfxMessageBox("CBotSystem::IgnoreObject()");
		RecordObjectUse(pIgnore);
		AfxMessageBox("CBotSystem::IgnoreObject() - After");
	}

*/