#pragma once
#include <string>

class Region
{
public:
	Region();

	void SetScore(int score);
	void SetName(const std::string& name);
	void SetOwner(const std::string& owner);

	int GetScore() const;
	std::string GetName() const;
	std::string GetOwner() const;

private:
	int m_score;
	std::string m_name;
	std::string m_owner;
};

