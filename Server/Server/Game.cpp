#include "Game.h"

Game::Game()
{
	m_numericalQuestionIndex = 0;
	m_multipleChoiceQuestionIndex = 0;
	m_currentPlayerSelection = 0;

	m_gameCode = std::string();
	m_playerCount = 0;
	m_players = std::vector<std::string>();
	m_orderedPlayers = std::vector<std::tuple<std::string, double, int>>();
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

void Game::SetNumericalQuestions(const std::vector<Question>& numericalQuestions)
{
	m_numericalQuestions = numericalQuestions;
}

void Game::SetMultipleChoiceQuestions(const std::vector<Question>& multipleChoiceQuestions)
{
	m_multipleChoiceQuestions = multipleChoiceQuestions;
}

void Game::SetCurrentPlayerSelection(int value)
{
	m_currentPlayerSelection = value;
}

void Game::SetSelectedRegions(int value)
{
	m_selectedRegions = value;
}

void Game::SetRegions(const std::vector<Region>& regions)
{
	m_regions = regions;
}

int Game::GetPlayerCount() const
{
	return m_playerCount;
}

int Game::GetRegionsCount() const
{
	return m_regionsNumber;
}

int Game::GetCurrentPlayerSelection() const
{
	return m_currentPlayerSelection;
}

int Game::GetSelectedRegions() const
{
	return m_selectedRegions;
}

std::vector<Question> Game::GetNumericalQuestions() const
{
	return m_numericalQuestions;
}

std::vector<Question> Game::GetMultipleChoiceQuestions() const
{
	return m_multipleChoiceQuestions;
}

std::vector<Region> Game::GetRegions() const
{
	return m_regions;
}

Question Game::SelectNumericalQuestion()
{
	return m_numericalQuestions[m_numericalQuestionIndex];
}

Question Game::SelectMultipleChoiceQuestion()
{
	return m_multipleChoiceQuestions[m_multipleChoiceQuestionIndex];
}

void Game::ResetPlayerOrder()
{
	m_orderedPlayers.clear();
}

void Game::AdvanceNumericalQuestion()
{
	m_numericalQuestionIndex++;
}

void Game::AdvanceMultipleChoiceQuestion()
{
	m_multipleChoiceQuestionIndex++;
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

void Game::AddRegion(const Region& region)
{
	m_regions.push_back(region);
}

double Game::FindAnswerScore(const std::string& answer)
{
	if (answer == "")
	{
		return INT_MAX;
	}

	try
	{
		double answerValue = std::stod(answer);
		double questionValue = std::stod(m_numericalQuestions[m_numericalQuestionIndex].GetAnswer());

		return std::abs(questionValue - answerValue);
	}
	catch (std::exception)
	{
		if (answer == m_multipleChoiceQuestions[m_multipleChoiceQuestionIndex].GetAnswer())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

void Game::AddPlayerAnswer(const std::string& playerName, double answer, int answerTime)
{
	if (m_orderedPlayers.size() == 0)
	{
		m_orderedPlayers.push_back(std::make_tuple(playerName, answer, answerTime));
	}
	else
	{
		int index = 0;
		for (auto element : m_orderedPlayers)
		{
			if (answer < std::get<1>(element))
			{
				m_orderedPlayers.insert(m_orderedPlayers.begin() + index, std::make_tuple(playerName, answer, answerTime));
				return;
			}
			else if (answer == std::get<1>(element))
			{
				if (answerTime < std::get<2>(element))
				{
					m_orderedPlayers.insert(m_orderedPlayers.begin() + index, std::make_tuple(playerName, answer, answerTime));
					return;
				}
				else
				{
					m_orderedPlayers.push_back(std::make_tuple(playerName, answer, answerTime));
					return;
				}
			}
			index++;
		}

		m_orderedPlayers.push_back(std::make_tuple(playerName, answer, answerTime));
	}
}

void Game::ShuffleQuestions()
{
	std::random_shuffle(std::begin(m_numericalQuestions), std::end(m_numericalQuestions));
	std::random_shuffle(std::begin(m_multipleChoiceQuestions), std::end(m_multipleChoiceQuestions));
}

void Game::SelectRegionCount()
{
	m_selectedRegions--;
}

bool Game::IsFull()
{
	if (m_players.size() == m_playerCount)
	{
		return true;
	}

	return false;
}

bool Game::AllAnswered()
{
	if (m_orderedPlayers.size() != m_playerCount)
	{
		return false;
	}

	return true;
}

std::string Game::CurrentPlayerSelection()
{
	return std::get<0>(m_orderedPlayers[m_currentPlayerSelection]);
}

void Game::AdvancePlayer()
{
	m_currentPlayerSelection++;
}

void Game::ResetCurrentPlayer()
{
	m_currentPlayerSelection = 0;
}

int Game::FindPlayerIndex(const std::string& playerName)
{
	int playerIndex = 1;
	for (auto& player : m_players)
	{
		if (player == playerName)
		{
			return playerIndex;
		}

		playerIndex++;
	}
}

bool Game::operator==(const std::string gameCode)
{
	if (m_gameCode == gameCode)
	{
		return true;
	}

	return false;
}
