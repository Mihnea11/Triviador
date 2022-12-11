#include "Room.h"

Room::Room()
{
	users = std::vector<User>();
	typeOfRoom = 2; // by default a room of 2 players
	timer = 10;
	codeToJoin = 0; // generate random code
}

void Room::SetUsers(const std::vector<User>& users)
{
	this->users = users;
}

void Room::SetTypeOfRoom(int typeOfRoom)
{
	this->typeOfRoom = typeOfRoom;
}

void Room::SetTimer(int timer)
{
	this->timer = timer;
}

void Room::SetCodeToJoin(int codeToJoin)
{
	this->codeToJoin = codeToJoin;
}

std::vector<User> Room::GetUsers() const
{
	return users;
}

int Room::GetTypeOfRoom() const
{
	return typeOfRoom;
}

int Room::GetTimer() const
{
	return timer;
}

int Room::GetCodeToJoin() const
{
	return codeToJoin;
}
