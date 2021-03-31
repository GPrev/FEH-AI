#pragma once

#include "UnitData.h"

class FEHSIM_API StatGrowth
{
public:
	static Stats getStats(const UnitData& unit, int rarity, int level);

private:
	static Stats getBaseStats(const UnitData& unit, int rarity);
	static double getRarityMultiplier(int rarity) { return 1 + 0.07 * (rarity - 3); }
};

