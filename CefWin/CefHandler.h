#pragma once
#include "include/cef_client.h"

class CefHandler : public CefClient,
	public CefContextMenuHandler,
	public CefDisplayHandler,
	public CefDownloadHandler,
	public CefDragHandler,
	public CefKeyboardHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler,
	public CefRequestHandler
{
public:
	CefHandler();
	virtual ~CefHandler();
	CefRefPtr<CefBrowser> GetBrowser();

#pragma region CefClient

	// since we are letting the base implementations handle all of the heavy lifting,
	// these functions just return the this pointer
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler() override;
	virtual CefRefPtr<CefDragHandler> GetDragHandler() override;
	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override;
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() override;

#pragma endregion 

#pragma region CefDownloadHandler

	// this function is virtual and must be implemented; we do nothing in it, so downloading files won't work as the callback function isn't invoked
	virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback) override;

#pragma endregion 

#pragma region CefLifeSpanHandler

	// cache a reference to the browser
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	// release the browser reference
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

#pragma endregion // CefLifeSpanHandler  

protected:
	// the browser reference
	CefRefPtr<CefBrowser> browser;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(CefHandler);
	// Include the default locking implementation.
//	IMPLEMENT_LOCKING(CefHandler);
};