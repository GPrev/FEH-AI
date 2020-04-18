#include "Rules.h"



Rules::Rules()
{
}

void Rules::doBattle(Map& map, Unit* _attacker, Unit* _defender)
{
	UnitState& attState = map.getState(_attacker);
	UnitState& defState = map.getState(_defender);
	bool attackerDoubles = (attState.getSpd() >= defState.getSpd() + 4);
	bool defenderDoubles = (defState.getSpd() >= attState.getSpd() + 4);
	strike(attState, defState);
	strike(defState, attState);
	if (attackerDoubles)
	{
		strike(attState, defState);
	}
	if (defenderDoubles)
	{
		strike(defState, attState);
	}
}

void Rules::strike(UnitState& _attacker, UnitState& _defender)
{
	if (!_attacker.isDead())
	{
		int attackPower = _attacker.getAtk() + (int) std::trunc(_attacker.getAtk() * .2 * weaponTriangle(_attacker, _defender));
		_defender.loseLife(std::max(0, attackPower - _defender.getDef()));
	}
}

int Rules::weaponTriangle(UnitState& _attacker, UnitState& _defender)
{
	return weaponTriangle(_attacker.getUnit()->getData()->getColor(), _defender.getUnit()->getData()->getColor());
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