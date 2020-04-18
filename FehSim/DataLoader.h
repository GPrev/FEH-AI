#pragma once

#include <string>
#include <map>
#include "UnitData.h"
#include "Weapon.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API DataLoader
{
private:
	std::string m_heroDataPath = "../../kagerochart-data/hero/";
	std::string m_weaponDataPath = "../../kagerochart-data/weapon/";

	std::map<std::string, UnitData> m_units;
	std::map<std::string, Weapon> m_weapons;

public:
	DataLoader();
	~DataLoader();

	UnitData* GetUnitData(std::string unitID);
	Weapon* GetWeaponData(std::string unitID);

private:
	UnitData UnitDataFromFile(std::string filePath);
	Weapon WeaponDataFromFile(std::string filePath);
};

#pragma warning( pop )
