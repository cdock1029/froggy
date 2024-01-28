#pragma once
#include <drogon/HttpClient.h>

namespace frog::ctl
{
	using namespace drogon;
	extern HttpClientPtr getHttpClient();
}