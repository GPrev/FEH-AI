#pragma once

#include "FehSim.h"
#include "MapData.h"
#include "UnitState.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Map
{
private:
	MapData* m_data;

	std::map<Unit*, UnitState> m_unitsStates;
	std::map<Unit*, Position> m_unitsPos;

public:
	Map() {}
	Map(MapData& data) : m_data(&data) {}

	void init(Unit* ally1, Unit* ally2 = nullptr, Unit* ally3 = nullptr, Unit* ally4 = nullptr);

	bool isValid(Position pos) const;
	bool isFree(Position pos) const;

	Position getPos(Unit* unit) const;

	bool canMakeMove(Unit* unit, Position movement, Position action = Position::nowhere);

private:
	void clearUnits() { m_unitsStates.clear(); m_unitsPos.clear(); };
	void setUnit(Unit* ally, const Position& pos);
};

#pragma warning( pop ) 
