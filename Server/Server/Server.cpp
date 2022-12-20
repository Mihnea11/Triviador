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

    //Room creation
    CROW_ROUTE(app, "/CreateRoom").methods(crow::HTTPMethod::Put)([&rooms](const crow::request& request)
    {
        auto arguments = ParseUrlArgs(request.body);

        auto username = arguments.find("User name")->second;
        auto imagePath = arguments.find("Image path")->second;

        username = curl_unescape(username.c_str(), username.length());
        imagePath = curl_unescape(imagePath.c_str(), imagePath.length());

        User owner;
        owner.SetName(username);
        owner.SetImagePath(imagePath);

        std::string roomCode = CreateRoomCode(rooms.size());

        rooms.emplace_back(Room(owner));

        return crow::json::wvalue{ { "Room code", roomCode } };
    });

    //Room deletion
    auto& deleteRoom = CROW_ROUTE(app, "/DeleteRoom_<string>").methods(crow::HTTPMethod::Put);
    deleteRoom(Database::DeleteRoomHandler(rooms));  

    //Room access
    CROW_ROUTE(app, "/Room_<string>")([&rooms](std::string roomCode)
    {
        int roomIndex = std::stoi(roomCode);
        auto users = rooms[roomIndex].GetUsers();

        std::vector<crow::json::wvalue> roomInformations;

        roomInformations.push_back(crow::json::wvalue{ {"Owner", rooms[roomIndex].GetOwner().GetName()} });
        for (const auto& user : users)
        {
            roomInformations.push_back(crow::json::wvalue
            {
                {"User name", user.GetName()},
                {"Image path", user.GetImagePath()}
            });
        }

        return crow::json::wvalue(roomInformations);
    });
    auto& addUser = CROW_ROUTE(app, "/Room_<string>").methods(crow::HTTPMethod::Put);
    addUser(Database::RoomHandler(rooms));

    app.port(18080).multithreaded().run();

    return 0;
}