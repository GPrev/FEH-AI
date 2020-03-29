#pragma once

#include <stdlib.h>
#include <vector>
#include <map>
#include "FehSim.h"
#include "Unit.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Position
{
private:
	int m_x;
	int m_y;

public:
	Position(int x = 0, int y = 0) : m_x(x), m_y(y) {}

	int getX() const { return m_x; }
	int getY() const { return m_y; }

	bool isSomewhere() { return *this != nowhere; }
	int distance(const Position& pos) const { return abs(m_x - pos.m_x) + abs(m_y - pos.m_y); }

	bool operator==(const Position& pos) const { return m_x == pos.m_x && m_y == pos.m_y; }
	bool operator!=(const Position& pos) const { return !(*this == pos); }

	std::string toString() const;

	static const Position nowhere;
};

#pragma warning( pop )
