#include "Enums.h"

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