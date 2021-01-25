#include "simple_client.h"

#include <windows.h>
#include <string>

#include "include/cef_browser.h"

void SimpleClient::PlatformTitleChange(CefRefPtr<CefBrowser> browser,
    const CefString& title) {
    // 通过GetHost()来获取CEF浏览器对象的宿主对象（这里就是Windows原生窗体）
    // 再获取对应的窗体句柄
    // 通过#include <windows.h>得到的WindowsAPI完成标题修改
    CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
    if (hwnd)
        SetWindowText(hwnd, std::wstring(title).c_str());
}