#include "Unit.h"
#include "DataLoader.h"

void Unit::makeBaseKit(DataLoader& loader)
{
	m_weapon = loader.getWeaponData(m_data->getDefaultWeaponID());
}