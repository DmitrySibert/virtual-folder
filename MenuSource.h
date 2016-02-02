/**************************************************************************
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

(c) Microsoft Corporation. All Rights Reserved.
**************************************************************************/

#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include "utils.h"
#include "resource.h"
#include <new>  // std::nothrow
#include "DataProvider.h"
#include "CFolderViewImplFolder.h"

#define MENUVERB_DELETE          1

// The "terminator" ICIVERBTOIDMAP structure is {NULL, NULL, (UINT)-1,}

#define IS_UNICODE_ICI(pici) (((pici)->fMask & CMIC_MASK_UNICODE) == CMIC_MASK_UNICODE)

typedef struct
{
	LPCWSTR pszCmd;         // verbW
	LPCSTR  pszCmdA;        // verbA
	UINT    idCmd;          // hmenu id
	UINT    idsHelpText;    // id of help text
} ICIVERBTOIDMAP;

const ICIVERBTOIDMAP c_FolderViewImplContextMenuIDMap[] =
{
	{ L"delete",     "delete",    MENUVERB_DELETE,   0, },
	{ NULL,          NULL,       (UINT)-1,           0, }
};

class MyMenu : public IContextMenu

{
public:
	MyMenu(CFolderViewImplFolder *pFolder) : _cRef(1), m_pFolder(pFolder)
	{
		m_pFolder->AddRef();
	}

	// IUnknown
	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv)
	{
		static const QITAB qit[] = {
			QITABENT(MyMenu, IContextMenu),
			{ 0 },
		};
		return QISearch(this, qit, riid, ppv);
	}

	IFACEMETHODIMP_(ULONG) AddRef()
	{
		return InterlockedIncrement(&_cRef);
	}

	IFACEMETHODIMP_(ULONG) Release()
	{
		long cRef = InterlockedDecrement(&_cRef);
		if (!cRef)
		{
			delete this;
		}
		return cRef;
	}


	// IContextMenu
	IFACEMETHODIMP QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
	{
		WCHAR szMenuItem[80];
		LoadString(g_hInst, IDS_DELETE, szMenuItem, ARRAYSIZE(szMenuItem));
		InsertMenu(hmenu, indexMenu++, MF_BYPOSITION, idCmdFirst + MENUVERB_DELETE, szMenuItem);
		// other verbs could go here...

		// indicate that we added one verb.
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, (USHORT)(2));
	}
	IFACEMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO pici)
	{
		HRESULT hr = E_INVALIDARG;
		UINT uID;
		// Is this command for us?
		if (SUCCEEDED(_MapICIVerbToCmdID2(pici, c_FolderViewImplContextMenuIDMap, &uID)))
		{
			switch (uID)
			{
				case MENUVERB_DELETE:
				{
					m_pFolder->_OnCreateFolder();
					break;
				}
			}
		}
		return hr;
	}
	IFACEMETHODIMP GetCommandString(UINT_PTR idCmd, UINT uType, UINT *pRes, LPSTR pszName, UINT cchMax)
	{
		return E_NOTIMPL;
	}

private:
	const ICIVERBTOIDMAP* _CmdIDToMap2(UINT_PTR idCmd, BOOL fUnicode, const ICIVERBTOIDMAP* pmap)
	{
		const ICIVERBTOIDMAP* pmapRet = NULL;
		if (IS_INTRESOURCE(idCmd))
		{
			UINT idVerb = (UINT)idCmd;
			while (!pmapRet && -1 != pmap->idCmd)
			{
				if (pmap->idCmd == idVerb)
				{
					pmapRet = pmap;
				}
				pmap++;
			}
		}
		else if (fUnicode)
		{
			LPCWSTR pszVerb = (LPCWSTR)idCmd;
			while (!pmapRet && -1 != pmap->idCmd)
			{
				if (pmap->pszCmd && 0 == StrCmpIC(pszVerb, pmap->pszCmd))
				{
					pmapRet = pmap;
				}
				pmap++;
			}
		}
		else
		{
			LPCSTR pszVerbA = (LPCSTR)idCmd;
			while (!pmapRet && -1 != pmap->idCmd)
			{
				if (pmap->pszCmdA && 0 == StrCmpICA(pszVerbA, pmap->pszCmdA))
				{
					pmapRet = pmap;
				}
				pmap++;
			}
		}
		return pmapRet;
	}



	HRESULT _MapICIVerbToCmdID2(LPCMINVOKECOMMANDINFO pici, const ICIVERBTOIDMAP* pmap, UINT* pid)
	{
		HRESULT hr = E_FAIL;

		if (!IS_INTRESOURCE(pici->lpVerb))
		{
			UINT_PTR idCmd;
			BOOL fUnicode;

			if (IS_UNICODE_ICI(pici) && ((LPCMINVOKECOMMANDINFOEX)pici)->lpVerbW)
			{
				fUnicode = TRUE;
				idCmd = (UINT_PTR)(((LPCMINVOKECOMMANDINFOEX)pici)->lpVerbW);
			}
			else
			{
				fUnicode = FALSE;
				idCmd = (UINT_PTR)(pici->lpVerb);
			}

			pmap = _CmdIDToMap2(idCmd, fUnicode, pmap);
			if (pmap)
			{
				*pid = pmap->idCmd;
				hr = S_OK;
			}
		}
		else
		{
			*pid = LOWORD((UINT_PTR)pici->lpVerb);
			hr = S_OK;
		}
		return hr;
	}
	long    _cRef;
	CFolderViewImplFolder *m_pFolder;
	~MyMenu()
	{
		m_pFolder->Release();
	}
};

