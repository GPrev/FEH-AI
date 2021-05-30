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
	friend class DataLoader;

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
	UnitColor getColor() const { return m_data->getColor(); }
	MvtType getMvtType() const { return m_data->getMvtType(); }

	Stats getStats() const	{ return m_stats + Stats::atkStat(m_skills.getSkill(SkillCategory::WEAPON) == nullptr ? 0 : m_skills.getSkill(SkillCategory::WEAPON)->getMight()); }
	int getMvt() const   { return getMvtRange(m_data->getMvtType()); } // TODO consider mvt types
	int getRange() const { return getAttackRange(m_data->getWeaponType()); }
	bool canAttack() const { return m_skills.getSkill(SkillCategory::WEAPON) != nullptr; }
	bool canCC() const   { return getRange() == 1; } // TODO consider weapon and skills
	bool canDC() const   { return getRange() == 2; } // TODO consider weapon and skills
	bool canCounter(int range) const { return (range == 1 && canCC()) || (range == 2 && canDC()); }

	const SkillSet& getSkills() const { return m_skills; }
	Skill const* getSkill(SkillCategory slot) const { return m_skills.getSkill(slot); }
	bool hasSkill(SkillCategory slot) const { return m_skills.hasSkill(slot); }
	void setSkill(const Skill* skill) { return m_skills.setSkill(skill); }
	void removeSkill(SkillCategory slot) { return m_skills.removeSkill(slot); }

	int getWeaponEffectiveMask()	const { return m_skills.getWeaponEffectiveMask(); }
	int getMovementEffectiveMask()	const { return m_skills.getMovementEffectiveMask(); }
	int getWeaponProtectionMask()	const { return m_skills.getWeaponProtectionMask(); }
	int getMovementProtectionMask()	const { return m_skills.getMovementProtectionMask(); }
	int getWeaponWeaknessMask()		const { return m_skills.getWeaponWeaknessMask() | (1 << m_data->getWeaponIndex()); }
	int getMovementWeaknessMask()	const { return m_skills.getMovementWeaknessMask() | (1 << m_data->getMvtType()); }
	int getWeaponAdaptiveMask()		const { return m_skills.getWeaponAdaptiveMask(); }
	int getMovementAdaptiveMask()	const { return m_skills.getMovementAdaptiveMask(); }
};

typedef std::vector<Unit> Team;

#pragma warning( pop ) 
