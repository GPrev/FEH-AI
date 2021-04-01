#pragma once
#include "PvpOptimiser.h"
class FEHOPTIM_API ArenaAE : public PvpOptimiser
{
	typedef std::pair<Team, int> Indiv;

private:
	int m_popSize;
	int m_nbGen;
	std::vector<Indiv> m_offensePop;
	std::vector<Indiv> m_defensePop;

public:
	ArenaAE(int _popSize, int _nbGen);
	~ArenaAE();

	virtual void optimize();

private:
	void initTeams();
	void tournament();
	void replacement();
	void finalize();
};

