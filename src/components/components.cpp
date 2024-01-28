#include "components.h"
#include "htmx.h"

namespace components
{
	constexpr auto PICO_URL = "https://cdn.jsdelivr.net/npm/@picocss/pico@1/css/pico.min.css";

	constexpr auto HTMX_URL = "https://unpkg.com/htmx.org@1.9.10";

	constexpr auto HTMX_INTEGRITY = "sha384-D1Kt99CQMDuVetoL1lrYwg5t+9QdHe7NLX/SoJYkXDFfX37iInKRy5xLSi8nO7UC";

	constexpr auto SHORTCUT_ICON = "https://www.svgrepo.com/show/46184/frog.svg";

	using namespace Webxx;
	using namespace htmx;

	Layout::Layout(node&& mainContent)
		: component<Layout>{
		doc{
			html{
				head{
					title{ "Frog" },
					Webxx::link{{ _rel{ "stylesheet" }, _href{ PICO_URL }}},
					Webxx::script{
						{ _src{ HTMX_URL }, _integrity{ HTMX_INTEGRITY }, _crossorigin{ "anonymous" }},
					},
					Webxx::link{{ _rel{ "shortcut icon" }, _href{ SHORTCUT_ICON }}},
					styleTarget{},
					headTarget{},
				},
				body{
					main{
						{ _class{{ "container" }}},
						nav{
							{ _hxBoost() },
							a{{ _href{ "/" }}, "Home" },
							a{{ _href{ "/treasuries" }}, "Treasuries" },
						},
						hr{},
						dv{
							{ _id{ "content" }},
							std::move(mainContent),
						}
					},
				}}}
	}
	{
	}

	Home::Home()
		: component<Home>{
		fragment{
			h1{ "Home" },
			form{
				{
					_hxPost{ "/search" },
					_hxTarget{ "#result" },
					_hxSwap{ "innerHTML" },
					_hxResetAfterSuccess(),
				},
				input{
					{ _type{ "search" }, _name{ "cusip" }, _placeholder{ "CUSIP" }},
				},
			},
			p{
				{ _id{ "result" }},
			},
		},
	}
	{
	}

	Treasuries::Treasuries()
		: component<Treasuries>{
		fragment{
			h1{ "Treasuries Page" },
			button{
				"Click"
			}
		}
	}
	{
	}

	SearchResults::SearchResults(const std::shared_ptr<Json::Value>& arr)
		: component<SearchResults>{
		table{
			thead{
				th{ "CUSIP" },
				th{ "Issue Date" },
				th{ "Maturity Date" },
				th{}
			},
			tbody{
				loop(*arr, [](const Json::Value& v, const Loop& loop)
				{
					return tr{
						td{ v["cusip"].asCString() },
						td{ v["issueDate"].asCString() },
						td{ v["maturityDate"].asCString() },
						td{
							button{
								{ _style{ "margin-bottom:0;" }},
								"Save"
							}
						}
					};
				}) }},
	}
	{
	}
}
