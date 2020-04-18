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

UnitData* DataLoader::GetUnitData(std::string unitID)
{
	if (m_units.count(unitID) == 0)
	{
		try
		{
			m_units[unitID] = UnitDataFromFile(m_heroDataPath + unitID + ".json");
		}
		catch (...)
		{
			return nullptr;
		}
	}

	return &m_units.at(unitID);
}

UnitData DataLoader::UnitDataFromFile(std::string filePath)
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

	return d;
}