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
	friend class DataLoader;

private:
	std::string m_id;

	int m_turnsToWin = 0;
	bool m_lastEnemyPhase = false;
	int m_turnsToDefend = 0;

	int m_width;
	int m_height;

	std::vector<Position> m_allyPos;
	std::vector<Position> m_enemyPos;
	std::vector<Unit> m_foes;

public:
	MapData() {}
	MapData(std::string id, int width, int height, std::vector<Position> allyPos, std::vector<Position> enemyPos, std::vector<Unit> foes = std::vector<Unit>())
		: m_id(id), m_width(width), m_height(height), m_allyPos(allyPos), m_enemyPos(enemyPos), m_foes(foes) {}
	MapData(std::string id, int width, int height, std::vector<Position> allyPos, std::map<Position, Unit> foesPos)
		: m_id(id), m_width(width), m_height(height), m_allyPos(allyPos)
	{
		for (auto const& imap : foesPos)
		{
			m_foes.push_back(imap.second);
			m_enemyPos.push_back(imap.first);
		}
	}
	
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	std::vector<Position>& getAllyPositions() { return m_allyPos; }
	std::vector<Position>& getEnemyPositions() { return m_enemyPos; }
	std::vector<Unit>& getFoes() { return m_foes; }

};

#pragma warning( pop ) 
