#pragma once

#include <drogon/drogon.h>
#include <string>
#include <webxx.h>

namespace htmx
{
	namespace internal
	{
		constexpr char _hxBoostAttr[] = "hx-boost";
		constexpr char _hxOnAfterRequest[] = "hx-on::after-request";
	}
	inline std::shared_ptr<drogon::HttpResponse> redirect(std::string&& path)
	{
		auto resp = drogon::HttpResponse::newHttpResponse();
		auto headers = resp->headers();
		headers["HX-Redirect"] = path;
		return resp;
	}
	inline Webxx::internal::HtmlAttribute _hxBoost(bool status = true)
	{
		return Webxx::attr<internal::_hxBoostAttr>{ status ? "true" : "false" };
	}
	inline Webxx::internal::HtmlAttribute _hxResetAfterSuccess()
	{
		return Webxx::attr<internal::_hxOnAfterRequest>{ "if(event.detail.successful) this.reset()" };
	}
}

namespace Webxx
{
	// @formatter:off
	WEBXX_HTML_ATTR_ALIAS(hx-swap, hxSwap);
	WEBXX_HTML_ATTR_ALIAS(hx-post, hxPost);
	WEBXX_HTML_ATTR_ALIAS(hx-target, hxTarget);
	// @formatter:on
}