#pragma once
#include <string>
#include <vector>

#include "Region.h"

class Game
{
public:
	static enum GameState
	{
		JOINING,
		BASE_SELECTION,
		REGION_SELECTION,
		DUELS,
		ENDING
	};

	Game();

	void SetPlayerCount(int playerCount);
	void SetGameState(Game::GameState state);

	int GetPlayerCount() const;
	Game::GameState GetGameState() const;

private:
	GameState m_state;
	int m_playerCount;
	int m_regionsNumber;
	std::string m_gameCode;
	std::vector<std::string> m_players;
	std::vector<Region> m_regions;
};

