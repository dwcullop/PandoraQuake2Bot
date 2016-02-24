// BotAI.cpp: implementation of the CBotAI class.
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
#include "BotAI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBotAI::CBotAI()
{
	ResetAI();
	m_pGame = NULL;
	m_pClient = NULL;
}

CBotAI::~CBotAI()
{

}

//////////////////////////////////////////////////////////////////////
// General Operations
//////////////////////////////////////////////////////////////////////

void CBotAI::ResetAI()
{
	m_nMoveCount = 0;
	m_lstAmmo.RemoveAll();
	m_lstArmor.RemoveAll();
	m_lstDangerous.RemoveAll();
	m_lstHealing.RemoveAll();
	m_lstItems.RemoveAll();
	m_lstPlayers.RemoveAll();
	m_lstWeapons.RemoveAll();
	m_pBot = NULL;
	m_pAttackTarget = NULL;
	m_pMoveTarget = NULL;
	m_bMoveOkay = FALSE;
}

//////////////////////////////////////////////////////////////////////
// List Operations
//////////////////////////////////////////////////////////////////////

CPlayer* CBotAI::FindBestPlayer( CEntity* (CBotAI::*pSort)(CEntity*, CEntity*) )
{
	POSITION	pPos;
	CPlayer*	pOne = NULL;
	CPlayer*	pTwo = NULL;

	for ( pPos = m_lstPlayers.GetHeadPosition() ; pPos != NULL ; )
	{
		if ( pOne == NULL )
		{
			pOne = ( (CPlayer*) m_lstPlayers.GetNext(pPos) );
		}
		if ( pPos != NULL )
		{
			pTwo = ( (CPlayer*) m_lstPlayers.GetNext(pPos) );
			pOne = SortPlayer( pOne, pTwo, pSort );
			pTwo = NULL;
		}
	}
	return pOne;
}

CEntity* CBotAI::FindBestItem( CObList& rList, CEntity* (CBotAI::*pSort)(CEntity*, CEntity*) )
{
	POSITION	pPos;
	CEntity*	pOne = NULL;
	CEntity*	pTwo = NULL;

	for ( pPos = rList.GetHeadPosition() ; pPos != NULL ; )
	{
		if ( pOne == NULL )
		{
			pOne = ( (CPlayer*) rList.GetNext(pPos) );
		}
		if ( pPos != NULL )
		{
			pTwo = ( (CPlayer*) rList.GetNext(pPos) );
			pOne = (this->*pSort)( pOne, pTwo );
			pTwo = NULL;
		}
	}
	return pOne;
}

void CBotAI::AddEntity( CEntity* pEntity )
{
	ASSERT( pEntity != NULL );
	CEntityState* pCurrent = pEntity->GetCurrent();

	if ( pCurrent != NULL )
	{
		switch( m_aiGameData.GetType(pCurrent->GetModelIndex()) )
		{
		case ENTITY_TYPE_AMMO:
			AddListItem( m_lstAmmo, pEntity );
			break;
		case ENTITY_TYPE_ARMOR:
			AddListItem( m_lstArmor, pEntity );
			break;
		case ENTITY_TYPE_DANGEROUS:
			AddListItem( m_lstDangerous, pEntity );
			break;
		case ENTITY_TYPE_HEALING:
			AddListItem( m_lstHealing, pEntity );
			break;
		case ENTITY_TYPE_ITEMS:
			AddListItem( m_lstItems, pEntity );
			break;
		case ENTITY_TYPE_WEAPONS:
			AddListItem( m_lstWeapons, pEntity );
			break;
		case ENTITY_TYPE_OTHER:
			break;
		case ENTITY_TYPE_VISIBLE:
			TRACE("Visible Entities are invalid!\n");
			break;
		default:
			TRACE("Unknown Entity Type: %d\n", m_aiGameData.GetType(pCurrent->GetModelIndex()) );
			break;
		}
	}
}

void CBotAI::RemoveEntity( CEntity* pEntity )
{
	ASSERT( pEntity != NULL );
	CEntityState* pCurrent = pEntity->GetCurrent();

	if ( pCurrent != NULL )
	{
		switch( m_aiGameData.GetType(pCurrent->GetModelIndex()) )
		{
		case ENTITY_TYPE_AMMO:
			RemoveListItem( m_lstAmmo, pEntity );
			break;
		case ENTITY_TYPE_ARMOR:
			RemoveListItem( m_lstArmor, pEntity );
			break;
		case ENTITY_TYPE_DANGEROUS:
			RemoveListItem( m_lstDangerous, pEntity );
			break;
		case ENTITY_TYPE_HEALING:
			RemoveListItem( m_lstHealing, pEntity );
			break;
		case ENTITY_TYPE_ITEMS:
			RemoveListItem( m_lstItems, pEntity );
			break;
		case ENTITY_TYPE_WEAPONS:
			RemoveListItem( m_lstWeapons, pEntity );
			break;
		case ENTITY_TYPE_OTHER:
			break;
		case ENTITY_TYPE_VISIBLE:
			TRACE("Visible Entities are invalid!\n");
			break;
		default:
			TRACE("Unknown Entity Type: %d\n", m_aiGameData.GetType(pCurrent->GetModelIndex()) );
			break;
		}
	}
}

void CBotAI::AddPlayer( CPlayer* pPlayer )
{
	AddListItem( m_lstPlayers, pPlayer );
}

void CBotAI::RemovePlayer( CPlayer* pPlayer )
{
	RemoveListItem( m_lstPlayers, pPlayer );
}

//////////////////////////////////////////////////////////////////////
// Private List Operations
//////////////////////////////////////////////////////////////////////

void CBotAI::AddListItem( CObList& rList, CEntity* pAdd )
{
	POSITION pPos = rList.Find( pAdd );

	if ( pPos == NULL )
	{
		rList.AddHead( pAdd );
	}
}

void CBotAI::RemoveListItem( CObList& rList, CEntity* pRemove )
{
	POSITION pPos = rList.Find( pRemove );

	if ( pPos != NULL )
	{
		rList.RemoveAt( pPos );
	}
}

//////////////////////////////////////////////////////////////////////
// Move Operations
//////////////////////////////////////////////////////////////////////

const BOOL CBotAI::PrepareMove()
{
	ASSERT( m_pClient != NULL );
	ASSERT( m_pGame != NULL );
	if ( m_pClient->GetStatus() == csConnected )
	{
		m_pGame->Lock();
		m_pBot = m_pGame->GetBot();
		m_nMoveCount++;
		m_vBotOrigin = m_pClient->GetDeltaOrigin();;
		TRACE("DeltaOrigin: %s\t", m_vBotOrigin.GetString() );
		TRACE("Current: %s\t", m_pBot->GetOrigin().GetString() );
		m_vBotOrigin += m_pBot->GetOrigin();
		TRACE("Total: %s\n", m_vBotOrigin.GetString() );
		return TRUE;
	}
	return FALSE;
}

void CBotAI::SendMove()
{
	ASSERT( m_pClient != NULL );
	ASSERT( m_pGame != NULL );
	if ( m_pAttackTarget == NULL )
	{
		// If no target, look in the direction of travel
		m_bmCurrent.SetLook( m_bmCurrent.GetMove() );
	}
	else
	{
		AttackPlayer( m_pAttackTarget );
	}
	m_pBot->SetAttackTarget( m_pAttackTarget );
	m_pBot->SetMoveTarget( m_pMoveTarget );
	m_pBot = NULL;
	m_pGame->Unlock();
	m_pClient->SendMove( m_bmCurrent );
}

BOOL CBotAI::AttackPlayer( CPlayer* pTarget )
{
	ASSERT( m_pClient != NULL );
	ASSERT( m_pGame != NULL );

	float		nPing = ( (m_pClient->GetSocket()->GetPing()) / 1000.0f );
	CVector		vTempOrigin;
	CVector		vTargetVelocity;
	CVector		vTemp;

	ASSERT( m_pBot != NULL );
	ASSERT( pTarget != NULL );
	m_bmCurrent.GetMove( vTempOrigin );
	vTempOrigin *= m_pClient->GetAverageMoveTime();
	// Adjust the origin to reflect the intended move
	vTempOrigin += m_vBotOrigin;
	vTemp = pTarget->GetOrigin();
	pTarget->GetVelocity( vTargetVelocity );
	vTargetVelocity *= nPing;
	vTemp += vTargetVelocity;
	PredictImpactOrigin( vTempOrigin, vTemp, vTargetVelocity, m_pBot->GetWeapon() );
	vTemp -= vTempOrigin;
	if ( pTarget->IsCrouching() )
	{
		vTemp.GetSetZ() -= PLAYER_CROUCH_HEIGHT_OFFSET;
	}
	if ( m_pBot->IsCrouching() )
	{
		vTempOrigin.GetSetZ() -= PLAYER_CROUCH_HEIGHT_OFFSET;
	}
	m_bmCurrent.SetLook( vTemp );
	//if ( IsShotClear(vTemp, vTempOrigin, m_pBot->GetWeapon()) )
	if ( IsPathClear(vTemp, vTempOrigin) )
	{
		m_bmCurrent.SetAttack( Yes );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CBotAI::MoveRandomly( const WORD& nDist )
{
	CVector		vTemp;

	ASSERT( m_pBot != NULL );
	if ( m_pMoveTarget == &m_mpTemp )
	{
		m_pMoveTarget = &m_mpTemp2;
	}
	else
	{
		m_pMoveTarget = &m_mpTemp;
	}
	m_pMoveTarget->SetName("Random Move");
	vTemp.Randomize();
	vTemp.SetZ( 0 );
	vTemp.ScaleTo( nDist );
	vTemp += m_pBot->GetOrigin();
	m_pMoveTarget->SetOrigin( vTemp );
	MoveToMapPoint();
}

void CBotAI::MoveToEntity( const CEntity* pEntity )
{
	CString		strName;

	ASSERT( m_pBot != NULL );
	if ( m_pMoveTarget == &m_mpTemp )
	{
		m_pMoveTarget = &m_mpTemp2;
	}
	else
	{
		m_pMoveTarget = &m_mpTemp;
	}
	pEntity->GetModelName( strName );
	m_pMoveTarget->SetName( strName );
	m_pMoveTarget->SetOrigin( pEntity->GetOrigin() );
	MoveToMapPoint();
}

void CBotAI::MoveToMapPoint()
{
	CVector vLocation;

	ASSERT( m_pBot != NULL );
	vLocation = ( m_pMoveTarget->GetOrigin() - m_vBotOrigin );
	vLocation.SetZ( 0 );
	vLocation.ScaleTo( MAX_SPEED );
	m_bmCurrent.SetMove( vLocation );
}

BOOL CBotAI::IsBotStuck( )
{
	if ( m_pBot->GetVelocity() > 2.0 )
	{
		return FALSE;
	}
	else
	{
		m_bmCurrent.SetJump( Yes );
		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////
// Item Operations
//////////////////////////////////////////////////////////////////////

void CBotAI::UseItem( const CString& strUseMe )
{
	CString strUseCmd;

	ASSERT( m_pClient != NULL );
	strUseCmd.Format( CString((LPCSTR)IDS_CMD_USE), strUseMe );
	m_pClient->ConsoleCommand( strUseCmd );
}

void CBotAI::UseItem( const BYTE& nItem )
{
	ASSERT( m_pGame != NULL );
	UseItem( m_pGame->GetItemName(nItem) );
}

void CBotAI::DropItem( const CString& strDropMe )
{
	CString strDropCmd;

	ASSERT( m_pClient != NULL );
	strDropCmd.Format( CString((LPCSTR)IDS_CMD_DROP), strDropMe );
	m_pClient->ConsoleCommand( strDropCmd );
}

void CBotAI::DropItem( const BYTE& nItem )
{
	ASSERT( m_pGame != NULL );
	DropItem( m_pGame->GetItemName(nItem) );
}

//////////////////////////////////////////////////////////////////////
// Weapon Selection Operations
//////////////////////////////////////////////////////////////////////

BOOL CBotAI::IsWeaponAvailable( const CWeaponSpec* pWeapon )
{
	ASSERT( m_pBot != NULL );
	ASSERT( pWeapon != NULL );

	if ( m_pBot->GetItemCount(pWeapon->GetInventoryIndex()) > 0 )
	{
		if ( m_pBot->GetItemCount(pWeapon->GetAmmoInventoryIndex()) >= pWeapon->GetAmmoPerShot() )
		{
			return TRUE;
		}
	}
	return FALSE;
}

CWeaponSpec* CBotAI::SelectBestWeapon()
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////
// Targeting Operations
//////////////////////////////////////////////////////////////////////

BOOL CBotAI::IsShotClear( const CVector& vBegin, const CVector& vEnd, const CWeaponSpec* pWeapon )
{
	if ( IsPathClear(vBegin, vEnd) )
	{
		float nDist = vBegin - vEnd;

		if ( pWeapon->CheckRange(nDist) )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CBotAI::IsViableTarget( const CPlayer* pTarget )
{
	if ( (pTarget != NULL) && (pTarget != m_pBot) )
	{
		if ( !pTarget->IsDead() )
		{
			// TODO: Have it check for teammates / friends
			return TRUE;
		}
	}
	return FALSE;
}

void CBotAI::PredictImpactOrigin( const CVector& vBot, CVector& vPlayer, const CVector& vPlayerVelocity, const CWeaponSpec* pWeapon )
{
	if ( vPlayerVelocity.Length() && (pWeapon != NULL) )
	{
		WORD	nWeaponSpeed;
		float	nA, nB, nC, nTime;
		CVector vPath = vPlayer - vBot;

		nWeaponSpeed = pWeapon->GetDangerSpec()->GetSpeed();
		nA = ( (float)( pow(vPlayerVelocity.Length(), 2.0) - pow(nWeaponSpeed, 2.0) ));
		nB = ( (float)( vPlayerVelocity.GetX()*vPath.GetX() + vPlayerVelocity.GetY()*vPath.GetY() + vPlayerVelocity.GetZ()*vPath.GetZ() ));
		nC = ( (float) pow(vPath.Length(), 2.0) );
		nTime = ( (float)( (-nB - sqrt( nB*nB - 4*nA*nC )) / (2*nA) ));
		vPlayer += ( vPlayerVelocity * nTime );
	}
}

//////////////////////////////////////////////////////////////////////
// Map Operations
//////////////////////////////////////////////////////////////////////

BOOL CBotAI::IsPathClear( const CVector&, const CVector& )
{
	// TODO: have this use the BSP info to determine if the path is clear
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Sorting Functions
//////////////////////////////////////////////////////////////////////

CPlayer* CBotAI::SortPlayer( CPlayer* pOne, CPlayer* pTwo, CEntity* (CBotAI::*pSort)(CEntity*, CEntity*) )
{
	if ( IsViableTarget(pOne) )
	{
		if ( IsViableTarget(pTwo) )
		{
			return ( (CPlayer*) ((this->*pSort)(pOne, pTwo)) );
		}
		else
		{
			return pOne;
		}
	}
	else
	{
		if ( IsViableTarget(pTwo) )
		{
			return pTwo;
		}
		else
		{
			return NULL;
		}
	}
}

CEntity* CBotAI::Closest( CEntity* pOne, CEntity* pTwo )
{
	CVector	vDeltaOne, vDeltaTwo;
	
	ASSERT( m_pBot != NULL );
	vDeltaOne = pOne->GetOrigin() - m_pBot->GetOrigin();
	vDeltaTwo = pTwo->GetOrigin() - m_pBot->GetOrigin();

	if ( vDeltaOne.Length() > vDeltaTwo.Length() )
	{
		return pTwo;
	}
	else
	{
		return pOne;
	}
}

//////////////////////////////////////////////////////////////////////
// End of BotAI.cpp
//////////////////////////////////////////////////////////////////////