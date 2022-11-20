#include "Quiz.h"

Quiz::Quiz()
{
	questionText = std::string();
	questionAnswer = std::string();

	questionScore = 0;
}

Quiz::Quiz(const std::string& questionText, const std::string& questionAnswer, const unsigned int& questionScore)
{
	this->questionText = questionText;
	this->questionAnswer = questionAnswer;

	this->questionScore = questionScore;
}

void Quiz::SetQuestionText(const std::string& questionText)
{
	this->questionText = questionText;
}

void Quiz::SetQuestionAnswer(const std::string& questionAnswer)
{
	this->questionAnswer = questionAnswer;
}

void Quiz::SetQuestionScore(const unsigned int& questionScore)
{
	this->questionScore = questionScore;
}

std::string Quiz::GetQuestionText()
{
	return questionText;
}

std::string Quiz::GetQuestionAnswer()
{
	return questionAnswer;
}

unsigned int Quiz::GetQuestionScore()
{
	return questionScore;
}
