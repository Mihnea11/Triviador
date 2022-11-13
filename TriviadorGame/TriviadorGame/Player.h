#pragma once
#include <string>
#include <fstream>

class Player
{
private:
	std::string userName;
	std::string userEmail;
	std::string userPassword;

public:
	Player();

	void SetUserName(const std::string userName);
	void SetUserEmail(const std::string userEmail);
	void SetUserPassword(const std::string userPassword);

	std::string GetUserName() const;
	std::string GetUserEmail() const;

	friend std::ostream& operator<<(std::ostream&, const Player&);
};

