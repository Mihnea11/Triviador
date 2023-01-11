#pragma once
#include <string>
#include <vector>

#include "Region.h"

class Game
{
public:
	static enum GameState
	{
		EMPTY,
		JOINING,
		BASE_SELECTION,
		REGION_SELECTION,
		DUELS,
		ENDING
	};

	Game();

	void SetGameCode(const std::string& gameCode);
	void SetPlayerCount(int playerCount);
	void SetGameState(Game::GameState state);
	void SetRegionsNumber(int regionsNumber);
	void SetPlayers(const std::vector<std::string>& players);

	std::string GetGameCode();
	Game::GameState GetGameState() const;
	int GetPlayerCount() const;
	int GetRegionsCount() const;
	std::vector<std::string> GetPlayers() const;

	void AddPlayer(const std::string& playerName);

	bool operator== (const std::string gameCode);

private:
	GameState m_state;
	int m_playerCount;
	int m_regionsNumber;
	std::string m_gameCode;
	std::vector<std::string> m_players;
	std::vector<Region> m_regions;
};

