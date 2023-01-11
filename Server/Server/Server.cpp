#include <vector>
#include <string>

#include "Game.h"
#include "Room.h"
#include "Database.h"
#include "Utilities.h"

namespace sql = sqlite_orm;

int main()
{
    srand(time(NULL));

    std::vector<Room> rooms;
    std::vector<Game> games;

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
        auto maxUsers = arguments.find("Player count")->second;

        username = curl_unescape(username.c_str(), username.length());
        imagePath = curl_unescape(imagePath.c_str(), imagePath.length());
        maxUsers = curl_unescape(maxUsers.c_str(), maxUsers.length());

        User owner;
        owner.SetName(username);
        owner.SetImagePath(imagePath);

        std::string roomCode = "";
        while (std::find(rooms.begin(), rooms.end(), roomCode) != rooms.end() || roomCode == "")
        {
            roomCode = CreateRoomCode();

            if (rooms.size() == 0)
            {
                break;
            }
        }

        Room room(owner);
        room.SetMaxUsers(std::stoi(maxUsers));
        room.SetRoomCode(roomCode);

        rooms.push_back(room);

        return crow::json::wvalue{ { "Room code", roomCode } };
    });

    //LeaveRoom
    auto& leaveRoom = CROW_ROUTE(app, "/LeaveRoom_<string>").methods(crow::HTTPMethod::Put);
    leaveRoom(Database::LeaveRoomHandler(rooms));

    //Room access
    CROW_ROUTE(app, "/Room_<string>")([&rooms](std::string roomCode)
    {
        auto foundRoom = std::find(rooms.begin(), rooms.end(), roomCode);

        if (foundRoom == rooms.end())
        {
            return crow::json::wvalue{ {""} };
        }
        
        auto users = foundRoom->GetUsers();

        std::vector<crow::json::wvalue> roomInformations;

        roomInformations.push_back(crow::json::wvalue{ {"Game start", std::to_string(foundRoom->GetStartGame())} });
        roomInformations.push_back(crow::json::wvalue{ {"Owner", foundRoom->GetOwner().GetName()} });
        roomInformations.push_back(crow::json::wvalue{ {"Player count", foundRoom->GetMaxUsers()} });
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
    auto& updateInformaton = CROW_ROUTE(app, "/Room_<string>").methods(crow::HTTPMethod::Post);
    updateInformaton(Database::RoomHandler(rooms));

    //Game creation
    CROW_ROUTE(app, "/Game_<string>")([&rooms, &games](std::string gameCode)
    {
        auto room = std::find(rooms.begin(), rooms.end(), gameCode);

        Game newGame;
        newGame.SetPlayerCount(room->GetMaxUsers());
        newGame.SetGameState(Game::JOINING);

        games.push_back(newGame);

        return crow::json::wvalue{ {"Player count", newGame.GetPlayerCount()} };
    });

    //Join game

    app.port(18080).multithreaded().run();
    return 0;
}