#include "Question.h"

Question::Question()
{
	difficulty = std::string();
	text = std::string();
	correctAnswer = std::string();
	incorrectAnswers = std::vector<std::string>();
	isMultipleChoice = true;
	score = 0;
}

void Question::SetDifficulty(const std::string& difficulty)
{
	this->difficulty = difficulty;
}

void Question::SetText(const std::string& text)
{
	this->text = text;
}

void Question::SetCorrectAnswer(const std::string& correctAnswer)
{
	this->correctAnswer = correctAnswer;
}

void Question::SetIncorrectAnswers(const std::vector<std::string>& incorrectAnswers)
{
	this->incorrectAnswers = incorrectAnswers;
}

void Question::SetIsMultipleChoice(bool isMultipleChoice)
{
	this->isMultipleChoice = isMultipleChoice;
}

void Question::SetScore(int score)
{
	this->score = score;
}

std::string Question::GetDifficulty() const
{
	return difficulty;
}

std::string Question::GetText() const
{
	return text;
}

std::string Question::GetCorrectAnswer() const
{
	return correctAnswer;
}

std::vector<std::string> Question::GetIncorrectAnswers() const
{
	return incorrectAnswers;
}

bool Question::GetIsMultipleChoice() const
{
	return isMultipleChoice;
}

int Question::GetScore() const
{
	return score;
}
