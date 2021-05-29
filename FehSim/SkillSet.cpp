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

void SkillSet::setSkillIfMoreExpensive(const Skill* skill)
{
	const Skill* previousSkill = getSkill(skill->getCategory());
	if (previousSkill == nullptr || previousSkill->getSpCost() < skill->getSpCost())
	{
		setSkill(skill);
	}
}

void SkillSet::addAll(const SkillSet& skills)
{
	for (const Skill* s : skills.m_skills)
	{
		if (s != nullptr)
		{
			setSkill(s);
		}
	}
}

void SkillSet::addAllIfMoreExpensive(const SkillSet& skills)
{
	for (const Skill* s : skills.m_skills)
	{
		if (s != nullptr)
		{
			setSkillIfMoreExpensive(s);
		}
	}
}