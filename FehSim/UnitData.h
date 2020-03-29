#pragma once

#include <string>
#include "FehSim.h"

#pragma warning( push )
#pragma warning( disable : 4251)

enum UnitColor { RED, BLUE, GREEN, COLORLESS };

enum UnitType { SWORD, LANCE, AXE, TOME, BOW, DAGGER, STAFF, DRAGONSTONE, BEAST };

enum MvtType { INFANTRY, CAVALRY, FLYER, ARMOUR };

class FEHSIM_API UnitData
{
protected:
	std::string m_name;

	UnitColor m_color;
	UnitType m_type;
	MvtType m_mvt;

	int m_baseHP;
	int m_baseAtk;
	int m_baseSpd;
	int m_baseDef;
	int m_baseRes;

public:
	UnitData() {}
	UnitData(std::string name, UnitColor color, UnitType type, int hp, int atk, int spd, int def, int res)
		: m_name(name), m_color(color), m_type(type), m_baseHP(hp), m_baseAtk(atk), m_baseSpd(spd), m_baseDef(def), m_baseRes(res) {}

	int getBaseHP()  const { return m_baseHP; }
	int getBaseAtk() const  { return m_baseAtk; }
	int getBaseSpd() const { return m_baseSpd; }
	int getBaseDef() const { return m_baseDef; }
	int getBaseRes() const { return m_baseRes; }
	int getBST() const { return m_baseHP + m_baseAtk + m_baseSpd + m_baseDef + m_baseRes; }
};

#pragma warning( pop ) 
