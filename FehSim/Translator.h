#pragma once

#include <string>
#include <map>
#include "FehSim.h"
#include "json.hpp"

#pragma warning( push )
#pragma warning( disable : 4251)

enum class Language
{
	EUDE = 0,
	EUEN = 1,
	EUES = 2,
	EUFR = 3,
	EUIT = 4,
	JPJA = 5,
	TWZH = 6,
	USEN = 7,
	USES = 8,
	USPT = 9,
	NONE = 10
};

class FEHSIM_API Translator
{
public:
	Translator(Language language = Language::NONE) { m_translations[Language::NONE]; setLanguage(language); }

	void setLanguage(Language language = Language::NONE, bool load = false) { m_language = language; if (load) loadTranslations(language); }
	std::string translate(std::string text);

	static std::string toString(Language language) { return m_unitColorStr[(int)language]; }

private:
	static std::string m_translationPathBegin;
	static std::string m_translationPathEnd;
	static std::string m_unitColorStr[11];

	Language m_language = Language::NONE;
	std::map<Language, std::map<std::string, std::string>> m_translations;

	void loadTranslations(Language language);
	void translationsFromFile(std::string filePath, Language language);
	void translationsFromJson(const nlohmann::json& j, Language language);
};

#pragma warning( pop )
