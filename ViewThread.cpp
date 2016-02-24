// ViewThread.cpp: implementation of the CViewThread class.
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
#include "ViewThread.h"
#include "PandoraDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CViewThread Defines
//////////////////////////////////////////////////////////////////////

// Colors
#define COLOR_NORMAL		COLOR_DEFAULT
#define COLOR_BOTINFO		0x00800000	// Dark Blue
#define COLOR_ERROR			0x000000FF	// Red
#define COLOR_CHAT			0x00008000	// Dark Green
#define COLOR_STUFFTEXT		0x00FF0000	// Blue
#define COLOR_CENTER		0x00800080	// Magenta
#define COLOR_LOW			0x00000080	// Dark Red
#define COLOR_MEDIUM		0x00000000	// Black
#define COLOR_HIGH			0x00404000	// Dark Cyan

//////////////////////////////////////////////////////////////////////
// CViewThread
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CViewThread, CBotThread)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewThread::CViewThread()
{
	m_pConsole = FALSE;
	m_pBotInfo = FALSE;
}

CViewThread::~CViewThread()
{

}

BOOL CViewThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CViewThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CBotThread::ExitInstance();
}

//////////////////////////////////////////////////////////////////////
// CViewThread Operations
//////////////////////////////////////////////////////////////////////

void CViewThread::Clear()
{
	m_nDeaths = 0;
	m_nAmmo = 0;
	m_nFrags = 0;
	m_nHealth = 0;
	m_vBotPos.Clear();
	m_vBotVelocity.Clear();
	m_strAttackName = _T("None");
	m_pAttackTarget = NULL;
	m_vAttackDist.Clear();
	m_vAttackPos.Clear();
	m_strMoveName = _T("None");
	m_pMoveTarget = NULL;
	m_vMoveDist.Clear();
	m_vMovePos.Clear();
	UpdateAmmoAndWeapon();
	UpdateAttackDist();
	UpdateAttackName();
	UpdateAttackPos();
	UpdateBotOrigin();
	UpdateBotVelocity();
	UpdateDeathsAndFrags();
	UpdateHealth();
	UpdateMoveDist();
	UpdateMoveName();
	UpdateMovePos();
}

BOOL CViewThread::UpdateOkay()
{
	return ((m_pBotInfo != NULL) && (m_pBotDoc->IsReady()));
}

void CViewThread::UpdateAttackName()
{
	m_pBotInfo->SetAttackName( m_strAttackName );
}

void CViewThread::UpdateAttackPos()
{
	m_pBotInfo->SetAttackPos( m_vAttackPos.GetString() );
}

void CViewThread::UpdateAttackDist()
{
	CString strTemp;

	strTemp.Format("%5.2f", m_vAttackDist.Length() );
	m_pBotInfo->SetAttackDist( strTemp );
}

void CViewThread::UpdateMoveName()
{
	m_pBotInfo->SetMoveName( m_strMoveName );
}

void CViewThread::UpdateMovePos()
{
	m_pBotInfo->SetMovePos( m_vMovePos.GetString() );
}

void CViewThread::UpdateMoveDist()
{
	CString strTemp;

	strTemp.Format("%5.2f", m_vMoveDist.Length() );
	m_pBotInfo->SetMoveDist( strTemp );
}

void CViewThread::UpdateDeathsAndFrags()
{
	CString strInfo;

	strInfo.Format(" %d (%d)", m_nFrags, m_nDeaths );
	m_pBotInfo->SetFrags( strInfo );
}

void CViewThread::UpdateHealth()
{
	CString strInfo;

	strInfo.Format("%d", m_nHealth);
	m_pBotInfo->SetHealth( strInfo );
}

void CViewThread::UpdateAmmoAndWeapon()
{
	CString strInfo;

	strInfo.Format(" %s (%d)", m_strWeapon, m_nAmmo );
	m_pBotInfo->SetWeapon( strInfo );
}

void CViewThread::UpdateBotOrigin()
{
	m_pBotInfo->SetBotPos( m_vBotPos.GetString() );
}

void CViewThread::UpdateBotVelocity()
{
	m_pBotInfo->SetVelocity( m_vBotVelocity.GetString() );
}

void CViewThread::AddPrefix( const CString& strPrefix )
{
	ASSERT( m_pConsole != NULL );
	m_pConsole->DisplayText( strPrefix, COLOR_NORMAL, TO_BOLD | TO_ITALIC );
	m_pConsole->DisplayText( ": ", COLOR_NORMAL, TO_BOLD );
}

//////////////////////////////////////////////////////////////////////
// CViewThread Message Map Definition
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CViewThread, CBotThread)
	//{{AFX_MSG_MAP(CViewThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// CViewThread Message Handlers
//////////////////////////////////////////////////////////////////////

void CViewThread::OnTextMessage( CTextMessage* pNew )
{
	if ( m_pConsole == NULL )
	{
		m_pBotSys->IgnoreObject( pNew );
	}
	else
	{
		COLORREF	clrText;
		CString		strFiltered;

		m_pBotSys->LockObject( pNew );
		switch( pNew->GetType() )
		{
		case PRINT_CHAT:
			clrText = COLOR_CHAT;
			break;
		case PRINT_LOW:
			clrText = COLOR_LOW;
			break;
		case PRINT_MEDIUM:
			clrText = COLOR_MEDIUM;
			break;
		case PRINT_HIGH:
			clrText = COLOR_HIGH;
			break;
		case PRINT_OTHER:
			clrText = COLOR_NORMAL;
			break;
		default:
			clrText = COLOR_ERROR;
			break;
		}
		pNew->GetFiltered( strFiltered );
		m_pBotSys->ReleaseObject( pNew );

		if ( strFiltered.Find( m_pBotDoc->GetBotName() ) != -1 )
		{
			m_pConsole->DisplayText( strFiltered, clrText, TO_ITALIC );
		}
		else
		{
			m_pConsole->DisplayText( strFiltered, clrText );
		}
	}
}

void CViewThread::OnStuffText( CTextMessage* pNew )
{
	if ( m_pConsole == NULL )
	{
		m_pBotSys->IgnoreObject( pNew );
	}
	else
	{
		AddPrefix("CMD");
		m_pBotSys->LockObject( pNew );
		m_pConsole->DisplayText( pNew->GetText(), COLOR_STUFFTEXT, TO_NEWLINE );
		m_pBotSys->ReleaseObject( pNew );
	}
}

void CViewThread::OnCenterMessage( CTextMessage* pNew )
{
	if ( m_pConsole == NULL )
	{
		m_pBotSys->IgnoreObject( pNew );
	}
	else
	{
		CString strFiltered;

		m_pBotSys->LockObject( pNew );
		pNew->GetFiltered( strFiltered );
		m_pBotSys->ReleaseObject( pNew );
		// Display the centered message
		m_pConsole->DisplayText( strFiltered, COLOR_CENTER, TO_CENTER );
	}
}

void CViewThread::OnInfoErrorMessage( const UINT nResID )
{
	if ( m_pConsole != NULL )
	{
		CString strMessage;

		if ( strMessage.LoadString( nResID ) )
		{
			AddPrefix("Error");
			m_pConsole->DisplayText( strMessage, COLOR_ERROR, TO_BOLD | TO_ITALIC | TO_NEWLINE );
		}
	}
}

void CViewThread::OnNetworkBeginLevel()
{
	if ( m_pBotInfo != NULL )
	{
		m_pBotInfo->Clear();
	}
	Clear();
}

void CViewThread::OnNetworkEndLevel()
{
	Clear();
}

void CViewThread::OnPlayerUpdateOrigin( const BYTE nPlayer )
{
	if ( UpdateOkay() )
	{
		if ( m_pBotDoc->IsReady() )
		{
			CPlayer* pPlayer = m_pBotDoc->GetPlayer( nPlayer );
			if ( pPlayer == m_pAttackTarget )
			{
				ASSERT( pPlayer != NULL );
				m_vAttackPos = pPlayer->GetOrigin();
				m_vAttackDist = m_vAttackPos - m_vBotPos;
				UpdateAttackPos();
				UpdateAttackDist();
			}
		}
	}
}

void CViewThread::OnBotUpdateOrigin()
{
	if ( UpdateOkay() )
	{
		if ( m_pBotDoc->IsReady() )
		{
			CBot* pBot = m_pBotDoc->GetBot();
			ASSERT( pBot != NULL );
			m_vBotPos = pBot->GetOrigin();
		}
		UpdateBotOrigin();
		if ( m_pAttackTarget != NULL )
		{
			m_vAttackDist = m_vAttackPos - m_vBotPos;
			UpdateAttackDist();
		}
		if ( m_pMoveTarget != NULL )
		{
			m_vMoveDist = m_vMovePos - m_vBotPos;
			UpdateMoveDist();
		}
	}
}

void CViewThread::OnBotUpdateVelocity()
{
	if ( UpdateOkay() )
	{
		if ( m_pBotDoc->IsReady() )
		{
			CBot* pBot = m_pBotDoc->GetBot();
			ASSERT( pBot != NULL );
			m_vBotVelocity = pBot->GetVelocity();
			UpdateBotVelocity();
		}
	}
}

void CViewThread::OnBotUpdateWeapon()
{
	if ( UpdateOkay() )
	{
		if ( m_pBotDoc->IsReady() )
		{
			CBot* pBot = m_pBotDoc->GetBot();
			ASSERT( pBot != NULL );
			const CWeaponSpec* pWeapon = pBot->GetWeapon();
			if ( pWeapon != NULL )
			{
				m_pBotDoc->GetItemName( pWeapon->GetInventoryIndex(), m_strWeapon );
			}
			else
			{
				m_strWeapon = _T("None");
			}
			UpdateAmmoAndWeapon();
		}
	}
}

void CViewThread::OnBotKilled( const WORD nNewDeaths )
{
	if ( UpdateOkay() )
	{
		m_nDeaths = nNewDeaths;
		UpdateDeathsAndFrags();
	}
}

void CViewThread::OnBotUpdateFrags( const short nFrags )
{
	if ( UpdateOkay() )
	{
		m_nFrags = nFrags;
		UpdateDeathsAndFrags();
	}
}

void CViewThread::OnBotUpdateAttackTarget( CPlayer* pAttack )
{
	if ( UpdateOkay() )
	{
		m_pAttackTarget = pAttack;
		if ( m_pAttackTarget != NULL )
		{
			m_strAttackName = m_pAttackTarget->GetName();
			m_vAttackPos = m_pAttackTarget->GetOrigin();
			m_vAttackDist = m_vAttackPos - m_vBotPos;
		}
		else
		{
			m_strAttackName = _T("None");
			m_vAttackPos.Clear();
			m_vAttackDist.Clear();
		}
		UpdateAttackName();
		UpdateAttackPos();
		UpdateAttackDist();
	}
}

void CViewThread::OnBotUpdateMoveTarget( CMapPoint* pMove )
{
	if ( UpdateOkay() )
	{
		m_pMoveTarget = pMove;
		if ( m_pMoveTarget != NULL )
		{
			m_strMoveName	= m_pMoveTarget->GetName();
			m_vMovePos		= m_pMoveTarget->GetOrigin();
			m_vMoveDist = m_vMovePos - m_vBotPos;
		}
		else
		{
			m_strMoveName = _T("None");
			m_vMovePos.Clear();
			m_vMoveDist.Clear();
		}
		UpdateMoveName();
		UpdateMovePos();
		UpdateMoveDist();
	}
}

void CViewThread::OnBotUpdateHealth( const short nHealth )
{
	if ( UpdateOkay() )
	{
		m_nHealth = nHealth;
		UpdateHealth();
	}
}

void CViewThread::OnBotUpdateAmmo( const short nAmmo )
{
	if ( UpdateOkay() )
	{
		m_nAmmo = nAmmo;
		UpdateAmmoAndWeapon();
	}
}

void CViewThread::OnBotUpdateAIInfo( const UINT nResID )
{
	if ( UpdateOkay() )
	{
		CString strInfo;

		if ( strInfo.LoadString(nResID) )
		{
			m_pBotInfo->SetAIInfo( strInfo );
		}
	}
}
