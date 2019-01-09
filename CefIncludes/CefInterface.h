namespace CefWin
{
	using InitializeCefFunc = void __stdcall(HINSTANCE hInstance);
	using ShutdownCefFunc = void __stdcall();
	using CreateBrowserWindowFunc = HWND __stdcall(HWND parent);

	extern InitializeCefFunc* InitializeCef;
	extern ShutdownCefFunc* ShutdownCef;
	extern CreateBrowserWindowFunc* CreateBrowserWindow;

	extern void Initialize();
}