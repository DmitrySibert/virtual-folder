/**************************************************************************
    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   (c) Microsoft Corporation. All Rights Reserved.
**************************************************************************/

#pragma once

#include <windows.h>
#include <shlobj.h>
#include <propkey.h>
#include <shlwapi.h>
#include <strsafe.h>
#include "DataProvider.h"
#include "CFolderViewImplFolder.h"

#include "resource.h"

typedef HRESULT (*PFN_ExplorerCommandExecute)(IShellItemArray *psiItemArray, IUnknown* pv);
typedef unsigned short int COM_ID;

//define command identifiers
#define NEW_FOLDER_COM 1001
#define DISPLAY_COM 1002

struct FVCOMMANDITEM
{
    const GUID* pguidCanonicalName;
	COM_ID commandId;
    DWORD dwTitleID;
    DWORD dwToolTipID;
    PCWSTR pszIcon;
    EXPCMDFLAGS ecFlags;
    PFN_ExplorerCommandExecute pfnInvoke;
    const FVCOMMANDITEM *pFVCIChildren;
    UINT uChildCommands;
};


// GUIDs for our commands

// {CA133333-0D7D-47ff-BEE5-2C99DA47A7D9}
DEFINE_GUID(GUID_Display, 0xca133333, 0xd7d, 0x47ff, 0xbe, 0xe5, 0x2c, 0x99, 0xda, 0x47, 0xa7, 0xd9);
// {BE901C03-EA3B-4d3d-B6F7-C3D2FE94BE69}
DEFINE_GUID(GUID_Settings, 0xbe901c03, 0xea3b, 0x4d3d, 0xb6, 0xf7, 0xc3, 0xd2, 0xfe, 0x94, 0xbe, 0x69);
// {3F6FA710-63A8-4843-92CE-F3216D2B20D6}
DEFINE_GUID(GUID_Setting1, 0x3f6fa710, 0x63a8, 0x4843, 0x92, 0xce, 0xf3, 0x21, 0x6d, 0x2b, 0x20, 0xd6);
// {43077C60-029C-4e1e-9CF6-9C38B9512342}
DEFINE_GUID(GUID_Setting2, 0x43077c60, 0x29c, 0x4e1e, 0x9c, 0xf6, 0x9c, 0x38, 0xb9, 0x51, 0x23, 0x42);
// {B8F3F98F-DDB6-48b3-BF93-81D2A791BFF9}
DEFINE_GUID(GUID_Setting3, 0xb8f3f98f, 0xddb6, 0x48b3, 0xbf, 0x93, 0x81, 0xd2, 0xa7, 0x91, 0xbf, 0xf9);
// {F2930723-DA4F-4CDE-B338-186CF99CE988}
DEFINE_GUID(GUID_New_folder,   0xf2930723, 0xda4f, 0x4cde, 0xb3, 0x38, 0x18, 0x6c, 0xf9, 0x9c, 0xe9, 0x88);

class CFolderViewCommandProvider : public IExplorerCommandProvider
{
public:
    // IUnknown
    IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        static const QITAB qit[] =
        {
            QITABENT(CFolderViewCommandProvider, IExplorerCommandProvider),
            { 0 },
        };
        return QISearch(this, qit, riid, ppv);
    }

    IFACEMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&_cRef); }
    IFACEMETHODIMP_(ULONG) Release()
    {
        long cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
        {
            delete this;
        }
        return cRef;
    }

    // IExplorerCommandProvider
    IFACEMETHODIMP GetCommands(IUnknown *punkSite, REFIID riid, void **ppv);
    IFACEMETHODIMP GetCommand(REFGUID /* rguidCommandId */, REFIID /* riid */, void **ppv)
        { *ppv = NULL; return E_NOTIMPL; }

	CFolderViewCommandProvider(CFolderViewImplFolder *pFolderView) : _cRef(1), m_pFolderView(pFolderView)
    {
    }

private:
    static HRESULT s_OnDisplay(IShellItemArray *psiItemArray, IUnknown *pv);
    static HRESULT s_OnSetting1(IShellItemArray *psiItemArray, IUnknown *pv);
    static HRESULT s_OnSetting2(IShellItemArray *psiItemArray, IUnknown *pv);
    static HRESULT s_OnSetting3(IShellItemArray *psiItemArray, IUnknown *pv);
	static HRESULT s_OnNewFolder(IShellItemArray *psiItemArray, IUnknown *pv);

private:
	CFolderViewImplFolder *m_pFolderView;
    /*static const FVCOMMANDITEM c_FVTaskSettings[];*/
    static const FVCOMMANDITEM c_FVTasks[];
    long _cRef;
};

class CFolderViewCommandEnumerator : public IEnumExplorerCommand
{
public:
    // IUnknown
    IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv)
    {
        static const QITAB qit[] =
        {
            QITABENT(CFolderViewCommandEnumerator, IEnumExplorerCommand),
            { 0 },
        };
        return QISearch(this, qit, riid, ppv);
    }

    IFACEMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&_cRef); }
    IFACEMETHODIMP_(ULONG) Release()
    {
        long cRef = InterlockedDecrement(&_cRef);
        if (!cRef)
        {
            delete this;
        }
        return cRef;
    }

    // IEnumExplorerCommand
    IFACEMETHODIMP Next(ULONG celt, IExplorerCommand **apUICommand, ULONG *pceltFetched);
    IFACEMETHODIMP Skip(ULONG celt);
    IFACEMETHODIMP Reset();
    IFACEMETHODIMP Clone(IEnumExplorerCommand **ppenum)
        { *ppenum = NULL; return E_NOTIMPL; }

	CFolderViewCommandEnumerator(const FVCOMMANDITEM *apfvc, UINT uCommands, CFolderViewImplFolder *pFolderView)
		: _cRef(1), _uCurrent(0), _uCommands(uCommands), _apfvci(apfvc), m_pFolderView(pFolderView)
    {
    }

private:
    HRESULT _CreateCommandFromCommandItem(FVCOMMANDITEM *pfvci, IExplorerCommand **ppExplorerCommand);

    ~CFolderViewCommandEnumerator(){}

private:
	CFolderViewImplFolder *m_pFolderView;
    long _cRef;
    ULONG _uCurrent;
    ULONG _uCommands;
    const FVCOMMANDITEM *_apfvci;
};


