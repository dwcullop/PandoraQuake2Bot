// PandoraDefs.h: Defines used through out Pandora Bot
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

#ifndef PANDORA_DEFS_H
#define PANDORA_DEFS_H

//////////////////////////////////////////////////////////////////////
// Quake 2 Network Stuff
//////////////////////////////////////////////////////////////////////

// General
	//#define PROTOCOL_VERSION					31	// v3.14
	//#define PROTOCOL_VERSION					32	// v3.15
#define PROTOCOL_VERSION					34	// v3.16 - v3.20

//////////////////////////////////////////////////////////////////////
// Quake 2 Defines
//////////////////////////////////////////////////////////////////////

// These come from "q_shared.h" in the DLL source
	// Max Values
#define	MAX_CLIENTS							256	
#define	MAX_EDICTS							1024
#define	MAX_LIGHTSTYLES						256
#define	MAX_MODELS							256	
#define	MAX_SOUNDS							256
#define	MAX_IMAGES							256
#define	MAX_ITEMS							256
#define MAX_STATS							32
	// Config String Index Numbers
#define	CS_NAME								0
#define	CS_CDTRACK							1
#define	CS_SKY								2
#define	CS_SKYAXIS							3
#define	CS_SKYROTATE						4
#define	CS_STATUSBAR						5
#define	CS_MAXCLIENTS						30
#define	CS_MAPCHECKSUM						31
#define	CS_MODELS							32
#define	CS_SOUNDS							(CS_MODELS+MAX_MODELS)
#define	CS_IMAGES							(CS_SOUNDS+MAX_SOUNDS)
#define	CS_LIGHTS							(CS_IMAGES+MAX_IMAGES)
#define	CS_ITEMS							(CS_LIGHTS+MAX_LIGHTSTYLES)
#define	CS_PLAYERSKINS						(CS_ITEMS+MAX_ITEMS)
#define	MAX_CONFIGSTRINGS					(CS_PLAYERSKINS+MAX_CLIENTS)
	// Pressed Button Values
#define BUTTON_ATTACK						0x01
#define BUTTON_USE							0x02
#define BUTTON_ANY							0x80
// End from "q_shared.h"
#define FRAME_HISTORY_SIZE					16
#define DEFAULT_SERVER_PORT					27910
#define DEFAULT_CLIENT_PORT					27901
#define DEFAULT_MASTER_PORT					27900
#define DEFAULT_IP							"127.0.0.1"

//////////////////////////////////////////////////////////////////////
// Packet Information
//////////////////////////////////////////////////////////////////////

#define RELIABLE_FLAG						0x80000000
#define PACKET_HEADER_SIZE					(sizeof(UINT) + sizeof(UINT))
#define CONNECTIONLESS_HEADER_SIZE			(sizeof(UINT))
#define MAX_PACKET_LENGTH					1400
#define NEW_LINE							((char)(0x0A))
#define MOVE_FRAMES							3

//////////////////////////////////////////////////////////////////////
// Server Message Types
//////////////////////////////////////////////////////////////////////

#define SVC_BAD								0x00
#define SVC_MUZZLEFLASH						0x01
#define SVC_MUZZLFLASH2						0x02
#define SVC_TEMP_ENTITY						0x03
#define SVC_LAYOUT							0x04
#define SVC_INVENTORY						0x05
#define SVC_NOP								0x06
#define SVC_DISCONNECT						0x07
#define SVC_RECONNECT						0x08
#define SVC_SOUND							0x09
#define SVC_PRINT							0x0A
#define SVC_STUFFTEXT						0x0B
#define SVC_SERVERDATA						0x0C
#define SVC_CONFIGSTRING					0x0D
#define SVC_SPAWNBASELINE					0x0E
#define SVC_CENTERPRINT						0x0F
#define SVC_DOWNLOAD						0x10
#define SVC_PLAYERINFO						0x11
#define SVC_PACKETENTITIES					0x12
#define SVC_DELTAPACKETENTITIES				0x13
#define SVC_FRAME							0x14

//////////////////////////////////////////////////////////////////////
// Client Message Types
//////////////////////////////////////////////////////////////////////

#define CLC_BAD								0x00
#define CLC_NOP								0x01
#define CLC_MOVE							0x02
#define CLC_USERINFO						0x03
#define CLC_STRINGCMD						0x04

//////////////////////////////////////////////////////////////////////
// Player Move Types
//////////////////////////////////////////////////////////////////////

#define PM_NORMAL							0x00
#define PM_SPECTATOR						0x01
#define PM_DEAD								0x02
#define PM_GIB								0x03
#define PM_FREEZE							0x04

//////////////////////////////////////////////////////////////////////
// Player Move Flags
//////////////////////////////////////////////////////////////////////

#define PMF_DUCKED							0x01
#define PMF_JUMP_HELD						0x02
#define PMF_ON_GROUND						0x04
#define PMF_TIME_WATERJUMP					0x08
#define PMF_TIME_LAND						0x10
#define PMF_TIME_TELEPORT					0x20
#define PMF_NO_PREDICTION					0x40

//////////////////////////////////////////////////////////////////////
// Player Rendering Flags
//////////////////////////////////////////////////////////////////////

#define RDF_UNDERWATER						0x01
#define RDF_NOWORLDMODEL					0x02

//////////////////////////////////////////////////////////////////////
// Player Stat Array Index Values
//////////////////////////////////////////////////////////////////////

#define STAT_HEALTH_ICON					0x00
#define STAT_HEALTH							0x01
#define STAT_AMMO_ICON						0x02
#define STAT_AMMO							0x03
#define STAT_ARMOR_ICON						0x04
#define STAT_ARMOR							0x05
#define STAT_SELECTED_ICON					0x06
#define STAT_PICKUP_ICON					0x07
#define STAT_PICKUP_STRING					0x08
#define STAT_TIMER_ICON						0x09
#define STAT_TIME							0x0A
#define STAT_HELPICON						0x0B
#define STAT_SELECTED_ITEM					0x0C
#define STAT_LAYOUTS						0x0D
#define STAT_FRAGS							0x0E
#define STAT_FLASHES						0x0F

//////////////////////////////////////////////////////////////////////
// Attenuation Types
//////////////////////////////////////////////////////////////////////

#define ATTN_NONE							0x00
#define ATTN_NORM							0x01
#define ATTN_IDLE							0x02
#define ATTN_STATIC							0x03

//////////////////////////////////////////////////////////////////////
// Sound Channels
//////////////////////////////////////////////////////////////////////

#define CHAN_AUTO							0x00
#define CHAN_WEAPON							0x01
#define CHAN_VOICE							0x02
#define CHAN_ITEM							0x03
#define CHAN_BODY							0x04

//////////////////////////////////////////////////////////////////////
// Entity Effects
//////////////////////////////////////////////////////////////////////

#define EF_ROTATE							0x000001
#define EF_GIB								0x000002
#define EF_BLASTER							0x000008
#define EF_ROCKET							0x000010
#define EF_GRENADE							0x000020
#define EF_HYPERBLASTER						0x000040
#define	EF_BFG								0x000080
#define EF_COLOR_SHELL						0x000100
#define EF_POWERSCREEN						0x000200
#define EF_ANIM01							0x000400
#define EF_ANIM23							0x000800
#define EF_ANIM_ALL							0x001000
#define EF_ANIM_ALLFAST						0x002000
#define EF_FLIES							0x004000
#define EF_QUAD								0x008000
#define EF_PENT								0x010000
#define EF_TELEPORTER						0x020000
#define EF_FLAG1							0x040000
#define EF_FLAG2							0x080000
#define EF_BOOMER							0x100000
#define EF_GREENGIB							0x200000

//////////////////////////////////////////////////////////////////////
// RenderFX
//////////////////////////////////////////////////////////////////////

#define RF_MINLIGHT							0x0001
#define RF_VIEWERMODEL						0x0002
#define RF_WEAPONMODEL						0x0004
#define RF_FULLBRIGHT						0x0008
#define RF_DEPTHHACK						0x0010
#define RF_TRANSLUCENT						0x0020
#define RF_FRAMELERP						0x0040
#define RF_BEAM								0x0080
#define RF_CUSTOMSKIN						0x0100
#define RF_GLOW								0x0200
#define RF_SHELL_RED						0x0400
#define RF_SHELL_GREEN						0x0800
#define RF_SHELL_BLUE						0x1000

//////////////////////////////////////////////////////////////////////
// Entity Events
//////////////////////////////////////////////////////////////////////

#define EV_NONE								0x00
#define EV_ITEM_RESPAWN						0x01
#define EV_FOOTSTEP							0x02
#define EV_FALLSHORT						0x03
#define EV_MALE_FALL						0x04
#define EV_MALE_FALLFAR						0x05
#define EV_FEMALE_FALL						0x06
#define EV_FEMALE_FALLFAR					0x07
#define EV_PLAYER_TELEPORT					0x08

//////////////////////////////////////////////////////////////////////
// Message Levels
//////////////////////////////////////////////////////////////////////

#define PRINT_LOW							0x00
#define PRINT_MEDIUM						0x01
#define PRINT_HIGH							0x02
#define PRINT_CHAT							0x03
	// This is added just for the Pandora Bot
#define PRINT_OTHER							0xFF

//////////////////////////////////////////////////////////////////////
// Muzzle Flashes
//////////////////////////////////////////////////////////////////////

#define MZ_BLASTER							0x00
#define MZ_MACHINEGUN						0x01
#define MZ_SHOTGUN							0x02
#define MZ_CHAINGUN1						0x03
#define MZ_CHAINGUN2						0x04
#define MZ_CHAINGUN3						0x05
#define MZ_RAILGUN							0x06
#define MZ_ROCKET							0x07
#define MZ_GRENADE							0x08
#define MZ_LOGIN							0x09
#define MZ_LOGOUT							0x0A
#define MZ_RESPAWN							0x0B
#define MZ_BFG								0x0C
#define MZ_SSHOTGUN							0x0D
#define MZ_HYPERBLASTER						0x0E
#define MZ_ITEMRESPAWN						0x0F
#define MZ_BOOMERGUN						0x10
#define MZ_SILENCED							0xF0

//////////////////////////////////////////////////////////////////////
// Temporary Entities
//////////////////////////////////////////////////////////////////////

#define TE_GUNSHOT							0
#define TE_BLOOD							1
#define TE_BLASTER							2
#define TE_RAILTRAIL						3
#define TE_SHOTGUN							4
#define TE_EXPLOSION1						5
#define TE_EXPLOSION2						6
#define TE_ROCKET_EXPLOSION					7
#define TE_GRENADE_EXPLOSION				8
#define TE_SPARKS							9
#define TE_SPLASH							10
#define TE_BUBBLETRAIL						11
#define TE_SCREEN_SPARKS					12
#define TE_SHIELD_SPARKS					13
#define TE_BULLET_SPARKS					14
#define TE_LASER_SPARKS						15
#define TE_PARASITE_ATTACK					16
#define TE_ROCKET_EXPLOSION_WATER			17
#define TE_GRENADE_EXPLOSION_WATER			18
#define TE_MEDIC_CABLE_ATTACK				19
#define TE_BFG_EXPLOSION					20
#define TE_BFG_BIGEXPLOSION					21
#define TE_BOSSTPORT						22
#define TE_BFG_LASER						23
#define TE_GRAPPLE_CABLE					24
#define TE_WELDING_SPARKS					25
#define TE_PLASMATRAIL						26
#define TE_GREENBLOOD						27

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////

#endif // PANDORA_DEFS_H