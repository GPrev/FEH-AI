#include <vector>
#include <algorithm>
#include "StatGrowth.h"

void StatGrowth::addStat(Stats& toBeAdded, int statID, int amount)
{
	switch (statID)
	{
	case 0:
		toBeAdded = toBeAdded + Stats::hpStat(amount);
		break;
	case 1:
		toBeAdded = toBeAdded + Stats::atkStat(amount);
		break;
	case 2:
		toBeAdded = toBeAdded + Stats::spdStat(amount);
		break;
	case 3:
		toBeAdded = toBeAdded + Stats::defStat(amount);
		break;
	case 4:
		toBeAdded = toBeAdded + Stats::resStat(amount);
		break;
	default:
		break;
	}
}

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
			addStat(res, vect[i].second);
		}
	}
	return res;
}

Stats StatGrowth::getMergeBonus(const UnitData& unit, int merges, bool neutral)
{
	Stats res;
	if (merges > 0)
	{
		Stats lvl15star = getBaseStats(unit, 5);
		std::vector<std::pair<int, int>> buffOrder;
		buffOrder.push_back(std::pair<int, int>(lvl15star.getHp(), 0));
		buffOrder.push_back(std::pair<int, int>(lvl15star.getAtk(), 1));
		buffOrder.push_back(std::pair<int, int>(lvl15star.getSpd(), 2));
		buffOrder.push_back(std::pair<int, int>(lvl15star.getDef(), 3));
		buffOrder.push_back(std::pair<int, int>(lvl15star.getRes(), 4));
		// Sort by value. If equal, hp > atk > vit > def > res
		std::sort(buffOrder.begin(), buffOrder.end(), [](std::pair<int, int> a, std::pair<int, int> b)
			{return a.first * 10 - a.second > b.first * 10 - b.second; });

		if (neutral)
		{
			for (int i = 0; i < 3; ++i)
			{
				std::pair<int, int>& buff = buffOrder[i];
				addStat(res, buff.second);
			}
		}

		for (int i = 0; i < 2 * merges; ++i)
		{
			std::pair<int, int>& buff = buffOrder[i % 5];
			addStat(res, buff.second);
		}
	}

	return res;
}

Stats StatGrowth::getStats(const UnitData& unit, int rarity, int level, int merges, StatNames boon, StatNames bane)
{
	bool neutral = boon == StatNames::NONE && bane == StatNames::NONE;
	return getBaseStats(unit, rarity) + getMergeBonus(unit, merges, neutral) + (unit.getGrowths() * getRarityMultiplier(rarity)) * ((double)(level - 1) / 100);
}
