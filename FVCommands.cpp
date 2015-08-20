#include "fvcommands.h"
#include "utils.h"
#include <new>  // std::nothrow
#include "CFolderViewCommand.h"
#include "NewFolderCommand.h"
#include "DisplayCommand.h"

extern HINSTANCE g_hInst;

// Sub Commands for Settings
//const FVCOMMANDITEM CFolderViewCommandProvider::c_FVTaskSettings[] =
//{
//    // Icon reference should be replaced by absolute reference to own icon resource.
//    {&GUID_Setting1, IDS_SETTING1,   IDS_SETTING1_TT,  L"shell32.dll,-16710",  0, CFolderViewCommandProvider::s_OnSetting1, NULL, 0},
//    {&GUID_Setting2, IDS_SETTING2,   IDS_SETTING2_TT,  L"shell32.dll,-16710",  0, CFolderViewCommandProvider::s_OnSetting2, NULL, 0},
//    {&GUID_Setting3, IDS_SETTING3,   IDS_SETTING3_TT,  L"shell32.dll,-16710",  0, CFolderViewCommandProvider::s_OnSetting3, NULL, 0}
//};

// Top-level commands
const FVCOMMANDITEM CFolderViewCommandProvider::c_FVTasks[] =
{
    // Icon reference should be replaced by absolute reference to own icon resource.
    {&GUID_Display, DISPLAY_COM ,IDS_DISPLAY,    IDS_DISPLAY_TT,   L"shell32.dll,-42",     0,                  CFolderViewCommandProvider::s_OnDisplay,             NULL,                          0 },
	{&GUID_New_folder, NEW_FOLDER_COM, IDS_NEW_FOLDER, IDS_NEW_FOLDER_TT, L"shell32.dll,-42", 0, CFolderViewCommandProvider::s_OnNewFolder, NULL, 0 }
    //{&GUID_Settings, IDS_SETTINGS,   IDS_SETTINGS_TT,  L"shell32.dll,-16710",  ECF_HASSUBCOMMANDS, NULL,                                    c_FVTaskSettings, ARRAYSIZE(c_FVTaskSettings)}
};

IFACEMETHODIMP CFolderViewCommandProvider::GetCommands(IUnknown * /* punkSite */, REFIID riid, void **ppv)
{
    *ppv = NULL;
    CFolderViewCommandEnumerator *pFVCommandEnum = new (std::nothrow) CFolderViewCommandEnumerator(c_FVTasks, ARRAYSIZE(c_FVTasks), m_pFolderView);
    HRESULT hr = pFVCommandEnum ? S_OK : E_OUTOFMEMORY;
    if (SUCCEEDED(hr))
    {
        hr = pFVCommandEnum->QueryInterface(riid, ppv);
        pFVCommandEnum->Release();
    }
    return hr;
}

HRESULT CFolderViewCommandProvider::s_OnDisplay(IShellItemArray *psiItemArray, IUnknown * /* pv */)
{
    return DisplayItem(psiItemArray, NULL);
}

HRESULT CFolderViewCommandProvider::s_OnNewFolder(IShellItemArray * /* psiItemArray */, IUnknown * /* pv */)
{
	DataProvider dataProvider;
	dataProvider.logInfo("Create new folder");
	//SendMessage(pici->hwnd, 0x111, 0x7103, 0);
	return S_OK;
}

HRESULT CFolderViewCommandProvider::s_OnSetting1(IShellItemArray * /* psiItemArray */, IUnknown * /* pv */)
{
    WCHAR sz[100];
    HRESULT hr = LoadString(g_hInst, IDS_SETTING1, sz, ARRAYSIZE(sz)) ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        MessageBox(NULL, sz, sz, MB_OK);
    }
    return hr;
}

HRESULT CFolderViewCommandProvider::s_OnSetting2(IShellItemArray * /* psiItemArray */, IUnknown * /* pv */)
{
    WCHAR sz[100];
    HRESULT hr = LoadString(g_hInst, IDS_SETTING2, sz, ARRAYSIZE(sz)) ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        MessageBox(NULL, sz, sz, MB_OK);
    }
    return hr;
}

HRESULT CFolderViewCommandProvider::s_OnSetting3(IShellItemArray * /* psiItemArray */, IUnknown * /* pv */)
{
    WCHAR sz[100];
    HRESULT hr = LoadString(g_hInst, IDS_SETTING3, sz, ARRAYSIZE(sz)) ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        MessageBox(NULL, sz, sz, MB_OK);
    }
    return hr;
}

HRESULT CFolderViewCommandEnumerator::_CreateCommandFromCommandItem(FVCOMMANDITEM *pfvci, IExplorerCommand **ppExplorerCommand)
{
	CFolderViewCommand *pCommand;
	switch (pfvci->commandId)
	{
		case NEW_FOLDER_COM:
		{
			pCommand = new (std::nothrow) NewFolderCommand(pfvci, m_pFolderView);
			break;
		}
		case DISPLAY_COM:
		{
			pCommand = new (std::nothrow) DisplayCommand(pfvci);
			break;
		}
	}
    HRESULT hr = pCommand ? S_OK : E_OUTOFMEMORY;
    if (SUCCEEDED(hr))
    {
        hr = pCommand->QueryInterface(IID_PPV_ARGS(ppExplorerCommand));
        pCommand->Release();
    }
    return hr;
}

IFACEMETHODIMP CFolderViewCommandEnumerator::Next(ULONG celt, IExplorerCommand** apUICommand, ULONG *pceltFetched)
{
    HRESULT hr = S_FALSE;
    if (_uCurrent <= _uCommands)
    {
        UINT uIndex = 0;
        HRESULT hrLocal = S_OK;
        while (uIndex < celt && _uCurrent < _uCommands && SUCCEEDED(hrLocal))
        {
            hrLocal = _CreateCommandFromCommandItem((FVCOMMANDITEM*)&(_apfvci[_uCurrent]), &(apUICommand[uIndex]));
            uIndex++;
            _uCurrent++;
        }

        if (pceltFetched != NULL)
        {
            *pceltFetched = uIndex;
        }

        if (uIndex == celt)
        {
            hr = S_OK;
        }
    }
    return hr;
}

IFACEMETHODIMP CFolderViewCommandEnumerator::Skip(ULONG celt)
{
    _uCurrent += celt;

    HRESULT hr = S_OK;
    if (_uCurrent > _uCommands)
    {
        _uCurrent = _uCommands;
        hr = S_FALSE;
    }
    return hr;
}

IFACEMETHODIMP CFolderViewCommandEnumerator::Reset()
{
    _uCurrent = 0;
    return S_OK;
}


