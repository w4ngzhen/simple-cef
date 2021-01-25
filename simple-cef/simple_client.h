#ifndef SIMPLE_CLIENT_H
#define SIMPLE_CLIENT_H

#include "include/cef_client.h"

#include <list>

class SimpleClient : public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler
{
public:
	explicit SimpleClient(bool use_views);
	~SimpleClient();

	static SimpleClient* GetInstance();

	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE
	{
		return this;
	}

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE
	{
		return this;
	}

	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }

	// CefDisplayHandler的实现声明:
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) OVERRIDE;
	// CefLifeSpanHandler的实现声明:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	// CefLoadHandler的实现声明:
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) OVERRIDE;

	void CloseAllBrowsers(bool force_close); // 请求将所有的已经存在的浏览器窗体进行关闭
	bool IsClosing() const { return is_closing_; }

private:
	// 平台特定的标题修改
	// 当我们没有CEF的GUI视图框架的时候，就需要特定平台的标题修改实现
	// 例如，Windows中需要我们获取窗体句柄，调用Windows的API完成对该窗体的标题修改
	void PlatformTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title);
	const bool use_views_; // 是否使用了CEF的GUI视图框架
	// List of existing browser windows. Only accessed on the CEF UI thread.
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList browser_list_;

	bool is_closing_;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SimpleClient);
};

#endif