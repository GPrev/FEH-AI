#pragma once

#include "FehOptim.h"

class FEHOPTIM_API TeamBuilder
{
public:
	TeamBuilder();
	~TeamBuilder();

	Team buildTeam(int teamSize);
};

