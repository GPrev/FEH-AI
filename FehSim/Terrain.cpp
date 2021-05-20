#include "Terrain.h"

const Terrain Terrain::noTerrain;

int Terrain::moveCost(MvtType mvt) const
{
	switch (mvt)
	{
	case INFANTRY:
		return walkCost();
	case ARMORED:
		return crawlCost();
	case CAVALRY:
		return rideCost();
	case FLYING:
		return flyCost();
	default:
		return 0;
	}
}