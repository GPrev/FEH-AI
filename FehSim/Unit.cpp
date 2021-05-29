#include "Unit.h"
#include "DataLoader.h"
#include "StatGrowth.h"

Unit::Unit(UnitData& data, int rarity, int level, int merges, StatNames boon, StatNames bane)
	: m_data(&data), m_rarity(rarity), m_level(level), m_merges(merges), m_boon(boon), m_bane(bane)
{
	m_stats = StatGrowth::getStats(data, rarity, level, merges);
}

void Unit::makeBaseKit()
{
	m_skills = m_data->getLearnedSkills(m_rarity);
}

void Unit::makeFullKit()
{
	// Start with the base kit
	makeBaseKit();
	// We miss some skills if we don't go through every rarity
	for (int rarity = 1; rarity < m_rarity; ++rarity)
	{
		m_skills.addAllIfMoreExpensive(m_data->getLearnableSkills(rarity));
	}
}