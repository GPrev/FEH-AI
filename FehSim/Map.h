#pragma once

#include "FehSim.h"
#include "MapData.h"
#include "UnitState.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Move
{
public:
	const Unit* m_unit = nullptr;
	Position m_movement = Position::nowhere;
	Position m_action = Position::nowhere;

	Move(const Unit* unit = nullptr, Position movement = Position::nowhere, Position action = Position::nowhere)
		: m_unit(unit), m_movement(movement), m_action(action) {}
};

class FEHSIM_API Map
{
private:
	MapData* m_data;
	std::vector<UnitColor> m_sides = { BLUE, RED };

	int m_turnNumber = 1;
	int m_turnPlayer = 0;
	std::map<const Unit*, UnitState> m_unitsStates;
	std::map<const Unit*, Position> m_unitsPos;

public:
	Map() {}
	Map(MapData& data) : m_data(&data) {}

	void init(Unit* ally1, Unit* ally2 = nullptr, Unit* ally3 = nullptr, Unit* ally4 = nullptr);
	void init(const std::vector<Unit*>* allies, const std::vector<Unit*>* foes = nullptr);
	void init(std::vector<Unit>* allies, std::vector<Unit>* foes = nullptr);

	bool isValid(Position pos) const;
	bool isFree(Position pos) const;
	bool isFreeOrAlly(Position pos, UnitColor side) const;

	const std::map<const Unit*, Position>& getUnits() const { return m_unitsPos; }

	const Position& getPos(const Unit* unit) const;
	const Unit* getUnit(Position pos);
	const UnitState& getState(const Unit* unit) const { return m_unitsStates.at(unit); };
	UnitState& getState(const Unit* unit) { return m_unitsStates.at(unit); };
	UnitState& getUnitState(Position pos) { return getState(getUnit(pos)); };

	int getTurnNumber() { return m_turnNumber; }
	int getTurnPlayerID() { return m_turnPlayer; }
	UnitColor getTurnPlayerColor() { return m_sides[m_turnPlayer]; }

	bool isGameOver();
	UnitColor getWinnerColor();

	bool canMakeMove(const Unit* unit, Position movement, Position action = Position::nowhere);
	inline bool makeMove(Move move) { return makeMove(move.m_unit, move.m_movement, move.m_action); }
	bool makeMove(const Unit* unit, Position movement, Position action = Position::nowhere);

	std::vector<Move> getPossibleMoves(UnitColor side);
	std::vector<Move> getPossibleMoves(const Unit* unit);

	void newTurn();

	UnitColor playerIdToColor(int id) { return m_sides[id]; }
	int colorToPlayerId(UnitColor color) { return (int) std::distance(m_sides.begin(), std::find(m_sides.begin(), m_sides.end(), color)); }

private:
	void clearUnits() { m_unitsStates.clear(); m_unitsPos.clear(); };
	void addUnit(const Unit* ally, const Position& pos, UnitColor side);
	void getPossibleMoves(const Unit* unit, Position movement, std::vector<Move>& res);
	bool canBeOnTile(MvtType mvtType, const Position& pos) { return  m_data->getTerrain(pos)->moveCost(mvtType) != Terrain::noMove; }
	bool canBeOnTile(const Unit* unit, const Position& pos) { return canBeOnTile(unit->getMvtType(), pos); }
	bool canFindPath(const Position& origin, const Position& destination, MvtType mvtType, int maxLength, UnitColor side);
	bool canPerformAssist(const Skill* assist, const Unit* user, const Unit* target, const Position& userPos);
	std::pair<Position, Position> getAssistMovement(const Skill* assist, const Position & userPos, const Position & targetPos);
};

#pragma warning( pop ) 
