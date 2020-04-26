#include "Map.h"
#include "Rules.h"

void Map::init(Unit* ally1, Unit* ally2, Unit* ally3, Unit* ally4)
{
	std::vector<Unit*> allies;
	allies.push_back(ally1);
	if (m_data->getAllyPositions().size() > 1) { allies.push_back(ally2); }
	if (m_data->getAllyPositions().size() > 2) { allies.push_back(ally3); }
	if (m_data->getAllyPositions().size() > 3) { allies.push_back(ally4); }
	init(&allies);
}

void Map::init(std::vector<Unit>* allies, std::vector<Unit>* foes)
{
	std::vector<Unit*> alliesp;
	alliesp.reserve(allies->size());
	std::vector<Unit*> foesp;
	foesp.reserve(foes->size());
	for (Unit& ally : *allies)
	{
		alliesp.push_back(&ally);
	}
	for (Unit& foe : *foes)
	{
		foesp.push_back(&foe);
	}
	init(&alliesp, &foesp);
}

void Map::init(const std::vector<Unit*>* allies, const std::vector<Unit*>* foes)
{
	if (foes == nullptr)
	{
		foes = &m_data->getFoes();
	}

	clearUnits();
	for (size_t i = 0; i < allies->size(); ++i)
	{
		Unit* ally = allies->at(i);
		Position pos = m_data->getAllyPositions().at(i);
		addUnit(ally, pos, BLUE);
	}
	for (size_t i = 0; i < foes->size(); ++i)
	{
		Unit* foe = foes->at(i);
		Position pos = m_data->getEnemyPositions().at(i);
		addUnit(foe, pos, RED);
	}

	m_turnNumber = 1;
	m_turnPlayer = 0;
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
	UnitState state = getState(unit);
	bool ok = state.getSide() == getTurnPlayerColor() && !(state.hasActed() || state.isDead());
	
	// Vérif départ
	Position unitPos = getPos(unit);
	if (ok)
	{
		ok = unitPos.isSomewhere() && isValid(movement) && (!action.isSomewhere() || isValid(action));
	}

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

bool Map::makeMove(Unit* unit, Position movement, Position action)
{
	if (unit != nullptr && movement.isSomewhere())
	{
		UnitState& state = getState(unit);

		m_unitsPos[unit] = movement;
		// TODO actions on allies
		if (action.isSomewhere())
		{
			Rules::doBattle(*this, unit, getUnit(action));

			// Check death
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
		// Mark unit as "has acted"
		state.setHasActed(true);
	}

	return movement.isSomewhere();
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

void Map::newTurn()
{
	m_turnPlayer = (m_turnPlayer + 1) % m_sides.size();
	if (m_turnPlayer == 0)
	{
		m_turnNumber++;
	}

	for (std::pair<Unit* const, UnitState>& unit : m_unitsStates)
	{
		unit.second.setHasActed(false);
	}
}

bool Map::isGameOver()
{
	std::map<UnitColor, int> nbAlive;
	for (auto state : m_unitsStates)
	{
		if (!state.second.isDead())
		{
			nbAlive[state.second.getSide()]++;
		}
	}
	return nbAlive.size() > 1;
}

UnitColor Map::getWinnerColor()
{
	for (auto state : m_unitsStates)
	{
		if (!state.second.isDead())
		{
			return state.second.getSide();
		}
	}
	return COLORLESS;
}