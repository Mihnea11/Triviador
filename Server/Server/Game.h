#pragma once
#include <string>
#include <vector>
#include <random>
#include <unordered_map>

#include "Region.h"
#include "Question.h"

class Game
{
public:
	static int numericalQuestionIndex;
	static int multipleChoiceQuestionIndex;

	static enum GameState
	{
		EMPTY,
		JOINING,
		BASE_FIGHT,
		BASE_SELECTION,
		REGION_FIGHT,
		REGION_SELECTION,
		DUELS,
		ENDING
	};

	Game();

	void SetGameCode(const std::string& gameCode);
	void SetPlayerCount(int playerCount);
	void SetGameState(Game::GameState state);
	void SetRegionsNumber(int regionsNumber);
	void SetNumericalQuestions(const std::vector<Question>& numericalQuestions);
	void SetMultipleChoiceQuestions(const std::vector<Question>& multipleChoiceQuestions);

	std::string GetGameCode();
	Game::GameState GetGameState() const;
	int GetPlayerCount() const;
	int GetRegionsCount() const;
	std::vector<Question> GetNumericalQuestions() const;
	std::vector<Question> GetMultipleChoiceQuestions() const;

	Question SelectNumericalQuestion();
	Question SelectMultipleChoiceQuestion();
	void AddPlayer(const std::string& playerName);
	void ShuffleQuestions();
	bool IsFull();

	bool operator== (const std::string gameCode);

private:
	GameState m_state;
	int m_playerCount;
	int m_regionsNumber;
	std::string m_gameCode;
	std::unordered_map<std::string, std::string> m_playersAndAnswers;
	std::vector<Region> m_regions;
	std::vector<Question> m_numericalQuestions;
	std::vector<Question> m_multipleChoiceQuestions;
};