#include "Room.h"

Room::Room()
{
	m_users = std::vector<std::string>();
	m_owner = std::string();
}

Room::Room(const std::vector<Question>& numericalQuestions, const std::vector<Question>& multipleChoiceQuesition)
{
	m_numericalQuestions = numericalQuestions;
	m_multipleChoiceQuestions = multipleChoiceQuesition;
}

void Room::SetUsers(const std::vector<std::string>& users)
{
	this->m_users = users;
}

void Room::SetNumericalQuestions(const std::vector<Question> numericalQuestions)
{
	m_numericalQuestions = numericalQuestions;
}

void Room::SetMultipleChoiceQuestions(const std::vector<Question> multipleChoiceQuestions)
{
	m_multipleChoiceQuestions = multipleChoiceQuestions;
}

std::vector<std::string> Room::GetUsers() const
{
	return m_users;
}

std::vector<Question> Room::GetNumericalQuestions() const
{
	return m_numericalQuestions;
}

std::vector<Question> Room::GetMultipleChoiceQuestions() const
{
	return std::vector<Question>();
}

