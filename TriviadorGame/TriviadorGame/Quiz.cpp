#include "Quiz.h"
#include <vector>
#include <fstream>
#include <random>
Quiz::Quiz()
{
	questionText = std::string();
	questionAnswer = std::string();

	questionScore = 0;
}

Quiz::Quiz(const std::string& questionText, const std::string& questionAnswer)
{
	this->questionText = questionText;
	this->questionAnswer = questionAnswer;
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

std::string Quiz::GetQuestionText() const
{
	return questionText;
}

std::string Quiz::GetQuestionAnswer() const
{
	return questionAnswer;
}

unsigned int Quiz::GetQuestionScore() const 
{
	return questionScore;
}

Quiz Quiz::PickRandomQuiz()
{
	std::ifstream in("questions.txt");

	int randomNumber = QRandomGenerator::global()->generate() % 100;

	std::string question;
	std::string answer;

	for (int i = 0; i < randomNumber; i++)
	{
		std::getline(in, question);
		std::getline(in, answer);
	}

	return Quiz(question, answer);
}

std::istream& operator>>(std::istream& in , Quiz& quiz)
{
	std::string fileLine;
	std::getline(in, fileLine);
	std::string delimiter = "?";
	std::string question=fileLine.substr(0,fileLine.find(delimiter));
	std::string answer=fileLine.substr(fileLine.find(delimiter),fileLine.back());
	quiz.SetQuestionText(question);
	quiz.SetQuestionAnswer(answer);
	return in;
}
