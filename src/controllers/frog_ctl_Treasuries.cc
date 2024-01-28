#include "frog_ctl_Treasuries.h"
#include "components/components.h"
#include "webxx.h"

using namespace frog::ctl;

void Treasuries::get(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
	LOG_DEBUG << "Treasuries ctrl";
	auto resp = HttpResponse::newHttpResponse();
	resp->setBody(Webxx::render(components::Layout{ components::Treasuries{}}));
	callback(resp);
}
