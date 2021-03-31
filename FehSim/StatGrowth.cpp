#include <vector>
#include <algorithm>
#include "StatGrowth.h"

Stats StatGrowth::getBaseStats(const UnitData& unit, int rarity)
{
	Stats res = unit.getBaseStats();
	switch (rarity)
	{
	case 1:
	case 2:
		// 1 or 2 stars have -1 to all stats
		res = res - 1;
		break;
	case 5:
		// 5 stars have +1 to all stats
		res = res + 1;
		break;
	default:
		break;
	}
	if(rarity == 2 || rarity == 4)
	{
		// 2 and 4 stars have +1 to their 2 best stats beside HP
		std::vector<std::pair<int, int>> vect;
		vect.push_back(std::pair<int, int>(res.getAtk(), 1));
		vect.push_back(std::pair<int, int>(res.getSpd(), 2));
		vect.push_back(std::pair<int, int>(res.getDef(), 3));
		vect.push_back(std::pair<int, int>(res.getRes(), 4));
		// Sort by value. If equal, atk > vit > def > res
		std::sort(vect.begin(), vect.end(), [](std::pair<int, int> a, std::pair<int, int> b) 
			{return a.first*10-a.second > b.first * 10 - b.second; });
		// Apply the bonus to the 2 greatest stats
		for (int i = 0; i < 2; ++i)
		{
			switch (vect[i].second)
			{
			case 1:
				res = res + Stats::atkStat(1);
				break;
			case 2:
				res = res + Stats::spdStat(1);
				break;
			case 3:
				res = res + Stats::defStat(1);
				break;
			case 4:
				res = res + Stats::resStat(1);
				break;
			default:
				break;
			}
		}
	}
	return res;
}

Stats StatGrowth::getStats(const UnitData& unit, int rarity, int level)
{
	return getBaseStats(unit, rarity) + (unit.getGrowths() * getRarityMultiplier(rarity)) * ((double)(level - 1) / 100);
}
