#include "Map.h"


void Map::init(Unit* ally1, Unit* ally2, Unit* ally3, Unit* ally4)
{
	clearUnits();
	for (auto foe : m_data->getFoes())
	{
		setUnit(foe.first, foe.second, RED);
	}
	setUnit(ally1, m_data->getAllyPositions().at(0), BLUE);
	if (m_data->getAllyPositions().size() > 1) { setUnit(ally2, m_data->getAllyPositions().at(1), BLUE); }
	if (m_data->getAllyPositions().size() > 2) { setUnit(ally3, m_data->getAllyPositions().at(2), BLUE); }
	if (m_data->getAllyPositions().size() > 3) { setUnit(ally4, m_data->getAllyPositions().at(3), BLUE); }
}

bool Map::isValid(Position pos) const
{
	return pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < m_data->getWidth() && pos.getY() < m_data->getHeight();
}

bool Map::isFree(Position pos) const
{
	return isValid(pos) && m_unitsPos.end() == std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&pos](const std::pair<Unit*, Position> &pair) { return pair.second == pos; });
}

void Map::setUnit(Unit* unit, const Position& pos, UnitColor side)
{
	if (unit != nullptr)
	{
		m_unitsStates[unit] = UnitState(*unit, side);
		m_unitsPos[unit] = pos;
	}
}

Position Map::getPos(Unit* unit) const
{
	Position res = Position::nowhere;
	auto it = std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&unit](const std::pair<Unit*, Position> &pair) { return pair.first == unit; });
	if (it != m_unitsPos.end())
	{
		res = it->second;
	}
	return res;
}

Unit* Map::getUnit(Position pos)
{
	Unit* res = nullptr;
	auto it = std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&pos](const std::pair<Unit*, Position> &pair) { return pair.second == pos; });
	if (it != m_unitsPos.end())
	{
		res = it->first;
	}
	return res;
}

bool Map::canMakeMove(Unit* unit, Position movement, Position action)
{
	bool ok = true;
	
	// Vérif départ
	Position unitPos = getPos(unit);
	ok = unitPos.isSomewhere();

	// Vérif mvt
	if (ok)
	{
		// TODO consider terrain
		ok = isFree(movement) && unitPos.distance(movement) <= unit->getMvt();
	}

	// Vérif action
	if (ok && action.isSomewhere())
	{
		// TODO check equips, teams...
		UnitState& state = getState(unit);
		ok = !isFree(action) && movement.distance(action) <= unit->getRange() && state.canAttack() && getUnitState(action).getSide() != state.getSide();
	}

	return ok;
}
