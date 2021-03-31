#include <stdexcept>
#include "SkillSet.h"

const Skill* SkillSet::getSkill(SkillCategory slot) const
{
	return m_skills[(int)slot];
}

void SkillSet::setSkill(const Skill* skill)
{
	if ((int)skill->getCategory() > 6)
	{
		throw std::exception("Cannot put this skill in a skill set");
	}
	m_skills[(int)skill->getCategory()] = skill;
}