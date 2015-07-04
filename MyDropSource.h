#include <atlbase.h>

class MyDropSource : public IDropSource
{

private:
	long m_cRef;
	IUnknown *m_pFolder;

public :

	MyDropSource::MyDropSource(IUnknown *pFolder) : m_cRef(0), m_pFolder(pFolder)
	{
		//DllAddRef();
		m_pFolder->AddRef();
	}

	MyDropSource::~MyDropSource()
	{
		//DllRelease();
		m_pFolder->Release();
	}

	//IUnknown implementation
	HRESULT MyDropSource::QueryInterface(REFIID riid, void **ppv)
	{
		static const QITAB qit[] =
		{
			QITABENT(MyDropSource, IUnknown),
			QITABENT(MyDropSource, IDropSource),
			{ 0 },
		};
		return QISearch(this, qit, riid, ppv);
	}

	ULONG MyDropSource::AddRef()
	{
		return InterlockedIncrement(&m_cRef);
	}

	ULONG MyDropSource::Release()
	{
		long cRef = InterlockedDecrement(&m_cRef);
		if (0 == cRef)
		{
			delete this;
		}
		return cRef;
	}

	HRESULT MyDropSource::QueryContinueDrag(BOOL bEsc, DWORD dwKeyState)
	{
		if (bEsc)
			return ResultFromScode(DRAGDROP_S_CANCEL);

		if ((dwKeyState & MK_LBUTTON) == 0)
			return ResultFromScode(DRAGDROP_S_DROP);

		return S_OK;
	}

	HRESULT MyDropSource::GiveFeedback(DWORD)
	{
		return ResultFromScode(DRAGDROP_S_USEDEFAULTCURSORS);
	}

};