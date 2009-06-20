#include "Utilities.h"

#include "windows.h"

bool Warning(bool _test, cStr _str)
{
	if (_test)
		return false;

	OutputDebugStr("Warning : ");
	OutputDebugStr(_str);
	OutputDebugStr("\n");

	return true;
}