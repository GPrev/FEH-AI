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
		_defender.loseLife(std::max(0, _attacker.getAtk() - _defender.getDef()));
	}
}