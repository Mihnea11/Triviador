#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "LibDefine.h"


class DLL_API Question
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

	std::vector<std::string> ShuffleAnswers();

private:
	int m_id;
	bool m_isNumerical;
	std::string m_text;
	std::string m_answer;
	std::string m_incorrectAnswers;
};