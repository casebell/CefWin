#include <Windows.h>
#include <string>
#include <array>

#include "include/cef_app.h"
#include "app.h"
#include "CefHandler.h"
using namespace std;

CefRefPtr<App> app;
CefRefPtr<CefHandler> cef_handler;
void* sandbox_info{ nullptr };
HINSTANCE instance{ nullptr };
const wstring BROWSER_WINDOW_CLASS(L"CefWin");


LRESULT CALLBACK BrowserWindowWndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	LRESULT result{ 0 };
	switch (message)
	{
		case WM_CREATE:
		{
			cef_handler = new CefHandler; 
			RECT rect = { 0 };
			GetClientRect(hWnd, &rect);

			CefWindowInfo info;
			info.SetAsChild(hWnd, rect);

			CefBrowserSettings settings;
			CefBrowserHost::CreateBrowser(info, cef_handler.get(), CefString("http://www.google.com"), settings, nullptr);
			//CefBrowserHost::CreateBrowser(info, example_cef_handler.get(), CefString("client://tests/handler.html"), settings, NULL);
		}
		break;

		case WM_SIZE:
		{
			// from the cefclient example, do not allow the window to be resized to 0x0 or the layout will break;
			// also be aware that if the size gets too small, GPU acceleration disables
			if ((wparam != SIZE_MINIMIZED) && (cef_handler.get()) && (cef_handler->GetBrowser()))
			{
				CefWindowHandle cefWindow(cef_handler->GetBrowser()->GetHost()->GetWindowHandle());
				if (cefWindow)
				{
					RECT rect = { 0 };
					GetClientRect(hWnd, &rect);
					HDWP hdwp = BeginDeferWindowPos(1);
					hdwp = DeferWindowPos(hdwp, cefWindow, nullptr, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
					EndDeferWindowPos(hdwp);
				}
			}
		}
		break;

		case WM_ERASEBKGND:
		{
			if ((cef_handler.get()) && (cef_handler->GetBrowser()))
			{
				CefWindowHandle cefWindow(cef_handler->GetBrowser()->GetHost()->GetWindowHandle());
				// from the cefclient example, don't erase the background 
				// if the browser window has been loaded to avoid flashing
				result = cefWindow ? 1 : DefWindowProc(hWnd, message, wparam, lparam);
			}
		}
		break;

		case WM_ENTERMENULOOP:
		{
			if (!wparam)
				CefSetOSModalLoop(true);
			result = DefWindowProc(hWnd, message, wparam, lparam);
		}
		break;

		case WM_EXITMENULOOP:
		{
			if (!wparam)
				CefSetOSModalLoop(false);
			result = DefWindowProc(hWnd, message, wparam, lparam);
		}
		break;

		case WM_DESTROY:
		{
			cef_handler->GetBrowser()->GetHost()->CloseBrowser(false);
			//cef_handler->OnBeforeClose(brauser);
			cef_handler->DoClose(cef_handler->GetBrowser());
			break;
		}

		default:
		{
			result = DefWindowProc(hWnd, message, wparam, lparam);
		}
		break;
	}
	return result;
}

void RegisterBrowser()
{
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BrowserWindowWndProc;
	wcex.hInstance = instance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = WHITE_BRUSH;
	wcex.lpszClassName = BROWSER_WINDOW_CLASS.c_str();
	RegisterClassEx(&wcex);
}

void InitializeCef(HINSTANCE hInstance)
{
	instance = hInstance;
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
#if !defined(CEF_USE_SANDBOX)
		settings.no_sandbox = true;
#endif
		CefString(&settings.browser_subprocess_path) = subprocess;
		settings.multi_threaded_message_loop = true;
		CefInitialize(main_args, settings, app.get(), sandbox_info);

		RegisterBrowser();
	}
}

void ShutdownCef()
{
//	cef_handler->GetBrowser()->Release();
	//cef_handler->Release();
	//delete app;
	//delete cef_handler;

	CefShutdown();
}

HWND brause;
HWND __stdcall CreateBrowserWindow(HWND parent)
{
	HWND hwnd{ CreateWindow(BROWSER_WINDOW_CLASS.c_str(), BROWSER_WINDOW_CLASS.c_str(),
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0, parent, nullptr, instance, nullptr) };
	UpdateWindow(hwnd);
	brause = hwnd;
	return hwnd;
}