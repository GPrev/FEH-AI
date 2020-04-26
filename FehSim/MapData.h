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
	std::vector<Position> m_enemyPos;
	std::vector<Unit*> m_foes;

public:
	MapData() {}
	MapData(int width, int height, std::vector<Position> allyPos, std::vector<Position> enemyPos, std::vector<Unit*> foes)
		: m_width(width), m_height(height), m_allyPos(allyPos), m_enemyPos(enemyPos), m_foes(foes) {}
	MapData(int width, int height, std::vector<Position> allyPos, std::map<Unit*, Position> foesPos)
		: m_width(width), m_height(height), m_allyPos(allyPos)
	{
		for (auto const& imap : foesPos)
		{
			m_foes.push_back(imap.first);
			m_enemyPos.push_back(imap.second);
		}
	}
	
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	std::vector<Position>& getAllyPositions() { return m_allyPos; }
	std::vector<Position>& getEnemyPositions() { return m_enemyPos; }
	std::vector<Unit*>& getFoes() { return m_foes; }

};

#pragma warning( pop ) 
