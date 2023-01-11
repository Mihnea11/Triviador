#include "Game.h"

Game::Game()
{

}

void Game::SetPlayerCount(int playerCount)
{
	m_playerCount = playerCount;
}

void Game::SetGameState(Game::GameState state)
{
	m_state = state;
}

int Game::GetPlayerCount() const
{
	return m_playerCount;
}

Game::GameState Game::GetGameState() const
{
	return m_state;
}
