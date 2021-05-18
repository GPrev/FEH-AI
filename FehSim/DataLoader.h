#pragma once

#include <string>
#include <map>
#include <vector>
#include "json.hpp"
#include "UnitData.h"
#include "Weapon.h"
#include "Skill.h"
#include "SkillSet.h"
#include "MapData.h"
#include "Terrain.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API DataLoader
{
private:
	std::string m_heroDataPath = "../../feh-assets-json/files/assets/Common/SRPG/Person/";
	std::string m_enemyDataPath = "../../feh-assets-json/files/assets/Common/SRPG/Enemy/";
	std::string m_skillDataPath = "../../feh-assets-json/files/assets/Common/SRPG/Skill/";
	std::string m_mapDataPath = "../../feh-assets-json/files/assets/Common/SRPGMap/";
	std::string m_terrainDataPath = "../../feh-assets-json/files/assets/Common/SRPG/Terrain.json";

	std::map<std::string, UnitData> m_units;
	std::map<std::string, Weapon> m_weapons;
	std::map<std::string, Skill> m_skills;
	std::map<std::string, MapData> m_maps;
	std::vector<Terrain> m_terrain;

	std::vector<std::string> m_unitNames;
	std::vector<std::string> m_mapNames;

public:
	DataLoader(bool loadNow = false);

	UnitData* getUnitData(std::string unitID);
	Skill* getSkillData(std::string skillID);
	MapData* getMapData(std::string mapID);
	Terrain* getTerrain(int terrainID);

	std::vector<std::string>& getUnitNames(); // Used to pick random units
	std::vector<std::string>& getMapNames();

private:
	Stats statsFromJson(const nlohmann::json& j);
	Position DataLoader::positionFromJson(const nlohmann::json& j);

	void loadAllUnits();
	void unitDataFromFile(std::string filePath, bool playable);
	void unitDataFromJson(const nlohmann::json& j, bool playable);

	void loadAllSkills();
	void skillDataFromFile(std::string filePath);
	void skillDataFromJson(const nlohmann::json& j);

	SkillSet skillSetFromJson(const nlohmann::json& j);
	std::pair<SkillSet, SkillSet> twoSkillSetsFromJson(const nlohmann::json& j);

	void loadAllMapNames();
	void loadAllMaps();
	void mapDataFromFile(std::string filePath);
	void mapDataFromJson(const nlohmann::json& j);
	std::pair<Position, Unit> mapDataUnitFromJson(const nlohmann::json& j);

	void loadAllTerrain();
	void terrainFromJson(const nlohmann::json& j);
};

#pragma warning( pop )
