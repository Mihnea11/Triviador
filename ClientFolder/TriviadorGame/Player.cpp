#include "Player.h"

Player::Player()
{
	userName = std::string();
	userEmail = std::string();

	wonGames = 0;
	playedGames = 0;
	winRate = 0;
}

Player::Player(const std::string& userName, const std::string& userEmail)
{
	this->userName = userName;
	this->userEmail = userEmail;

	wonGames = 0;
	playedGames = 0;
	winRate = 0;
}

void Player::SetUserName(const std::string& userName)
{
	this->userName = userName;
}

void Player::SetUserEmail(const std::string& userEmail)
{
	this->userEmail = userEmail;
}

void Player::SetPlayedGames(const int& playedGames)
{
	this->playedGames = playedGames;
}

void Player::SetWonGames(const int& wonGames)
{
	this->wonGames = wonGames;
}

std::string Player::GetUserName() const
{
	return userName;
}

std::string Player::GetUserEmail() const
{
	return userEmail;
}

int Player::GetPlayedGames() const
{
	return playedGames;
}

int Player::GetWonGames() const
{
	return wonGames;
}

float Player::GetWinRate() const
{
	return winRate;
}

void Player::CalculateWinRate()
{
	float percentage = wonGames;
	percentage /= playedGames;
	percentage *= 100;

	winRate = percentage;
}

void Player::IncreaseWinGames(int value)
{
	wonGames += value;
	CalculateWinRate();
}

std::ostream& operator<<(std::ostream& out, const Player& player)
{
	out << player.userName << " " << player.userEmail << " " << '\n';
	return out;
}
