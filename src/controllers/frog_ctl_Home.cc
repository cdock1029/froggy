#include "frog_ctl_Home.h"
#include "components/components.h"
#include "utils.h"
#include "webxx.h"
#include <QString>
#include <QDebug>

namespace frog::ctl
{
	void Home::get([[maybe_unused]] const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
	{
		auto resp = HttpResponse::newHttpResponse();
		resp->setBody(Webxx::render(components::Layout{ components::Home{}}));
		callback(resp);
	}
	void Home::search(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
	{
		auto cusip = req->getParameter("cusip");
		{
			auto cusipCheck = QString{ cusip.data() };
			if (cusipCheck.trimmed().isEmpty())
			{
				callback(HttpResponse::newHttpResponse(k200OK, CT_TEXT_PLAIN));
				return;
			}
		}

		auto client = getHttpClient();
		auto r = HttpRequest::newHttpRequest();
		r->setMethod(Get);
		r->setPath("/TA_WS/securities/search");
		r->setParameter("cusip", cusip);
		r->setParameter("format", "json");
		client->sendRequest(r, [callback](ReqResult result, const HttpResponsePtr& response)
		{
			if (result != ReqResult::Ok)
			{
				LOG_DEBUG << "error sending request: " << result;
				callback(HttpResponse::newHttpResponse(k500InternalServerError, CT_TEXT_PLAIN));
				return;
			}
			if (!response->getJsonError().empty())
			{
				LOG_DEBUG << "json error not empty: " << response->getJsonError();
				callback(HttpResponse::newHttpResponse(k400BadRequest, CT_TEXT_PLAIN));
				return;
			}
			const auto arr = response->getJsonObject();
			if (!arr->isArray())
			{
				if (arr->isObject())
				{
					LOG_DEBUG << "TD api error: " << arr->get("error", "").asCString();
				}
				callback(HttpResponse::newHttpResponse(k400BadRequest, CT_TEXT_PLAIN));
				return;
			}
			auto resp = HttpResponse::newHttpResponse();
			LOG_DEBUG << "arr: " << arr->toStyledString();
			resp->setBody(Webxx::render(components::SearchResults(arr)));
			callback(resp);
		});
	}
}
