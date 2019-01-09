#include <Windows.h>
#include <string>
#include <array>

#include "include/cef_app.h"
#include "app.h"
using namespace std;

CefRefPtr<App> app(new App);
void* sandbox_info{ nullptr };

void InitializeCef(HINSTANCE hInstance)
{
	CefMainArgs main_args(hInstance);

	CefEnableHighDPISupport();


#if defined(CEF_USE_SANDBOX)
	// Manage the life span of the sandbox information object. This is necessary
	// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif

	// CefExecuteProcess returns -1 for the host process
	if (CefExecuteProcess(main_args, app.get(), sandbox_info) == -1)
	{
		array<char, MAX_PATH> buffer;
		GetModuleFileNameA(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
		string subprocess(buffer.data());
		auto pos = subprocess.find_last_of('\\');
		subprocess = subprocess.substr(0, pos+1);
		subprocess += "sub.exe";

		CefSettings settings;
		CefString(&settings.browser_subprocess_path) = subprocess;
		settings.multi_threaded_message_loop = true;
		CefInitialize(main_args, settings, app.get(), sandbox_info);
	}
}

void ShutdownCef()
{
	CefShutdown();
}