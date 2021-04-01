#include "ArenaAE.h"

#include <algorithm>
#include <random>


ArenaAE::ArenaAE(int _popSize, int _nbGen)
	: m_popSize(_popSize), m_nbGen(_nbGen)
{
}


ArenaAE::~ArenaAE()
{
}

void ArenaAE::optimize()
{
	initTeams();
	for (int i = 0; i < m_nbGen; ++i)
	{
		tournament();
		replacement();
	}
	finalize();
}
void ArenaAE::initTeams()
{
	m_offensePop.reserve(m_popSize);
	for (int i = 0; i < m_popSize; ++i)
	{
		m_offensePop.push_back(Indiv(m_builder.buildTeam(m_teamSize), 0));
	}
	m_defensePop.reserve(m_popSize);
	for (int i = 0; i < m_popSize; ++i)
	{
		m_defensePop.push_back(Indiv(m_builder.buildTeam(m_teamSize), 0));
	}
}

void ArenaAE::tournament()
{
	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(m_defensePop), std::end(m_defensePop), rng);
	for (int i = 0; i < m_popSize; ++i)
	{
		bool offWin = battle(m_offensePop[i].first, m_defensePop[i].first);
		if (offWin)
		{
			m_offensePop[i].second++;
		}
		else
		{
			m_defensePop[i].second++;
		}
	}
}

void ArenaAE::replacement()
{
	// TODO
}

void ArenaAE::finalize()
{
	for (auto& off : m_offensePop)
	{
		m_offenseScores.insert(std::pair<int, Team>(off.second, off.first));
	}
	for (auto& def : m_defensePop)
	{
		m_defenseScores.insert(std::pair<int, Team>(def.second, def.first));
	}
}
