/**************************************************************************
    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   (c) Microsoft Corporation. All Rights Reserved.
**************************************************************************/

#include <windows.h>
#include <shlobj.h>
#include "resource.h"
#include "Utils.h"
#include "shlwapi.h"

// Do not modify order here
static const UINT g_rgIDs[] =
{
    IDS_ZERO,
    IDS_ONE,
    IDS_TWO,
    IDS_THREE,
    IDS_FOUR,
    IDS_FIVE,
    IDS_SIX,
    IDS_SEVEN,
    IDS_EIGHT,
    IDS_NINE
};

/**
uIndex - ����� �������� � ������� ��������
psz - ��������� �� ������, � ������� ����� ������� ������
��� - ������ ������ � ������� ����� ����� ������
*/
HRESULT LoadFolderViewImplDisplayString(UINT uIndex, PWSTR psz, UINT cch)
{
    HRESULT hr = E_FAIL;

    UINT uString = 0; //����� ���������� �������
    if (uIndex < ARRAYSIZE(g_rgIDs))
    {
        uString = g_rgIDs[uIndex];
    }

    if (uString)
    {
        if (LoadString(g_hInst, uString, psz, cch))
        {
            hr = S_OK;
        }
    }
    return hr;
}

HRESULT GetIndexFromDisplayString(PCWSTR psz, UINT *puIndex)
{
    HRESULT hr = E_FAIL;

    *puIndex = 0;
    WCHAR szBuff[100] = {};
    for (UINT u = 0; u < ARRAYSIZE(g_rgIDs); u++)
    {
        if (LoadString(g_hInst, g_rgIDs[u], szBuff, ARRAYSIZE(szBuff)))
        {
            if (lstrcmpi(szBuff, psz) == 0)
            {
                *puIndex = u;
                hr = S_OK;
                break;
            }
        }
    }
    return hr;
}

HRESULT LoadFolderViewImplDisplayStrings(PWSTR wszArrStrings[], UINT cArray)
{
    HRESULT hr = S_OK;
    for (UINT i = 0; SUCCEEDED(hr) && i < cArray; i++)
    {
        WCHAR wszTemp[MAX_PATH];
        hr = LoadFolderViewImplDisplayString(i, wszTemp, ARRAYSIZE(wszTemp));
        if (SUCCEEDED(hr))
        {
            hr = SHStrDup(wszTemp, &wszArrStrings[i]);
            if (FAILED(hr))
            {
                // Free those already allocated.
                for (UINT k = 0; k < i; k++)
                {
                    CoTaskMemFree(wszArrStrings[k]);
                    wszArrStrings[k] = NULL;
                }
                break;
            }
        }
        else
        {
            // Somebody tried increasing the size of the array without
            // adding additional strings.
            wszArrStrings[i] = NULL;
        }
    }
    return hr;
}

STDAPI StringToStrRet(PCWSTR pszName, STRRET *pStrRet)
{
    pStrRet->uType = STRRET_WSTR;
    return SHStrDup(pszName, &pStrRet->pOleStr);
}

WCHAR* getFolderTitle()
{	
	WCHAR *szBuff = new WCHAR[100];
	LoadString(g_hInst, IDS_FOLDER_TITLE, szBuff, 100);
	return szBuff;
}

char* GetRefPath(PIDLIST_ABSOLUTE ppidlCurrentFolder)
{
	wchar_t *pszThisFolder1 = new wchar_t[MAX_PATH];
	//�������� ��������������� ���� ������ ���������� �� ������� �����
	SHGetNameFromIDList(ppidlCurrentFolder, SIGDN_DESKTOPABSOLUTEEDITING, &pszThisFolder1);
	//�������� ��� ���������� ������ ����������
	wchar_t *folderName = getFolderTitle();
	int len = wcslen(folderName);
	//�������� ��������� �� ������ ��������� ����� ���������� � ���������� ��� -> �������� ��������� �� ��� ���� ������ ����������
	wchar_t * contentPath = NULL;
	wchar_t emptyStr[1] = L"";
	if (wcslen(wcsstr(pszThisFolder1, folderName)) == len)
	{
		contentPath = emptyStr;
	}
	else
	{
		contentPath = wcsstr(pszThisFolder1, folderName) + len + 1;
	}
	//������� ����������� DataProvider ��� ��������� ���������� � ���������� ���� ����������
	//���������� ��������� tchar ���� � ������������� ����� � char
	char *cFolderPath = new char[MAX_PATH];
	WideCharToMultiByte(CP_ACP, // ANSI Code Page
		0, // No special handling of unmapped chars
		contentPath, // wide-character string to be converted
		MAX_PATH,
		cFolderPath,
		MAX_PATH,
		NULL, NULL);
	int kk = 10;
	//delete[] pszThisFolder1;
	delete[] folderName;

	return cFolderPath;
}

HRESULT DisplayItem(IShellItemArray *psia, HWND hwnd)
{
    // Get the first ShellItem and display its name
    IShellItem *psi;
    HRESULT hr = psia->GetItemAt(0, &psi);
    if (SUCCEEDED(hr))
    {
        PWSTR pszDisplayName;
        hr = psi->GetDisplayName(SIGDN_NORMALDISPLAY, &pszDisplayName);
        if (SUCCEEDED(hr))
        {
            MessageBox(hwnd, pszDisplayName, pszDisplayName, MB_OK);
            CoTaskMemFree(pszDisplayName);
        }
        psi->Release();
    }
    return hr;
}