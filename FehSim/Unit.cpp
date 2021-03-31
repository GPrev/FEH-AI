#include "Unit.h"
#include "DataLoader.h"
#include "StatGrowth.h"

Unit::Unit(UnitData& data, int rarity, int level, int merges, StatNames boon, StatNames bane)
	: m_data(&data), m_rarity(rarity), m_level(level), m_merges(merges), m_boon(boon), m_bane(bane)
{
	m_stats = StatGrowth::getStats(data, rarity, level);
}

void Unit::makeBaseKit()
{
	m_skills = m_data->getLearnedSkills(m_rarity);
}

void Unit::makeFullKit()
{
	m_skills = m_data->getLearnableSkills(m_rarity);
}