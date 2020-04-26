#pragma once

#ifdef FEHAI_EXPORTS
#define FEHAI_API __declspec(dllexport)
#else
#define FEHAI_API __declspec(dllimport)
#endif