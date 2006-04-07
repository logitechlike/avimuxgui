#if !defined(AFX_RIFFCHUNKTREEDLG_H__A85847D2_EE36_4B4E_A3B5_61C7FB2C0400__INCLUDED_)
#define AFX_RIFFCHUNKTREEDLG_H__A85847D2_EE36_4B4E_A3B5_61C7FB2C0400__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RIFFChunkTreeDlg.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRIFFChunkTreeDlg 

#include "Languages.h"
#include "..\basestreams.h"
#include "AVIFile.h"

class CRIFFChunkTreeDlg : public CDialog
{
// Konstruktion
private:
	STREAM*		source;
	void	RenderItem(FILE* file, HTREEITEM hItem, int iLevel);
public:
	CRIFFChunkTreeDlg(CWnd* pParent = NULL);   // Standardkonstruktor
	void	SetSource(STREAM*	lpSource);
	STREAM* GetSource(void);

	void ParseAVIH(HTREEITEM hParent,CHUNKHEADER ch);
	void ParseSTRH(HTREEITEM hParent,CHUNKHEADER ch);
	void ParseINDX(HTREEITEM hParent,CHUNKHEADER ch);
	void ParseDMLH(HTREEITEM hParent,CHUNKHEADER ch);

	void InsertChunk(HTREEITEM hParent,CHUNKHEADER ch, int iType = 0);
	void InsertList(HTREEITEM hParent,LISTHEADER lh);

// Dialogfelddaten
	//{{AFX_DATA(CRIFFChunkTreeDlg)
	enum { IDD = IDD_RIFFCHUNKTREEDLG };
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CRIFFChunkTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CRIFFChunkTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RIFFCHUNKTREEDLG_H__A85847D2_EE36_4B4E_A3B5_61C7FB2C0400__INCLUDED_
