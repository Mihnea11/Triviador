#include "Region.h"

Region::Region()
{
	m_score = 0;
	m_name = std::string();
	m_owner = std::string();
	m_type = std::string();
}

void Region::SetScore(int score)
{
	m_score = score;
}

void Region::SetName(const std::string& name)
{
	m_name = name;
}

void Region::SetOwner(const std::string& owner)
{
	m_owner = owner;
}

void Region::SetType(const std::string& type)
{
	m_type = type;
}

int Region::GetScore() const
{
	return m_score;
}

std::string Region::GetName() const
{
	return m_name;
}

std::string Region::GetOwner() const
{
	return m_owner;
}

std::string Region::GetType() const
{
	return m_type;
}
