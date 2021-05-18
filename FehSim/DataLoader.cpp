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

MapData* DataLoader::getMapData(std::string mapID)
{
	if (m_maps.count(mapID) == 0)
	{
		try
		{
			mapDataFromFile(m_mapDataPath + mapID + ".json");
		}
		catch (...)
		{
			return nullptr;
		}
	}

	return &m_maps.at(mapID);
}

Terrain* DataLoader::getTerrain(int terrainID)
{
	if (m_terrain.size() == 0)
	{
		loadAllTerrain();
	}

	if (m_terrain.size() > terrainID)
		return &m_terrain.at(terrainID);
	else
		return nullptr;
}

std::vector<std::string>& DataLoader::getUnitNames()
{
	loadAllUnits();
	return m_unitNames;
}

std::vector<std::string>& DataLoader::getMapNames()
{
	loadAllMapNames();
	return m_mapNames;
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
			 unitDataFromFile(file.path().string(), true);
		}
		for (const auto& file : directory_iterator(m_enemyDataPath))
		{
			unitDataFromFile(file.path().string(), false);
		}
	}
}

void DataLoader::unitDataFromFile(std::string filePath, bool playable)
{
	std::ifstream i(filePath);
	json j;
	i >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		unitDataFromJson(*it, playable);
	}
}

void DataLoader::unitDataFromJson(const json& j, bool playable)
{
	std::string unitID = j["id_tag"];

	m_unitNames.push_back(unitID);

	UnitData& d = m_units[unitID];
	d = UnitData();

	d.m_id = unitID;
	d.m_name = "M" + unitID; // Not found elsewhere to my knowledge

	d.m_playable = playable;

	d.m_weaponIdx = (WeaponIndex)j["weapon_type"];
	d.m_color = getWeaponColor(d.m_weaponIdx);
	d.m_type = getWeaponType(d.m_weaponIdx);
	d.m_mvt = (MvtType)j["move_type"];

	d.m_baseStats = statsFromJson(j["base_stats"]);
	d.m_growths = statsFromJson(j["growth_rates"]);

	// Only playable units can learn skills
	if (playable)
	{
		for (int i = 0; i < 5; ++i)
		{
			std::pair<SkillSet, SkillSet> skillSets = twoSkillSetsFromJson(j["skills"][i]);
			d.m_learnedSkills[i] = skillSets.first;
			d.m_learnableSkills[i] = skillSets.second;
		}
	}
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

	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		skillDataFromJson(*it);
	}
}

void DataLoader::skillDataFromJson(const json& j)
{
	std::string skillID = j["id_tag"];

	Skill& d = m_skills[skillID];
	d = Skill();

	d.m_id = skillID;
	d.m_name = j["name_id"];
	d.m_category = j["category"];
	d.m_stats = statsFromJson(j["stats"]);
	d.m_might = j["might"];
}

SkillSet DataLoader::skillSetFromJson(const json& j)
{
	SkillSet ss;
	for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it)
	{
		if (it->is_string())
		{
			Skill* skillData = getSkillData(it->get<std::string>());
			ss.setSkill(skillData);
		}
	}
	return ss;
}

std::pair<SkillSet, SkillSet> DataLoader::twoSkillSetsFromJson(const json& j)
{
	SkillSet ss1;
	SkillSet ss2;
	int i = 0;
	for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it)
	{
		i++;
		if (it->is_string())
		{
			Skill* skillData = getSkillData(it->get<std::string>());
			if (i < 7)
			{
				// First set has only the 7 first skills
				ss1.setSkill(skillData);
			}
			// Second set has all of the skills
			ss2.setSkill(skillData);
		}
	}
	return std::pair<SkillSet, SkillSet>(ss1, ss2);
}

void DataLoader::loadAllMapNames()
{
	if (m_mapNames.size() == 0)
	{
		for (const auto& file : directory_iterator(m_mapDataPath))
		{
			m_mapNames.push_back(file.path().stem().string());
		}
	}
}

void DataLoader::loadAllMaps()
{
	if (m_maps.size() == 0)
	{
		for (const auto& file : directory_iterator(m_mapDataPath))
		{
			mapDataFromFile(file.path().string());
		}
	}
}

void DataLoader::mapDataFromFile(std::string filePath)
{
	std::ifstream i(filePath);
	json j;
	i >> j;
	mapDataFromJson(j);
}

void DataLoader::mapDataFromJson(const json& j)
{
	const json& jField = j["field"];

	std::string mapID = jField["id"];

	int width = jField["width"];
	int height = jField["height"];

	const json& jTerrain = jField["terrain"];
	std::vector<std::vector<const Terrain*>> terrain(height);
	int x = 0;
	for (json::const_iterator itRow = jTerrain.cbegin(); itRow != jTerrain.cend(); ++itRow)
	{
		terrain[x] = std::vector<const Terrain*>(width);
		std::vector<const Terrain*>& row = terrain[x];
		x++;
		row = std::vector<const Terrain*>(width);
		int y = 0;
		for (json::const_iterator itCol = itRow->cbegin(); itCol != itRow->cend(); ++itCol)
		{
			int terrainID = itCol->get<int>();
			row[y] = getTerrain(terrainID);
			y++;
		}
	}

	int allyCount = j["player_count"];
	std::vector<Position> allyPos(allyCount);
	const json& jAllies = j["player_pos"];
	int i = 0;
	for (json::const_iterator it = jAllies.cbegin(); it != jAllies.cend(); ++it)
	{
		allyPos[i] = positionFromJson(*it);
		i++;
	}

	int foeCount = j["unit_count"];
	std::vector<Unit> foes(foeCount);
	std::vector<Position> foesPos(foeCount);
	const json& jFoes = j["units"];
	i = 0;
	for (json::const_iterator it = jFoes.cbegin(); it != jFoes.cend(); ++it)
	{
		std::pair<Position, Unit> foe = mapDataUnitFromJson(*it);
		foesPos[i] = foe.first;
		foes[i] = foe.second;
		i++;
	}

	MapData& data = m_maps[mapID];
	data = MapData(mapID, width, height, allyPos, foesPos, foes);

	data.m_terrain = terrain;

	data.m_turnsToWin		= j["turns_to_win"];
	data.m_lastEnemyPhase	= j["last_enemy_phase"];
	data.m_turnsToDefend	= j["turns_to_defend"];
}

Position DataLoader::positionFromJson(const json& j)
{
	return Position(j["x"], j["y"]);
}

std::pair<Position, Unit> DataLoader::mapDataUnitFromJson(const json& j)
{
	Position pos = positionFromJson(j["pos"]);

	Unit u;

	std::string unitID = j["id_tag"];

	u.m_data = getUnitData(unitID);

	u.m_rarity = j["rarity"];
	u.m_level = j["lv"];
	u.m_stats = statsFromJson(j["stats"]);
	u.m_skills = skillSetFromJson(j["skills"]);

	return std::pair<Position, Unit>(pos, u);
}

void DataLoader::loadAllTerrain()
{
	std::ifstream i(m_terrainDataPath);
	json j;
	i >> j;

	// Resize once to save time
	m_terrain.resize(j.size());

	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		terrainFromJson(*it);
	}
}

void DataLoader::terrainFromJson(const json& j)
{
	int terrainID = j["index"];

	// Makes sure we don't go out of bounds
	if (m_terrain.size() <= terrainID)
	{
		m_terrain.resize(terrainID + 1);
	}

	Terrain& t = m_terrain[terrainID];
	t.m_index = terrainID;
	t.m_baseTerrain = j["base_terrain"];
	t.m_foeBaseTerrain = j["foe_base_terrain"];
	t.m_side = j["side"];
	t.m_terrainGroup = j["terrain_group"];
	t.m_inaccessible = j["inaccessible"];
	t.m_hp = j["hp"];
	t.m_isWall = j["is_wall"];
	t.m_isLiquid = j["is_liquid"];
	t.m_isBridge = j["is_bridge"];
	t.m_isTrench = j["is_trench"];
	t.m_isFortress = j["is_fortress"];
	t.m_isRdTerrain = j["is_rd_terrain"];
	t.m_mitMod = j["mit_mod"];
	t.m_regenHp = j["regen_hp"];
}