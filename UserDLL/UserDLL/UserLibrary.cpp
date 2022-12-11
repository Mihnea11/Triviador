#include "pch.h"
#include "UserLibrary.h"

UserLibrary::UserLibrary()
{
    this->name = std::string();
    this->email = std::string();
    this->password = std::string();
    this->imagePath = std::string();
}

UserLibrary::UserLibrary(const std::string& name, const std::string& email, const std::string& password)
{
    this->name = name;
    this->email = email;
    this->password = password;
}

void UserLibrary::SetName(const std::string& name)
{
    this->name = name;
}

void UserLibrary::SetEmail(const std::string& email)
{
    this->email = email;
}

void UserLibrary::SetPassword(const std::string& password)
{
    this->password = password;
}

void UserLibrary::SetImagePath(const std::string& imagePath)
{
    this->imagePath = imagePath;
}

std::string UserLibrary::GetName() const
{
    return name;
}

std::string UserLibrary::GetEmail() const
{
    return email;
}

std::string UserLibrary::GetPassword() const
{
    return password;
}

std::string UserLibrary::GetImagePath() const
{
    return imagePath;
}