﻿// VideoInformationDlgListbox.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "AVIMux_GUI.h"
#include "VideoInformationDlgListbox.h"
#include "..\Basestreams.h"
#include "AVIFile.h"
#include "Mode2Form2Reader.h"
#include "VideoInformationDlg.h"
#include "FILE_INFO.h"
#include "SetFramerateDlg.h"
#include "SetMainAVIHeaderFlagsDlg.h"
#include "Languages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoInformationDlgListbox

CVideoInformationDlgListbox::CVideoInformationDlgListbox()
{
	EnableAutomation();
	NewRepairList();

}

void CVideoInformationDlgListbox::NewRepairList()
{
	lpcahFirst=new CHANGEAVIHEADER;
	lpcahFirst->lpNext=NULL;
	lpcahFirst->dwValid=0;
	lpcahCurr=lpcahFirst;
	dwDone=0;
}

CVideoInformationDlgListbox::~CVideoInformationDlgListbox()
{
}

void CVideoInformationDlgListbox::OnFinalRelease()
{
	// Nachdem die letzte Referenz auf ein Automatisierungsobjekt freigegeben wurde,
	// wird OnFinalRelease aufgerufen. Die Basisklasse l鰏cht das Objekt
	// automatisch. F黦en Sie zus鋞zlichen Bereinigungscode f黵 Ihr Objekt
	// hinzu, bevor Sie die Basisklasse aufrufen.

	CListBox::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CVideoInformationDlgListbox, CListBox)
	//{{AFX_MSG_MAP(CVideoInformationDlgListbox)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVideoInformationDlgListbox, CListBox)
	//{{AFX_DISPATCH_MAP(CVideoInformationDlgListbox)
		// HINWEIS - Der Klassen-Assistent f黦t hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Hinweis: Wir stellen Unterst黷zung f黵 IID_IVideoInformationDlgListbox zur Verf黦ung, um typsicheres Binden
//  von VBA zu erm鰃lichen. Diese IID muss mit der GUID 黚ereinstimmen, die in der
//  Disp-Schnittstelle in der .ODL-Datei angegeben ist.

// {2E22572D-43EB-4143-930C-308F680B55B1}
static const IID IID_IVideoInformationDlgListbox =
{ 0x2e22572d, 0x43eb, 0x4143, { 0x93, 0xc, 0x30, 0x8f, 0x68, 0xb, 0x55, 0xb1 } };

BEGIN_INTERFACE_MAP(CVideoInformationDlgListbox, CListBox)
	INTERFACE_PART(CVideoInformationDlgListbox, IID_IVideoInformationDlgListbox, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f黵 Nachrichten CVideoInformationDlgListbox 

void CVideoInformationDlgListbox::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Code f黵 die Behandlungsroutine f黵 Nachrichten hier einf黦en und/oder Standard aufrufen
	CMenu*		cmPopupMenu;
//	int			iIndex;
	CString		cStr;
	bool		bShowMenu=false;
	FILE_INFO*	lpFI;
	AVIFILEEX*	avifile;
	DWORD		dwKind;

	lpFI=((CVideoInformationDlg*)GetParent())->GetFile();
	dwKind=((CVideoInformationDlg*)GetParent())->GetKindOfSource();

	if (GetCount())
	{
		cmPopupMenu=new CMenu;
		cmPopupMenu->CreatePopupMenu();
		if (dwKind==KOS_AVIFILEEX) {
			avifile=lpFI->AVIFile;
			if (avifile)
			{
			if (!(lpFI->bInUse))
			{
				if (!(dwDone&REPAIRS_ODML))
				{
					if (avifile->GetLoadSuperIndexProtocol())
					{
						cStr=LoadString(IDS_VILB_REPAIRODML);
						cmPopupMenu->AppendMenu(MF_STRING,IDM_VILB_REPAIRODML,cStr);
						bShowMenu=true;
					}
				}

				if (!(dwDone&REPAIRS_FRAMERATE))
				{
					cStr=LoadString(IDS_VILB_REPAIRFRAMERATE);
					cmPopupMenu->AppendMenu(MF_STRING,IDM_VILB_REPAIRFRAMERATE,cStr);
					bShowMenu=true;
				}

				if (!(dwDone&REPAIRS_CHANGEFRAMERATE))
				{
					cStr=LoadString(IDS_VILB_SETFRAMERATE);
					cmPopupMenu->AppendMenu(MF_STRING,IDM_VILB_SETFRAMERATE,cStr);
					bShowMenu=true;
				}
				if (!(dwDone&REPAIRS_MAHFLAGS))
				{
					cStr=LoadString(IDS_VILB_SETMAHFLAGS);
					cmPopupMenu->AppendMenu(MF_STRING,IDM_VILB_SETMAHFLAGS,cStr);
					bShowMenu=true;
				}
				if (!(dwDone&REPAIRS_TOTALFRAMES))
				{
					cStr=LoadString(IDS_VILB_TOTALFRAMES);
					cmPopupMenu->AppendMenu(MF_STRING,IDM_VILB_TOTALFRAMES,cStr);
					bShowMenu=true;
				}

			}
			}
		}

	
		if (bShowMenu)
			cmPopupMenu->AppendMenu(MF_SEPARATOR,0);
		
		cStr=LoadString(STR_SAVEAS);
		cmPopupMenu->AppendMenu(MF_STRING,IDM_VILB_SAVEAS,cStr);
		bShowMenu=true;
			
		if (bShowMenu)	{
			ClientToScreen(&point);
			cmPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,point.x,point.y,this);
		}
		if (cmPopupMenu) delete cmPopupMenu;
		
	}
		
			
	CListBox::OnRButtonUp(nFlags, point);
}

void AddRepair(CHANGEAVIHEADER**	lpcahRepair,DWORD dwSize,__int64 qwFilePos,__int64 qwOld,__int64 qwNew)
{
	(*lpcahRepair)->dwSize=dwSize;
	(*lpcahRepair)->dwValid=1;
	(*lpcahRepair)->qwFilePos=qwFilePos;
	(*lpcahRepair)->qwOldVal=qwOld;
	(*lpcahRepair)->qwNewVal=qwNew;
	(*lpcahRepair)->lpNext=new CHANGEAVIHEADER;
	(*lpcahRepair)=(CHANGEAVIHEADER*)((*lpcahRepair)->lpNext);
	(*lpcahRepair)->lpNext=NULL;
	(*lpcahRepair)->dwValid=0;
}

BOOL CVideoInformationDlgListbox::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Speziellen Code hier einf黦en und/oder Basisklasse aufrufen
	DWORD					i,j,dwWritten;
	CString					cStr1,cStr2;
	READSUPERINDEXPROTOCOL*	lpRSIP;	
	CFileDialog*			cfd;
	CSetFramerateDlg*		csfrd;
	CSetMainAVIHeaderFlagsDlg*	csmahfd;
	HANDLE					hFile;
//	BYTE					Buffer[200];
	DWORD					dwNNSPF;
	DWORD					dwNMSPF;
	DWORD					dwKind;
	FRAME_RATE               f;

	dwKind=((CVideoInformationDlg*)GetParent())->GetKindOfSource();
	if (dwKind==KOS_AVIFILEEX)
	{
		if (avifile) lpRSIP=avifile->GetLoadSuperIndexProtocol();
	}

	switch (LOWORD(wParam))
	{
		case IDM_VILB_REPAIRODML:
			for (i=0;i<avifile->GetNbrOfStreams();i++)
			{
				for (j=0;j<lpRSIP[i].dwEntries;j++)
				{
					if (lpRSIP[i].rsipEntries[j].dwDurationValue!=lpRSIP[i].rsipEntries[j].dwRealDuration)
					{
						AddRepair(&lpcahCurr,4,lpRSIP[i].rsipEntries[j].qwFilePos,
							lpRSIP[i].rsipEntries[j].dwDurationValue,lpRSIP[i].rsipEntries[j].dwRealDuration);
					}
				}
			}
			dwDone|=REPAIRS_ODML;
			break;
		case IDM_VILB_REPAIRFRAMERATE:
			AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwMicroSecPerFrame,0,avimux_round(avifile->GetMicroSecPerFrame()));
			dwDone|=REPAIRS_FRAMERATE;
			break;
		case IDM_VILB_SAVEAS:
			cfd = new CFileDialog(false, _T("txt"), NULL, 4 | 2, _T("Text files (*.txt)|*.txt||"));
			if (cfd->DoModal()==IDOK)
			{
				hFile=CreateFile(cfd->GetPathName().GetBuffer(512), GENERIC_WRITE, 0, NULL,	CREATE_ALWAYS, 0, NULL);
				if (hFile==INVALID_HANDLE_VALUE)
				{
					cStr1=LoadString(IDS_ERROR);
					cStr2=LoadString(IDS_COULDNOTOPENOUTPUTFILE);
					MessageBox(cStr2,cStr1,MB_ICONERROR);
				}
				else
				{
					for (i=0;i<(DWORD)GetCount();i++)
					{
						int textLength = GetTextLen(i);
						std::vector<TCHAR> textBuffer(textLength+3);
						GetText(i, &textBuffer[0]);

						textBuffer[textLength] = 13;
						textBuffer[textLength+1] = 10;

						CUTF8 utf8TextBuffer(&textBuffer[0]);
						const char* utf8TextBufferPtr = utf8TextBuffer.UTF8();
						int utf8TextBufferLength = strlen(utf8TextBufferPtr);
						WriteFile(hFile, utf8TextBufferPtr, utf8TextBufferLength, &dwWritten, NULL);
					}
					CloseHandle(hFile);
				}
				
			}
			delete cfd;
			break;
		case IDM_VILB_SETFRAMERATE:
			csfrd=new CSetFramerateDlg;

			f.den = 0;
			f.nom = 0;
			f.frate = 1000000000./(double)avifile->GetNanoSecPerFrame();
			csfrd->SetData(&f);
			if (csfrd->DoModal()==IDOK)
			{
				csfrd->GetData(&f);
				dwNNSPF=(DWORD)avimux_round(((double)1000000000./f.frate)/100)*100;
				dwNMSPF=(DWORD)avimux_round(((double)dwNNSPF)/1000);
				if (f.den == 0) {
					AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwMicroSecPerFrame,0,dwNMSPF);
					AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwRateSTRH0,0,10000000);
					AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwScaleSTRH0,0,dwNNSPF/100);
				} else {

					AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwMicroSecPerFrame,0,dwNMSPF);
					AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwRateSTRH0,0,f.nom);
					AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwScaleSTRH0,0,f.den);
				}
			}

			delete csfrd;
			break;
		case IDM_VILB_SETMAHFLAGS:
			csmahfd=new CSetMainAVIHeaderFlagsDlg;
			csmahfd->SetData(avifile->lpMainAVIHeader->dwFlags);
			if (csmahfd->DoModal()==IDOK)
			{
				AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwFlags,0,csmahfd->GetData());
			}
			delete csmahfd;
			break;
		case IDM_VILB_TOTALFRAMES:
			dwDone|=REPAIRS_TOTALFRAMES;
			avifile->GetFramesInFirstRIFF(NULL,&j);
			AddRepair(&lpcahCurr,4,avifile->GetAbsolutePositions()->dwTotalFrames,0,j);
			break;
	}
			
	return CListBox::OnCommand(wParam, lParam);
}

void CVideoInformationDlgListbox::ClearRepairs(bool bStartNew)
{
	CHANGEAVIHEADER*	lpcahRepairs=GetRepairs();
	CHANGEAVIHEADER*	lpcahCurr=lpcahRepairs;
	CHANGEAVIHEADER*	lpcahNext;

	while (lpcahCurr)
	{
		lpcahNext=(CHANGEAVIHEADER*)lpcahCurr->lpNext;
		free(lpcahCurr);
		lpcahCurr=lpcahNext;
	}

	if (bStartNew) NewRepairList();

}

void CVideoInformationDlgListbox::SetUnavailableRepairs(DWORD dwUnavailable)
{
	dwDone|=dwUnavailable;
}
