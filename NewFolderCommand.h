#pragma once
#include "fvcommands.h"
#include "CFolderViewImplFolder.h"
#include "DataProvider.h"

class NewFolderCommand :
	public CFolderViewCommand
{
	CFolderViewImplFolder *m_pFolderView;
public:
	NewFolderCommand(FVCOMMANDITEM *pfvci, CFolderViewImplFolder *pFolderView);
	IFACEMETHODIMP Invoke(IShellItemArray *psiItemArray, IBindCtx *pbc);
	~NewFolderCommand();
};

