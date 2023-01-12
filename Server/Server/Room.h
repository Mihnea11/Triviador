#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "User.h"
#include "Question.h"

class Room
{
public:
	Room();
	Room(const User& owner);

	void SetOwner(const User& owner);
	void SetMaxUsers(int maxUsers);
	void SetRoomCode(const std::string& roomCode);
	void SetStartGame(bool startGame);
	void SetUsers(const std::vector<User>& users);

	User GetOwner() const;
	int GetMaxUsers() const;
	std::string GetRoomCode() const;
	bool GetStartGame() const;
	std::vector<User> GetUsers() const;

	void AddUser(const User& user);
	void RemoveUser(const std::string& username);

	bool operator== (const std::string& roomCode);
private:
	User m_owner;
	int m_maxUsers;
	bool m_startGame;
	std::string m_roomCode;
	std::vector<User> m_users;
};