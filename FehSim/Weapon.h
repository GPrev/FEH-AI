#pragma once

#include <string>

class Weapon
{
	friend class DataLoader;

public:
	Weapon();
	~Weapon();

	std::string getName() { return m_name; }
	int getMight() { return m_might; }

protected:
	std::string m_name;
	int m_might;
};

