#pragma once

#include <string>
#include "Enums.h"
#include "FehSim.h"
#include "Stats.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Skill
{
	friend class DataLoader;

protected:
	std::string m_id;
	std::string m_name;

	Stats m_stats;
	int m_might;

public:
	Skill() {};

	std::string getName() const { return m_name; }
	int getMight() const { return m_might; }
	const Stats& getStats() const { return m_stats; }
};

