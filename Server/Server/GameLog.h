#pragma once

#include <string>

class GameLog {
public:
	GameLog();

	void SetId(int id);
	void SetPlayerOne(const std::string& playerOne);
	void SetPlayerTwo(const std::string& playerTwo);
	void SetPlayerThree(const std::string& playerThree);
	void SetPlayerFour(const std::string& playerFour);
	void SetGameResult(const std::string& gameResult);
	void SetGameDate(const std::string& gameDate);

	int GetId() const;
	std::string GetPlayerOne() const;
	std::string GetPlayerTwo() const;
	std::string GetPlayerThree() const;
	std::string GetPlayerFour() const;
	std::string GetGameResult() const;
	std::string GetGameDate() const;

private:
	int m_id;
	std::string m_playerOne;
	std::string m_playerTwo;
	std::string m_playerThree;
	std::string m_playerFour;
	std::string m_gameResult;
	std::string m_gameDate;
};

//struct GameLog {
//	int id;
//	std::string playerOne;
//	std::string playerTwo;
//	std::string playerThree;
//	std::string playerFour;
//	std::string gameResult;
//	std::string gameDate;
//};