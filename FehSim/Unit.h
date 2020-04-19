#pragma once

#include <algorithm>
#include "FehSim.h"
#include "UnitData.h"
#include "Weapon.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Unit
{
private:
	UnitData* m_data;

	int m_stars = 5;
	int m_merges = 0;

	Weapon* m_weapon = nullptr;

public:
	Unit() {}
	Unit(UnitData& data) : m_data(&data) {}
	~Unit() {};

	void makeBaseKit(DataLoader& loader);

	const UnitData* getData() const { return m_data; }

	int getMaxHP() { return m_data->getBaseHP(); }
	int getAtk() { return m_data->getBaseAtk() + (m_weapon == nullptr ? 0 : m_weapon->getMight()); }
	int getSpd()   { return m_data->getBaseSpd(); }
	int getDef()   { return m_data->getBaseDef(); }
	int getRes()   { return m_data->getBaseRes(); }
	int getMvt()   { return getMvtRange(m_data->getMvtType()); } // TODO consider mvt types
	int getRange() { return getAttackRange(m_data->getWeaponType()); }
	bool canAttack() { return m_weapon != nullptr; }
	bool canCC()   { return true; } // TODO consider weapon and skills
	bool canDC()   { return false; } // TODO consider weapon and skills

	Weapon* getWeapon() { return m_weapon; }

};

#pragma warning( pop ) 
