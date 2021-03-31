#pragma once

#include <string>
#include "Enums.h"
#include "FehSim.h"
#include "Stats.h"
#include "SkillSet.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API UnitData
{
	friend class DataLoader;

protected:
	std::string m_id;
	std::string m_name;

	WeaponIndex m_weaponIdx;
	UnitColor m_color;
	WeaponType m_type;
	MvtType m_mvt;

	Stats m_baseStats;
	Stats m_growths;

	SkillSet m_learnedSkills[5] = { SkillSet(), SkillSet(), SkillSet(), SkillSet(), SkillSet() };
	SkillSet m_learnableSkills[5] = { SkillSet(), SkillSet(), SkillSet(), SkillSet(), SkillSet() };

public:
	UnitData() {}

	std::string getName() const { return m_name; }

	UnitColor getColor() const { return m_color; }
	WeaponType getWeaponType() const { return m_type; }
	MvtType getMvtType() const { return m_mvt; }

	const Stats& getBaseStats() const { return m_baseStats; }

	const SkillSet& getLearnedSkills(int nbStar) const { return m_learnedSkills[nbStar - 1]; }
	const SkillSet& getLearnableSkills(int nbStar) const { return m_learnableSkills[nbStar - 1]; }
};

#pragma warning( pop ) 
