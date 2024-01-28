#include "utils.h"

namespace frog::ctl
{
	constexpr auto TD = "https://www.treasurydirect.gov";

	HttpClientPtr getHttpClient()
	{
		static auto client = HttpClient::newHttpClient(TD);
		return client;
	}
}
