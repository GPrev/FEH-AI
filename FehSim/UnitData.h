#pragma once

#include <string>
#include "Enums.h"
#include "FehSim.h"
#include "Stats.h"

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

	std::string m_defaultWeaponID;

public:
	UnitData() {}

	std::string getName() const { return m_name; }

	UnitColor getColor() const { return m_color; }
	WeaponType getWeaponType() const { return m_type; }
	MvtType getMvtType() const { return m_mvt; }

	const Stats& getBaseStats() const { return m_baseStats; }

	std::string getDefaultWeaponID() { return m_defaultWeaponID; }
};

#pragma warning( pop ) 
