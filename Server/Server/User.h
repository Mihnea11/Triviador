#pragma once

#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

#include "Utilities.h"

namespace sql = sqlite_orm;


class User
{
private:
	std::string name;
	std::string email;
	std::string password;
	std::string imagePath;

public:
	User();
	User(const std::string& name, const std::string& email, const std::string& password);

	void SetName(const std::string& name);
	void SetEmail(const std::string& email);
	void SetPassword(const std::string& password);
	void SetImagePath(const std::string& imagePath);

	std::string GetName() const;
	std::string GetEmail() const;
	std::string GetPassword() const;
	std::string GetImagePath() const;
};

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
		)
	);
}

using UsersStorage = decltype(CreateStorage(""));
class UserDatabaseControl
{
private:
	UsersStorage& database;

public:
	UserDatabaseControl(UsersStorage& storage);

	crow::response operator() (const crow::request& request) const;
};