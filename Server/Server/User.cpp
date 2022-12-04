#include "User.h"

User::User()
{
    this->name = std::string();
    this->email = std::string();
    this->password = std::string();
}

User::User(const std::string& name, const std::string& email, const std::string& password)
{
    this->name = name;
    this->email = email;
    this->password = password;
}

void User::SetName(const std::string& name)
{
    this->name = name;
}

void User::SetEmail(const std::string& email)
{
    this->email = email;
}

void User::SetPassword(const std::string& password)
{
    this->password = password;
}

std::string User::GetName() const
{
    return name;
}

std::string User::GetEmail() const
{
    return email;
}

std::string User::GetPassword() const
{
    return password;
}

UserDatabaseControl::UserDatabaseControl(UsersStorage& storage) : database{storage}
{
}

crow::response UserDatabaseControl::operator()(const crow::request& request) const
{
    auto bodyArgs = ParseUrlArgs(request.body);
    auto end = bodyArgs.end();
    auto userId = bodyArgs.find("Id");
    auto userEmail = bodyArgs.find("Email");
    auto userPassword = bodyArgs.find("Password");

    if (userId != end && userEmail != end && userPassword != end)
    {
        User user;

        user.SetName(userId->second);
        user.SetEmail(userEmail->second);
        user.SetPassword(userPassword->second);

        database.replace(user);
    }

    return crow::response(201);
}