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

	int m_level = 40;
	int m_rarity = 5;
	int m_merges = 0;
	StatNames m_boon;
	StatNames m_bane;

	Stats m_stats;
	SkillSet m_skills;

public:
	Unit() {}
	Unit(UnitData& data, int rarity = 5, int level = 40, int merges = 0, StatNames boon = StatNames::NONE, StatNames bane = StatNames::NONE);
	~Unit() {};

	void makeBaseKit();
	void makeFullKit();

	const UnitData* getData() const { return m_data; }

	WeaponType getWeaponType() const { return m_data->getWeaponType(); }
	UnitColor getColor() const		{ return m_data->getColor(); }
	Stats getStats() const	{ return m_stats + Stats::atkStat(m_skills.getSkill(SkillCategory::WEAPON) == nullptr ? 0 : m_skills.getSkill(SkillCategory::WEAPON)->getMight()); }
	int getMvt() const   { return getMvtRange(m_data->getMvtType()); } // TODO consider mvt types
	int getRange() const { return getAttackRange(m_data->getWeaponType()); }
	bool canAttack() const { return m_skills.getSkill(SkillCategory::WEAPON) != nullptr; }
	bool canCC() const   { return getRange() == 1; } // TODO consider weapon and skills
	bool canDC() const   { return getRange() == 2; } // TODO consider weapon and skills
	bool canCounter(int range) const { return (range == 1 && canCC()) || (range == 2 && canDC()); }

	const SkillSet& getSkills() const { return m_skills; }
	Skill const* getSkill(SkillCategory slot) const { return m_skills.getSkill(slot); }

};

typedef std::vector<Unit> Team;

#pragma warning( pop ) 
