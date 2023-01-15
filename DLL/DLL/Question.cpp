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

std::vector<std::string> Question::ShuffleAnswers()
{
	std::stringstream ss(m_incorrectAnswers);
	std::vector<std::string> shuffledAnswers;

	shuffledAnswers.push_back(m_answer);

	while (ss.good())
	{
		std::string substr;
		std::getline(ss, substr, ',');
		shuffledAnswers.push_back(substr);
	}

	std::random_shuffle(shuffledAnswers.begin(), shuffledAnswers.end());

	return shuffledAnswers;
}
