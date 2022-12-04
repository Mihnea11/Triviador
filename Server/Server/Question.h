#pragma once
#include <string>
#include <vector>
class Question
{
private:
	std::string difficulty;
	std::string text;
	std::string correctAnswer;
	std::vector<std::string> incorrectAnswers;
	bool isMultipleChoice;
	int score;
public:
	Question();

	void SetDifficulty(const std::string& difficulty);
	void SetText(const std::string& text);
	void SetCorrectAnswer(const std::string& correctAnswer);
	void SetIncorrectAnswers(const std::vector<std::string>& incorrectAnswers);
	void SetIsMultipleChoice(bool isMultipleChoice);
	void SetScore(int score);

	
};

