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