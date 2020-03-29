#pragma once

#include <stdlib.h>
#include <vector>
#include <map>
#include "FehSim.h"
#include "Unit.h"
#include "Position.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API MapData
{
private:
	int m_width;
	int m_height;

	std::vector<Position> m_allyPos;
	std::map<Unit*, Position> m_foes;

public:
	MapData() {}
	MapData(int width, int height, std::vector<Position> allyPos, std::map<Unit*, Position> foes) 
		: m_width(width), m_height(height), m_allyPos(allyPos), m_foes(foes) {}
	
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	std::vector<Position>& getAllyPositions() { return m_allyPos; }
	std::map<Unit*, Position>& getFoes() { return m_foes; }

};

#pragma warning( pop ) 
