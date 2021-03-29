#pragma once

#include <string>
#include "FehSim.h"

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

static std::string unitColorStr[4]{ "RED", "BLUE", "GREEN", "COLORLESS" };
static std::string weaponTypeStr[9]{ "SWORD", "LANCE", "AXE", "TOME", "BOW", "DAGGER", "STAFF", "BREATH", "BEAST" };
static std::string mvtTypeStr[4]{ "INFANTRY", "ARMORED", "CAVALRY", "FLYING" };

inline std::string FEHSIM_API toString(const UnitColor color) { if (color < RED || color > COLORLESS) return "ERROR"; else return unitColorStr[(int)color]; }
inline std::string FEHSIM_API toString(const WeaponType type) { if (type < SWORD || type > BEAST)     return "ERROR"; else return weaponTypeStr[(int)type]; }
inline std::string FEHSIM_API toString(const MvtType type) { if (type < INFANTRY || type > ARMORED) return "ERROR"; else return mvtTypeStr[(int)type]; }
std::string FEHSIM_API toString(const WeaponIndex weapon);

UnitColor getWeaponColor(const WeaponIndex weapon);
WeaponType getWeaponType(const WeaponIndex weapon);

int FEHSIM_API findInArray(const std::string& str, std::string* values, int size);

inline UnitColor  FEHSIM_API unitColorFromString(const std::string& str) { return (UnitColor)findInArray(str, unitColorStr, COLORLESS); }
inline WeaponType FEHSIM_API weaponTypeFromString(const std::string& str) { return (WeaponType)findInArray(str, weaponTypeStr, BEAST); }
inline MvtType    FEHSIM_API mvtTypeFromString(const std::string& str) { return (MvtType)findInArray(str, mvtTypeStr, ARMORED); }

inline int getAttackRange(WeaponType type) { return (type == TOME || type == BOW || type == DAGGER || type == STAFF) ? 2 : 1; }
inline int getMvtRange(MvtType type) { return type == ARMORED ? 1 : type == CAVALRY ? 3 : 2; }
inline bool canFly(MvtType type) { return (type == FLYING); }
