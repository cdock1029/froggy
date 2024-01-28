#pragma once
#include "webxx.h"
#include <drogon/drogon.h>

namespace components {

struct Layout : Webxx::component<Layout> {
    explicit Layout(Webxx::node&& mainContent);
};

struct Home : Webxx::component<Home> {
    explicit Home();
};

struct SearchResults : Webxx::component<SearchResults> {
    explicit SearchResults(const std::shared_ptr<Json::Value>& arr);
};

struct Treasuries : Webxx::component<Treasuries> {
    explicit Treasuries();
};

}
