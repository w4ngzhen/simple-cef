#ifndef SIMPLE_APP_H
#define SIMPLE_APP_H
#pragma once

#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
    SimpleApp();

    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
        OVERRIDE {
        return this;
    }

    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;

private:
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif