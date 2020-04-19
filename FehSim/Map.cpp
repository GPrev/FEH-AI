#include "Map.h"
#include "Rules.h"

void Map::init(Unit* ally1, Unit* ally2, Unit* ally3, Unit* ally4)
{
	clearUnits();
	for (auto foe : m_data->getFoes())
	{
		addUnit(foe.first, foe.second, RED);
	}
	addUnit(ally1, m_data->getAllyPositions().at(0), BLUE);
	if (m_data->getAllyPositions().size() > 1) { addUnit(ally2, m_data->getAllyPositions().at(1), BLUE); }
	if (m_data->getAllyPositions().size() > 2) { addUnit(ally3, m_data->getAllyPositions().at(2), BLUE); }
	if (m_data->getAllyPositions().size() > 3) { addUnit(ally4, m_data->getAllyPositions().at(3), BLUE); }
}

bool Map::isValid(Position pos) const
{
	return pos.getX() >= 0 && pos.getY() >= 0 && pos.getX() < m_data->getWidth() && pos.getY() < m_data->getHeight();
}

bool Map::isFree(Position pos) const
{
	return isValid(pos) && m_unitsPos.end() == std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&pos](const std::pair<Unit*, Position> &pair) { return pair.second == pos; });
}

void Map::addUnit(Unit* unit, const Position& pos, UnitColor side)
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
	ok = unitPos.isSomewhere() && isValid(movement) && (!action.isSomewhere() || isValid(action));

	// Vérif mvt
	if (ok)
	{
		// TODO consider terrain
		ok = (movement == unitPos) || (isFree(movement) && unitPos.distance(movement) <= unit->getMvt());
	}

	// Vérif action
	if (ok && action.isSomewhere())
	{
		// TODO check equips, teams...
		// TODO actions on allies
		UnitState& state = getState(unit);
		ok = !isFree(action) && movement.distance(action) == unit->getRange() && state.canAttack() && getUnitState(action).getSide() != state.getSide();
	}

	return ok;
}

void Map::makeMove(Unit* unit, Position movement, Position action)
{
	m_unitsPos[unit] = movement;
	// TODO actions on allies
	if (action.isSomewhere())
	{
		Rules::doBattle(*this, unit, getUnit(action));

		// Check death
		UnitState& state = getState(unit);
		Unit* oponent = getUnit(action);
		UnitState& opState = getState(oponent);
		if (state.isDead())
		{
			m_unitsPos[unit] = Position::nowhere;
		}
		if (opState.isDead())
		{
			m_unitsPos[oponent] = Position::nowhere;
		}
	}
}

std::vector<Move> Map::getPossibleMoves(UnitColor side)
{
	std::vector<Move> res;
	for (auto unit : m_unitsStates)
	{
		if (!unit.second.isDead() && unit.second.getSide() == side)
		{
			std::vector<Move> unitRes = getPossibleMoves(unit.first);
			res.reserve(res.size() + unitRes.size());
			res.insert(res.end(), unitRes.begin(), unitRes.end());
		}
	}
	return res;
}

int distance1[][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
int distance2[][2] = { { -2, 0 },{ -1, -1 },{ 0, -2 },{ 1, -1 },{ 2, 0 },{ 1, 1 },{ 0, 2 },{ -1, 1 } };
int distance3[][2] = { { -3, 0 }, { -2, -1 }, { -1, -2 }, { 0, -3 }, { 1, -2 }, { 2, -1 }, { 3, 0 }, { 2, 1 }, { 1, 2 }, { 0, 3 }, { -1, 2 }, { -2, 1 } };

std::vector<Move> Map::getPossibleMoves(Unit* unit)
{
	std::vector<Move> res;

	Position pos = getPos(unit);

	getPossibleMoves(unit, pos, res);
	for (int* offset : distance1)
	{
		getPossibleMoves(unit, pos + offset, res);
	}
	if (unit->getMvt() > 1)
	{
		for (int* offset : distance2)
		{
			getPossibleMoves(unit, pos + offset, res);
		}
	}
	if (unit->getMvt() > 2)
	{
		for (int* offset : distance3)
		{
			getPossibleMoves(unit, pos + offset, res);
		}
	}

	return res;
}

void Map::getPossibleMoves(Unit* unit, Position movement, std::vector<Move>& res)
{
	if (canMakeMove(unit, movement))
	{
		res.push_back(Move(unit, movement));
	}
	for (int* offset : distance1)
	{
		Position action = movement + offset;
		if (canMakeMove(unit, movement, action))
		{
			res.push_back(Move(unit, movement, action));
		}
	}
	for (int* offset : distance2)
	{
		Position action = movement + offset;
		if (canMakeMove(unit, movement, action))
		{
			res.push_back(Move(unit, movement, action));
		}
	}
}