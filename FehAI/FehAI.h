#pragma once

#include <vector>
#include "Unit.h"

typedef std::vector<Unit*> Team;

#ifdef FEHAI_EXPORTS
#define FEHAI_API __declspec(dllexport)
#else
#define FEHAI_API __declspec(dllimport)
#endif