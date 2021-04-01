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

		std::string realText = u8"MPID_比翼マルス";
		std::string realTextTranslated = "Marth";
		std::string falseText = "FooBar";

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
	};
}