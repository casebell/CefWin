namespace CefWin
{
	using InitializeCefFunc = void __stdcall(HINSTANCE hInstance);
	using ShutdownCefFunc = void __stdcall();

	extern InitializeCefFunc* InitializeCef;
	extern ShutdownCefFunc* ShutdownCef;

	extern void Initialize();
}