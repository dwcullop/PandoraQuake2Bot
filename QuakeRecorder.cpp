// QuakeRecorder.cpp: implementation of the CQuakeRecorder class.
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
#include "QuakeRecorder.h"
#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuakeRecorder::CQuakeRecorder()
{
	m_bFileOpen = FALSE;
}

CQuakeRecorder::~CQuakeRecorder()
{
	CloseFile();
}

//////////////////////////////////////////////////////////////////////
// Public Operations
//////////////////////////////////////////////////////////////////////

void CQuakeRecorder::OpenFile()
{
	if ( !m_bFileOpen )
	{
		CString		strFilename;
		register	nCount;
		BOOL		bFindFile = FALSE;

		nCount = 0;
		while ( !bFindFile )
		{
			strFilename.Format("pandora%03d.dm2", nCount++);
			bFindFile = _access(strFilename, 0);
		}
		if ( m_fDemoFile.Open(strFilename, CFile::modeWrite | CFile::modeCreate) )
		{
			m_bFileOpen = TRUE;
		}
	}
}

void CQuakeRecorder::CloseFile()
{
	if ( m_bFileOpen )
	{
		UINT nClose = 0xFFFFFFFF;

		m_fDemoFile.Write( &nClose, sizeof(nClose) );
		m_fDemoFile.Close();
		m_bFileOpen = FALSE;
	}
}

void CQuakeRecorder::WriteBlock( CQuakePacket* pBlock )
{
	if ( m_bFileOpen )
	{
		UINT nSize = pBlock->GetSize();

		m_fDemoFile.Write( &nSize, sizeof(nSize) );
		m_fDemoFile.Write( pBlock->GetDataPtr(), pBlock->GetSize() );
	}
}

//////////////////////////////////////////////////////////////////////
// Private Operations
//////////////////////////////////////////////////////////////////////

void CQuakeRecorder::SetFileName()
{
	m_fDemoFile.SetFilePath( m_strPath );

}

//////////////////////////////////////////////////////////////////////
// End of QuakeRecorder.cpp
//////////////////////////////////////////////////////////////////////