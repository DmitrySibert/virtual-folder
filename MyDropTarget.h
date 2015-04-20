#include <atlbase.h>
//#include "Utils.h"

class MyDropTarget : public IDropTarget
{
private:
	long m_cRef;
public:

	MyDropTarget::MyDropTarget() : m_cRef(0)
	{
		//DllAddRef();
	}

	MyDropTarget::~MyDropTarget()
	{
		//DllRelease();
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
		if (S_OK == hr)
		{
			HDROP hDrop = (HDROP)stgmed.hGlobal;
			UINT nFiles = DragQueryFile(hDrop, (UINT)-1, NULL, 0);
			for (UINT i = 0; i < nFiles; i++)
			{
				TCHAR szFileDropped[MAX_PATH];
				DragQueryFile(hDrop, i, szFileDropped, sizeof(szFileDropped));
				bool t = true;
			}
		}
		ReleaseStgMedium(&stgmed);

		if (dwDropEffect == DROPEFFECT_NONE)
			return S_OK;
		return S_OK;
	}
};


