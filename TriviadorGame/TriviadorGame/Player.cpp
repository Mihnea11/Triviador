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

void Player::SetUserPassword(const std::string userPassword)
{
	this->userPassword = userPassword;
}

std::string Player::GetUserName() const
{
	return userName;
}

std::string Player::GetUserEmail() const
{
	return userEmail;
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << player.userName << " " << player.userEmail << " " << player.userPassword << '\n';
	return out;
}
