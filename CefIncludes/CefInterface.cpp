#include <Windows.h>
#include "CefInterface.h"

namespace CefWin
{
	InitializeCefFunc* InitializeCef{ nullptr };
	ShutdownCefFunc* ShutdownCef{ nullptr };
	HMODULE cefDll{ nullptr };

	void Initialize()
	{
		cefDll = LoadLibrary("CefWin.dll");
		InitializeCef = reinterpret_cast<InitializeCefFunc*>(GetProcAddress(cefDll, "InitializeCef"));
		ShutdownCef = reinterpret_cast<ShutdownCefFunc*>(GetProcAddress(cefDll, "ShutdownCef"));
	}
}
