#pragma once

#include <string>
#include "FehSim.h"

#pragma warning( push )
#pragma warning( disable : 4251)

enum UnitColor { RED, BLUE, GREEN, COLORLESS };

enum WeaponType { SWORD, LANCE, AXE, TOME, BOW, DAGGER, STAFF, BREATH, BEAST };

// Indexes based on https://feheroes.fandom.com/wiki/User:HertzDevil/Reverse-engineering_notes/Enumeration_types
enum MvtType
{ 
	INFANTRY = 0, 
	ARMORED = 1, 
	CAVALRY = 2, 
	FLYING = 3
};

// Indexes based on https://feheroes.fandom.com/wiki/User:HertzDevil/Reverse-engineering_notes/Enumeration_types
enum WeaponIndex
{
	RED_SWORD = 0,
	BLUE_LANCE = 1,
	GREEN_AXE = 2,
	RED_BOW = 3,
	BLUE_BOW = 4,
	GREEN_BOW = 5,
	COLORLESS_BOW = 6,
	RED_DAGGER = 7,
	BLUE_DAGGER = 8,
	GREEN_DAGGER = 9,
	COLORLESS_DAGGER = 10,
	RED_TOME = 11,
	BLUE_TOME = 12,
	GREEN_TOME = 13,
	COLORLESS_TOME = 14,
	COLORLESS_STAFF = 15,
	RED_BREATH = 16,
	BLUE_BREATH = 17,
	GREEN_BREATH = 18,
	COLORLESS_BREATH = 19,
	RED_BEAST = 20,
	BLUE_BEAST = 21,
	GREEN_BEAST = 22,
	COLORLESS_BEAST = 23
};

static std::string unitColorStr[4] { "RED", "BLUE", "GREEN", "COLORLESS" };
static std::string weaponTypeStr[9] { "SWORD", "LANCE", "AXE", "TOME", "BOW", "DAGGER", "STAFF", "BREATH", "BEAST" };
static std::string mvtTypeStr[4] { "INFANTRY", "ARMORED", "CAVALRY", "FLYING" };

inline std::string FEHSIM_API toString(const UnitColor color) { if (color < RED || color > COLORLESS) return "ERROR"; else return unitColorStr[(int)color]; }
inline std::string FEHSIM_API toString(const WeaponType type) { if (type < SWORD || type > BEAST)     return "ERROR"; else return weaponTypeStr[(int)type]; }
inline std::string FEHSIM_API toString(const MvtType type)    { if (type < INFANTRY || type > ARMORED) return "ERROR"; else return mvtTypeStr[(int)type]; }
std::string FEHSIM_API toString(const WeaponIndex weapon);

static UnitColor getWeaponColor(const WeaponIndex weapon);
static WeaponType getWeaponType(const WeaponIndex weapon);

int FEHSIM_API findInArray(const std::string& str, std::string* values, int size);

inline UnitColor  FEHSIM_API unitColorFromString (const std::string& str) { return (UnitColor) findInArray(str, unitColorStr, COLORLESS); }
inline WeaponType FEHSIM_API weaponTypeFromString(const std::string& str) { return (WeaponType)findInArray(str, weaponTypeStr, BEAST); }
inline MvtType    FEHSIM_API mvtTypeFromString   (const std::string& str) { return (MvtType)   findInArray(str, mvtTypeStr, ARMORED); }

inline int getAttackRange(WeaponType type) { return (type == TOME || type == BOW || type == DAGGER || type == STAFF) ? 2 : 1; }
inline int getMvtRange(MvtType type) { return type == ARMORED ? 1 : type == CAVALRY ? 3 : 2; }
inline bool canFly(MvtType type) { return (type == FLYING); }

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
