#pragma once
#include <string>
#include <fstream>

class Player
{
private:
	std::string userName;
	std::string userEmail;
	int playedGames;
	int wonGames;
	float winRate;

public:
	Player();
	Player(const std::string& userName, const std::string& userEmail);

	void SetUserName(const std::string& userName);
	void SetUserEmail(const std::string& userEmail);
	void SetPlayedGames(const int& playedGames);
	void SetWonGames(const int& wonGames);

	std::string GetUserName() const;
	std::string GetUserEmail() const;
	int GetPlayedGames() const;
	int GetWonGames() const;
	float GetWinRate() const;

	void CalculateWinRate();
	void IncreaseWinGames(int value = 1);

	friend std::ostream& operator<<(std::ostream& out, const Player&);
};

