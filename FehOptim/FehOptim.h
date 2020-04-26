#pragma once

#include <vector>
#include "Unit.h"

typedef std::vector<Unit*> Team;

#ifdef FEHOPTIM_EXPORTS
#define FEHOPTIM_API __declspec(dllexport)
#else
#define FEHOPTIM_API __declspec(dllimport)
#endif