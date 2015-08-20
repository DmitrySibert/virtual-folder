#include "NewFolderCommand.h"


NewFolderCommand::NewFolderCommand(FVCOMMANDITEM *pfvci, CFolderViewImplFolder *pFolderView) : CFolderViewCommand(pfvci), m_pFolderView(pFolderView)
{
}

IFACEMETHODIMP NewFolderCommand::Invoke(IShellItemArray *psiItemArray, IBindCtx *pbc)
{
	DataProvider dataProvider;
	dataProvider.logInfo("Create new folder");
	m_pFolderView->_OnCreateFolder();
	return S_OK;
}

NewFolderCommand::~NewFolderCommand()
{
}
