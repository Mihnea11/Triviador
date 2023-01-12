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

void Room::SetOwner(const User& owner)
{
	m_owner = owner;
}

void Room::SetMaxUsers(int maxUsers)
{
	m_maxUsers = maxUsers;
}

void Room::SetRoomCode(const std::string& roomCode)
{
	m_roomCode = roomCode;
}

void Room::SetStartGame(bool startGame)
{
	m_startGame = startGame;
}

void Room::SetUsers(const std::vector<User>& users)
{
	this->m_users = users;
}

User Room::GetOwner() const
{
	return m_owner;
}

int Room::GetMaxUsers() const
{
	return m_maxUsers;
}

std::string Room::GetRoomCode() const
{
	return m_roomCode;
}

bool Room::GetStartGame() const
{
	return m_startGame;
}

std::vector<User> Room::GetUsers() const
{
	return m_users;
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

bool Room::operator==(const std::string& roomCode)
{
	if (m_roomCode == roomCode)
	{
		return true;
	}

	return false;
}

