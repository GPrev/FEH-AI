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
	for (Unit& ally : *allies)
	{
		alliesp.push_back(&ally);
	}
	std::vector<Unit*> foesp;
	if (foes != nullptr)
	{
		foesp.reserve(foes->size());
		for (Unit& foe : *foes)
		{
			foesp.push_back(&foe);
		}
	}
	if (foes != nullptr)
	{
		init(&alliesp, &foesp);
	}
	else
	{
		init(&alliesp);
	}
}

void Map::init(const std::vector<Unit*>* allies, const std::vector<Unit*>* foes)
{
	clearUnits();
	for (size_t i = 0; i < allies->size(); ++i)
	{
		Unit* ally = allies->at(i);
		Position pos = m_data->getAllyPositions().at(i);
		addUnit(ally, pos, BLUE);
	}

	if (foes == nullptr)
	{
		// Foes from map data
		const std::vector<Unit>* dataFoes = &m_data->getFoes();
		for (size_t i = 0; i < dataFoes->size(); ++i)
		{
			const Unit& foe = dataFoes->at(i);
			Position pos = m_data->getEnemyPositions().at(i);
			addUnit(&foe, pos, RED);
		}
	}
	else
	{
		// Foes from arguments
		for (size_t i = 0; i < foes->size(); ++i)
		{
			Unit* foe = foes->at(i);
			Position pos = m_data->getEnemyPositions().at(i);
			addUnit(foe, pos, RED);
		}
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
	return isValid(pos) && m_unitsPos.end() == std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&pos](const std::pair<const Unit*, Position>& pair) { return pair.second == pos; });
}

bool Map::isFreeOrAlly(Position pos, UnitColor side) const
{
	return isValid(pos) && m_unitsPos.end() == std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [this, &pos, &side](const std::pair<const Unit*, Position>& pair) { return pair.second == pos && getState(pair.first).getSide() != side; });
}

void Map::addUnit(const Unit* unit, const Position& pos, UnitColor side)
{
	if (unit != nullptr)
	{
		m_unitsStates[unit] = UnitState(*unit, side);
		m_unitsPos[unit] = pos;
	}
}

const Position& Map::getPos(const Unit* unit) const
{
	auto it = std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&unit](const std::pair<const Unit*, Position> &pair) { return pair.first == unit; });
	if (it != m_unitsPos.end())
	{
		return it->second;
	}
	else
	{
		return Position::nowhere;
	}
}

const Unit* Map::getUnit(Position pos)
{
	const Unit* res = nullptr;
	auto it = std::find_if(m_unitsPos.begin(), m_unitsPos.end(), [&pos](const std::pair<const Unit*, Position> &pair) { return pair.second == pos; });
	if (it != m_unitsPos.end())
	{
		res = it->first;
	}
	return res;
}

bool Map::canMakeMove(const Unit* unit, Position movement, Position action)
{
	const UnitState& state = getState(unit);
	bool ok = state.getSide() == getTurnPlayerColor() && !(state.hasActed() || state.isDead());
	
	// V�rif d�part
	const Position& unitPos = getPos(unit);
	if (ok)
	{
		ok = unitPos.isSomewhere() && isValid(movement) && (!action.isSomewhere() || isValid(action));
	}

	// V�rif mvt
	if (ok)
	{
		// Not moving is always valid. Destination must be free and not too far. Lastly, a path must exist that is not too long.
		ok = (movement == unitPos) || (isFree(movement) && unitPos.distance(movement) <= unit->getMvt() && canFindPath(unitPos, movement, unit->getMvtType(), unit->getMvt(), state.getSide()));
	}

	// V�rif action
	if (ok && action.isSomewhere())
	{
		// TODO check equips, teams...
		// TODO actions on allies
		ok = !isFree(action) && movement.distance(action) == unit->getRange() && state.canAttack() && getUnitState(action).getSide() != state.getSide();
	}

	return ok;
}

bool Map::makeMove(const Unit* unit, Position movement, Position action)
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
			const Unit* oponent = getUnit(action);
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

std::vector<Move> Map::getPossibleMoves(const Unit* unit)
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

void Map::getPossibleMoves(const Unit* unit, Position movement, std::vector<Move>& res)
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

bool Map::canFindPath(const Position& origin, const Position& destination, MvtType mvtType, int maxLength, UnitColor side)
{
	// We can always not move
	if (origin.distance(destination) == 0)
	{
		return true;
	}
	// Destination must be free
	else if (!isFree(destination))
	{
		return false;
	}
	// Moving one tile depends on the cost of the tile
	else if (origin.distance(destination) == 1)
	{
		// Note that if the tile is not accessible its move cost will just be very big
		return  m_data->getTerrain(destination)->moveCost(mvtType) <= maxLength;
	}
	// When the tiles are not side by side we have to try different paths
	else
	{
		// Since the maximum movement length is 3, moving in the direction opposite of the destination will always fail
		// That means we can test only the tiles going in the direction we want to go
		std::vector<Position> toBeTested;
		if (origin.getX() < destination.getX())
		{
			toBeTested.push_back(origin + Position(1, 0));
		}
		else if (origin.getX() > destination.getX())
		{
			toBeTested.push_back(origin + Position(-1, 0));
		}
		if (origin.getY() < destination.getY())
		{
			toBeTested.push_back(origin + Position(0, 1));
		}
		else if (origin.getY() > destination.getY())
		{
			toBeTested.push_back(origin + Position(0, -1));
		}
		for (Position& pos : toBeTested)
		{
			// We cannot use a position occupied by an enemy
			if (isFreeOrAlly(pos, side))
			{
				// We test one path, substracting the cost of the first move to the total
				// Note that if the tile is not accessible its move cost will just be very big
				int firstMoveCost = m_data->getTerrain(pos)->moveCost(mvtType);
				if (maxLength > firstMoveCost && canFindPath(pos, destination, mvtType, maxLength - firstMoveCost, side))
				{
					// No need to test more if one path works
					return true;
				}
			}
		}
		// If no path was found
		return false;
	}
}

void Map::newTurn()
{
	m_turnPlayer = (m_turnPlayer + 1) % m_sides.size();
	if (m_turnPlayer == 0)
	{
		m_turnNumber++;
	}

	for (std::pair<const Unit* const, UnitState>& unit : m_unitsStates)
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