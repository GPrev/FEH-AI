#pragma once

#include <algorithm>
#include "FehSim.h"
#include "UnitData.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Unit
{
private:
	UnitData* m_data;

	int m_stars = 5;
	int m_merges = 0;

public:
	Unit() {}
	Unit(UnitData& data) : m_data(&data) {}
	~Unit() {};

	int getMaxHP() { return m_data->getBaseHP(); }
	int getAtk()   { return m_data->getBaseAtk(); }
	int getSpd()   { return m_data->getBaseSpd(); }
	int getDef()   { return m_data->getBaseDef(); }
	int getRes()   { return m_data->getBaseRes(); }
	int getMvt()   { return 2; } // TODO consider mvt types
	int getRange() { return 2; } // TODO consider weapon
	bool canCC()   { return true; } // TODO consider weapon and skills
	bool canDC()   { return false; } // TODO consider weapon and skills
};

#pragma warning( pop ) 
