#pragma once

#include "Enums.h"
#include "Skill.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API SkillSet
{
public:

	SkillSet() { };

	const Skill* getSkill(SkillCategory slot) const;
	void setSkill(const Skill* skill);

protected:
	Skill const* m_skills[7] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
};

#pragma warning( pop ) 
