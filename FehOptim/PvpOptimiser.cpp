#include "PvpOptimiser.h"



PvpOptimiser::PvpOptimiser() : m_builder(&m_loader)
{
}


PvpOptimiser::~PvpOptimiser()
{
}

bool PvpOptimiser::battle(Team& offense, Team& defense)
{
	int mapID = std::rand() % m_availableMaps->size();
	MapData* map = m_availableMaps->at(mapID);
	return m_player.playToTheEnd(*map, &offense, &defense);
}