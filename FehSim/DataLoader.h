#pragma once

#include <string>
#include <map>
#include "UnitData.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API DataLoader
{
private:
	std::string m_heroDataPath = "../../kagerochart-data/hero/";

	std::map<std::string, UnitData> m_units;

public:
	DataLoader();
	~DataLoader();

	UnitData* GetUnitData(std::string unitID);

private:
	UnitData UnitDataFromFile(std::string filePath);
};

#pragma warning( pop )
