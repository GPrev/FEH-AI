#pragma once
#include "AI.h"

class FEHAI_API DumbAI : public FehAI
{
public:
	DumbAI();
	~DumbAI();

protected:
	virtual Move chooseMove(Map& map, UnitColor side);

private:
	Position closestEnemy(Map& map, const Unit* unit);
};

