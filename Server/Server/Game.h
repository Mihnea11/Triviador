#pragma once
#include <string>
#include <vector>
#include <random>
#include <climits>
#include <unordered_map>

#include "Region.h"
#include "Question.h"

class Game
{
public:
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
	void SetCurrentPlayerSelection(int value);

	std::string GetGameCode();
	Game::GameState GetGameState() const;
	int GetPlayerCount() const;
	int GetRegionsCount() const;
	int GetCurrentPlayerSelection() const;
	std::vector<Question> GetNumericalQuestions() const;
	std::vector<Question> GetMultipleChoiceQuestions() const;

	Question SelectNumericalQuestion();
	Question SelectMultipleChoiceQuestion();
	void AdvanceNumericalQuestion();
	void AdvanceMultipleChoiceQuestion();
	void AddPlayer(const std::string& playerName);
	double FindAnswerScore(const std::string& answer);
	void AddPlayerAnswer(const std::string& playerName, double answerScore, int answerTime);
	int FindPlayerIndex(const std::string& playerName);
	void ShuffleQuestions();
	bool IsFull();
	bool AllAnswered();

	std::string CurrentPlayerSelection();
	void AdvancePlayer();
	void ResetCurrentPlayer();

	bool operator== (const std::string gameCode);

private:
	GameState m_state;
	int m_playerCount;
	int m_regionsNumber;
	int m_numericalQuestionIndex;
	int m_multipleChoiceQuestionIndex;
	int m_currentPlayerSelection;
	std::string m_gameCode;
	std::vector<std::string> m_players;
	std::vector<std::tuple<std::string, double, int>> m_orderedPlayers;
	std::vector<Region> m_regions;
	std::vector<Question> m_numericalQuestions;
	std::vector<Question> m_multipleChoiceQuestions;
};