#pragma once
#include <string>

class Player
{
private:
	std::string userName;
	std::string userEmail;

public:
	Player();

	void SetUserName(const std::string userName);
	void SetUserEmail(const std::string userEmail);

	std::string GetUserName() const;
	std::string GetUserEmail() const;
};

