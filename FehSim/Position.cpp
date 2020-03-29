#include "Position.h"
#include <sstream>

const Position Position::nowhere = Position(-1, -1);

std::string Position::toString() const
{
	std::stringstream ss;
	ss << "[ " << m_x << " ; " << m_y << " ]";
	return ss.str();
}