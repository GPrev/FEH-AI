#pragma once

#include "AutoPlayer.h"
#include "TeamBuilder.h"
#include "DataLoader.h"
#include <set>

class FEHOPTIM_API PvpOptimiser
{
protected:
	int m_teamSize = 4;

	std::multimap<int, Team> m_offenseScores;
	std::multimap<int, Team> m_defenseScores;

	TeamBuilder m_builder;
	DataLoader m_loader;
	AutoPlayer m_player;
	std::vector<MapData*>* m_availableMaps;

public:
	PvpOptimiser();
	~PvpOptimiser();

	virtual void init(FehAI* offenseAI, FehAI* defenseAI, std::vector<MapData*>* availableMaps)
	{
		m_player = AutoPlayer(offenseAI, defenseAI);
		m_availableMaps = availableMaps;
	}

	virtual void optimize() = 0;

	bool battle(Team& offense, Team& defense);

	const std::multimap<int, Team>& getOffenseScores() const { return m_offenseScores; }
	const std::multimap<int, Team>& getDefenseScores() const { return  m_defenseScores; }
};

