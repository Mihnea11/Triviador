#pragma once

#include <string>
#include <vector>

#include "User.h"

class Room
{
private:
	std::vector<User> users;
	int typeOfRoom; // 2, 3 or 4 players;
	int timer; // when all players click the Ready button, timer starts
	int codeToJoin; // code required to join the room

public:
	Room();

	void SetUsers(const std::vector<User>& users);
	void SetTypeOfRoom(int typeOfRoom);
	void SetTimer(int timer);
	void SetCodeToJoin(int codeToJoin);

	std::vector<User> GetUsers() const;
	int GetTypeOfRoom() const;
	int GetTimer() const;
	int GetCodeToJoin() const;
};