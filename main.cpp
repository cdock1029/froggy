#include <drogon/drogon.h>

int main()
{
    using namespace drogon;

    app()
        .setLogLevel(trantor::Logger::kTrace)
        .addListener("127.0.0.1", 3000)
        .createDbClient("sqlite3", "", 0, "", "", "", 1, "frog.db")
        .setThreadNum(20)
        .run();
}
