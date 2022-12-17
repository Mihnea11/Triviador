#pragma once

#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

#include "Utilities.h"

namespace sql = sqlite_orm;

class Question
{
public:
	Question();

	void SetId(int id);
	void SetIsNumerical(bool isNumerical);
	void SetText(const std::string& text);
	void SetAnswer(const std::string& answer);
	void SetIncorrectAnswers(const std::string& incorrectAnswers);

	int GetId() const;
	bool GetIsNumerical() const;
	std::string GetText() const;
	std::string GetAnswer() const;
	std::string GetIncorrectAnswers() const;

private:
	int m_id;
	bool m_isNumerical;
	std::string m_text;
	std::string m_answer;
	std::string m_incorrectAnswers;
};


template<class T> T CompareAnswers(const Question& question, const std::string& userAnswer)
{
	return question.GetAnswer() == userAnswer;
}
