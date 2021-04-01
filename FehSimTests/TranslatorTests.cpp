#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "UniversalDataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{
	TEST_CLASS(TranslatorTests)
	{
	private:
		DataLoader& m_dataLoader = UniversalDataLoader::m_dataLoader;
		Translator& m_translator = UniversalDataLoader::m_translator;

		std::string realText = u8"MPID_マルス";
		std::string realTextTranslated = "Marth";
		std::string falseText = "FooBar";

		std::string unitID = u8"PID_マルス";
		std::string unitName = "Marth";
		std::string unitTitle = "Altean Prince";

		std::string skillID = u8"SID_ファルシオン";
		std::string skillName = "Falchion";

	public:
		// Testing no translation mode
		TEST_METHOD(NoTranslation)
		{
			m_translator.setLanguage(Language::NONE);
			Assert::AreEqual(realText, m_translator.translate(realText));
			Assert::AreEqual(falseText, m_translator.translate(falseText));
		}

		TEST_METHOD(SimpleTranslation)
		{
			m_translator.setLanguage(Language::EUEN);
			Assert::AreEqual(realTextTranslated, m_translator.translate(realText));
			Assert::AreEqual(falseText, m_translator.translate(falseText));
		}

		TEST_METHOD(UnitTranslation)
		{
			m_translator.setLanguage(Language::EUEN);
			UnitData* data = m_dataLoader.getUnitData(unitID);
			Assert::AreEqual(unitName, data->getName(m_translator));
			Assert::AreEqual(unitTitle, data->getTitle(m_translator));
		}

		TEST_METHOD(SkillTranslation)
		{
			m_translator.setLanguage(Language::EUEN);
			Skill* data = m_dataLoader.getSkillData(skillID);
			Assert::AreEqual(skillName, data->getName(m_translator));
		}
	};
}