#pragma once

#include <windows.h>
#include <shlobj.h>

class CFolderViewImplEnumIDList : public IEnumIDList
{
public:
	CFolderViewImplEnumIDList(DWORD grfFlags, int nCurrent, CFolderViewImplFolder *pFolderViewImplShellFolder);

	// IUnknown methods
	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
	IFACEMETHODIMP_(ULONG) AddRef();
	IFACEMETHODIMP_(ULONG) Release();

	// IEnumIDList
	IFACEMETHODIMP Next(ULONG celt, PITEMID_CHILD *rgelt, ULONG *pceltFetched);
	IFACEMETHODIMP Skip(DWORD celt);
	IFACEMETHODIMP Reset();
	IFACEMETHODIMP Clone(IEnumIDList **ppenum);

	HRESULT Initialize();

private:
	~CFolderViewImplEnumIDList();

	long m_cRef;
	DWORD m_grfFlags;
	int m_nItem;
	int m_nLevel;
	ITEMDATA m_aData[MAX_OBJS];

	CFolderViewImplFolder *m_pFolder;
};
