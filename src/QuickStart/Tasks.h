// Tasks.h: interface for the CTasks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKS_H__B1A0766D_30BE_4C85_B923_9EF57DBA5252__INCLUDED_)
#define AFX_TASKS_H__B1A0766D_30BE_4C85_B923_9EF57DBA5252__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
	  TASK_ID_DIC	= 0
	, TASK_ID_HIC
	, TASK_ID_SOL
	, TASK_ID_ECD
	, TASK_ID_CCD
	, TASK_ID_CTP
	, TASK_ID_SSC
	, TASK_ID_IDR
	, TASK_ID_DDR
	, TASK_ID_CAP
	, TASK_ID_SEM
	, TASK_ID_ERB
};

class CTasks  
{
public:
	static BOOL CALLBACK EnumDesktopWindowsProc(HWND hWnd, LPARAM lParam);
	HICON GetIcon(LPCTSTR szTask);
	int GetTaskIndex(LPCTSTR szTask);
	void OpenCloseCDDrive(TCHAR cDrive, BOOL bOpen);
	CString GetTaskName(int iIndex);
	int GetCount();
	CString GetTaskDesc(int iIndex);
	void Execute(LPCTSTR szTask, LPCTSTR szOpt);
	CTasks();
	virtual ~CTasks();
	CStringArray m_szTasks;
private:
	void Init();
};

#endif // !defined(AFX_TASKS_H__B1A0766D_30BE_4C85_B923_9EF57DBA5252__INCLUDED_)
