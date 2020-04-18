#include "Unit.h"
#include "DataLoader.h"

void Unit::makeBaseKit(DataLoader& loader)
{
	m_weapon = loader.GetWeaponData(m_data->getDefaultWeaponID());
}