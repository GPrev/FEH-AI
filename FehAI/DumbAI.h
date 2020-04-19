#pragma once
#include "FehAI.h"

class DumbAI : public FehAI
{
public:
	DumbAI();
	~DumbAI();

protected:
	virtual Move chooseMove(Map& map, UnitColor side);

private:
	Position closestEnemy(Map& map, Unit* unit);
};

