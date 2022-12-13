#include "Database.h"

//------------------------------------- LOGIN -------------------------------------
																					
Database::LoginUserHandler::LoginUserHandler(Storage& storage) : database{storage}	
{																					
}																					
																					
crow::response Database::LoginUserHandler::operator()(const crow::request& request)	const
{																					
	auto arguments = ParseUrlArgs(request.body);
	auto username = arguments.find("Username")->second;
	auto password = arguments.find("Password")->second;

	username = curl_unescape(username.c_str(), username.length());
	password = curl_unescape(password.c_str(), password.length());

	for (const auto& user : database.iterate<User>())
	{
		if (username == user.GetName() && password == user.GetPassword())
		{
			return crow::response(200);
		}

		if (username == user.GetName() && password != user.GetPassword())
		{
			return crow::response(409, "Invalid password");
		}
	}

	return crow::response(409, "Username not found");
}																					
																					
																					
//------------------------------------ REGISTER ------------------------------------


Database::RegisterUserHandler::RegisterUserHandler(Storage& storage) : database{storage}
{
}

crow::response Database::RegisterUserHandler::operator()(const crow::request& request) const
{
	auto arguments = ParseUrlArgs(request.body);
	auto username = arguments.find("Username")->second;

	username = curl_unescape(username.c_str(), username.length());

	for (const auto& user : database.iterate<User>())
	{
		if (username == user.GetName())
		{
			return crow::response(409, "Username already used");
		}
	}

	auto email = arguments.find("Email")->second;
	auto password = arguments.find("Password")->second;
	auto imagePath = arguments.find("Image path")->second;

	email = curl_unescape(email.c_str(), email.length());
	password = curl_unescape(password.c_str(), password.length());
	imagePath = curl_unescape(imagePath.c_str(), imagePath.length());

	User user;
	user.SetName(username);
	user.SetEmail(email);
	user.SetPassword(password);
	user.SetImagePath(imagePath);

	database.replace(user);

	return crow::response(200);
}

//-------------------------------------- USER --------------------------------------

Database::UserHandler::UserHandler(Storage& storage) : database{storage}
{
}

crow::response Database::UserHandler::operator()(const crow::request& request, const std::string& userId) const
{
	auto arguments = ParseUrlArgs(request.body);
	auto end = arguments.end();

	auto email = arguments.find("Email");
	auto password = arguments.find("Password");
	auto imagePath = arguments.find("Image path");

	User user = database.get<User>(userId);

	if (email != end)
	{
		user.SetEmail(curl_unescape(email->second.c_str(), email->second.length()));
	}
	if (password != end)
	{
		user.SetPassword(curl_unescape(password->second.c_str(), password->second.length()));
	}
	if (imagePath != end)
	{
		user.SetImagePath(curl_unescape(imagePath->second.c_str(), imagePath->second.length()));

	}

	database.update(user);

	return crow::response(200);
}
