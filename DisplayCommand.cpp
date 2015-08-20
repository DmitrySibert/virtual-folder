#include "DisplayCommand.h"


DisplayCommand::DisplayCommand(FVCOMMANDITEM *pfvci) : CFolderViewCommand(pfvci)
{
}

IFACEMETHODIMP DisplayCommand::Invoke(IShellItemArray *psiItemArray, IBindCtx *pbc)
{
	return DisplayItem(psiItemArray, NULL);
}

DisplayCommand::~DisplayCommand()
{
}
