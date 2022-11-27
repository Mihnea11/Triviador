#pragma once
#include <qrandom.h>
#include <sstream>
#include <string>

class Quiz
{
private:
	std::string questionText;
	std::string questionAnswer;
	unsigned int questionScore;

public:
	Quiz();
	Quiz(const std::string& questionText, const std::string& questionAnswer);
	Quiz(const std::string& questionText, const std::string& questionAnswer, const unsigned int& questionScore);

	void SetQuestionText(const std::string& questionText);
	void SetQuestionAnswer(const std::string& questionAnswer);
	void SetQuestionScore(const unsigned int& questionScore);

	std::string GetQuestionText() const;
	std::string GetQuestionAnswer() const;
	unsigned int GetQuestionScore() const;

	Quiz PickRandomQuiz();

	friend std::istream& operator>>(std::istream&, Quiz&);
};

