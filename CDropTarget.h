#include <atlbase.h>
//#include "Utils.h"

//////////////////////////////////////////////////////////////////////////////
// CNSFDropTarget
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

	//IUnknown
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

	// IDropTarget
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

		*pdwEffect = DROPEFFECT_NONE; // default to failed/cancelled
		// Determine drop effect...
		DWORD dwDropEffect = _QueryDrop();
		// Did we accept this drop effect?
		if (dwDropEffect == DROPEFFECT_NONE)
			return S_OK;
		return S_OK;
	}
};


