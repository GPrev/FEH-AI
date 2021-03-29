#include <cmath>
#include "Rules.h"


Rules::Rules()
{
}

void Rules::doBattle(Map& map, Unit* _attacker, Unit* _defender)
{
	UnitState& attState = map.getState(_attacker);
	Stats attStats = attState.getStats();
	UnitState& defState = map.getState(_defender);
	Stats defStats = defState.getStats();
	bool attackerDoubles = (attStats.getSpd() >= defStats.getSpd() + 4);
	bool defenderDoubles = false;
	strike(attState, defState, attStats, defStats);
	if (_defender->canCounter(_attacker->getRange()))
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
		int attackPower = _attStats.getAtk() + (int) std::trunc(_attStats.getAtk() * .2 * weaponTriangle(_attacker, _defender));
		_defender.loseLife(std::max(0, attackPower - _defStats.getDef()));
	}
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
		if (_defender == BLUE)
			result = -1;
		break;
	default:
		break;
	}
	return result;
}