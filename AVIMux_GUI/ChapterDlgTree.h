#if !defined(AFX_CHAPTERDLGTREE_H__A3F7B1C2_A762_4C81_877F_67F9FCE6F8FA__INCLUDED_)
#define AFX_CHAPTERDLGTREE_H__A3F7B1C2_A762_4C81_877F_67F9FCE6F8FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChapterDlgTree.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CChapterDlgTree 


#include "UnicodeTreeCtrl.h"
#include "..\chapters.h"

int RemoveFromTree(CUnicodeTreeCtrl* tree, HTREEITEM hParent);
int FormatChapterEntry(__int64 iBegin, __int64 iEnd, char* cText, char* cBuffer);

class CChapterDlgTree : public CUnicodeTreeCtrl
{
// Konstruktion
public:
	CChapterDlgTree();

// Attribute
public:
	void virtual GetTextCallback(NMHDR* pNMHDR, LRESULT* pResult);
	void OpenContextMenu(CPoint point);
// Operationen
public:
	CChapters* c;
	void SetChapters(CChapters* _c);
// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CChapterDlgTree)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CChapterDlgTree();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CChapterDlgTree)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnSelchangedChaptertree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generierte OLE-Dispatch-Zuordnungsfunktionen
	//{{AFX_DISPATCH(CChapterDlgTree)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_CHAPTERDLGTREE_H__A3F7B1C2_A762_4C81_877F_67F9FCE6F8FA__INCLUDED_
