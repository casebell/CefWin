#include "CefHandler.h"
#include "include/wrapper/cef_helpers.h"

CefHandler::CefHandler() { }

CefHandler::~CefHandler() {
}

CefRefPtr<CefBrowser> CefHandler::GetBrowser() {
	return cefBrowser;
}

CefRefPtr<CefContextMenuHandler> CefHandler::GetContextMenuHandler() {
	return this;
}

CefRefPtr<CefDisplayHandler> CefHandler::GetDisplayHandler() {
	return this;
}

CefRefPtr<CefDownloadHandler> CefHandler::GetDownloadHandler() {
	return this;
}

CefRefPtr<CefDragHandler> CefHandler::GetDragHandler() {
	return this;
}

CefRefPtr<CefKeyboardHandler> CefHandler::GetKeyboardHandler() {
	return this;
}

CefRefPtr<CefLifeSpanHandler> CefHandler::GetLifeSpanHandler() {
	return this;
}

CefRefPtr<CefLoadHandler> CefHandler::GetLoadHandler() {
	return this;
}

CefRefPtr<CefRequestHandler> CefHandler::GetRequestHandler() {
	return this;
}

void CefHandler::OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item,
	const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback) {
	UNREFERENCED_PARAMETER(browser);
	UNREFERENCED_PARAMETER(download_item);
	callback->Continue(suggested_name, true);
}

void CefHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	//	AutoLock lock_scope(this);

	this->cefBrowser = browser;
	CefLifeSpanHandler::OnAfterCreated(browser);
}

void CefHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	//	AutoLock lock_scope(this);
	browser = NULL;
	CefLifeSpanHandler::OnBeforeClose(browser);
}
