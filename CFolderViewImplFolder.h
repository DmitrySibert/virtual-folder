#pragma once

#include "IDropHandler.h"
#include "Utils.h"

#define MYOBJID 0x1234

// FVITEMID is allocated with a variable size, szName is the beginning
// of a NULL-terminated string buffer.
#pragma pack(1)
typedef struct tagObject
{
	USHORT  cb;
	WORD    MyObjID;
	BYTE    nLevel;
	BYTE    nSize;
	BYTE    nSides;
	BYTE    cchName;
	BOOL    fIsFolder;
	WCHAR   szName[1];
} FVITEMID;
#pragma pack()

typedef UNALIGNED FVITEMID *PFVITEMID;
typedef const UNALIGNED FVITEMID *PCFVITEMID;

class CFolderViewImplFolder : public IShellFolder2,
	public IPersistFolder2,
	public IDropHandler
{
public:
	CFolderViewImplFolder(UINT nLevel);

	// IUnknown methods
	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
	IFACEMETHODIMP_(ULONG) AddRef();
	IFACEMETHODIMP_(ULONG) Release();

	// IShellFolder
	IFACEMETHODIMP ParseDisplayName(HWND hwnd, IBindCtx *pbc, PWSTR pszName,
		ULONG *pchEaten, PIDLIST_RELATIVE *ppidl, ULONG *pdwAttributes);
	IFACEMETHODIMP EnumObjects(HWND hwnd, DWORD grfFlags, IEnumIDList **ppenumIDList);
	IFACEMETHODIMP BindToObject(PCUIDLIST_RELATIVE pidl, IBindCtx *pbc, REFIID riid, void **ppv);
	IFACEMETHODIMP BindToStorage(PCUIDLIST_RELATIVE pidl, IBindCtx *pbc, REFIID riid, void **ppv);
	IFACEMETHODIMP CompareIDs(LPARAM lParam, PCUIDLIST_RELATIVE pidl1, PCUIDLIST_RELATIVE pidl2);
	IFACEMETHODIMP CreateViewObject(HWND hwnd, REFIID riid, void **ppv);
	IFACEMETHODIMP GetAttributesOf(UINT cidl, PCUITEMID_CHILD_ARRAY apidl, ULONG *rgfInOut);
	IFACEMETHODIMP GetUIObjectOf(HWND hwnd, UINT cidl, PCUITEMID_CHILD_ARRAY apidl,
		REFIID riid, UINT* prgfInOut, void **ppv);
	IFACEMETHODIMP GetDisplayNameOf(PCUITEMID_CHILD pidl, SHGDNF shgdnFlags, STRRET *pName);
	IFACEMETHODIMP SetNameOf(HWND hwnd, PCUITEMID_CHILD pidl, PCWSTR pszName, DWORD uFlags, PITEMID_CHILD * ppidlOut);

	// IShellFolder2
	IFACEMETHODIMP GetDefaultSearchGUID(GUID *pGuid);
	IFACEMETHODIMP EnumSearches(IEnumExtraSearch **ppenum);
	IFACEMETHODIMP GetDefaultColumn(DWORD dwRes, ULONG *pSort, ULONG *pDisplay);
	IFACEMETHODIMP GetDefaultColumnState(UINT iColumn, SHCOLSTATEF *pbState);
	IFACEMETHODIMP GetDetailsEx(PCUITEMID_CHILD pidl, const PROPERTYKEY *pkey, VARIANT *pv);
	IFACEMETHODIMP GetDetailsOf(PCUITEMID_CHILD pidl, UINT iColumn, SHELLDETAILS *pDetails);
	IFACEMETHODIMP MapColumnToSCID(UINT iColumn, PROPERTYKEY *pkey);

	// IPersist
	IFACEMETHODIMP GetClassID(CLSID *pClassID);

	// IPersistFolder
	IFACEMETHODIMP Initialize(PCIDLIST_ABSOLUTE pidl);

	// IPersistFolder2
	IFACEMETHODIMP GetCurFolder(PIDLIST_ABSOLUTE *ppidl);

	// IDList constructor public for the enumerator object
	HRESULT CreateChildID(PCWSTR pszName, int nLevel, int nSize, int nSides, BOOL fIsFolder, PITEMID_CHILD *ppidl);

	// IDropHandler
	void DoDrop(list<TCHAR*> files, list<bool> isFolderFlags, LPCITEMIDLIST subfolder);
	HRESULT _OnCreateFolder();
	~CFolderViewImplFolder();

private:
	HRESULT _GetName(PCUIDLIST_RELATIVE pidl, PWSTR pszName, int cchMax);
	HRESULT _GetName(PCUIDLIST_RELATIVE pidl, PWSTR *pszName);
	HRESULT _GetSides(PCUIDLIST_RELATIVE pidl, int* pSides);
	HRESULT _GetLevel(PCUIDLIST_RELATIVE pidl, int* pLevel);
	HRESULT _GetSize(PCUIDLIST_RELATIVE pidl, int* pSize);
	HRESULT _GetFolderness(PCUIDLIST_RELATIVE pidl, BOOL* pfIsFolder);
	HRESULT _ValidatePidl(PCUIDLIST_RELATIVE pidl);
	PCFVITEMID _IsValid(PCUIDLIST_RELATIVE pidl);

	HRESULT _GetColumnDisplayName(PCUITEMID_CHILD pidl, const PROPERTYKEY* pkey, VARIANT* pv, WCHAR* pszRet, UINT cch);

	long                m_cRef;
	HWND				m_hWnd;
	int                 m_nLevel;
	PIDLIST_ABSOLUTE    m_pidl;             // where this folder is in the name space
	PWSTR               m_rgNames[MAX_OBJS];
	WCHAR               m_szModuleName[MAX_PATH];
};