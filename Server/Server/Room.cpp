#include "Room.h"

Room::Room()
{
	m_users = std::vector<User>();
	m_owner = User();
	m_startGame = false;
}

Room::Room(const User& owner)
{
	m_owner = owner;
	m_startGame = false;
}

Room::Room(const std::vector<Question>& numericalQuestions, const std::vector<Question>& multipleChoiceQuesition)
{
	m_numericalQuestions = numericalQuestions;
	m_multipleChoiceQuestions = multipleChoiceQuesition;
}

void Room::SetOwner(const User& owner)
{
	m_owner = owner;
}

void Room::SetMaxUsers(int maxUsers)
{
	m_maxUsers = maxUsers;
}

void Room::SetStartGame(bool startGame)
{
	m_startGame = startGame;
}

void Room::SetUsers(const std::vector<User>& users)
{
	this->m_users = users;
}

void Room::SetNumericalQuestions(const std::vector<Question>& numericalQuestions)
{
	m_numericalQuestions = numericalQuestions;
}

void Room::SetMultipleChoiceQuestions(const std::vector<Question>& multipleChoiceQuestions)
{
	m_multipleChoiceQuestions = multipleChoiceQuestions;
}

User Room::GetOwner() const
{
	return m_owner;
}

int Room::GetMaxUsers() const
{
	return m_maxUsers;
}

bool Room::GetStartGame() const
{
	return m_startGame;
}

std::vector<User> Room::GetUsers() const
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

void Room::ShuffleQuestions()
{
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(m_numericalQuestions), std::end(m_numericalQuestions), rng);
	std::shuffle(std::begin(m_multipleChoiceQuestions), std::end(m_multipleChoiceQuestions), rng);
}

void Room::AddUser(const User& user)
{
	m_users.push_back(user);
}

void Room::RemoveUser(const std::string& username)
{
	for (int i = 0; i < m_users.size(); i++)
	{
		if (username == m_users[i].GetName())
		{
			m_users.erase(m_users.begin() + i);
			return;
		}
	}
}

