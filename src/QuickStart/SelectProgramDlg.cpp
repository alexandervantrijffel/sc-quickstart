//CSelectProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "SelectProgramDlg.h"

#include "shretr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDS_APPPATHS "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths"

/////////////////////////////////////////////////////////////////////////////
// CSelectProgramDlg dialog


CSelectProgramDlg::CSelectProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectProgramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectProgramDlg)
	//}}AFX_DATA_INIT
}

CSelectProgramDlg::~CSelectProgramDlg()
{
	m_ImageList.DeleteImageList();
}

void CSelectProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectProgramDlg)
	DDX_Control(pDX, IDC_CHOOSE_PROGRAM_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectProgramDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectProgramDlg)
	ON_BN_CLICKED(IDC_SELECT_PROGRAM_OTHER, OnOther)
	ON_LBN_SELCHANGE(IDC_CHOOSE_PROGRAM_LIST, OnSelchange)
	ON_LBN_DBLCLK(IDC_CHOOSE_PROGRAM_LIST, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectProgramDlg message handlers

void CSelectProgramDlg::OnOK() 
{
	m_List.GetText( m_List.GetCurSel(), m_szPath);

	CSHRetr shretr;
	m_szPath = shretr.GetAppPath(m_szPath);
	
	CDialog::OnOK();
}

void CSelectProgramDlg::OnOther() 
{
	CFileDialog FDlg(TRUE
		, NULL 
		, NULL
		, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY
		, "Executable files|*.exe|All files (*.*)|*.*||"
		, this);
	FDlg.m_ofn.lpstrInitialDir = "C:\\Program Files";

	if (FDlg.DoModal() == IDOK)
	{
		m_szPath = FDlg.GetPathName();
		EndDialog(IDOK);
	}
}

CString CSelectProgramDlg::GetPathName()
{
	return m_szPath;
}

BOOL CSelectProgramDlg::OnInitDialog() 
{
	BeginWaitCursor();

	CDialog::OnInitDialog();

	m_List.SetFocus();
	m_ImageList.Create( 16,16,ILC_COLOR16,1,1);
	m_ImageList.SetBkColor(RGB(255,255,255));
	m_List.SetImageList( &m_ImageList );

	HKEY hKey, hSubKey;
	long lRet=0;
	
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		IDS_APPPATHS, 0, KEY_READ, &hKey);
	
	if (lRet != ERROR_SUCCESS)
		return FALSE;

	char szSubKey[MAX_PATH], szPath[MAX_PATH];
	DWORD dwIndex=0, dw1, dw2;
	FILETIME ft;

	int ic=0;

	LVITEM lvitem={0};
	lvitem.mask = LVIF_TEXT|LVIF_IMAGE;
	lvitem.iSubItem = 0;

	CSHRetr IRetr;
	
	while (TRUE)
	{
		dw1=dw2=MAX_PATH;
		// enumerate subkeys
		lRet = ::RegEnumKeyEx(hKey,dwIndex++, szSubKey, 
			&dw1, 0, szPath, &dw2, &ft);

		if (lRet!=ERROR_SUCCESS)
			break;
	
		// open subkey(app title)
		lRet = RegOpenKeyEx(hKey, szSubKey, 0, 
			KEY_READ|KEY_SET_VALUE, &hSubKey);

		if (lRet!=ERROR_SUCCESS)
			continue;

		dw2=MAX_PATH;
		lRet = RegQueryValueEx(hSubKey, 0, 0, &dw1, (LPBYTE)szPath, &dw2);

		if (lRet==ERROR_SUCCESS)
		{
			// only add item to list if file exists
//			if (GetFileAttributes(szPath) != -1)
				m_List.AddString(szSubKey, m_ImageList.Add(IRetr.GetIcon(szPath)));
//			else
//				TRACE2("not acc: %s (%d)\n", szPath, GetFileAttributes(szPath));
		}

		RegCloseKey(hSubKey);
		
	}
	RegCloseKey(hKey);

	EndWaitCursor();

	return FALSE;
}

void CSelectProgramDlg::OnSelchange() 
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CSelectProgramDlg::OnDblclk() 
{
	m_List.GetText( m_List.GetCurSel(), m_szPath);
	CSHRetr shretr;
	m_szPath = shretr.GetAppPath(m_szPath);

	EndDialog(IDOK);
}
