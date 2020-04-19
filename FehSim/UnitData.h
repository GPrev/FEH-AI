#pragma once

#include <string>
#include "FehSim.h"

#pragma warning( push )
#pragma warning( disable : 4251)

enum UnitColor { RED, BLUE, GREEN, COLORLESS };

enum WeaponType { SWORD, LANCE, AXE, TOME, BOW, DAGGER, STAFF, DRAGONSTONE, BEAST };

enum MvtType { INFANTRY, CAVALRY, FLYER, ARMOUR };

static std::string unitColorStr[4] { "RED", "BLUE", "GREEN", "COLORLESS" };
static std::string weaponTypeStr[9] { "SWORD", "LANCE", "AXE", "TOME", "BOW", "DAGGER", "STAFF", "DRAGONSTONE", "BEAST" };
static std::string mvtTypeStr[4] { "INFANTRY", "CAVALRY", "FLYER", "ARMOUR" };

inline std::string FEHSIM_API toString(const UnitColor color) { if (color < RED || color > COLORLESS) return "ERROR"; else return unitColorStr[(int)color]; }
inline std::string FEHSIM_API toString(const WeaponType type) { if (type < SWORD || type > BEAST)     return "ERROR"; else return weaponTypeStr[(int)type]; }
inline std::string FEHSIM_API toString(const MvtType type)    { if (type < INFANTRY || type > ARMOUR) return "ERROR"; else return mvtTypeStr[(int)type]; }

int FEHSIM_API findInArray(const std::string& str, std::string* values, int size);

inline UnitColor  FEHSIM_API unitColorFromString (const std::string& str) { return (UnitColor) findInArray(str, unitColorStr, COLORLESS); }
inline WeaponType FEHSIM_API weaponTypeFromString(const std::string& str) { return (WeaponType)findInArray(str, weaponTypeStr, BEAST); }
inline MvtType    FEHSIM_API mvtTypeFromString   (const std::string& str) { return (MvtType)   findInArray(str, mvtTypeStr, ARMOUR); }

inline int getAttackRange(WeaponType type) { return (type == TOME || type == BOW || type == DAGGER || type == STAFF) ? 2 : 1; }
inline int getMvtRange(MvtType type) { return type == ARMOUR ? 1 : type == CAVALRY ? 3 : 2; }
inline bool canFly(MvtType type) { return (type == FLYER); }

class FEHSIM_API UnitData
{
	friend class DataLoader;

protected:
	std::string m_name;

	UnitColor m_color;
	WeaponType m_type;
	MvtType m_mvt;

	int m_baseHP;
	int m_baseAtk;
	int m_baseSpd;
	int m_baseDef;
	int m_baseRes;

	std::string m_defaultWeaponID;

public:
	UnitData() {}
	UnitData(std::string name, UnitColor color, WeaponType type, int hp, int atk, int spd, int def, int res)
		: m_name(name), m_color(color), m_type(type), m_baseHP(hp), m_baseAtk(atk), m_baseSpd(spd), m_baseDef(def), m_baseRes(res) {}

	std::string getName() const { return m_name; }

	UnitColor getColor() const { return m_color; }
	WeaponType getWeaponType() const { return m_type; }
	MvtType getMvtType() const { return m_mvt; }

	int getBaseHP()  const { return m_baseHP; }
	int getBaseAtk() const  { return m_baseAtk; }
	int getBaseSpd() const { return m_baseSpd; }
	int getBaseDef() const { return m_baseDef; }
	int getBaseRes() const { return m_baseRes; }
	int getBST() const { return m_baseHP + m_baseAtk + m_baseSpd + m_baseDef + m_baseRes; }

	std::string getDefaultWeaponID() { return m_defaultWeaponID; }
};

#pragma warning( pop ) 
