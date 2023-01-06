#include "pch.h"
#include "Question.h"

Question::Question()
{
	m_id = -1;
	m_isNumerical = false;
	m_text = std::string();
	m_answer = std::string();
	m_incorrectAnswers = std::string();
}

void Question::SetId(int id)
{
	m_id = id;
}

void Question::SetIsNumerical(bool isNumerical)
{
	m_isNumerical = isNumerical;
}

void Question::SetText(const std::string& text)
{
	m_text = text;
}

void Question::SetAnswer(const std::string& answer)
{
	m_answer = answer;
}

void Question::SetIncorrectAnswers(const std::string& incorrectAnswers)
{
	m_incorrectAnswers = incorrectAnswers;
}

int Question::GetId() const
{
	return m_id;
}

bool Question::GetIsNumerical() const
{
	return m_isNumerical;
}

std::string Question::GetText() const
{
	return m_text;
}

std::string Question::GetAnswer() const
{
	return m_answer;
}

std::string Question::GetIncorrectAnswers() const
{
	return m_incorrectAnswers;
}

template<> double CompareAnswers<double>(const Question& question, const std::string& userAnswer)
{
	double questionAnswerNumerical = std::stod(question.GetAnswer());
	double userAnswerNumerical = std::stod(userAnswer);

	return std::abs(questionAnswerNumerical - userAnswerNumerical);
}
