#include "Unit.h"
#include "DataLoader.h"

void Unit::makeBaseKit()
{
	m_skills = m_data->getLearnedSkills(m_rarity);
}

void Unit::makeFullKit()
{
	m_skills = m_data->getLearnableSkills(m_rarity);
}