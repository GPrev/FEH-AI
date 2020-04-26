#pragma once

#include "FehSim.h"
#include "MapData.h"
#include "UnitState.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Move
{
public:
	Unit* m_unit = nullptr;
	Position m_movement = Position::nowhere;
	Position m_action = Position::nowhere;

	Move(Unit* unit = nullptr, Position movement = Position::nowhere, Position action = Position::nowhere)
		: m_unit(unit), m_movement(movement), m_action(action) {}
};

class FEHSIM_API Map
{
private:
	MapData* m_data;
	std::vector<UnitColor> m_sides = { BLUE, RED };

	int m_turnNumber = 1;
	int m_turnPlayer = 0;
	std::map<Unit*, UnitState> m_unitsStates;
	std::map<Unit*, Position> m_unitsPos;

public:
	Map() {}
	Map(MapData& data) : m_data(&data) {}

	void init(Unit* ally1, Unit* ally2 = nullptr, Unit* ally3 = nullptr, Unit* ally4 = nullptr);
	void init(const std::vector<Unit*>* allies, const std::vector<Unit*>* foes = nullptr);
	void init(std::vector<Unit>* allies, std::vector<Unit>* foes = nullptr);

	bool isValid(Position pos) const;
	bool isFree(Position pos) const;

	const std::map<Unit*, Position>& getUnits() const { return m_unitsPos; }

	Position getPos(Unit* unit) const;
	Unit* getUnit(Position pos);
	UnitState& getState(Unit* unit) { return m_unitsStates.at(unit); };
	UnitState& getUnitState(Position pos) { return getState(getUnit(pos)); };

	int getTurnNumber() { return m_turnNumber; }
	int getTurnPlayerID() { return m_turnPlayer; }
	UnitColor getTurnPlayerColor() { return m_sides[m_turnPlayer]; }

	bool isGameOver();
	UnitColor getWinnerColor();

	bool canMakeMove(Unit* unit, Position movement, Position action = Position::nowhere);
	inline bool makeMove(Move move) { return makeMove(move.m_unit, move.m_movement, move.m_action); }
	bool makeMove(Unit* unit, Position movement, Position action = Position::nowhere);

	std::vector<Move> getPossibleMoves(UnitColor side);
	std::vector<Move> getPossibleMoves(Unit* unit);

	void newTurn();

	UnitColor playerIdToColor(int id) { return m_sides[id]; }
	int colorToPlayerId(UnitColor color) { return std::distance(m_sides.begin(), std::find(m_sides.begin(), m_sides.end(), color)); }

private:
	void clearUnits() { m_unitsStates.clear(); m_unitsPos.clear(); };
	void addUnit(Unit* ally, const Position& pos, UnitColor side);
	void getPossibleMoves(Unit* unit, Position movement, std::vector<Move>& res);
};

#pragma warning( pop ) 
