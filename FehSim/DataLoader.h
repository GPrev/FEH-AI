#pragma once

#include <string>
#include <map>
#include <vector>
#include "json.hpp"
#include "UnitData.h"
#include "Weapon.h"
#include "Skill.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API DataLoader
{
private:
	std::string m_heroDataPath = "../../feh-assets-json/files/assets/Common/SRPG/Person/";
	std::string m_skillDataPath = "../../feh-assets-json/files/assets/Common/SRPG/Skill/";

	std::map<std::string, UnitData> m_units;
	std::map<std::string, Weapon> m_weapons;
	std::map<std::string, Skill> m_skills;

	std::vector<std::string> m_unitNames;

public:
	DataLoader(bool loadNow = false);

	UnitData* getUnitData(std::string unitID);
	Skill* getSkillData(std::string unitID);

	std::vector<std::string>& getUnitNames(); // Used to pick random units

private:
	Stats statsFromJson(const nlohmann::json& j);

	void loadAllUnits();
	void unitDataFromFile(std::string filePath);
	void unitDataFromJson(const nlohmann::json& j);

	void loadAllSkills();
	void skillDataFromFile(std::string filePath);
	void skillDataFromJson(const nlohmann::json& j);
};

#pragma warning( pop )
