//	AIThread.cpp : implementation file
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
#include "Pandora.h"
#include "AIThread.h"
#include "PandoraDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIThread Defines

#define TWO_RADICAL_TWO					( 2.828427124746f )
#define MOVE_DISTANCE					( 30.0f )

/////////////////////////////////////////////////////////////////////////////
// CAIThread

IMPLEMENT_DYNCREATE(CAIThread, CBotThread)

/////////////////////////////////////////////////////////////////////////////
// CAIThread Construction / Destruction

CAIThread::CAIThread()
{
	ResetAI();
}

CAIThread::~CAIThread()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAIThread Avoid Operations
/*
BOOL CAIThread::AvoidDangerous(CQuakeVisObjectList* pVisible)
{
	if ( AvoidFlyingDanger(pVisible) == FALSE)
	{
		if ( AvoidSittingDanger(pVisible) == FALSE )
		{
			if ( AvoidPlayersSights() == FALSE )
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CAIThread::AvoidEntity(CQuakeEntity* pAvoidMe)
{
	CQuakeVector	vSafe;
	float			nSafeDistance;
	float			nSafeYaw	= pAvoidMe->GetYawAngle();
	float			nSafePitch	= pAvoidMe->GetPitchAngle();

	nSafeDistance	= Length( pAvoidMe->GetPosition() - GetBotPosition() );
	nSafeDistance	*= TWO_RADICAL_TWO;
	if ( IsBotStuck() )
	{
		m_bAvoidYawPlus		= ( !(m_bAvoidYawPlus) );
		m_bAvoidPitchPlus	= ( !(m_bAvoidPitchPlus) );
	}
	else
	{
		if ( m_tAvoidTimer.Elapsed() > ((double)(1.5)) )
		{
			m_tAvoidTimer.SetCurrent();
			m_bAvoidYawPlus		= ( (rand() % 2) ? TRUE : FALSE );
			m_bAvoidPitchPlus	= ( (rand() % 2) ? TRUE : FALSE );
		}
	}
	nSafeYaw		+= ( m_bAvoidYawPlus ? ((float)(45.0)) : ((float)(-45.0)) );
	nSafePitch		+= ( m_bAvoidPitchPlus ? ((float)(45.0)) : ((float)(-45.0)) );
	vSafe.SetAngles( nSafePitch, nSafeYaw );
	vSafe.ScaleTo( nSafeDistance );
	GetBot()->SetMoveTarget( vSafe );
}

BOOL CAIThread::AvoidFlyingDanger(CQuakeVisObjectList* pVisible)
{
	CQuakeEntity*		pCurrent;
	POSITION			pPosition;

	pVisible->FindVisibleObjects( &m_lstVisible, m_arrFlyingDanger, GetBotPosition() );
	pPosition = m_lstVisible.GetHeadPosition();
	while (pPosition != NULL)
	{
		pCurrent = (CQuakeEntity*)m_lstVisible.GetNext(pPosition);
		if (pCurrent->IsPointingAt( GetBotPosition() ))
		{
			//TRACE("Trying to avoid a \"%s\"\n", pCurrent->GetModelName() );
			AvoidEntity( pCurrent );
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAIThread::AvoidPlayersSights()
{
	POSITION pPosition = m_lstPlayers.GetHeadPosition();
	if (pPosition != NULL)
	{
		CQuakePlayer*	pCurrent;
		while (pPosition != NULL)
		{
			pCurrent = ( (CQuakePlayer*) m_lstPlayers.GetNext(pPosition) );
			if ( pCurrent->IsPointingAt(GetBotPosition()) )
			{
				if ( pCurrent != GetBot() )
				{
					//TRACE("Trying to avoid \"%s\"\n", pCurrent->GetName() );
					AvoidEntity( pCurrent );
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CAIThread::AvoidSittingDanger(CQuakeVisObjectList* pVisible)
{
	CQuakeEntity*	pCurrent;
	POSITION		pPosition;

	pVisible->FindVisibleObjects( &m_lstVisible, m_arrSittingDanger, GetBotPosition() );
	pPosition = m_lstVisible.GetHeadPosition();
	if (pPosition != NULL)
	{
		pCurrent = (CQuakeEntity*)m_lstVisible.GetNext(pPosition);
		float nDistance = Length( pCurrent->GetPosition() - GetBotPosition() );
		if ( nDistance < ((float)(300.0)) )
		{
			//TRACE("Trying to avoid a \"%s\"\n", pCurrent->GetModelName() );
			m_pBotDoc->GetBot()->Jump();
			CQuakeVector vMoveGoal = ( pCurrent->GetPosition() - GetBotPosition() );
			vMoveGoal *= -1;
			vMoveGoal += GetBotPosition();
			GetBot()->SetMoveTarget( vMoveGoal );
			return TRUE;
		}
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CAIThread Find Operations

BOOL CAIThread::FindItems(CQuakeVisObjectList* pVisible)
{
	if ( (GetBot()->GetMaxDamage() > 80) || (FindCloseItem(pVisible, m_arrHealthItems)==FALSE) )
	{
		if ( FindCloseItem(pVisible, m_arrPowerUps) == FALSE)
		{
			if ( FindCloseItem(pVisible, m_arrWeaponItems) == FALSE)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CAIThread::FindNeeded(CQuakeVisObjectList* pVisible)
{
	if ( GetBot()->GetMaxDamage() < 50 )
	{
		// Find Health
		if ( FindCloseItem(pVisible, m_arrHealthItems) )
		{
			return TRUE;
		}
	}
	if ( GetBot()->GetWeapon() == IT_AXE )
	{
		// Find weapons
		if ( FindCloseItem(pVisible, m_arrWeaponItems) )
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAIThread::FindCloseItem(CQuakeVisObjectList* pVisible, CByteArray& arrModelList)
{
	CQuakeEntity*		pCurrent;
	POSITION			pPosition;

	pVisible->FindVisibleObjects( &m_lstVisible, arrModelList, GetBotPosition() );
	pPosition = m_lstVisible.GetHeadPosition();
	while (pPosition != NULL)
	{
		pCurrent = (CQuakeEntity*)m_lstVisible.GetNext(pPosition);
		if ( Length(pCurrent->GetPosition() - GetBotPosition()) < 150.0)
		{
			GetBot()->SetMoveTarget( pCurrent->GetPosition() );
			return TRUE;
		}
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////
// CAIThread Targeting / Weapons Operations

BOOL CAIThread::AttackTarget()
{
	// If there is a current target, try to circle around them while attacking
	CQuakePlayer*	pTarget		= GetBot()->GetTarget();

	if (pTarget == NULL)
	{
		return FALSE;
	}
	else
	{
		if ( IsBotStuck() )
		{
			GetBot()->SetMoveTarget( CQuakeVector(TRUE) );
		}
		else
		{
			float			nArcYaw;
			float			nArcPitch;
			CQuakeVector	vMoveGoal	= (GetBotPosition() - pTarget->GetPosition());

			vMoveGoal.SetZ( 0.0 );
			nArcYaw		= vMoveGoal.GetYawAngle();
			nArcPitch	= vMoveGoal.GetPitchAngle();

			if ( m_tAttackTimer.Elapsed() >= ((double)(1.0)) )
			{
				m_bAttackPlus = ( (rand() % 2) ? TRUE : FALSE );
				m_tAttackTimer.SetCurrent();
			}
			nArcYaw += ( m_bAttackPlus ? ((float)(90.0)) : ((float)(-90.0)) );
			vMoveGoal.SetAngles( nArcPitch, nArcYaw );
			vMoveGoal.ScaleTo( (100) );
			vMoveGoal += pTarget->GetPosition();
			GetBot()->SetMoveTarget( vMoveGoal );
		}
	}
	return TRUE;
}

BOOL CAIThread::IsViableTarget(CQuakePlayer* pTarget)
{
	ASSERT( pTarget != NULL );
	if ( pTarget == m_pBotDoc->GetBot() )
	{
		// The bot should not target itself
		return FALSE;
	}
	if ( pTarget->IsDead() )
	{
		// Already dead targets are no good
		return FALSE;
	}
	if ( m_pBotDoc->GetServer()->IsTeamGame() )
	{
		if ( pTarget->IsTeamMate(m_pBotDoc->GetBot()) )
		{
			// Do not attack teammates
			return FALSE;
		}
	}

	// Otherwise, if it's visible, then it's good!
	return ( pTarget->IsVisible() );

	// TODO: put in code to see if there is a clear shot at the target
	// TODO: put in code to see if there is a weapon to safely hit the target
	// with.  For example, if all the bot has is the rocket launcher and the
	// axe, and they are out of axe range, but too close for the rocket launcher
	// then don't attack them (unless it's teamplay 1, then fire away).
}

BOOL CAIThread::CurrentTargetInvalid()
{
	CQuakePlayer* pTarget;
	
	pTarget = m_pBotDoc->GetBot()->GetTarget();
	if ( pTarget == NULL )
	{
		return TRUE;
	}
	else
	{
		return ( !(IsViableTarget( pTarget )) );
	}
}

void CAIThread::AcquireTarget()
{
	POSITION pPosition = m_lstPlayers.GetHeadPosition();
	if (pPosition != NULL)
	{
		CQuakePlayer*	pCurrent;
		while (pPosition != NULL)
		{
			pCurrent = ( (CQuakePlayer*) m_lstVisible.GetNext(pPosition) );
			if ( IsViableTarget( pCurrent ) )
			{
				// If the current target is good, then select it
				GetBot()->SetTarget( pCurrent );
				pPosition = NULL;
			}
			else
			{
				// Otherwise, if it's the last one in the list
				// then select no target
				if ( pPosition == NULL )
				{
					GetBot()->SetTarget( NULL );
				}
			}
		}
	}
	else
	{
		// If there are no visible players, then don't select a target
		GetBot()->SetTarget( NULL );
	}
	// Select the best weapon
	SelectWeapon();
	// Determine whether or not to fire
	SelectFire();
}

void CAIThread::SelectWeapon()
{
	// This function will select the best weapon based on current bot conditions,
	// the bot's target, and server settings
	// If there is no current target, the bot will select the Axe, that way it
	// will appear to be out of ammo, when it might have the rocket launcher.
	// Pretty sneaky, huh?
	//
	// TODO : Have it take distance to the target into account when selecting
	// a weapon
	CQuakePlayer*	pTarget		= GetBot()->GetTarget();
	BOOL			bUseSafety	= m_pBotDoc->GetServer()->CanHurtSelf();

	if (pTarget != NULL)
	{
		GetBot()->Attack();
		if ( GetBot()->UseWeapon( SELECT_WEAPON_LIGHTNING, bUseSafety ) == FALSE )
			if ( GetBot()->UseWeapon( SELECT_WEAPON_ROCKET, bUseSafety ) == FALSE )
				if ( GetBot()->UseWeapon( SELECT_WEAPON_GRENADE, bUseSafety ) == FALSE )
					if ( GetBot()->UseWeapon( SELECT_WEAPON_SUPER_NAILGUN, bUseSafety ) == FALSE )
						if ( GetBot()->UseWeapon( SELECT_WEAPON_SUPER_SHOTGUN, bUseSafety ) == FALSE )
							if ( GetBot()->UseWeapon( SELECT_WEAPON_NAILGUN, bUseSafety ) == FALSE )
								if ( GetBot()->UseWeapon( SELECT_WEAPON_SHOTGUN, bUseSafety ) == FALSE )
								{
									if ( Length(GetBotPosition() - pTarget->GetPosition()) > 50.0)
									{
										GetBot()->SetTarget( NULL );
									}
									GetBot()->UseWeapon( SELECT_WEAPON_AXE, bUseSafety );
								}
	}
}

void CAIThread::SelectFire()
{
	// TODO: Combine this with SelectWeapon and AcquireTarget, so it can determine
	// whether or not it has a suitable weapon for the current target...
	// As in, if all it has is the Axe, it won't attack when the target is out of
	// range of the axe
	if ( GetBot()->GetTarget() == NULL )
	{
		GetBot()->NoAttack();
	}
	else
	{
		GetBot()->Attack();
		//m_pBotDoc->GetBot()->NoAttack();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAIThread Movement Operations

void CAIThread::NoTargetMove()
{
	// Do the jump stuff (randomly jump and randomly stop jumping)
	if ((rand() % 15) == 0)
	{
		GetBot()->Jump();
	}
	else
	{
		GetBot()->NoJump();
	}
	// Turn randomly every 5 seconds
	if (m_tTurnTimer.Elapsed() > ((double)(5.0)))
	{
		m_tTurnTimer.SetCurrent();
		GetBot()->SetLook( CQuakeVector(TRUE) );
	}
	// Change directions randomly every 1 second
	if (m_tMoveTimer.Elapsed() > ((double)(1.0)))
	{
		m_tMoveTimer.SetCurrent();
		GetBot()->SetMoveTarget( CQuakeVector(TRUE) );
	}
}

void CAIThread::DoMove(CQuakeVisObjectList* pVisible)
{
	// Increment the move counter
	m_nMoveCount++;

	// Always, always, always attack if possible
	// This function will start shooting if there is a target
	// and stop shooting if there is not.
	AcquireTarget();

	if ( IsBotStuck() )
	{
		m_tMoveTimer.SetCurrent();
		GetBot()->SetMoveTarget( CQuakeVector(TRUE) );
	}
	else
	{
		// If there is something to avoid, avoid it
		if ( AvoidDangerous(pVisible) == FALSE )
		{
			if ( FindNeeded(pVisible) == FALSE )
			{
				if ( AttackTarget() == FALSE )
				{
					if ( FindItems(pVisible) == FALSE )
					{
						NoTargetMove();
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAIThread Operations

BOOL CAIThread::IsBotStuck()
{
	return ( Length( GetBot()->GetVelocity() ) < ((float)(10.0)) );
}

void CAIThread::ResetAI()
{
	m_nMoveCount	= 0;
	m_nRespawnPhase	= RESPAWN_PHASE_ALIVE;
	m_pBotDoc->GetBot()->NoAttack();
}
*/

/////////////////////////////////////////////////////////////////////////////
// CAIThread Programmed Moves

void CAIThread::RespawnOne()
{
	m_bmCurrent.Clear();
	m_pDoMove = &CAIThread::RespawnTwo;
}

void CAIThread::RespawnTwo()
{
	m_bmCurrent.Clear();
	m_bmCurrent.SetAttack( Yes );
	m_bmCurrent.SetJump( Yes );
	SelectMove();
}

void CAIThread::NewInventoryMove()
{
	CWeaponSpec* pBest = SelectBestWeapon();

	if ( pBest != NULL )
	{
		UseItem( pBest->GetInventoryIndex() );
	}
	SelectMove();
}

void CAIThread::NormalMove()
{
	float	nDist;

	if ( m_pMoveTarget != NULL )
	{
		nDist = ( m_vBotOrigin - m_pMoveTarget->GetOrigin() );
		if ( (nDist < MOVE_DISTANCE) || (nDist > MOVE_DISTANCE*3) )
		{
			m_pMoveTarget = NULL;
		}
	}
	if ( m_pAttackTarget == NULL )
	{
		GetAttackTarget();
	}
	if ( m_pMoveTarget == NULL )
	{
		GetMoveTarget();
	}
	MoveToMapPoint();
}

void CAIThread::RandomMove()
{
	MoveRandomly( MOVE_DISTANCE*2 );
	SelectMove();
}

/////////////////////////////////////////////////////////////////////////////
// CAIThread Operations

void CAIThread::GetAttackTarget()
{
	// TODO: Make this more better
	m_pAttackTarget = FindBestPlayer( &CBotAI::Closest );
}

void CAIThread::GetMoveTarget()
{
	// TODO: Make this more better
	if ( m_pAttackTarget == NULL )
	{
		RandomMove();
	}
	else
	{
		MoveToEntity( m_pAttackTarget );
	}
	// m_pMoveTarget should never be NULL when exiting this function
	ASSERT( m_pMoveTarget != NULL );
}

BOOL CAIThread::InitInstance()
{
	SetClient( m_pBotDoc );
	SetGameState( m_pBotDoc );
	m_aiGameData.ReadDataFile("gamedata.txt");
	m_pDoMove = &CAIThread::NormalMove;
	return TRUE;
}

int CAIThread::ExitInstance()
{
	return CBotThread::ExitInstance();
}

void CAIThread::UpdateInfo( const UINT& nResID )
{
	CBot* pBot;

	m_pBotDoc->Lock();
	pBot = m_pBotDoc->GetBot();
	if ( pBot != NULL )
	{
		pBot->SetAIInfo( nResID );
	}
	m_pBotDoc->Unlock();
}

void CAIThread::SelectMove()
{
	// TODO: Make this less useless
	m_pDoMove = &CAIThread::NormalMove;
	// This should never be NULL when exiting this function
	ASSERT( m_pDoMove != NULL );
}

void CAIThread::ComputeMove()
{
	if ( m_pDoMove == NULL )
	{
		SelectMove();
	}
	if ( PrepareMove() )
	{
		( this->*m_pDoMove )();
		SendMove();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAIThread Message Map Definition

BEGIN_MESSAGE_MAP(CAIThread, CBotThread)
	//{{AFX_MSG_MAP(CAIThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIThread message handlers

void CAIThread::OnBotKilled( const WORD nDeaths )
{
	m_pDoMove = &CAIThread::RespawnOne;
	m_pAttackTarget = NULL;
	m_pMoveTarget = NULL;
}

void CAIThread::OnBotRespawned()
{
	WORD nDeaths;

	ASSERT( m_pBotDoc != NULL );
	nDeaths = m_pBotDoc->GetBot()->GetDeaths();
	m_pBotDoc->ConsoleCommand( CString((LPCSTR)IDS_CMD_INVEN) );
	if ( nDeaths == 0 )
	{
		CString strChat;

		strChat.Format("%s %s %s", 
			CString((LPCSTR)IDS_CHAT_GREETING1),
			CString((LPCSTR)IDS_CHAT_GREETING2),
			CString((LPCSTR)IDS_WEB_PANDORA));
		m_pBotDoc->Say( strChat );
	}
	SelectMove();
}

void CAIThread::OnBotUpdateAttackTarget()
{
	m_pMoveTarget = NULL;
}

void CAIThread::OnBotUpdateInventory()
{
	m_pDoMove = &CAIThread::NewInventoryMove;
}

void CAIThread::OnBotUpdateGunIndex()
{
	ASSERT( m_pBotDoc != NULL );
	CBot* pBot = m_pBotDoc->GetBot();

	if ( pBot != NULL )
	{
		BYTE				nIndex	= pBot->GetPlayerInfo().GetGunIndex();
		const CWeaponSpec*	pTemp;

		pTemp = m_aiGameData.FindWeaponByViewModel( pBot->GetPlayerInfo().GetGunIndex() );
		pBot->SetWeapon( pTemp );
	}
}

void CAIThread::OnBotUpdateOrigin()
{
	ASSERT( m_pBotDoc != NULL );
	if ( m_pMoveTarget != NULL )
	{
		CBot*	pBot = m_pBotDoc->GetBot();
		float	nDist;

		if ( pBot != NULL )
		{
			nDist = ( pBot->GetOrigin() - m_pMoveTarget->GetOrigin() );
			if ( nDist < MOVE_DISTANCE )
			{
				m_pMoveTarget = NULL;
			}
			if ( nDist > MOVE_DISTANCE*3 )
			{
				m_pMoveTarget = NULL;
			}
		}
	}
}

void CAIThread::OnBotUpdateVelocity()
{
	ASSERT( m_pBotDoc != NULL );
	m_pBot = m_pBotDoc->GetBot();

	if ( m_pBot != NULL )
	{
		if ( IsBotStuck() )
		{
			m_pDoMove = &CAIThread::RandomMove;
		}
		m_pBot = NULL;
	}
}

void CAIThread::OnBotPickupItem()
{
	ASSERT( m_pBotDoc != NULL );
	m_pBotDoc->ConsoleCommand( CString((LPCSTR)IDS_CMD_INVEN) );
}

void CAIThread::OnEntityUpdateActive( const WORD nEntity )
{
	ASSERT( m_pBotDoc != NULL );
	if ( m_pBotDoc->IsReady() )
	{
		CEntity* pEntity = m_pBotDoc->GetEntity( nEntity );
		AddEntity( pEntity );
	}
}

void CAIThread::OnEntityUpdateRemove( const WORD nEntity )
{
	ASSERT( m_pBotDoc != NULL );
	if ( m_pBotDoc->IsReady() )
	{
		CEntity* pEntity = m_pBotDoc->GetEntity( nEntity );
		RemoveEntity( pEntity );
	}
}

void CAIThread::OnPlayerUpdateFrame( const BYTE nPlayer )
{
	m_pBotDoc->Lock();
	if ( m_pBotDoc->IsReady() )
	{
		CPlayer* pUpdated = m_pBotDoc->GetPlayer( nPlayer );
		if ( pUpdated->IsSaluting() )
		{
			m_pBotDoc->WaveSalute();
		}
	}
	m_pBotDoc->Unlock();
}

void CAIThread::OnPlayerUpdateActive( const BYTE nPlayer )
{
	ASSERT( m_pBotDoc != NULL );
	if ( m_pBotDoc->IsReady() )
	{
		CPlayer* pPlayer = m_pBotDoc->GetPlayer( nPlayer );
		AddPlayer( pPlayer );
	}
}

void CAIThread::OnPlayerUpdateRemove( const BYTE nPlayer )
{
	ASSERT( m_pBotDoc != NULL );
	if ( m_pBotDoc->IsReady() )
	{
		CPlayer* pAttack = m_pBotDoc->GetPlayer( nPlayer );

		if ( pAttack ==	m_pAttackTarget )
		{
			m_pAttackTarget = NULL;
		}
		RemovePlayer( pAttack );
	}
}

void CAIThread::OnPlayerKilled( const BYTE nPlayer )
{
	ASSERT( m_pBotDoc != NULL );
	if ( m_pBotDoc->IsReady() )
	{
		CPlayer* pAttack = m_pBotDoc->GetPlayer( nPlayer );

		if ( pAttack ==	m_pAttackTarget )
		{
			m_pAttackTarget = NULL;
		}
		RemovePlayer( pAttack );
	}
}

void CAIThread::OnNetworkBeginLevel()
{
	ResetAI();
	m_aiGameData.ProcessNewConfigStrings( m_pBotDoc );
}

void CAIThread::OnNetworkEndLevel()
{
	CString strTemp;

	strTemp.Format("CAIThread: %d Moves\n", m_nMoveCount);
	m_pBotDoc->DisplayText( strTemp );
}

/*
void CAIThread::OnDamage(CQuakeDamage* pDamage)
{
	m_pBotDoc->LockObject( pDamage );
	// TODO: Have it try to determine who attacked it, and start targeting them
	m_pBotDoc->ReleaseObject( pDamage );
}

void CAIThread::OnTempEntity(CQuakeTempEntity* pTempEnt)
{
	m_pBotDoc->LockObject( pTempEnt );
	// TODO: Have it try to determine whether or not it hit
	// it's target
	m_pBotDoc->ReleaseObject( pTempEnt );
}

void CAIThread::OnLevelInitialized()
{
	// Set up the flying dangerous objects list
	m_arrFlyingDanger.RemoveAll();
	AddModelIndex( m_arrFlyingDanger, MODEL_DANGEROUS_MISSILE );
	AddModelIndex( m_arrFlyingDanger, MODEL_DANGEROUS_SUPER_SPIKE );
	AddModelIndex( m_arrFlyingDanger, MODEL_DANGEROUS_SPIKE );
	AddModelIndex( m_arrFlyingDanger, MODEL_DANGEROUS_LAVABALL );
	AddModelIndex( m_arrFlyingDanger, MODEL_DANGEROUS_LASER );
	AddModelIndex( m_arrFlyingDanger, MODEL_DANGEROUS_SPIKEBALL );
	// Set up the stationary dangerous objects list
	m_arrSittingDanger.RemoveAll();
	AddModelIndex( m_arrSittingDanger, MODEL_DANGEROUS_GRENADE );
	AddModelIndex( m_arrSittingDanger, MODEL_EXPLOSIVE_BOX_1 );
	AddModelIndex( m_arrSittingDanger, MODEL_EXPLOSIVE_BOX_2 );
	// Set up the health items list
	m_arrHealthItems.RemoveAll();
	AddModelIndex( m_arrHealthItems, MODEL_HEALTH_SMALL);
	AddModelIndex( m_arrHealthItems, MODEL_HEALTH_LARGE);
	AddModelIndex( m_arrHealthItems, MODEL_HEALTH_SUPER);
	AddModelIndex( m_arrHealthItems, MODEL_ARMOR);
	// Set up the weapons item list
	m_arrWeaponItems.RemoveAll();
	AddModelIndex( m_arrWeaponItems, MODEL_WEAPON_LIGHTNING_GUN);
	AddModelIndex( m_arrWeaponItems, MODEL_WEAPON_ROCKET_LAUNCHER);
	AddModelIndex( m_arrWeaponItems, MODEL_WEAPON_GRENADE_LAUNCHER);
	AddModelIndex( m_arrWeaponItems, MODEL_WEAPON_SUPER_NAILGUN);
	AddModelIndex( m_arrWeaponItems, MODEL_WEAPON_NAILGUN);
	AddModelIndex( m_arrWeaponItems, MODEL_WEAPON_DB_SHOTGUN);
	AddModelIndex( m_arrWeaponItems, MODEL_EXTRA_BACKPACK);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_CELLS_LARGE);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_CELLS_SMALL);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_ROCKETS_LARGE);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_ROCKETS_SMALL);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_NAILS_LARGE);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_NAILS_SMALL);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_SHELLS_LARGE);
	AddModelIndex( m_arrWeaponItems, MODEL_AMMO_SHELLS_SMALL);
	// Set up the power up item list
	m_arrPowerUps.RemoveAll();
	AddModelIndex( m_arrPowerUps, MODEL_EXTRA_BACKPACK);
	AddModelIndex( m_arrPowerUps, MODEL_EXTRA_QUAD);
	AddModelIndex( m_arrPowerUps, MODEL_EXTRA_EYES);
	AddModelIndex( m_arrPowerUps, MODEL_EXTRA_PENT);
	AddModelIndex( m_arrPowerUps, MODEL_EXTRA_SUIT);
}

void CAIThread::OnVisList(CQuakeVisObjectList* pVisList)
{
	m_pBotDoc->LockObject(pVisList);
	if (m_pBotDoc->GetServerStatus() == SERVER_STATUS_CONNECTED)
	{
		switch(m_nRespawnPhase)
		{
		case RESPAWN_PHASE_ALIVE:
			pVisList->FindVisiblePlayers( &m_lstPlayers, m_pBotDoc->GetMaxPlayers(), GetBotPosition() );
			DoMove(pVisList);
			break;
		case RESPAWN_PHASE_1:
			m_pBotDoc->GetBot()->NoAction();
			m_nRespawnPhase = RESPAWN_PHASE_2;
			break;
		case RESPAWN_PHASE_2:
			m_pBotDoc->GetBot()->JumpAndAttack();
			m_nRespawnPhase = RESPAWN_PHASE_1;
			break;
		}
		m_pBotDoc->PostMessage(QB_BOT_MOVE_PROCESSED);
	}
	m_pBotDoc->ReleaseObject(pVisList);
}

*/

/////////////////////////////////////////////////////////////////////////////