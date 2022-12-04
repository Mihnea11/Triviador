#pragma once
#include <string>

class Player
{
private:
	std::string name;
	std::string email;
	std::string password;
	std::string imagePath;

public:
	Player();

	void SetName(const std::string& name);
	void SetEmail(const std::string& email);
	void SetPassword(const std::string& password);
	void SetImagePath(const std::string& imagePath);

	std::string GetName() const;
	std::string GetEmail() const;
	std::string GetPassword() const;
	std::string GetImagePath() const;
};

