#include <atlbase.h>
#include "IDropHandler.h"
//#include "Utils.h"

class MyDropTarget : public IDropTarget
{
private:
	long m_cRef;
	IUnknown *m_pFolder;
public:

	MyDropTarget::MyDropTarget(IUnknown *pFolder) : m_cRef(0), m_pFolder(pFolder)
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
		DWORD dwDropEffect = _QueryDrop();		
		STGMEDIUM stgmed;
		FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
		HRESULT hr = pDataObj->GetData(&fe, &stgmed);
		std::list<TCHAR*> files;
		if (S_OK == hr)
		{
			HDROP hDrop = (HDROP)stgmed.hGlobal;
			UINT nFiles = DragQueryFile(hDrop, (UINT)-1, NULL, 0);
			for (UINT i = 0; i < nFiles; i++)
			{
				UINT nameSize = DragQueryFile(hDrop, i, NULL, 0) + 1;
				TCHAR *szFileDropped = new TCHAR[nameSize];
				DragQueryFile(hDrop, i, szFileDropped, nameSize);
				files.push_back(szFileDropped);
				bool t = true;
			}
		}
		ReleaseStgMedium(&stgmed);
		IDropHandler *pDropHandler;
		this->m_pFolder->QueryInterface(IID_IDropHandler, (void**) &pDropHandler);
		pDropHandler->DoDrop(files);
		while(!files.empty())
		{
			TCHAR *file = files.back();
			delete[] file;
			files.pop_back();
		}
		this->m_pFolder->Release();
		if (dwDropEffect == DROPEFFECT_NONE)
			return S_OK;
		return S_OK;
	}
};


