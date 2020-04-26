#include "DumbAI.h"


DumbAI::DumbAI()
{
}


DumbAI::~DumbAI()
{
}

Move DumbAI::chooseMove(Map& map, UnitColor side)
{
	auto choices = map.getPossibleMoves(side);
	int minDistance = 1000;
	if (choices.size() == 0)
	{
		return Move();
	}
	Move best = choices[0];
	for (auto choice : choices)
	{
		if (choice.m_action != Position::nowhere)
		{
			// Priority to action
			return choice;
		}
		else
		{
			// We go towards enemies
			int dist = choice.m_movement.distance(closestEnemy(map, choice.m_unit));
			if (dist < minDistance)
			{
				minDistance = dist;
				best = choice;
			}
		}
	}
	return best;
}

Position DumbAI::closestEnemy(Map& map, Unit* unit)
{
	UnitColor side = map.getState(unit).getSide();
	Position pos = map.getPos(unit);
	auto units = map.getUnits();
	int minDistance = 1000;
	Position best = Position::nowhere;
	for (auto unit : units)
	{
		if (map.getState(unit.first).getSide() != side)
		{
			int dist = pos.distance(unit.second);
			if (minDistance > dist)
			{
				minDistance = dist;
				best = unit.second;
			}
		}
	}
	return best;
}