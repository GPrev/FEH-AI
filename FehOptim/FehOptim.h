#pragma once

#include <vector>
#include "Unit.h"

#ifdef FEHOPTIM_EXPORTS
#define FEHOPTIM_API __declspec(dllexport)
#else
#define FEHOPTIM_API __declspec(dllimport)
#endif