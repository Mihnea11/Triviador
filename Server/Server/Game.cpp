#include "Game.h"

Game::Game()
{
	m_gameCode = std::string();
	m_playerCount = 0;
	m_players = std::vector<std::string>();
	m_regions = std::vector<Region>();
	m_regionsNumber = 0;
	m_state = EMPTY;
}

void Game::SetGameCode(const std::string& gameCode)
{
	m_gameCode = gameCode;
}

void Game::SetPlayerCount(int playerCount)
{
	m_playerCount = playerCount;
}

void Game::SetGameState(Game::GameState state)
{
	m_state = state;
}

void Game::SetRegionsNumber(int regionsNumber)
{
	m_regionsNumber = regionsNumber;
}

void Game::SetPlayers(const std::vector<std::string>& players)
{
	m_players = players;
}

int Game::GetPlayerCount() const
{
	return m_playerCount;
}

int Game::GetRegionsCount() const
{
	return m_regionsNumber;
}

std::vector<std::string> Game::GetPlayers() const
{
	return m_players;
}

std::string Game::GetGameCode()
{
	return m_gameCode;
}

Game::GameState Game::GetGameState() const
{
	return m_state;
}

void Game::AddPlayer(const std::string& playerName)
{
	m_players.push_back(playerName);
}

bool Game::operator==(const std::string gameCode)
{
	if (m_gameCode == gameCode)
	{
		return true;
	}

	return false;
}
