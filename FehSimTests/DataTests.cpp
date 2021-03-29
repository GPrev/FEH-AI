#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "DataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{
	TEST_CLASS(DataTests)
	{
	private:
		DataLoader m_dataLoader = DataLoader(true);

	public:

		TEST_METHOD(EnumToString)
		{
			Assert::AreEqual(std::string("BLUE"), toString(BLUE));
			Assert::AreEqual(std::string("LANCE"), toString(LANCE));
		}

		TEST_METHOD(LoadMarth)
		{
			UnitData* data = m_dataLoader.getUnitData("toto");
			Assert::IsNull(data);

			data = m_dataLoader.getUnitData(u8"PID_マルス");
			Assert::IsNotNull(data);
			Assert::AreEqual(std::string("MARTH"), data->getName());
			Assert::AreEqual(RED, data->getColor());
			Assert::AreEqual(SWORD, data->getWeaponType());
			Assert::AreEqual(INFANTRY, data->getMvtType());
			Assert::AreEqual(18, data->getBaseStats().getHp());
			Assert::AreEqual(6, data->getBaseStats().getAtk());
			Assert::AreEqual(7, data->getBaseStats().getSpd());
			Assert::AreEqual(6, data->getBaseStats().getDef());
			Assert::AreEqual(5, data->getBaseStats().getRes());
		}

		TEST_METHOD(LoadSieglinde)
		{
			Skill* weapon = m_dataLoader.getSkillData(u8"SID_ジークリンデ");
			Assert::IsNotNull(weapon);
			Assert::AreEqual(std::string(u8"MSID_ジークリンデ"), weapon->getName());
			Assert::AreEqual(16, weapon->getMight());
		}

		TEST_METHOD(LoadBaseKit)
		{
			UnitData* data = m_dataLoader.getUnitData(u8"PID_マルス");
			Assert::AreEqual(std::string("folkvangr"), data->getDefaultWeaponID());

			Unit unit(*data);
			Assert::IsNull(unit.getWeapon());

			unit.makeBaseKit(m_dataLoader);
			Assert::AreEqual(std::string(u8"MSID_ジークリンデ"), unit.getWeapon()->getName());
		}
	};
}