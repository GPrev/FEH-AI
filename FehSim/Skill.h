#pragma once

#include <string>
#include "Enums.h"
#include "FehSim.h"
#include "Stats.h"
#include "Translator.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Skill
{
	friend class DataLoader;

protected:
	std::string m_id;
	std::string m_name;

	SkillCategory m_category = SkillCategory::WEAPON;

	Stats m_stats;
	int m_might = 0;

	int m_wepEffective	= 0; // A bitmask indexed by weapon_index, representing weapon class effectivenesses this skill grants. Only meaningful on weapon skills.
	int m_movEffective	= 0; // A bitmask indexed by move_index, representing movement class effectivenesses this skill grants. Only meaningful on weapon skills.
	int wep_shield		= 0; // A bitmask indexed by weapon_index, representing weapon class effectivenesses this skill protects from.Used by Icon Skill Weapon.png Breath of Blight.
	int mov_shield		= 0; // A bitmask indexed by move_index, representing movement class effectivenesses this skill protects from.
	int wep_weakness	= 0; // A bitmask indexed by weapon_index, representing weapon class weaknesses this skill grants.Used by Icon Class Red Tome.png Loptous.
	int mov_weakness	= 0; // A bitmask indexed by move_index, representing movement class weaknesses this skill grants.Currently unused.
	int wep_adaptive	= 0; // A bitmask indexed by weapon_index, representing weapon classes that receive damage from this skill calculated using the lower of Def or Res.Used by breaths.Only meaningful on weapon skills.
	int mov_adaptive	= 0; // A bitmask indexed by move_index, representing movement classes that receive damage from this skill calculated using the lower of Def or Res.Currently unused.Only meaningful on weapon skills.

public:
	Skill() {};

	std::string getId() const { return m_id; }
	std::string getName() const { return m_name; }
	std::string getName(Translator& t)	const { return t.translate(getName()); }
	SkillCategory getCategory() const { return m_category; }

	int getMight() const { return m_might; }
	const Stats& getStats() const { return m_stats; }

	int getWeaponEffectiveMask()	const { return m_wepEffective; }
	int getMovementEffectiveMask()	const { return m_movEffective; }
	int getWeaponProtectionMask()	const { return wep_shield; }
	int getMovementProtectionMask()	const { return mov_shield; }
	int getWeaponWeaknessMask()		const { return wep_weakness; }
	int getMovementWeaknessMask()	const { return mov_weakness; }
	int getWeaponAdaptiveMask()		const { return wep_adaptive; }
	int getMovementAdaptiveMask()	const { return mov_adaptive; }

};

#pragma warning( pop ) 
