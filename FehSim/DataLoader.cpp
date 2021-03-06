#include "DataLoader.h"
#include "json.hpp"
#include <fstream>
#include <string>
#include <sstream>

using json = nlohmann::json;


DataLoader::DataLoader()
{
}


DataLoader::~DataLoader()
{
}

UnitData* DataLoader::getUnitData(std::string unitID)
{
	if (m_units.count(unitID) == 0)
	{
		try
		{
			m_units[unitID] = unitDataFromFile(m_heroDataPath + unitID + ".json");
		}
		catch (...)
		{
			return nullptr;
		}
	}

	return &m_units.at(unitID);
}

UnitData DataLoader::unitDataFromFile(std::string filePath)
{
	std::ifstream i(filePath);
	json j;
	i >> j;

	UnitData d;

	d.m_name = j["name"];

	std::string weapontypeStr, colorStr;
	std::string s = j["weaponType"];
	std::istringstream iss(s);
	iss >> colorStr >> weapontypeStr;
	std::string mvtTypeStr = j["moveType"];

	d.m_color = unitColorFromString (colorStr);
	d.m_type  = weaponTypeFromString(weapontypeStr);
	d.m_mvt   = mvtTypeFromString   (mvtTypeStr);

	d.m_baseHP  = j["maxStats"]["5"]["hp"]["base"];
	d.m_baseAtk = j["maxStats"]["5"]["atk"]["base"];
	d.m_baseSpd = j["maxStats"]["5"]["spd"]["base"];
	d.m_baseDef = j["maxStats"]["5"]["def"]["base"];
	d.m_baseRes = j["maxStats"]["5"]["res"]["base"];

	std::string weaponStr = j["weapon"][0]["_id"];
	d.m_defaultWeaponID = weaponStr.substr(7);

	return d;
}

Weapon* DataLoader::getWeaponData(std::string weaponID)
{
	if (m_weapons.count(weaponID) == 0)
	{
		try
		{
			m_weapons[weaponID] = weaponDataFromFile(m_weaponDataPath + weaponID + ".json");
		}
		catch (...)
		{
			return nullptr;
		}
	}

	return &m_weapons.at(weaponID);
}

Weapon DataLoader::weaponDataFromFile(std::string filePath)
{
	std::ifstream i(filePath);
	json j;
	i >> j;

	Weapon w;

	w.m_name = j["name"];
	w.m_might = j["might"];

	return w;
}

std::vector<std::string>& DataLoader::getUnitNames()
{
	if (m_unitNames.size() == 0)
	{
		std::string path = m_heroDataPath + "_heroes.txt";
		std::ifstream i(path);

		for (std::string name; std::getline(i, name); )
		{
			m_unitNames.push_back(name);
		}
	}
	return m_unitNames;
}
