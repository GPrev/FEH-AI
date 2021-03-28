#include "UnitData.h"
#include <string>
#include <iostream>
#include <string>
#include <cctype>

std::string toString(const WeaponIndex weapon)
{
	UnitColor color = getWeaponColor(weapon);
	WeaponType type = getWeaponType(weapon);
	return toString(color) + " " + toString(type);
}

UnitColor getWeaponColor(const WeaponIndex weapon)
{
	switch (weapon)
	{
	case RED_SWORD:
	case RED_BOW:
	case RED_DAGGER:
	case RED_TOME:
	case RED_BREATH:
	case RED_BEAST:
		return RED;
	case BLUE_LANCE:
	case BLUE_BOW:
	case BLUE_DAGGER:
	case BLUE_TOME:
	case BLUE_BREATH:
	case BLUE_BEAST:
		return BLUE;
	case GREEN_AXE:
	case GREEN_BOW:
	case GREEN_DAGGER:
	case GREEN_TOME:
	case GREEN_BREATH:
	case GREEN_BEAST:
		return GREEN;
	case COLORLESS_BOW:
	case COLORLESS_DAGGER:
	case COLORLESS_TOME:
	case COLORLESS_STAFF:
	case COLORLESS_BREATH:
	case COLORLESS_BEAST:
	default:
		return COLORLESS;
	}
}

WeaponType getWeaponType(const WeaponIndex weapon)
{
	switch (weapon)
	{
	case RED_SWORD:
		return SWORD;
	case BLUE_LANCE:
		return LANCE;
	case GREEN_AXE:
		return AXE;
	case RED_BOW:
	case BLUE_BOW:
	case GREEN_BOW:
	case COLORLESS_BOW:
		return BOW;
	case RED_DAGGER:
	case BLUE_DAGGER:
	case GREEN_DAGGER:
	case COLORLESS_DAGGER:
		return DAGGER;
	case RED_TOME:
	case BLUE_TOME:
	case GREEN_TOME:
	case COLORLESS_TOME:
		return TOME;
	case COLORLESS_STAFF:
		return STAFF;
	case RED_BREATH:
	case BLUE_BREATH:
	case GREEN_BREATH:
	case COLORLESS_BREATH:
		return BREATH;
	case RED_BEAST:
	case BLUE_BEAST:
	case GREEN_BEAST:
	case COLORLESS_BEAST:
		return BEAST;
	default:
		return SWORD;
	}
}

bool compareChar(const char & c1, const char & c2)
{
	if (c1 == c2)
		return true;
	else if (std::toupper(c1) == std::toupper(c2))
		return true;
	return false;
}

bool caseInSensStringCompare(const std::string & str1, const std::string &str2)
{
	return ((str1.size() == str2.size()) &&
		std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar));
}

int findInArray(const std::string& str, std::string* values, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (caseInSensStringCompare(str, values[i]))
		{
			return i;
		}
	}
	// Valeur par défaut
	return size - 1;
}