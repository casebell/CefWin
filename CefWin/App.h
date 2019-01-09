#pragma once

#include "include/cef_app.h"

// CefApp does all of the work, but it is an abstract base class that needs reference counting implemented;
// thus, we create a dummy class that inherits off of CefApp but does nothing
class App : public CefApp
{
public:
	App() {}
	virtual ~App() {}

private:
	IMPLEMENT_REFCOUNTING(App);
};