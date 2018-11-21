// AddQSOTask.cpp : implementation file
//

#include "stdafx.h"
#include "QuickStart.h"
#include "AddQSOTask.h"

#include "shretr.h"
#include "tipsmgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddQSOTask property page

IMPLEMENT_DYNCREATE(CAddQSOTask, CPropPTemplate)

CAddQSOTask::CAddQSOTask() 
	: CPropPTemplate(CAddQSOTask::IDD, 0, IDS_ADDQSO_TASK)
{
	//{{AFX_DATA_INIT(CAddQSOTask)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	iPrevSel=-1;
}

CAddQSOTask::~CAddQSOTask()
{
}

void CAddQSOTask::DoDataExchange(CDataExchange* pDX)
{
	CPropPTemplate::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddQSOTask)
	DDX_Control(pDX, IDC_ADDQSO_TASK_DRIVES, m_ComboDrives);
	DDX_Control(pDX, IDC_ADDQSO_TASK_NAME, m_Combo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddQSOTask, CPropPTemplate)
	//{{AFX_MSG_MAP(CAddQSOTask)
	ON_CBN_SELCHANGE(IDC_ADDQSO_TASK_NAME, OnSelchange)
	ON_BN_CLICKED(IDC_ADDQSO_TASK_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddQSOTask message handlers

BOOL CAddQSOTask::OnSetActive()
{
	CPropPTemplate::OnSetActive();
	m_bDisplayResolutionTipShowed=FALSE;

	if (m_bFirstT)
	{
		m_bFirstT = FALSE;
		
		CTasks tasks;

		// task combo
		for (int i=0; i<m_Tasks.GetCount() ; i++)
			m_Combo.AddString(m_Tasks.GetTaskDesc(i));

		// select task
		if (m_Info.szPath.GetLength())
			m_Combo.SetCurSel(tasks.GetTaskIndex(m_Info.szPath));

		// enlarge combo
		RECT rc;
		m_Combo.GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.right = rc.right - rc.left;
		rc.bottom = 300;
		m_Combo.MoveWindow(&rc);

		// shutdown / logoff
		if (!m_Info.szOpt.GetLength() || m_Info.szOpt == "0")
			GetDlgItem(IDC_SHUTDOWN)->SendMessage(BM_SETCHECK, 1, 0L);
		else if (m_Info.szOpt == "1")
			GetDlgItem(IDC_REBOOT)->SendMessage(BM_SETCHECK, 1, 0L);
		else
			GetDlgItem(IDC_LOGOFF)->SendMessage(BM_SETCHECK, 1, 0L);

		// controlpanel
		if (!m_Info.szOpt.GetLength() || m_Info.szOpt == "open")
			GetDlgItem(IDC_CTP_OPEN)->SendMessage(BM_SETCHECK, 1, 0L);
		else
			GetDlgItem(IDC_CTP_EXPLORE)->SendMessage(BM_SETCHECK, 1, 0L);

		// drives combo
		m_ComboDrives.AddString("All cd-rom drives");
		m_ComboDrives.SetCurSel(0);

		CString szDrives = CSHRetr::GetAllCDDrives();
		char szDrive[]="?:";
		for (i=0;i<szDrives.GetLength();i++)
		{
			szDrive[0] = szDrives.GetAt(i);
			m_ComboDrives.AddString(szDrive);

			// select drive
			if (m_Info.szOpt.GetLength() && szDrive[0] == m_Info.szOpt[0])
				m_ComboDrives.SetCurSel(i+1);
		}
		
		// enlarge combo
		m_ComboDrives.GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.right = rc.right - rc.left;
		rc.bottom = 300;
		m_ComboDrives.MoveWindow(&rc);

		OnSelchange();
	}

	return TRUE;
}

void CAddQSOTask::OnSelchange() 
{
	int iCurSel = m_Combo.GetCurSel();

	if (iCurSel==iPrevSel)
		return;

	if (iCurSel!=-1)
		GetDlgItem(IDC_ADDQSO_TASK_TEST)->EnableWindow(TRUE);

	switch (iPrevSel)
	{
		case TASK_ID_SOL :
			Show(IDC_SHUTDOWN, FALSE);
			Show(IDC_REBOOT, FALSE);
			Show(IDC_LOGOFF, FALSE);
			break;

		case TASK_ID_ECD :
		case TASK_ID_CCD :
			Show(IDC_ADDQSO_TASK_DRIVES, FALSE);
			Show(IDC_ADDQSO_TASK_DRIVE, FALSE);
			break;

		case TASK_ID_CTP :
			Show(IDC_CTP_OPEN, FALSE);
			Show(IDC_CTP_EXPLORE, FALSE);
			break;
	}

	switch (iCurSel)
	{
		case TASK_ID_SOL	:
			Show(IDC_SHUTDOWN, TRUE);
			Show(IDC_REBOOT, TRUE);
			Show(IDC_LOGOFF, TRUE);
			break;

		case TASK_ID_ECD:
		case TASK_ID_CCD:
		{	
			Show(IDC_ADDQSO_TASK_DRIVES, TRUE);
			Show(IDC_ADDQSO_TASK_DRIVE, TRUE);
			break;
	    }

		case TASK_ID_CTP:
		{
			Show(IDC_CTP_OPEN, TRUE);
			Show(IDC_CTP_EXPLORE, TRUE);
			break;
		}
	}	
		
	iPrevSel = iCurSel;
}

void CAddQSOTask::Show(UINT ID, BOOL bShow)
{
	GetDlgItem(ID)->ShowWindow(bShow);
}

LRESULT CAddQSOTask::OnWizardBack()
{
	m_Info.szPath="";
	return CPropPTemplate::OnWizardBack();
}

LRESULT CAddQSOTask::OnWizardNext()
{
	if (ProcessInput())
	{
		SetTheIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_TASK)));		
		return CPropPTemplate::OnWizardNext();
	}
	return -1;
}

BOOL CAddQSOTask::ProcessInput()
{
	int iCurSel = m_Combo.GetCurSel();
	if (-1 == iCurSel)
	{
		AfxMessageBox(IDS_NOTASK);
		return FALSE;
	}

	m_Info.szPath = m_Tasks.GetTaskName(iCurSel);

	if (!m_Info.szName.GetLength())
		m_Info.szName =	m_Tasks.GetTaskDesc(iCurSel);
	
	switch (iCurSel)
	{
		case TASK_ID_SOL :
			if (GetDlgItem(IDC_SHUTDOWN)->SendMessage(BM_GETCHECK, 0, 0L))
				m_Info.szOpt = "0";
			else if (GetDlgItem(IDC_REBOOT)->SendMessage(BM_GETCHECK, 0, 0L))
				m_Info.szOpt = "1";
			else
				m_Info.szOpt = "2";
			break;

		case TASK_ID_ECD:
		case TASK_ID_CCD:
		{
			int iCurCDSel = m_ComboDrives.GetCurSel();
			if (!iCurCDSel)
				m_Info.szOpt = "€";
			else
				m_ComboDrives.GetLBText(m_ComboDrives.GetCurSel(), m_Info.szOpt);
			break;
		}
		case TASK_ID_CTP:
			if (GetDlgItem(IDC_CTP_OPEN)->SendMessage(BM_GETCHECK, 0, 0L))
				m_Info.szOpt = "open";
			else
				m_Info.szOpt = "Explore";
			break;
	}
	return TRUE;
}

void CAddQSOTask::OnTest() 
{
	ProcessInput();
	int iCurSel = m_Combo.GetCurSel();
	
	if (   !m_bDisplayResolutionTipShowed
		&& (iCurSel == TASK_ID_IDR || iCurSel == TASK_ID_DDR))
	{
		CTipsMgr tmgr;
		tmgr.ShowTip(ID_TIP_DISPLAYRESOLUTION_TEST);
		m_bDisplayResolutionTipShowed=TRUE;
	}
	m_Tasks.Execute(m_Info.szPath, m_Info.szOpt);	
}
