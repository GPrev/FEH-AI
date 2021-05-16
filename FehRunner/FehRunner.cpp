// FehRunner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <time.h>

#include "ArenaAE.h"
#include "DumbAI.h"
#include "DataLoader.h"
#include "Translator.h"

int main()
{
	srand((unsigned)time(NULL));

	Translator translator(Language::EUEN);
	ArenaAE ae(10, 10);
	DumbAI ai;
	std::vector<MapData*> availableMaps;

	std::vector<Position> allyPos, enemyPos;
	allyPos.push_back(Position(1, 1));
	allyPos.push_back(Position(2, 1));
	allyPos.push_back(Position(3, 1));
	allyPos.push_back(Position(4, 1));
	enemyPos.push_back(Position(1, 6));
	enemyPos.push_back(Position(2, 6));
	enemyPos.push_back(Position(3, 6));
	enemyPos.push_back(Position(4, 6));
	availableMaps.push_back(new MapData("map", 6, 8, allyPos, enemyPos));

	std::cout << "Optimising..." << std::endl;
	ae.init(&ai, &ai, &availableMaps);
	ae.optimize();
	std::cout << "Done." << std::endl;

	std::cout << std::endl << "== Best Offense Teams ==" << std::endl;
	auto it = ae.getOffenseScores().rbegin();
	for (int i = 0; i < 10 && it != ae.getOffenseScores().rend(); ++i, ++it)
	{
		std::cout << "-- " << i + 1 << " (" << it->first << ")" << " --" << std::endl;
		for (auto& unit : it->second)
		{
			std::cout << unit.getData()->toString(translator) << std::endl;
		}
	}

	std::cout << std::endl << "== Best Defense Teams ==" << std::endl;
	it = ae.getDefenseScores().rbegin();
	for (int i = 0; i < 10 && it != ae.getDefenseScores().rend(); ++i, ++it)
	{
		std::cout << "-- " << i + 1 << " (" << it->first << ")" << " --" << std::endl;
		for (auto& unit : it->second)
		{
			std::cout << unit.getData()->toString(translator) << std::endl;
		}
	}

	system("pause");
	return 0;
}

