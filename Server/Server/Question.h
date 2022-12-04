#pragma once

#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

#include "Utilities.h"

namespace sql = sqlite_orm;

class Question
{
private:
	int id;
	std::string difficulty;
	std::string text;
	std::string correctAnswer;
	//std::vector<std::string> incorrectAnswers;
	bool isMultipleChoice;
	int score;

public:
	Question();

	void SetId(int id);
	void SetDifficulty(const std::string& difficulty);
	void SetText(const std::string& text);
	void SetCorrectAnswer(const std::string& correctAnswer);
	//void SetIncorrectAnswers(const std::vector<std::string>& incorrectAnswers);
	void SetIsMultipleChoice(bool isMultipleChoice);
	void SetScore(int score);

	int GetId() const;
	std::string GetDifficulty() const;
	std::string GetText() const;
	std::string GetCorrectAnswer() const;
	//std::vector <std::string> GetIncorrectAnswers() const;
	bool GetIsMultipleChoice() const;
	int GetScore() const;
};

inline std::vector<std::string> CreateVector(const std::string& incorrectAnswers)
{
	std::vector<std::string> vector;
	std::string line;
	std::stringstream ss(incorrectAnswers);

	while (std::getline(ss, line, ' '))
	{
		vector.push_back(line);
	}

	return vector;
}

inline bool CreateBool(const std::string& isMultipleChoice)
{
	int answer = std::stoi(isMultipleChoice);

	if (answer == 1)
	{
		return true;
	}

	return false;
}

inline auto CreateQuestionsStorage(const std::string& fileName)
{
	return sql::make_storage(
		fileName,
		sql::make_table(
			"Questions",
			sql::make_column("Id", &Question::SetId, &Question::GetId, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Difficulty", &Question::SetDifficulty, &Question::GetDifficulty),
			sql::make_column("Text", &Question::SetText, &Question::GetText),
			sql::make_column("Correct answer", &Question::SetCorrectAnswer, &Question::GetCorrectAnswer),
			//sql::make_column("Incorrect answers", &Question::SetIncorrectAnswers, &Question::GetIncorrectAnswers),
			sql::make_column("Is multiple choice", &Question::SetIsMultipleChoice, &Question::GetIsMultipleChoice),
			sql::make_column("Score", &Question::SetScore, &Question::GetScore)
		)
	);
}

using QuestionsStorage = decltype(CreateQuestionsStorage(""));
class QuestionDatabaseControl
{
private:
	QuestionsStorage& database;

public:
	QuestionDatabaseControl(QuestionsStorage& storage);

	crow::response operator() (const crow::request& request) const;
};