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