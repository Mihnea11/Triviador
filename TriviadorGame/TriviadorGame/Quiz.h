#pragma once

#include <string>

class Quiz
{
public:
	Quiz();
	Quiz(const std::string& questionText, const std::string& questionAnswer, const unsigned int& questionScore);

	void SetQuestionText(const std::string& questionText);
	void SetQuestionAnswer(const std::string& questionAnswer);
	void SetQuestionScore(const unsigned int& questionScore);

	std::string GetQuestionText() const;
	std::string GetQuestionAnswer() const;
	unsigned int GetQuestionScore() const;

private:
	std::string questionText;
	std::string questionAnswer;
	unsigned int questionScore;
};

