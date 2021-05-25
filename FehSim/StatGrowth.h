#pragma once

#include "UnitData.h"

class FEHSIM_API StatGrowth
{
public:
	static Stats getStats(const UnitData& unit, int rarity, int level, int merges = 0, StatNames boon = StatNames::NONE, StatNames bane = StatNames::NONE);

private:
	static Stats getBaseStats(const UnitData& unit, int rarity);
	static Stats getMergeBonus(const UnitData& unit, int merges, bool neutral = true);
	static double getRarityMultiplier(int rarity) { return 1 + 0.07 * (rarity - 3); }

	static void addStat(Stats& toBeAdded, int statID, int amount = 1);
};

