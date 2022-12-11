#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <curl/curl.h>
#include <crow.h>

#include "User.h"
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
				sql::make_column("Difficulty", &Question::SetDifficulty, &Question::GetDifficulty),
				sql::make_column("Text", &Question::SetText, &Question::GetText),
				sql::make_column("Correct answer", &Question::SetCorrectAnswer, &Question::GetCorrectAnswer),
				//sql::make_column("Incorrect answers", &Question::SetIncorrectAnswers, &Question::GetIncorrectAnswers),
				sql::make_column("Incorrect answers", &Question::SetIncorrectAnswers, &Question::GetIncorrectAnswers),
				sql::make_column("Is multiple choice", &Question::SetIsMultipleChoice, &Question::GetIsMultipleChoice),
				sql::make_column("Score", &Question::SetScore, &Question::GetScore)
			)
		);
	}

	using Storage = decltype(CreateStorage(""));

	class LoginUserHandler
	{
	private:
		Storage& database;

	public:
		LoginUserHandler(Storage& storage);

		crow::response operator() (const crow::request& request) const;
	};

	class RegisterUserHandler
	{
	private:
		Storage& database;

	public:
		RegisterUserHandler(Storage& storage);

		crow::response operator() (const crow::request& request) const;
	};
}

