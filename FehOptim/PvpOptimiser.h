#pragma once

#include "AutoPlayer.h"
#include "TeamBuilder.h"
#include <set>

class FEHOPTIM_API PvpOptimiser
{
private:
	int m_teamSize = 4;

	std::multiset<int, Team> m_offenseScores;
	std::multiset<int, Team> m_defenseScores;

	TeamBuilder m_builder;
	AutoPlayer m_player;
	std::vector<MapData*> m_availableMaps;

public:
	PvpOptimiser();
	~PvpOptimiser();

	virtual void init(FehAI* offenseAI, FehAI* defenseAI, std::vector<MapData*> availableMaps)
	{
		m_player = AutoPlayer(offenseAI, defenseAI);
		m_availableMaps = availableMaps;
	}

	virtual void optimize() = 0;

	void battle(Team& offense, Team& defense);

	const std::multiset<int, Team>& getOffenseScores() const { return m_offenseScores; }
	const std::multiset<int, Team>& getDefenseScores() const { return  m_defenseScores; }
};

