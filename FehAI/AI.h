#pragma once

#include "FehAI.h"
#include "Map.h"

class FEHAI_API FehAI
{
public:
	FehAI();
	~FehAI();
	inline void makeMove(Map& map, UnitColor side) { map.makeMove(chooseMove(map, side)); }

protected:
	virtual Move chooseMove(Map& map, UnitColor side) = 0;
};
