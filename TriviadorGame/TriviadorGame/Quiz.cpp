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

Quiz Quiz::RandomQuiz(Quiz randQuiz)
{
	std::string line;
	std::vector<std::string> lines;
	std::ifstream file("questionsAndAnswers.txt");
	int totalLines = 0;
	while (getline(file, line))
	{
		totalLines++;
		lines.push_back(line);
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, totalLines);
	int lineNumber=dis(gen);
	Quiz auxiliary;
	std::string delimiter = "?";
	std::string question = lines[lineNumber].substr(0, lines[lineNumber].find(delimiter));
	std::string answer = lines[lineNumber].substr(lines[lineNumber].find(delimiter), lines[lineNumber].back());
	auxiliary.SetQuestionText(question);
	auxiliary.SetQuestionAnswer(answer);
	return auxiliary;
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
