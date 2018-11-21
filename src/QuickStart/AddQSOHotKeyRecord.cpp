// AddQSOHotKeyRecord.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOHotKeyRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAddQSOHotKeyRecord* pDlg=0;
/////////////////////////////////////////////////////////////////////////////
// CAddQSOHotKeyRecord dialog


CAddQSOHotKeyRecord::CAddQSOHotKeyRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CAddQSOHotKeyRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddQSOHotKeyRecord)
	m_szHotKey = _T("");
	//}}AFX_DATA_INIT
	m_hHook=0;
	m_dwHotKey=0;
}
CAddQSOHotKeyRecord::~CAddQSOHotKeyRecord()
{
	if (m_hHook)
		UnhookWindowsHookEx(m_hHook);
	pDlg=0;
}

void CAddQSOHotKeyRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOHotKeyRecord)
	DDX_Text(pDX, IDC_HOTKEY, m_szHotKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOHotKeyRecord, CDialog)
	//{{AFX_MSG_MAP(CAddQSOHotKeyRecord)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOHotKeyRecord message handlers


void CAddQSOHotKeyRecord::OnReset() 
{
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_RESET)->EnableWindow(FALSE);

	m_szHotKey="";
	m_dwHotKey=0;
	UpdateData(FALSE);
}

void CAddQSOHotKeyRecord::OnOK() 
{
	HWND hMainWnd = ::AfxGetMainWnd()->GetSafeHwnd();
	if (Test())
		CDialog::OnOK();
}

LRESULT CALLBACK CAddQSOHotKeyRecord::KeyboardProc( int code, WPARAM wParam, LPARAM lParam)
{
	// (31) 1 : key is pressed
	// (30) 1 : key was down before msg was sent
	
	if (!(lParam & (1 << 31))&& !(lParam & (1 << 30)) && wParam != VK_RETURN && pDlg)	
	{
		// only allow 1 single normal key per hotkey
		if ( pDlg->m_dwHotKey & 0xFF)
		{	
			pDlg->m_dwHotKey=0;
			pDlg->m_szHotKey="";
		}
		
		// change modulation virt keycodes
		switch (wParam)
		{
			case VK_CONTROL :	pDlg->m_dwHotKey |= MOD_CONTROL<<9;
				break;
			case 18			:	pDlg->m_dwHotKey |= MOD_ALT<<9;
				break;
			case VK_SHIFT	:	pDlg->m_dwHotKey |= MOD_SHIFT<<9;
				break;
			case 91			:	pDlg->m_dwHotKey |= MOD_WIN<<9;
				break;
			default :
				pDlg->m_dwHotKey |= wParam;
		}

		
		CString szTxt = pDlg->m_Kb.GetText(wParam);
		
		// only add if it's the first
		if (pDlg->m_szHotKey.Find(szTxt,0) == -1)
		{
			// add + to hotkey txt if neccessary
			if ( pDlg->m_szHotKey.GetLength())
				pDlg->m_szHotKey += " + ";
				
			pDlg->m_szHotKey += pDlg->m_Kb.GetText(wParam);
		
			pDlg->UpdateData(FALSE);
		}
	}

	pDlg->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pDlg->GetDlgItem(IDC_RESET)->EnableWindow(TRUE);

	return (code>0)?CallNextHookEx(pDlg->m_hHook, code, wParam, lParam):0;
}

BOOL CAddQSOHotKeyRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();

	pDlg = this;
	m_hHook = SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC) KeyboardProc
		, NULL, GetCurrentThreadId());

	GetDlgItem(IDC_HOTKEY)->SetFocus();

	return FALSE;
}

BOOL CAddQSOHotKeyRecord::Test()
{

	TRACE3("f5: %d	dwhotkey: %u    dwhotkey&f12: %d\n", VK_F5, m_dwHotKey, m_dwHotKey&VK_F1);
	BOOL bSuccess = VK_F12 != (m_dwHotKey & 0xff);
	bSuccess = 112 != (m_dwHotKey & 0xff); // 123 = f12  112 = f1

	if (bSuccess)
	{
		bSuccess = RegisterHotKey(GetSafeHwnd(), 0xBF00, m_dwHotKey>>9, m_dwHotKey & 0xFF);
		if (bSuccess)
			UnregisterHotKey(GetSafeHwnd(), 0xBF00);
	}

	if (!bSuccess)
		AfxMessageBox(IDS_REGHOTKEYFAILED);

	else if (0 == (m_dwHotKey & 0xffff<<9))
		bSuccess = (IDYES == AfxMessageBox(IDS_UNSAFEHOTKEY, MB_ICONQUESTION|MB_YESNO));
		
	else if (
		   1091 == m_dwHotKey // Ctrl+C
		|| 1110 == m_dwHotKey // Ctrl+V
		|| 1104 == m_dwHotKey // Ctrl+P
		|| 521  == m_dwHotKey // Alt+TAB
		|| 2057 == m_dwHotKey // Shift+TAB
		)
	{
		bSuccess = FALSE;
		AfxMessageBox(IDS_COMMONHOTKEY, MB_ICONEXCLAMATION);
	}

	return bSuccess;
}