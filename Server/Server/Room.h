#pragma once

#include <string>
#include <vector>

#include "User.h"
#include "Question.h"

class Room
{
public:
	Room();
	Room(const std::vector<Question> &numericalQuestions, const std::vector<Question> &multipleChoiceQuesition);

	void SetUsers(const std::vector<std::string>& users);
	void SetNumericalQuestions(const std::vector<Question> numericalQuestions);
	void SetMultipleChoiceQuestions(const std::vector<Question> multipleChoiceQuestions);

	std::vector<std::string> GetUsers() const;
	std::vector<Question> GetNumericalQuestions() const;
	std::vector<Question> GetMultipleChoiceQuestions() const; 

private:
	std::string m_owner;
	std::vector<std::string> m_users;
	std::string m_roomCode;
	std::vector<Question> m_numericalQuestions;
	std::vector<Question> m_multipleChoiceQuestions;
	 
};