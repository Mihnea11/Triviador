#include <vector>
#include <string>

#include "User.h"

namespace sql = sqlite_orm;

int main()
{
    const std::string usersDbFile = "Users.sqlite";
    UsersStorage usersDb = CreateStorage(usersDbFile);

    usersDb.sync_schema();

    crow::SimpleApp app;

    CROW_ROUTE(app, "/Users")(
    [&usersDb]()
    {
        std::vector<crow::json::wvalue> usersJson;
        for (const auto& user : usersDb.iterate<User>())
        {
            usersJson.push_back(crow::json::wvalue
            {
                {"Id", user.GetName()},
                {"Email", user.GetEmail()},
                {"Password", user.GetPassword()}
            });
        }

        return crow::json::wvalue{ usersJson };
    });

    auto& addUser = CROW_ROUTE(app, "/Users").methods(crow::HTTPMethod::PUT);
    addUser(UserDatabaseControl(usersDb));

    app.port(18080).multithreaded().run();

    return 0;
}