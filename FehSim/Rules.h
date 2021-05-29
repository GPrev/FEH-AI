#pragma once

#include "Map.h"

class FEHSIM_API Rules
{
public:
	Rules();

	static void doBattle(Map& map, const Unit* _attacker, const Unit* _defender);

private:
	static Stats getCombatBuffs(Map& map, const Unit* _unit, const Unit* _enemy, bool _isAttacker);
	static bool isSkillActive(Map& map, const Unit* _unit, const Unit* _enemy, bool _isAttacker, const Skill* skill);
	static bool isSkillLimitActive(Map& map, const Unit* _unit, const Unit* _enemy, bool _isAttacker, int limitId);
	static void strike(UnitState& _attacker, UnitState& _defender, Stats& _attStats, Stats& _defStats);
	static int effective(UnitState& _attacker, UnitState& _defender);
	static int weaponTriangle(UnitState& _attacker, UnitState& _defender);
	static int weaponTriangle(UnitColor _attacker, UnitColor _defender);
	static bool targetsRes(WeaponType weapon);
};

