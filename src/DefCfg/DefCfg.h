
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DEFCFG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DEFCFG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef DEFCFG_EXPORTS
#define DEFCFG_API __declspec(dllexport)
#else
#define DEFCFG_API __declspec(dllimport)
#endif


void DEFCFG_API PASCAL GetFirstCfg(LPVOID lpQSOInfo);
BOOL DEFCFG_API PASCAL GetNextCfg(LPVOID lpQSOInfo);

BOOL GetAppPath(LPCTSTR szFileName, LPTSTR szPath);
