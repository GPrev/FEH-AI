#include "UnitData.h"
#include <string>
#include <iostream>
#include <string>
#include <cctype>


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