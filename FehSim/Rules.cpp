#include <cmath>
#include "Rules.h"


Rules::Rules()
{
}

void Rules::doBattle(Map& map, const Unit* _attacker, const Unit* _defender)
{
	UnitState& attState = map.getState(_attacker);
	Stats attStats = attState.getStats();
	UnitState& defState = map.getState(_defender);
	Stats defStats = defState.getStats();
	bool canCounter = _defender->canCounter(_attacker->getRange());
	bool attackerDoubles = (attStats.getSpd() >= defStats.getSpd() + 4);
	bool defenderDoubles = canCounter && (defStats.getSpd() >= attStats.getSpd() + 4);
	strike(attState, defState, attStats, defStats);
	if (canCounter)
	{
		strike(defState, attState, defStats, attStats);
		defenderDoubles = (defStats.getSpd() >= attStats.getSpd() + 4);
	}
	if (attackerDoubles)
	{
		strike(attState, defState, attStats, defStats);
	}
	if (defenderDoubles)
	{
		strike(defState, attState, defStats, attStats);
	}
}

void Rules::strike(UnitState& _attacker, UnitState& _defender, Stats& _attStats, Stats& _defStats)
{
	if (!_attacker.isDead())
	{
		int atkEff = (int) std::floor(_attStats.getAtk() * (1.0 + 0.5 * effective(_attacker, _defender)));
		int attackPower = atkEff + (int) std::trunc(atkEff * .2 * weaponTriangle(_attacker, _defender));
		bool targetsRes = Rules::targetsRes(_attacker.getUnit()->getWeaponType());
		int defensePower = _defStats.getDef();
		if (targetsRes)
		{
			defensePower = _defStats.getRes();
		}
		_defender.loseLife(std::max(0, attackPower - defensePower));
	}
}

int Rules::effective(UnitState& _attacker, UnitState& _defender)
{
	int wep_vuln = _defender.getUnit()->getWeaponWeaknessMask();
	int mov_vuln = _defender.getUnit()->getMovementWeaknessMask();

	int wep_eff = _attacker.getUnit()->getWeaponEffectiveMask();
	int mov_eff = _attacker.getUnit()->getMovementEffectiveMask();

	bool isEffective = ((wep_vuln & wep_eff) != 0) || ((mov_vuln & mov_eff) != 0);

	return isEffective ? 1 : 0;
}

int Rules::weaponTriangle(UnitState& _attacker, UnitState& _defender)
{
	return weaponTriangle(_attacker.getUnit()->getColor(), _defender.getUnit()->getColor());
}

int Rules::weaponTriangle(UnitColor _attacker, UnitColor _defender)
{
	int result = 0;
	switch (_attacker)
	{
	case RED:
		if (_defender == GREEN)
			result = 1;
		if (_defender == BLUE)
			result = -1;
		break;
	case BLUE:
		if (_defender == RED)
			result = 1;
		if (_defender == GREEN)
			result = -1;
		break;
	case GREEN:
		if (_defender == BLUE)
			result = 1;
		if (_defender == RED)
			result = -1;
		break;
	default:
		break;
	}
	return result;
}

bool Rules::targetsRes(WeaponType weapon)
{
	return weapon == WeaponType::BREATH || weapon == WeaponType::STAFF || weapon == WeaponType::TOME;
}