#include "TeamBuilder.h"
#include "DataLoader.h"
#include "Unit.h"

TeamBuilder::~TeamBuilder()
{
}

Team TeamBuilder::buildTeam(int teamSize)
{
	Team t(teamSize);
	for (int i = 0; i < teamSize; ++i)
	{
		t[i] = getRandomUnit();
	}
	return t;
}

Unit TeamBuilder::getRandomUnit()
{
	int unitId = rand() % m_loader->getUnitNames().size();
	std::string unitName = m_loader->getUnitNames().at(unitId);
	Unit u(*m_loader->getUnitData(unitName));
	u.makeBaseKit(*m_loader);
	return u;
}