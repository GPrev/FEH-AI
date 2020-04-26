#pragma once

#include "FehOptim.h"

class FEHOPTIM_API TeamBuilder
{
private:
	DataLoader* m_loader;

public:
	TeamBuilder(DataLoader* loader) : m_loader(loader) {}
	~TeamBuilder();

	Team buildTeam(int teamSize = 4);

private:
	Unit getRandomUnit();
};

