#pragma once

#include <vector>
#include <algorithm>
#include "FehSim.h"
#include "UnitData.h"
#include "Skill.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Unit
{
private:
	UnitData* m_data;

	int m_stars = 5;
	int m_merges = 0;

	Skill* m_weapon = nullptr;

public:
	Unit() {}
	Unit(UnitData& data) : m_data(&data) {}
	~Unit() {};

	void makeBaseKit(DataLoader& loader);

	const UnitData* getData() const { return m_data; }

	WeaponType getWeaponType() { return m_data->getWeaponType(); }
	UnitColor getColor() { return m_data->getColor(); }
	Stats getStats() { return m_data->getBaseStats() + Stats::atkStat(m_weapon == nullptr ? 0 : m_weapon->getMight()); }
	int getMvt()   { return getMvtRange(m_data->getMvtType()); } // TODO consider mvt types
	int getRange() { return getAttackRange(m_data->getWeaponType()); }
	bool canAttack() { return m_weapon != nullptr; }
	bool canCC()   { return getRange() == 1; } // TODO consider weapon and skills
	bool canDC()   { return getRange() == 2; } // TODO consider weapon and skills
	bool canCounter(int range) { return (range == 1 && canCC()) || (range == 2 && canDC()); }

	Skill* getWeapon() { return m_weapon; }

};

typedef std::vector<Unit> Team;

#pragma warning( pop ) 
