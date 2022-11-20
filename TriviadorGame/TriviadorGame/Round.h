#pragma once

#include "Quiz.h"

class Round
{
public:
	Round();
	Round(const unsigned int& roundNumber, const Quiz& roundQuiz, const unsigned int& roundTime);

	void SetRoundNumber(const unsigned int& roundNumber);
	void SetRoundQuiz(const Quiz& roundQuiz);
	void SetRoundTime(const unsigned int& roundTime);

	unsigned int GetRoundNumber() const;
	Quiz GetRoundQuiz() const;
	unsigned int GetRoundTime() const;

private:
	unsigned int roundNumber;
	Quiz roundQuiz;
	unsigned int roundTime;
};

