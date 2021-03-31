#pragma once

#include <vector>
#include <algorithm>
#include "FehSim.h"
#include "UnitData.h"
#include "SkillSet.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Unit
{
private:
	UnitData* m_data;

	int m_rarity = 5;
	int m_merges = 0;

	SkillSet m_skills;

public:
	Unit() {}
	Unit(UnitData& data) : m_data(&data) {}
	~Unit() {};

	void makeBaseKit();
	void makeFullKit();

	const UnitData* getData() const { return m_data; }

	WeaponType getWeaponType() { return m_data->getWeaponType(); }
	UnitColor getColor() { return m_data->getColor(); }
	Stats getStats() { return m_data->getBaseStats() + Stats::atkStat(m_skills.getSkill(SkillCategory::WEAPON) == nullptr ? 0 : m_skills.getSkill(SkillCategory::WEAPON)->getMight()); }
	int getMvt()   { return getMvtRange(m_data->getMvtType()); } // TODO consider mvt types
	int getRange() { return getAttackRange(m_data->getWeaponType()); }
	bool canAttack() { return m_skills.getSkill(SkillCategory::WEAPON) != nullptr; }
	bool canCC()   { return getRange() == 1; } // TODO consider weapon and skills
	bool canDC()   { return getRange() == 2; } // TODO consider weapon and skills
	bool canCounter(int range) { return (range == 1 && canCC()) || (range == 2 && canDC()); }

	const SkillSet& getSkills() const { return m_skills; }
	Skill const* getSkill(SkillCategory slot) const { return m_skills.getSkill(slot); }

};

typedef std::vector<Unit> Team;

#pragma warning( pop ) 
