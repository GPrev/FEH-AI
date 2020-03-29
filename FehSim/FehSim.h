#pragma once

#ifdef FEHSIM_EXPORTS
#define FEHSIM_API __declspec(dllexport)
#else
#define FEHSIM_API __declspec(dllimport)
#endif