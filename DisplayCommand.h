#pragma once
#include "CFolderViewCommand.h"
class DisplayCommand :
	public CFolderViewCommand
{
public:
	DisplayCommand(FVCOMMANDITEM *pfvci);
	IFACEMETHODIMP Invoke(IShellItemArray *psiItemArray, IBindCtx *pbc);
	~DisplayCommand();
};

