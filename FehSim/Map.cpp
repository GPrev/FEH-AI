#include "Map.h"


void Map::init(Unit* ally1, Unit* ally2, Unit* ally3, Unit* ally4)
{
	m_units = m_data->getFoes();
	setUnit(ally1, m_data->getAllyPositions().at(0));
	if (m_data->getAllyPositions().size() > 1) { setUnit(ally2, m_data->getAllyPositions().at(1)); }
	if (m_data->getAllyPositions().size() > 2) { setUnit(ally3, m_data->getAllyPositions().at(2)); }
	if (m_data->getAllyPositions().size() > 3) { setUnit(ally4, m_data->getAllyPositions().at(3)); }
}

bool Map::isValid(Position pos) const
{
	return pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < m_data->getWidth() && pos.getY() < m_data->getHeight();
}

bool Map::isFree(Position pos) const
{
	return isValid(pos) && m_units.end() == std::find_if(m_units.begin(), m_units.end(), [&pos](const std::pair<Unit*, Position> &pair) { return pair.second == pos; });
}

void Map::setUnit(Unit* ally, const Position& pos)
{
	if (ally != nullptr)
	{
		m_units[ally] = pos;
	}
}

Position Map::getPos(Unit* unit) const
{
	Position res = Position::nowhere;
	auto it = std::find_if(m_units.begin(), m_units.end(), [&unit](const std::pair<Unit*, Position> &pair) { return pair.first == unit; });
	if (it != m_units.end())
	{
		res = it->second;
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
		ok = !isFree(movement) && movement.distance(action) <= unit->getRange();
	}

	return ok;
}
