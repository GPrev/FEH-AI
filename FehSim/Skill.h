#pragma once

#include <string>
#include "Enums.h"
#include "FehSim.h"
#include "Stats.h"
#include "Translator.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Skill
{
	friend class DataLoader;

protected:
	std::string m_id;
	std::string m_name;

	SkillCategory m_category;

	Stats m_stats;
	int m_might;

public:
	Skill() {};

	std::string getId() const { return m_id; }
	std::string getName() const { return m_name; }
	std::string getName(Translator& t)	const { return t.translate(getName()); }
	SkillCategory getCategory() const { return m_category; }
	int getMight() const { return m_might; }
	const Stats& getStats() const { return m_stats; }
};

#pragma warning( pop ) 
