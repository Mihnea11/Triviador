#include "Player.h"

Player::Player()
{
}

void Player::SetName(const std::string& name)
{
	this->name = name;
}

void Player::SetEmail(const std::string& email)
{
	this->email = email;
}

void Player::SetPassword(const std::string& password)
{
	this->password = password;
}

void Player::SetImagePath(const std::string& imagePath)
{
	this->imagePath = imagePath;
}

std::string Player::GetName() const
{
	return name;
}

std::string Player::GetEmail() const
{
	return email;
}

std::string Player::GetPassword() const
{
	return password;
}

std::string Player::GetImagePath() const
{
	return imagePath;
}
