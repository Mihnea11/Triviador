#include <vector>
#include <string>

#include "Database.h"
#include "Room.h"
#include "Utilities.h"

namespace sql = sqlite_orm;

int main()
{
    std::vector<Room> rooms;
    const std::string databaseFile = "Database.sqlite";
    Database::Storage database = Database::CreateStorage(databaseFile);
    database.sync_schema();
    Database::AddQuestions(database);

    std::vector<Question> numericalQuestions = database.get_all<Question>(sql::where(sql::is_equal(&Question::GetIsNumerical, true)));
    std::vector<Question> multipleChoiceQuestions = database.get_all<Question>(sql::where(sql::is_equal(&Question::GetIsNumerical, false)));

    crow::SimpleApp app;

    //User login route
    auto& loginUser = CROW_ROUTE(app, "/LoginUser").methods(crow::HTTPMethod::Put);
    loginUser(Database::LoginUserHandler(database));

    //User register route
    auto& registerUser = CROW_ROUTE(app, "/RegisterUser").methods(crow::HTTPMethod::Put);
    registerUser(Database::RegisterUserHandler(database));

    //User information
    CROW_ROUTE(app, "/User_<string>")([&database](std::string userId)
    {
        User user = database.get<User>(userId);

        crow::json::wvalue userData(
        {
            {"Username", user.GetName()},
            {"Email", user.GetEmail()},
            {"Password", user.GetPassword()},
            {"Image path", user.GetImagePath()}
        });

        return userData;
    });
    auto& updateUser = CROW_ROUTE(app, "/User_<string>").methods(crow::HTTPMethod::Post);
    updateUser(Database::UserHandler(database));
    
    CROW_ROUTE(app, "/Create_Room")([&database,&rooms]()
    {
        crow::json::wvalue roomCode(
            { "Room code", CreateRoomCode(rooms.size())});
        
        rooms.emplace_back(Room());

        return roomCode;
    });


    app.port(18080).multithreaded().run();

    return 0;
}