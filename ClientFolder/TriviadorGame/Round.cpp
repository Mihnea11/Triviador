#include "Round.h"

Round::Round() 
{
	roundNumber = 0;
	roundTime = 10;

	roundQuiz = Quiz::Quiz();
}

Round::Round(const unsigned int& roundNumber, const Quiz& roundQuiz, const unsigned int& roundTime)
{
	this->roundNumber = roundNumber;
	this->roundTime = roundTime;

	this->roundQuiz = roundQuiz;
}

void Round::SetRoundNumber(const unsigned int& roundNumber)
{
	this->roundNumber = roundNumber;
}

void Round::SetRoundQuiz(const Quiz& roundQuiz)
{
	this->roundQuiz = roundQuiz;
}

void Round::SetRoundTime(const unsigned int& roundTime)
{
	this->roundTime = roundTime;
}

unsigned int Round::GetRoundNumber() const
{
	return roundNumber;
}

Quiz Round::GetRoundQuiz() const
{
	return roundQuiz;
}

unsigned int Round::GetRoundTime() const
{
	return roundTime;
}