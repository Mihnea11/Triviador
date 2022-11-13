#include "Player.h"

Player::Player()
{
	userName = std::string();
	userEmail = std::string();
}

void Player::SetUserName(const std::string userName)
{
	this->userName = userName;
}

void Player::SetUserEmail(const std::string userEmail)
{
	this->userEmail = userEmail;
}

std::string Player::GetUserName() const
{
	return userName;
}

std::string Player::GetUserEmail() const
{
	return userEmail;
}
