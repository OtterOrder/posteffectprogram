#include "Utilities.h"

#include "windows.h"

void Warning(bool _test, cStr _str)
{
	if (_test)
		return;

	OutputDebugStr("Warning : ");
	OutputDebugStr(_str);
	OutputDebugStr("\n");
}