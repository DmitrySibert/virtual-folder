#pragma once

#include <list>
#include <vector>

// {052979AD-F172-4318-A828-9A6AC20FC403}
static const GUID IID_IDropHandler = { 0x52979ad, 0xf172, 0x4318, { 0xa8, 0x28, 0x9a, 0x6a, 0xc2, 0xf, 0xc4, 0x3 } };

//Provides dnag and drop handling interface
class IDropHandler
{
public:
	virtual void DoDrop(std::list<TCHAR*> files, LPCITEMIDLIST subfolder) = 0;
};
