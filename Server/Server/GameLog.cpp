#include "GameLog.h"

GameLog::GameLog()
{
	m_id = -1;
	m_playerOne = "";
	m_playerTwo = "";
	m_playerThree = "";
	m_playerFour = "";
	m_gameResult = "";
	m_gameDate = "";
}

void GameLog::SetId(int id)
{
	m_id = id;
}

void GameLog::SetPlayerOne(const std::string& playerOne)
{
	m_playerOne = playerOne;
}

void GameLog::SetPlayerTwo(const std::string& playerTwo)
{
	m_playerTwo = playerTwo;
}

void GameLog::SetPlayerThree(const std::string& playerThree)
{
	m_playerThree = playerThree;
}

void GameLog::SetPlayerFour(const std::string& playerFour)
{
	m_playerFour = playerFour;
}

void GameLog::SetGameResult(const std::string& gameResult)
{
	m_gameResult = gameResult;
}

void GameLog::SetGameDate(const std::string& gameDate)
{
	m_gameDate = gameDate;
}

int GameLog::GetId() const
{
	return m_id;
}

std::string GameLog::GetPlayerOne() const
{
	return m_playerOne;
}

std::string GameLog::GetPlayerTwo() const
{
	return m_playerTwo;
}

std::string GameLog::GetPlayerThree() const
{
	return m_playerThree;
}

std::string GameLog::GetPlayerFour() const
{
	return m_playerFour;
}

std::string GameLog::GetGameResult() const
{
	return m_gameResult;
}

std::string GameLog::GetGameDate() const
{
	return m_gameDate;
}
