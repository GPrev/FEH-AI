#include "PvpOptimiser.h"



PvpOptimiser::PvpOptimiser()
{
}


PvpOptimiser::~PvpOptimiser()
{
}

void PvpOptimiser::battle(Team& offense, Team& defense)
{
	int mapID = std::rand() % m_availableMaps.size();
	MapData* map = m_availableMaps.at(mapID);
	m_player.playToTheEnd(*map, &offense, &defense);
}