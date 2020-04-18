#pragma once

#include "Map.h"

class FEHSIM_API Rules
{
public:
	Rules();

	static void doBattle(Map& map, Unit* _attacker, Unit* _defender);

private:
	static void strike(UnitState& _attacker, UnitState& _defender);
};

