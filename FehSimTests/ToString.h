#pragma once

#include "Map.h"
#include <string>
#include <codecvt>
#include <locale>

using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;

inline std::string to_string(std::wstring wstr) { return strconverter.to_bytes(wstr); };

inline std::wstring to_wstring(std::string str) { return strconverter.from_bytes(str); };

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			static std::wstring ToString<Position>(const Position& coord) { return to_wstring(coord.toString()); }
		}
	}
}