// PandoraDoc.h : interface of the CPandoraDoc class
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

#if !defined(AFX_PANDORADOC_H__7BB2348D_BD1E_11D1_8720_444553540000__INCLUDED_)
#define AFX_PANDORADOC_H__7BB2348D_BD1E_11D1_8720_444553540000__INCLUDED_

#include "QuakeClient.h"
#include "BotThread.h"
#include "BotSystem.h"
#include "PandoraDefs.h"
#include "AIThread.h"
#include "ViewThread.h"
//#include "QuakeRecorder.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef	_DEBUG
	//#define	DOES_EXPIRE
#endif

class CPandoraDoc : public CDocument, public CQuakeClient
{
	DECLARE_DYNCREATE(CPandoraDoc)

// Attributes
private:
	CBotSystem		m_bsSystem;
	CAIThread		m_threadThink;
	CViewThread		m_threadView;
	//CQuakeRecorder	m_qrDemo;

// Construction / Destruction
protected: // create from serialization only
	CPandoraDoc();

public:
	virtual ~CPandoraDoc();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPandoraDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize( CArchive& );
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame( CFrameWnd* );
	//}}AFX_VIRTUAL

// Overridables
public:
	virtual void OnTimer( const UINT& );

// CQuakeClient Overrides
public:
	virtual void ProcessDataPacket( CQuakePacket* );

protected:
	virtual void OnMuzzleFlash( const WORD );
	virtual void OnMuzzleFlash2( const WORD );
	virtual void OnUpdateEntityActive( const WORD );
	virtual void OnUpdateEntityRemove( const WORD );
	virtual void OnUpdateInventory();
	virtual void OnUpdatePlayerInfo( const UINT );
	virtual void OnUpdatePlayerInfoStats( const UINT );
	virtual void OnUpdateServerData();

	virtual void OnDisconnected();
	virtual void OnMoveSent();
	virtual void OnPreConnect();
	virtual void OnServerBeginLevel();
	virtual void OnServerReadError( CQuakePacket* );
	virtual void ProcessCenterText( const CString& );
	virtual void ProcessDisplayText( CTextMessage* );
	virtual void ProcessErrorMessage( const UINT& );
	virtual void ProcessLayout( const CString& );
	virtual void ProcessPrint( CTextMessage* );
	virtual void ProcessSound( CSound* );
	virtual void ProcessStuffText( const CString& );
	virtual void ProcessTempEntity( CTempEntity* );

// Operations
public:
	CView*	GetView( const CRuntimeClass* );
	void	SetViewThreadViews();

private:
#ifdef DOES_EXPIRE
	BOOL CheckExpired() const;
#endif
	void SetBlankTitle();
	void SetConnectedTitle();
	void SetDisconnectedTitle();
	void StartTimer( const UINT&, const UINT& );
	void StopTimer( const UINT& );

// Diagnostics
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump( CDumpContext& ) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CPandoraDoc)
	afx_msg void OnCommandsFlipoff()				{ WaveFlipoff(); };
	afx_msg void OnCommandsPoint()					{ WavePoint(); };
	afx_msg void OnCommandsSalute()					{ WaveSalute(); };
	afx_msg void OnCommandsSuicide()				{ SendStringCmd( IDS_CMD_SUICIDE ); };
	afx_msg void OnCommandsTaunt()					{ WaveTaunt(); };
	afx_msg void OnCommandsWave()					{ WaveWave(); };
	afx_msg void OnFileConnect();
	afx_msg void OnFileDisconnect();
	afx_msg void OnUpdateFileConnect( CCmdUI* );
	afx_msg void OnUpdateFileDisconnect( CCmdUI* );
	afx_msg void OnUpdateCommandsFlipoff( CCmdUI* );
	afx_msg void OnUpdateCommandsPoint( CCmdUI* );
	afx_msg void OnUpdateCommandsSalute( CCmdUI* );
	afx_msg void OnUpdateCommandsSuicide( CCmdUI* );
	afx_msg void OnUpdateCommandsTaunt( CCmdUI* );
	afx_msg void OnUpdateCommandsWave( CCmdUI* );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANDORADOC_H__7BB2348D_BD1E_11D1_8720_444553540000__INCLUDED_)
