#pragma once

#include <string>

class Weapon
{
	friend class DataLoader;

public:
	Weapon();
	~Weapon();

	std::string getName() const { return m_name; }
	int getMight() const { return m_might; }

protected:
	std::string m_name;
	int m_might;
};

