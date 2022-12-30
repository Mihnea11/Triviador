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
	Room(const User& owner);
	Room(const std::vector<Question>& numericalQuestions, const std::vector<Question>& multipleChoiceQuesition);

	void SetOwner(const User& owner);
	void SetMaxUsers(int maxUsers);
	void SetStartGame(bool startGame);
	void SetUsers(const std::vector<User>& users);
	void SetNumericalQuestions(const std::vector<Question>& numericalQuestions);
	void SetMultipleChoiceQuestions(const std::vector<Question>& multipleChoiceQuestions);

	User GetOwner() const;
	int GetMaxUsers() const;
	bool GetStartGame() const;
	std::vector<User> GetUsers() const;
	std::vector<Question> GetNumericalQuestions() const;
	std::vector<Question> GetMultipleChoiceQuestions() const;

	void ShuffleQuestions();
	void AddUser(const User& user);
	void RemoveUser(const std::string& username);
private:
	User m_owner;
	int m_maxUsers;
	bool m_startGame;
	std::vector<User> m_users;
	std::string m_roomCode;
	std::vector<Question> m_numericalQuestions;
	std::vector<Question> m_multipleChoiceQuestions;
	
};