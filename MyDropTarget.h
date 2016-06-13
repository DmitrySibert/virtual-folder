#include <atlbase.h>
#include "IDropHandler.h"
#include <Shobjidl.h>
//#include "Utils.h"

class MyDropTarget : public IDropTarget
{
private:
	long m_cRef;
	IUnknown *m_pFolder;
	LPCITEMIDLIST m_subfolder;
public:

	MyDropTarget::MyDropTarget(IUnknown *pFolder, LPCITEMIDLIST subfolder) : m_cRef(0), m_pFolder(pFolder), m_subfolder(subfolder)
	{
		//DllAddRef();
		m_pFolder->AddRef();
	}

	MyDropTarget::~MyDropTarget()
	{
		//DllRelease();
		m_pFolder->Release();
	}

	//IUnknown implementation
	HRESULT MyDropTarget::QueryInterface(REFIID riid, void **ppv)
	{
		static const QITAB qit[] =
		{
			QITABENT(MyDropTarget, IUnknown),
			QITABENT(MyDropTarget, IDropTarget),
			{ 0 },
		};
		return QISearch(this, qit, riid, ppv);
	}

	ULONG MyDropTarget::AddRef()
	{
		return InterlockedIncrement(&m_cRef);
	}

	ULONG MyDropTarget::Release()
	{
		long cRef = InterlockedDecrement(&m_cRef);
		if (0 == cRef)
		{
			delete this;
		}
		return cRef;
	}

	// Implementation
	DWORD _QueryDrop()
	{
		return DROPEFFECT_MOVE;
	}

	// IDropTarget implementation
	STDMETHOD(DragEnter)(LPDATAOBJECT pDataObj, DWORD dwKeyState, POINTL, LPDWORD pdwEffect)
	{
		*pdwEffect = _QueryDrop();
		return S_OK;
	}

	STDMETHOD(DragOver)(DWORD dwKeyState, POINTL /*pt*/, LPDWORD pdwEffect)
	{
		*pdwEffect = _QueryDrop();
		return S_OK;
	}

	STDMETHOD(DragLeave)(VOID)
	{
		return S_OK;
	}

	STDMETHOD(Drop)(LPDATAOBJECT pDataObj, DWORD dwKeyState, POINTL /*pt*/, LPDWORD pdwEffect)
	{

		*pdwEffect = DROPEFFECT_NONE;	
		IShellItemArray *psia;
		HRESULT hr = SHCreateShellItemArrayFromDataObject(pDataObj, IID_PPV_ARGS(&psia));
		IShellItem *psi;
		DWORD nFiles;
		std::list<TCHAR*> files;
		std::list<bool> isFolderFlags;
		if (SUCCEEDED(hr))
		{
			hr = psia->GetCount(&nFiles);
			if (SUCCEEDED(hr))
			{
				for (DWORD i = 0; i < nFiles; ++i)
				{
					hr = psia->GetItemAt(i, &psi);
					if (SUCCEEDED(hr))
					{
						PIDLIST_ABSOLUTE pidl;
						hr = SHGetIDListFromObject(psi, &pidl);
						wchar_t *szFileDropped = new wchar_t[MAX_PATH];
						SHGetNameFromIDList(pidl, SIGDN_DESKTOPABSOLUTEEDITING, &szFileDropped);
						files.push_back(szFileDropped);
						SHFILEINFOW sfi = { 0 };
						hr = SHGetFileInfo((LPCTSTR)pidl,
							-1,
							&sfi,
							sizeof(sfi),
							SHGFI_PIDL | SHGFI_DISPLAYNAME
						);
						bool isFolder = sfi.dwAttributes & SFGAO_FOLDER;
						isFolderFlags.push_back(isFolder);
					}
				}
			}
		}
		IDropHandler *pDropHandler;
		this->m_pFolder->QueryInterface(IID_IDropHandler, (void**) &pDropHandler);
		pDropHandler->DoDrop(files, isFolderFlags, this->m_subfolder);
		while(!files.empty())
		{
			TCHAR *file = files.back();
			CoTaskMemFree(file);
			files.pop_back();
		}
		this->m_pFolder->Release();
		return S_OK;
	}
};


