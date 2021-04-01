#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include "Translator.h"

using json = nlohmann::json;
using std::filesystem::directory_iterator;

std::string Translator::m_translationPathBegin = "../../feh-assets-json/files/assets/";
std::string Translator::m_translationPathEnd = "/Message/Data/";
std::string Translator::m_unitColorStr[11]{ "EUDE", "EUEN", "EUES", "EUFR", "EUIT", "JPJA", "TWZH", "USEN", "USES", "USPT", "" };

std::string Translator::translate(std::string text)
{
	std::string res = text;
	loadTranslations(m_language);
	std::map<std::string, std::string>& translations = m_translations[m_language];
	if (MAP_CONTAINS_KEY(translations, text))
	{
		res = translations[text];
	}
	return res;
}

void Translator::loadTranslations(Language language)
{
	if (!MAP_CONTAINS_KEY(m_translations, m_language))
	{
		std::string path = m_translationPathBegin + toString(language) + m_translationPathEnd;
		for (const auto& file : directory_iterator(path))
		{
			translationsFromFile(file.path().string(), language);
		}
	}
}

void Translator::translationsFromFile(std::string filePath, Language language)
{
	std::ifstream i(filePath);
	json j;
	i >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		translationsFromJson(*it, language);
	}
}

void Translator::translationsFromJson(const json& j, Language language)
{
	if (j["key"].is_string() && j["value"].is_string())
	{
		m_translations[language][j["key"].get<std::string>()] = j["value"].get<std::string>();
	}
}