#pragma once

#include "Enums.h"
#include "Skill.h"
#include <numeric>

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API SkillSet
{
public:

	SkillSet() { };

	const Skill* getSkill(SkillCategory slot) const;
	void setSkill(const Skill* skill);

	int getWeaponEffectiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponEffectiveMask()); });
	}
	int getMovementEffectiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementEffectiveMask()); });
	}
	int getWeaponProtectionMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponProtectionMask()); });
	}
	int getMovementProtectionMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementProtectionMask()); });
	}
	int getWeaponWeaknessMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponWeaknessMask()); });
	}
	int getMovementWeaknessMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementWeaknessMask()); });
	}
	int getWeaponAdaptiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponAdaptiveMask()); });
	}
	int getMovementAdaptiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementAdaptiveMask()); });
	}

protected:
	Skill const* m_skills[7] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
};

#pragma warning( pop ) 
