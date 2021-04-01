#include "UnitData.h"

std::string UnitData::getTitle() const
{
	size_t splitPos = m_name.find('_');
	return m_name.substr(0, splitPos) + "_HONOR" + m_name.substr(splitPos);
}