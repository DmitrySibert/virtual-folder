#pragma once
#include "ShObjIdl.h"
#include "fvcommands.h"


class CFolderViewCommand : public IExplorerCommand
{
public:
	// IUnknown
	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv)
	{
		static const QITAB qit[] =
		{
			QITABENT(CFolderViewCommand, IExplorerCommand),
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

	// IExplorerCommand
	IFACEMETHODIMP GetTitle(IShellItemArray *psiItemArray, LPWSTR *ppszName);
	IFACEMETHODIMP GetIcon(IShellItemArray *psiItemArray, LPWSTR *ppszIcon);
	IFACEMETHODIMP GetToolTip(IShellItemArray *psiItemArray, LPWSTR *ppszInfotip);
	IFACEMETHODIMP GetCanonicalName(GUID *pguidCommandName);
	IFACEMETHODIMP GetState(IShellItemArray *psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE *pCmdState);
	virtual IFACEMETHODIMP Invoke(IShellItemArray *psiItemArray, IBindCtx *pbc);
	IFACEMETHODIMP GetFlags(EXPCMDFLAGS *pFlags);
	IFACEMETHODIMP EnumSubCommands(IEnumExplorerCommand **ppEnum);

	CFolderViewCommand(FVCOMMANDITEM *pfvci) : _cRef(1), _pfvci(pfvci)
	{ }

protected:
	~CFolderViewCommand() { }

	long _cRef;
	const FVCOMMANDITEM *_pfvci;
};

