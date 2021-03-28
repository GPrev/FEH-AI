#pragma once
#include "PvpOptimiser.h"
class FEHOPTIM_API ArenaAE : public PvpOptimiser
{
	typedef std::pair<Team, int> Indiv;

private:
	int m_popSize = 100;
	int m_nbGen = 2000;
	std::vector<Indiv> m_offensePop;
	std::vector<Indiv> m_defensePop;

public:
	ArenaAE();
	~ArenaAE();

	virtual void optimize();

private:
	void initTeams();
	void tournament();
	void replacement();
	void finalize();
};

