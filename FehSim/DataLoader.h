#pragma once

#include <string>
#include <map>
#include <vector>
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

	std::vector<std::string> m_unitNames;

public:
	DataLoader();
	~DataLoader();

	UnitData* getUnitData(std::string unitID);
	Weapon* getWeaponData(std::string unitID);

	std::vector<std::string>& getUnitNames();

private:
	UnitData unitDataFromFile(std::string filePath);
	Weapon weaponDataFromFile(std::string filePath);
};

#pragma warning( pop )
