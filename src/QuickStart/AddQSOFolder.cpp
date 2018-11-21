// AddQSOFolder.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOFolder.h"

#include "shretr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOFolder property page

IMPLEMENT_DYNCREATE(CAddQSOFolder, CPropPTemplate)

CAddQSOFolder::CAddQSOFolder() 
	: CPropPTemplate(CAddQSOFolder::IDD, 0, IDS_ADDQSO_FOLDER)
{
	//{{AFX_DATA_INIT(CAddQSOFolder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAddQSOFolder::~CAddQSOFolder()
{
}

void CAddQSOFolder::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOFolder)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOFolder, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOFolder)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOFolder message handlers

BOOL CAddQSOFolder::OnSetActive()
{
	CPropPTemplate::OnSetActive();

	SetBrowseBitmap();

	if (m_bFirstT)
	{
		m_bFirstT = FALSE;

		SetDlgItemText(IDC_ADDQSO_FOLDER_PATH, m_Info.szPath);
		
		if (!m_Info.szOpt.GetLength() || m_Info.szOpt == "open")
			SetCheck(IDC_ADDQSO_FOLDER_OPEN);
		else
			SetCheck(IDC_ADDQSO_FOLDER_EXPLORE);		
	}
	return TRUE;
}

LRESULT CAddQSOFolder::OnWizardNext()
{
	char szPath[MAX_PATH];
	if (!GetDlgItemText(IDC_ADDQSO_FOLDER_PATH, szPath, MAX_PATH)
		|| !(GetFileAttributes(szPath) & FILE_ATTRIBUTE_DIRECTORY))
	{
		AfxMessageBox(IDS_NOFOLDERNAME, MB_ICONQUESTION);
		return -1;
	}

	m_Info.szPath = szPath;
	m_Info.szPath.TrimRight("\\");

	SetTheIcon(CSHRetr::GetFolderIcon() );

	if (GetCheck(IDC_ADDQSO_FOLDER_OPEN))
		m_Info.szOpt="open";
	else
		m_Info.szOpt="explore";

	return CPropPTemplate::OnWizardNext();
}

void CAddQSOFolder::OnBrowse() 
{
	LPMALLOC pMalloc;
	/* Gets the Shell's default allocator */
	if (::SHGetMalloc(&pMalloc) != NOERROR)
	{
		AfxMessageBox(IDS_UNKNOWN, MB_ICONEXCLAMATION);
		return;
	}
	
	char szPath[MAX_PATH]="";
	LPITEMIDLIST pidl;
		
	BROWSEINFO bi={0};

	bi.hwndOwner = GetSafeHwnd();
	bi.pszDisplayName = szPath;
	bi.ulFlags = BIF_EDITBOX;
	
	// This next call issues the dialog box.
	if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
	{
		if (::SHGetPathFromIDList(pidl, szPath))
		{ 
			// At this point pszBuffer contains the selected path
			SetDlgItemText(IDC_ADDQSO_FOLDER_PATH, szPath);
			m_Info.szPath=szPath;
		}
		
		// Free the PIDL allocated by SHBrowseForFolder.
		pMalloc->Free(pidl);
	}
	// Release the shell's allocator.
	pMalloc->Release();
}
