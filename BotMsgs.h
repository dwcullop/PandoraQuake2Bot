//////////////////////////////////////////////////////////////////////////////
//	QuakeBotMsgs.h : header file to define custom Windows Messages for the Bot
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
//					
//	Developer Notes:
//		This file defines all the messages that the bot threads will
//		post to each other.  There are different events for each of
//		the many different aspects of a bot.					
//
//		They arranged the way they are to preserve readability	
//		and to make it easy it "insert" a message into a particular catagory
//		without having to do a lot of renumbering to keep it readable.		
//																			
//		For mnemonic reasons, all of the bot message defines use the format	
//		of QB_<sub system name>_<general>_<specific>						
//																			
//		This makes them both readable and easier to remember.				
//																			
//////////////////////////////////////////////////////////////////////////////////

#ifndef BOT_MSGS_H
#define BOT_MSGS_H

// Base Values
#define QB_BASE									WM_APP
#define QB_SYSTEM_BASE							QB_BASE+0
#define QB_SYSOBJ_BASE							QB_BASE+100
#define QB_TIMER_BASE							QB_BASE+200
#define QB_NETWORK_BASE							QB_BASE+300
#define QB_INFO_BASE							QB_BASE+400
#define QB_ENTITY_BASE							QB_BASE+500
#define QB_PLAYER_BASE							QB_BASE+600
#define QB_BOT_BASE								QB_BASE+700
/*
#define QB_USER_BASE							QB_BASE+200
#define QB_SERVER_BASE							QB_BASE+300

*/

// System
#define QB_SYSTEM_ERROR_NETWORK					QB_SYSTEM_BASE
#define QB_SYSTEM_ERROR_OTHER					QB_SYSTEM_BASE+1
#define QB_SYSTEM_SHUTDOWN						QB_SYSTEM_BASE+2

// System Objects
#define QB_SYSOBJ_TEXTMESSAGE					QB_SYSOBJ_BASE
#define QB_SYSOBJ_SOUND							QB_SYSOBJ_BASE+1
#define QB_SYSOBJ_TEMP_ENT						QB_SYSOBJ_BASE+2
#define QB_SYSOBJ_CENTER_MESSAGE				QB_SYSOBJ_BASE+3
#define QB_SYSOBJ_STUFFED_TEXT					QB_SYSOBJ_BASE+4
#define QB_SYSOBJ_LAYOUT						QB_SYSOBJ_BASE+5

// Timer Based Messages
#define QB_TIMER_CHECK_SEND						QB_TIMER_BASE
#define QB_TIMER_CHECK_RELIABLE					QB_TIMER_BASE+1
#define QB_TIMER_SEND_MOVE						QB_TIMER_BASE+2
#define QB_TIMER_SEND_STATUS					QB_TIMER_BASE+3
#define QB_TIMER_COMPUTE_MOVE					QB_TIMER_BASE+4

// Network Info
#define QB_NETWORK_MOVE_SENT					QB_NETWORK_BASE
#define QB_NETWORK_PACKET_DONE					QB_NETWORK_BASE+1
#define QB_NETWORK_BEGIN_LEVEL					QB_NETWORK_BASE+2
#define QB_NETWORK_END_LEVEL					QB_NETWORK_BASE+3

// Info Update Messages
#define QB_INFO_ERR_MESSAGE						QB_INFO_BASE
#define QB_INFO_SERVER_DATA						QB_INFO_BASE+1
#define QB_INFO_INVENTORY						QB_INFO_BASE+2

// Entity Update Messages
#define QB_ENTITY_UPDATE_ACTIVE					QB_ENTITY_BASE
#define QB_ENTITY_UPDATE_REMOVE					QB_ENTITY_BASE+1
#define QB_ENTITY_UPDATE_ORIGIN					QB_ENTITY_BASE+2
#define QB_ENTITY_UPDATE_MODEL					QB_ENTITY_BASE+3
#define QB_ENTITY_UPDATE_FRAME					QB_ENTITY_BASE+4
#define QB_ENTITY_UPDATE_EFFECTS				QB_ENTITY_BASE+5
#define QB_ENTITY_UPDATE_RENDER_FX				QB_ENTITY_BASE+6
#define QB_ENTITY_UPDATE_EVENT					QB_ENTITY_BASE+7
#define QB_ENTITY_MUZZLEFLASH					QB_ENTITY_BASE+8
#define QB_ENTITY_MUZZLEFLASH2					QB_ENTITY_BASE+9

// Player Update Messages
#define QB_PLAYER_UPDATE_ACTIVE					QB_PLAYER_BASE
#define QB_PLAYER_UPDATE_REMOVE					QB_PLAYER_BASE+1
#define QB_PLAYER_UPDATE_ORIGIN					QB_PLAYER_BASE+2
#define QB_PLAYER_UPDATE_MODEL					QB_PLAYER_BASE+3
#define QB_PLAYER_UPDATE_FRAME					QB_PLAYER_BASE+4
#define QB_PLAYER_UPDATE_EFFECTS				QB_PLAYER_BASE+5
#define QB_PLAYER_UPDATE_RENDER_FX				QB_PLAYER_BASE+6
#define QB_PLAYER_UPDATE_EVENT					QB_PLAYER_BASE+7
#define QB_PLAYER_MUZZLEFLASH					QB_PLAYER_BASE+8
#define QB_PLAYER_MUZZLEFLASH2					QB_PLAYER_BASE+9
#define QB_PLAYER_KILLED						QB_PLAYER_BASE+10
#define QB_PLAYER_RESPAWNED						QB_PLAYER_BASE+11
#define QB_PLAYER_UPDATE_SKIN					QB_PLAYER_BASE+12
#define QB_PLAYER_UPDATE_NAME					QB_PLAYER_BASE+13
#define QB_PLAYER_UPDATE_FRAGS					QB_PLAYER_BASE+14
#define QB_PLAYER_UPDATE_WEAPON					QB_PLAYER_BASE+15

// Bot Update Messages
#define QB_BOT_UPDATE_ACTIVE					QB_BOT_BASE
#define QB_BOT_UPDATE_REMOVE					QB_BOT_BASE+1
#define QB_BOT_UPDATE_ORIGIN					QB_BOT_BASE+2
#define QB_BOT_UPDATE_MODEL						QB_BOT_BASE+3
#define QB_BOT_UPDATE_FRAME						QB_BOT_BASE+4
#define QB_BOT_UPDATE_EFFECTS					QB_BOT_BASE+5
#define QB_BOT_UPDATE_RENDER_FX					QB_BOT_BASE+6
#define QB_BOT_UPDATE_EVENT						QB_BOT_BASE+7
#define QB_BOT_MUZZLEFLASH						QB_BOT_BASE+8
#define QB_BOT_MUZZLEFLASH2						QB_BOT_BASE+9
#define QB_BOT_KILLED							QB_BOT_BASE+10
#define QB_BOT_RESPAWNED						QB_BOT_BASE+11
#define QB_BOT_UPDATE_SKIN						QB_BOT_BASE+12
#define QB_BOT_UPDATE_NAME						QB_BOT_BASE+13
#define QB_BOT_UPDATE_FRAGS						QB_BOT_BASE+14
#define QB_BOT_UPDATE_WEAPON					QB_BOT_BASE+15
#define QB_BOT_UPDATE_ATTACK_TARGET				QB_BOT_BASE+16
#define QB_BOT_UPDATE_MOVE_TARGET				QB_BOT_BASE+17
#define QB_BOT_UPDATE_AI_INFO					QB_BOT_BASE+18
#define QB_BOT_UPDATE_HEALTH					QB_BOT_BASE+19
#define QB_BOT_UPDATE_AMMO						QB_BOT_BASE+20
#define QB_BOT_UPDATE_VELOCITY					QB_BOT_BASE+21
#define QB_BOT_UPDATE_GUN_INDEX					QB_BOT_BASE+22
#define QB_BOT_PICKUP_ITEM						QB_BOT_BASE+23


/*
#define QB_SYSOBJ_MSG							QB_SYSOBJ_BASE+1
#define QB_SYSOBJ_SERVER_COMM_MSG				QB_SYSOBJ_BASE+2
#define QB_SYSOBJ_BOTAI_MSG						QB_SYSOBJ_BASE+3
#define QB_SYSOBJ_SERVER_MSG					QB_SYSOBJ_BASE+4
#define QB_SYSOBJ_TALK_MSG						QB_SYSOBJ_BASE+5
#define QB_SYSOBJ_SERVER_CENTER_MSG				QB_SYSOBJ_BASE+6
#define QB_SYSOBJ_SERVER_CONSOLE_COMMAND		QB_SYSOBJ_BASE+7
#define QB_SYSOBJ_CONSOLE_COMMAND				QB_SYSOBJ_BASE+8
#define QB_SYSOBJ_VIS_LIST						QB_SYSOBJ_BASE+9
#define QB_SYSOBJ_DAMAGE						QB_SYSOBJ_BASE+10
#define QB_SYSOBJ_SOUND							QB_SYSOBJ_BASE+11
#define QB_SYSOBJ_TEMP_ENT						QB_SYSOBJ_BASE+12
#define QB_SYSOBJ_PARTICLE						QB_SYSOBJ_BASE+13

// User Initiated Events
#define QB_USER_CHANGE_NAME						QB_USER_BASE
#define QB_USER_CHANGE_COLORS					QB_USER_BASE+1
#define QB_USER_CONNECT							QB_USER_BASE+2
#define QB_USER_DISCONNECT						QB_USER_BASE+3
#define QB_USER_PAUSE_BOT_ON					QB_USER_BASE+4
#define QB_USER_PAUSE_BOT_OFF					QB_USER_BASE+5

// Server Status
#define QB_SERVER_BEGIN_CONNECT					QB_SERVER_BASE
#define QB_SERVER_QUERY_STATS_COMPLETE			QB_SERVER_BASE+1
#define QB_SERVER_QUERY_RULES_COMPLETE			QB_SERVER_BASE+2
#define QB_SERVER_CONNECT_ACCEPT				QB_SERVER_BASE+3
#define QB_SERVER_CONNECT_REJECT				QB_SERVER_BASE+4
#define QB_SERVER_CONNECT_ESTABLISHED			QB_SERVER_BASE+5
#define QB_SERVER_GOT_KEEP_ALIVE				QB_SERVER_BASE+6
#define QB_SERVER_SENT_KEEP_ALIVE				QB_SERVER_BASE+7
#define QB_SERVER_DISCONNECT					QB_SERVER_BASE+8
#define QB_SERVER_RECEIVE_TIME_OUT				QB_SERVER_BASE+9
#define QB_SERVER_TIMED_OUT						QB_SERVER_BASE+10
#define QB_SERVER_STATUS_DISCONNECTED			QB_SERVER_BASE+11
#define QB_SERVER_STATUS_GET_RULES				QB_SERVER_BASE+12
#define QB_SERVER_STATUS_GET_STATS				QB_SERVER_BASE+13
#define QB_SERVER_STATUS_ATTEMPT_CONNECT		QB_SERVER_BASE+14
#define QB_SERVER_STATUS_CONNECTED				QB_SERVER_BASE+15
#define QB_SERVER_STATUS_PAUSED					QB_SERVER_BASE+16
#define QB_SERVER_STATUS_TIMING_OUT				QB_SERVER_BASE+17
#define QB_SERVER_MOVE_SENT						QB_SERVER_BASE+18


// Game Status
#define QB_GAME_STATE_PRESPAWN					QB_GAME_BASE
#define QB_GAME_STATE_LIGHTING					QB_GAME_BASE+1
#define QB_GAME_STATE_RENDER					QB_GAME_BASE+2
#define QB_GAME_UPDATED							QB_GAME_BASE+3
#define QB_GAME_SET_BOT_VIEW					QB_GAME_BASE+4
#define QB_GAME_ENTITY_NEW						QB_GAME_BASE+7
#define QB_GAME_PLAYER_NEW						QB_GAME_BASE+8
#define QB_GAME_STATIC_NEW						QB_GAME_BASE+9
#define QB_GAME_ENTITY_UPDATE					QB_GAME_BASE+10
#define QB_GAME_PLAYER_UPDATE					QB_GAME_BASE+11
#define QB_GAME_STATIC_UPDATE					QB_GAME_BASE+12
#define QB_GAME_SELL_SCREEN						QB_GAME_BASE+13
#define QB_GAME_DISPLAY_SCORE					QB_GAME_BASE+14
#define QB_GAME_FOUND_SECRET					QB_GAME_BASE+15
#define QB_GAME_KILLED_MONSTER					QB_GAME_BASE+16
#define QB_GAME_LEVEL_INITIALIZED				QB_GAME_BASE+17
#define QB_GAME_LEVEL_CHANGE					QB_GAME_BASE+18

// Entity Status
#define QB_ENTITY_UPDATE_POSITION				QB_ENTITY_BASE
#define QB_ENTITY_UPDATE_ROTATION				QB_ENTITY_BASE+1
#define QB_ENTITY_UPDATE_MODEL					QB_ENTITY_BASE+2
#define QB_ENTITY_UPDATE_FRAME					QB_ENTITY_BASE+3

// Player Status 
#define QB_PLAYER_UPDATE_POSITION				QB_PLAYER_BASE
#define QB_PLAYER_UPDATE_ROTATION				QB_PLAYER_BASE+1
#define QB_PLAYER_UPDATE_MODEL					QB_PLAYER_BASE+2
#define QB_PLAYER_UPDATE_FRAME					QB_PLAYER_BASE+3
#define QB_PLAYER_UPDATE_NAME					QB_PLAYER_BASE+4
#define QB_PLAYER_UPDATE_COLORS					QB_PLAYER_BASE+5
#define QB_PLAYER_UPDATE_FRAGS					QB_PLAYER_BASE+6
#define QB_PLAYER_BEEN_KILLED					QB_PLAYER_BASE+7
#define QB_PLAYER_RESPAWNED						QB_PLAYER_BASE+8

// Bot Status
#define QB_BOT_UPDATE_POSITION					QB_BOT_BASE
#define QB_BOT_UPDATE_ROTATION					QB_BOT_BASE+1
#define QB_BOT_UPDATE_MODEL						QB_BOT_BASE+2
#define QB_BOT_UPDATE_FRAME						QB_BOT_BASE+3
#define QB_BOT_UPDATE_NAME						QB_BOT_BASE+4
#define QB_BOT_UPDATE_COLORS					QB_BOT_BASE+5
#define QB_BOT_UPDATE_FRAGS						QB_BOT_BASE+6
#define QB_BOT_BEEN_KILLED						QB_BOT_BASE+7
#define QB_BOT_RESPAWNED						QB_BOT_BASE+8
#define QB_BOT_UPDATE_INVENTORY					QB_BOT_BASE+9
#define QB_BOT_UPDATE_HEALTH					QB_BOT_BASE+10
#define QB_BOT_UPDATE_ARMOR						QB_BOT_BASE+11
#define QB_BOT_UPDATE_CELLS						QB_BOT_BASE+12
#define QB_BOT_UPDATE_NAILS						QB_BOT_BASE+13
#define QB_BOT_UPDATE_ROCKETS					QB_BOT_BASE+14
#define QB_BOT_UPDATE_SHELLS					QB_BOT_BASE+15
#define QB_BOT_UPDATE_WEAPON					QB_BOT_BASE+16
#define QB_BOT_UPDATE_ATTACKER					QB_BOT_BASE+17
#define QB_BOT_UPDATE_LOOK_TARGET				QB_BOT_BASE+18
#define QB_BOT_UPDATE_MOVE_TARGET				QB_BOT_BASE+19
#define QB_BOT_UPDATE_ACTUAL_SPEEDS				QB_BOT_BASE+20
#define QB_BOT_UPDATE_ACTUAL_ANGLES				QB_BOT_BASE+21
#define QB_BOT_MOVE_PROCESSED					QB_BOT_BASE+22
*/

#endif // #ifndef BOT_MSGS_H