#pragma once

#include "FehSim.h"
#include "Enums.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Terrain
{
	friend class DataLoader;

private:
	uint m_index;
	int m_baseTerrain;
	int m_foeBaseTerrain;
	int m_side;
	uint m_terrainGroup;
	bool m_inaccessible;
	uint m_hp;
	bool m_isWall;
	bool m_isLiquid;
	bool m_isBridge;
	bool m_isTrench;
	bool m_isFortress;
	bool m_isRdTerrain;
	uint m_mitMod;
	uint m_regenHp;

public:
	Terrain() {};

	uint getId() const { return m_index; }

	bool canMove(MvtType mvt) const { return moveCost(mvt) != noMove; }
	int moveCost(MvtType mvt) const;
	
	static const Terrain noTerrain;
	static const int noMove = 99;

private:
	bool isForest()	const { return m_terrainGroup == 3; }
	bool isLiquidOrMountain()	const { return m_isLiquid || m_index == 4; }
	int flyCost()	const { if (m_isWall) return noMove; else return 1; }
	int crawlCost()	const { if (m_isWall || isLiquidOrMountain()) return noMove; else return 1; }
	int walkCost()	const { if (m_isWall || isLiquidOrMountain()) return noMove; else if (isForest()) return 2; else return 1; }
	int rideCost()	const { if (m_isWall || isLiquidOrMountain() || isForest()) return noMove; else if (m_isTrench) return 2; else return 1; }
};

#pragma warning( pop )
