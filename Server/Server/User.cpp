#include "User.h"

User::User()
{
    this->name = std::string();
    this->email = std::string();
    this->password = std::string();
    this->imagePath = std::string();
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

void User::SetImagePath(const std::string& imagePath)
{
    this->imagePath = imagePath;
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

std::string User::GetImagePath() const
{
    return imagePath;
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
    auto userImagePath = bodyArgs.find("Image path");
    
    auto users = database.get_all<User>();
    for (const auto& user : users)
    {
        if (user.GetName() == userId->second)
        {
            User updatedUser;

            updatedUser.SetName(userId->second);
            updatedUser.SetEmail(userEmail->second);
            updatedUser.SetPassword(userPassword->second);
            updatedUser.SetImagePath(userImagePath->second);

            database.update(updatedUser);

            return crow::response(201);
        }
    }


    if (userId != end && userEmail != end && userPassword != end && userImagePath != end)
    {
        User user;

        user.SetName(userId->second);
        user.SetEmail(userEmail->second);
        user.SetPassword(userPassword->second);
        user.SetImagePath(userImagePath->second);

        database.replace(user);
    }

    return crow::response(201);
}