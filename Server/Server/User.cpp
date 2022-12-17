#include "User.h"

User::User()
{
    this->m_name = std::string();
    this->m_email = std::string();
    this->m_password = std::string();
    this->m_imagePath = std::string();
}

User::User(const std::string& name, const std::string& email, const std::string& password)
{
    this->m_name = name;
    this->m_email = email;
    this->m_password = password;
}

void User::SetName(const std::string& name)
{
    this->m_name = name;
}

void User::SetEmail(const std::string& email)
{
    this->m_email = email;
}

void User::SetPassword(const std::string& password)
{
    this->m_password = password;
}

void User::SetImagePath(const std::string& imagePath)
{
    this->m_imagePath = imagePath;
}

std::string User::GetName() const
{
    return m_name;
}

std::string User::GetEmail() const
{
    return m_email;
}

std::string User::GetPassword() const
{
    return m_password;
}

std::string User::GetImagePath() const
{
    return m_imagePath;
}