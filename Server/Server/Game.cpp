#include "Game.h"

int Game::numericalQuestionIndex = 0;
int Game::multipleChoiceQuestionIndex = 0;

Game::Game()
{
	m_gameCode = std::string();
	m_playerCount = 0;
	m_playersAndAnswers = std::unordered_map<std::string, std::string>();
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

int Game::GetPlayerCount() const
{
	return m_playerCount;
}

int Game::GetRegionsCount() const
{
	return m_regionsNumber;
}

std::vector<Question> Game::GetNumericalQuestions() const
{
	return m_numericalQuestions;
}

std::vector<Question> Game::GetMultipleChoiceQuestions() const
{
	return m_multipleChoiceQuestions;
}

Question Game::SelectNumericalQuestion()
{
	return m_numericalQuestions[Game::numericalQuestionIndex];
}

Question Game::SelectMultipleChoiceQuestion()
{
	return m_multipleChoiceQuestions[Game::multipleChoiceQuestionIndex];
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
	m_playersAndAnswers[playerName] = "";
}

void Game::ShuffleQuestions()
{
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(m_numericalQuestions), std::end(m_numericalQuestions), rng);
	std::shuffle(std::begin(m_multipleChoiceQuestions), std::end(m_multipleChoiceQuestions), rng);
}

bool Game::IsFull()
{
	if (m_playersAndAnswers.size() == m_playerCount)
	{
		return true;
	}

	return false;
}

bool Game::operator==(const std::string gameCode)
{
	if (m_gameCode == gameCode)
	{
		return true;
	}

	return false;
}
