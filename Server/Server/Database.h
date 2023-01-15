#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <curl/curl.h>
#include <cpr/cpr.h>
#include <crow.h>

#include "User.h"
#include "Room.h"
#include "Game.h"
#include "GameLog.h"
#include "Question.h"
#include "Utilities.h"

namespace sql = sqlite_orm;

namespace Database
{
	inline auto CreateStorage(const std::string& fileName)
	{
		return sql::make_storage(
			fileName,
			sql::make_table(
				"User",
				sql::make_column("Id", &User::SetName, &User::GetName, sql::primary_key()),
				sql::make_column("Email", &User::SetEmail, &User::GetEmail),
				sql::make_column("Password", &User::SetPassword, &User::GetPassword),
				sql::make_column("Image path", &User::SetImagePath, &User::GetImagePath)
			),
			sql::make_table(
				"Questions",
				sql::make_column("Id", &Question::SetId, &Question::GetId, sql::autoincrement(), sql::primary_key()),
				sql::make_column("Is numerical", &Question::SetIsNumerical, &Question::GetIsNumerical),
				sql::make_column("Text", &Question::SetText, &Question::GetText),
				sql::make_column("Answer", &Question::SetAnswer, &Question::GetAnswer),
				sql::make_column("Incorrect answers", &Question::SetIncorrectAnswers, &Question::GetIncorrectAnswers)
			),
			sql::make_table(
				"GameHistory",
				sql::make_column("Id", &GameLog::SetId, &GameLog::GetId, sql::autoincrement(), sql::primary_key()),
				sql::make_column("Player1", &GameLog::SetPlayerOne, &GameLog::GetPlayerOne),
				sql::make_column("Player2", &GameLog::SetPlayerTwo, &GameLog::GetPlayerTwo),
				sql::make_column("Player3", &GameLog::SetPlayerThree, &GameLog::GetPlayerThree),
				sql::make_column("Player4", &GameLog::SetPlayerFour, &GameLog::GetPlayerFour),
				sql::make_column("Game result", &GameLog::SetGameResult, &GameLog::GetGameResult),
				sql::make_column("Game date", &GameLog::SetGameDate, &GameLog::GetGameDate)
			)
		);
	}

	using Storage = decltype(CreateStorage(""));

	std::vector<Question> SeparateQuestions(const crow::json::rvalue& questionsJson);
	void AddQuestions(Storage& database);

	class LoginUserHandler
	{
	public:
		LoginUserHandler(Storage& storage);

		crow::response operator() (const crow::request& request) const;

	private:
		Storage& database;
	};

	class RegisterUserHandler
	{
	public:
		RegisterUserHandler(Storage& storage);

		crow::response operator() (const crow::request& request) const;

	private:
		Storage& database;
	};

	class UserHandler
	{
	public:
		UserHandler(Storage& storage);

		crow::response operator() (const crow::request& request, const std::string& userId) const;

	private:
		Storage& database;
	};

	class RoomHandler
	{
	public:
		RoomHandler(std::vector<Room>& rooms);

		crow::response operator() (const crow::request& request, const std::string& roomCode) const;

	private:
		std::vector<Room>& m_rooms;
	};

	class LeaveRoomHandler
	{
	public:
		LeaveRoomHandler(std::vector<Room>& rooms);

		crow::response operator() (const crow::request& request, const std::string& roomCode) const;

	private:
		std::vector<Room>& m_rooms;
	};

	class GameHandler
	{
	public: 
		GameHandler(std::vector<Game>& games);

		crow::response operator() (const crow::request& request, const std::string& gameCode) const;

	private:
		std::vector<Game>& m_games;
	};
}