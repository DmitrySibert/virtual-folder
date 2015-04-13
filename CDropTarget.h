
#if !defined(AFX_CNSFDROPTARGET_H__20041125_CE55_D769_D3CA_0080AD509054__INCLUDED_)
#define AFX_CNSFDROPTARGET_H__20041125_CE55_D769_D3CA_0080AD509054__INCLUDED_

#pragma once
#include <atlbase.h>
#include <atlcom.h>
#include <atldef.h>

//////////////////////////////////////////////////////////////////////////////
// CNSFDropTarget

class ATL_NO_VTABLE CNSFDropTarget :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDropTarget
{
public:

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CNSFDropTarget)
		COM_INTERFACE_ENTRY_IID(IID_IDropTarget, IDropTarget)
	END_COM_MAP()

public:

	//Data members
	UINT m_iAcceptFmt;
	LPITEMIDLIST m_pidl;  //simple PIDL relative to parent folder

	HRESULT FinalConstruct()
	{
		m_iAcceptFmt = 0;

		return S_OK;
	}

	void FinalRelease()
	{
		m_iAcceptFmt = 0;
	}

	HRESULT _Init(/* HWND hWnd,*/LPCITEMIDLIST pidl)
	{
		ATLTRACE(_T("CDropTarget::_Init\n"));
		/*ATLASSERT(pFolder);
		if (pFolder == NULL)
		{
			MessageBox(NULL, _T("CDropTarget::_Init() pFolder==NULL"), _T("NSF"), MB_OK);
			return E_FAIL;
		}
		m_pFolder = pFolder;
		m_pFolder->AddRef();*/
		return S_OK;
	}

	// Implementation
	DWORD _QueryDrop()
	{
		/*if (0 == m_iAcceptFmt)
			return DROPEFFECT_NONE;

		if (FMT_HDROP_INDEX == m_iAcceptFmt)
			return DROPEFFECT_COPY;

		if (FMT_NSEDRAGDROP_INDEX == m_iAcceptFmt)
			return DROPEFFECT_MOVE;*/

		return DROPEFFECT_MOVE;
	}

	// IDropTarget

	STDMETHOD(DragEnter)(LPDATAOBJECT pDataObj,
		DWORD dwKeyState,
		POINTL,
		LPDWORD pdwEffect)
	{
		ATLTRACE(_T("CDropTarget::DragEnter\n"));
		ATLASSERT(pDataObj);

		// Does the drag source provide self-defined CF types?
		m_iAcceptFmt = 0;

		if (m_iAcceptFmt == 0)
		{
			/*FORMATETC fe2 = { _Module.m_CFSTR_NSEDRAGDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
			if (S_OK == pDataObj->QueryGetData(&fe2))
			{
				m_iAcceptFmt = FMT_NSEDRAGDROP_INDEX;
			}
			else
			{
				FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
				if (S_OK == pDataObj->QueryGetData(&fe))
				{
					m_iAcceptFmt = FMT_HDROP_INDEX;
				}
			}*/
		}
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
		ATLTRACE(_T("CDropTarget::DragLeave\n"));
		m_iAcceptFmt = 0;
		return S_OK;
	}

	STDMETHOD(Drop)(LPDATAOBJECT pDataObj,
		DWORD dwKeyState,
		POINTL /*pt*/,
		LPDWORD pdwEffect)
	{
		ATLTRACE(_T("CDropTarget::Drop\n"));
		ATLASSERT(pDataObj);
		ATLASSERT(pdwEffect);
		//ATLASSERT(m_pFolder);

		*pdwEffect = DROPEFFECT_NONE; // default to failed/cancelled

		// Determine drop effect...
		DWORD dwDropEffect = _QueryDrop();

		// Did we accept this drop effect?
		if (dwDropEffect == DROPEFFECT_NONE)
			return S_OK;

		// Drop data...
		/*HRESULT Hr;
		if (SUCCEEDED(Hr = m_pFolder->_DoDrop(pDataObj, dwDropEffect, m_pidl, m_iAcceptFmt)))
		{
			*pdwEffect = dwDropEffect;
			return  S_OK;
		}
		else
		{
			return Hr;
		}*/
		return S_OK;
	}
};

#endif // !defined(AFX_CDROPTARGET_H__20041125_CE55_D769_D3CA_0080AD509054__INCLUDED_)

