#include "DataLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

using json = nlohmann::json;
using std::filesystem::directory_iterator;


DataLoader::DataLoader(bool loadNow)
{
	if (loadNow)
	{
		loadAllUnits();
		loadAllSkills();
	}
}

UnitData* DataLoader::getUnitData(std::string unitID)
{
	if (m_units.size() == 0)
	{
		getUnitNames();
	}

	if(MAP_CONTAINS_KEY(m_units, unitID))
		return &m_units.at(unitID);
	else
		return nullptr;
}

Skill* DataLoader::getSkillData(std::string skillID)
{
	if (m_skills.size() == 0)
	{
		loadAllSkills();
	}

	if (MAP_CONTAINS_KEY(m_skills, skillID))
		return &m_skills.at(skillID);
	else
		return nullptr;
}

std::vector<std::string>& DataLoader::getUnitNames()
{
	loadAllUnits();
	return m_unitNames;
}

Stats DataLoader::statsFromJson(const json& j)
{
	return Stats(j["hp"], j["atk"], j["spd"], j["def"], j["res"]);
}

void DataLoader::loadAllUnits()
{
	if (m_units.size() == 0)
	{
		for (const auto& file : directory_iterator(m_heroDataPath))
		{
			unitDataFromFile(file.path().string());
		}
	}
}

void DataLoader::unitDataFromFile(std::string filePath)
{
	std::ifstream i(filePath);
	json j;
	i >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		unitDataFromJson(*it);
	}
}

void DataLoader::unitDataFromJson(const json& j)
{
	std::string unitID = j["id_tag"];

	UnitData& d = m_units[unitID];
	d = UnitData();

	d.m_id = unitID;
	d.m_name = j["roman"]; // TODO use translation file

	d.m_weaponIdx = (WeaponIndex)j["weapon_type"];
	d.m_color = getWeaponColor(d.m_weaponIdx);
	d.m_type = getWeaponType(d.m_weaponIdx);
	d.m_mvt = (MvtType)j["move_type"];

	d.m_baseStats = statsFromJson(j["base_stats"]);
	d.m_growths = statsFromJson(j["growth_rates"]);
}

void DataLoader::loadAllSkills()
{
	if (m_skills.size() == 0)
	{
		for (const auto& file : directory_iterator(m_skillDataPath))
		{
			skillDataFromFile(file.path().string());
		}
	}
}

void DataLoader::skillDataFromFile(std::string filePath)
{
	std::ifstream i(filePath);
	json j;
	i >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		skillDataFromJson(*it);
	}
}

void DataLoader::skillDataFromJson(const json& j)
{
	std::string unitID = j["id_tag"];

	Skill& d = m_skills[unitID];
	d = Skill();

	d.m_id = unitID;
	d.m_name = j["name_id"]; // TODO use translation file
	d.m_stats = statsFromJson(j["stats"]);
	d.m_might = j["might"];
}