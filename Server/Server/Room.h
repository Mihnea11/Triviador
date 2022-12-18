#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <random>

#include "User.h"
#include "Question.h"

class Room
{
public:
	Room();
	Room(const std::string& owner);
	Room(const std::vector<Question>& numericalQuestions, const std::vector<Question>& multipleChoiceQuesition);

	void SetUsers(const std::vector<std::string>& users);
	void SetNumericalQuestions(const std::vector<Question>& numericalQuestions);
	void SetMultipleChoiceQuestions(const std::vector<Question>& multipleChoiceQuestions);

	std::vector<std::string> GetUsers() const;
	std::vector<Question> GetNumericalQuestions() const;
	std::vector<Question> GetMultipleChoiceQuestions() const; 

	void ShuffleQuestions();
	void AddUser(const std::string& user);

private:
	std::string m_owner;
	std::vector<std::string> m_users;
	std::string m_roomCode;
	std::vector<Question> m_numericalQuestions;
	std::vector<Question> m_multipleChoiceQuestions;
	 
};