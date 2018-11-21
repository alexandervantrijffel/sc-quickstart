// Crc.cpp: implementation of the CCrc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuickStart.h"
#include "Crc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrc::CCrc() : m_pdwCrcTable(NULL)
{
}

CCrc::~CCrc()
{
	Free();
}

inline void CCrc::CalcCrc(const BYTE byte, DWORD &dwCrc) const
{
	dwCrc = ((dwCrc) >> 8) ^ m_pdwCrcTable[(byte) ^ ((dwCrc) & 0x000000FF)];
}

void CCrc::Init()
{
	// This is the official polynomial used by Crc in PKZip.
	// Often times the polynomial shown reversed as 0x04C11DB7.
	DWORD dwPolynomial = 0xEDB88320;
	int i, j;

	Free();
	m_pdwCrcTable = new DWORD[256];

	DWORD dwCrc;
	for(i = 0; i < 256; i++)
	{
		dwCrc = i;
		for(j = 8; j > 0; j--)
		{
			if(dwCrc & 1)
				dwCrc = (dwCrc >> 1) ^ dwPolynomial;
			else
				dwCrc >>= 1;
		}
		m_pdwCrcTable[i] = dwCrc;
	}
}

void CCrc::Free()
{
	if (m_pdwCrcTable)
	{
		delete m_pdwCrcTable;
		m_pdwCrcTable = NULL;
	}
}

DWORD CCrc::FileCrcAsm(LPCTSTR szFileName, DWORD& dwCrc) const
{
	_ASSERTE(szFileName);
	_ASSERTE(lstrlen(szFileName));

	DWORD dwErrorCode = NO_ERROR;
	HANDLE hFile = NULL;

	dwCrc = 0xFFFFFFFF;

	try
	{
		// Is the table initialized?
		if(m_pdwCrcTable == NULL)
			throw 0;

		// Open the file
		hFile = CreateFile(szFileName,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM | FILE_FLAG_SEQUENTIAL_SCAN,
			NULL);
		if(hFile == INVALID_HANDLE_VALUE)
			dwErrorCode = GetLastError();
		else
		{
			BYTE buffer[4096];
			DWORD dwBytesRead;
			BOOL bSuccess = ReadFile(hFile, buffer, sizeof(buffer), &dwBytesRead, NULL);
			while(bSuccess && dwBytesRead)
			{
				// Register use:
				//		eax - Crc value
				//		ebx - a lot of things
				//		ecx - Crc value
				//		edx - address of end of buffer
				//		esi - address of start of buffer
				//		edi - Crc table
				__asm
				{
					// Save the esi and edi registers
					push esi
					push edi

					mov eax, dwCrc			// Load the pointer to dwCrc
					mov ecx, [eax]				// Dereference the pointer to load dwCrc

					mov ebx, this				// Load the Crc table
					mov edi, [ebx]CCrc.m_pdwCrcTable

					lea esi, buffer				// Load buffer
					mov ebx, dwBytesRead		// Load dwBytesRead
					lea edx, [esi + ebx]		// Calculate the end of the buffer

				Crcloop:
					xor eax, eax				// Clear the eax register
					mov bl, byte ptr [esi]		// Load the current source byte
					
					mov al, cl					// Copy crc value into eax
					inc esi						// Advance the source pointer

					xor al, bl					// Create the index into the Crc table
					shr ecx, 8

					mov ebx, [edi + eax * 4]	// Get the value out of the table
					xor ecx, ebx				// xor with the current byte

					cmp edx, esi				// Have we reached the end of the buffer?
					jne Crcloop

					// Restore the edi and esi registers
					pop edi
					pop esi

					mov eax, dwCrc			// Load the pointer to dwCrc
					mov [eax], ecx				// Write the result
				}

				// c++ equivalent:
				// dwCrc = ((dwCrc) >> 8) ^ m_pdwCrcTable[(buffer[i]) ^ ((dwCrc) & 0x000000FF)];

				bSuccess = ReadFile(hFile, buffer, sizeof(buffer), &dwBytesRead, NULL);
			}
		}
	}
	catch(...)
	{
		// An unknown exception happened, or the table isn't initialized
		dwErrorCode = ERROR_CRC;
	}

	if(hFile != NULL) CloseHandle(hFile);

	dwCrc = ~dwCrc;

	return dwErrorCode;
}

//***********************************************
DWORD CCrc::StringCrc(LPCTSTR szString, DWORD &dwCrc) const
{
	_ASSERTE(szString);

	DWORD dwErrorCode = NO_ERROR;

	dwCrc = 0xFFFFFFFF;

	try
	{
		// Is the table initialized?
		if(m_pdwCrcTable == NULL)
			throw 0;

		while(*szString != _T('\0'))
		{
			CalcCrc((BYTE)*szString, dwCrc);
			szString++;
		}
	}
	catch(...)
	{
		// An unknown exception happened, or the table isn't initialized
		dwErrorCode = ERROR_CRC;
	}

	dwCrc = ~dwCrc;

	return dwErrorCode;

}
