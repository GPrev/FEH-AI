#pragma once

#ifdef FEHSIM_EXPORTS
#define FEHSIM_API __declspec(dllexport)
#else
#define FEHSIM_API __declspec(dllimport)
#endif

#ifndef  MAP_CONTAINS_KEY
#define MAP_CONTAINS_KEY(M, X) ((M).find(X) != (M).end())
#endif

typedef unsigned int uint;
