#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "DataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{
	TEST_CLASS(UnitDataTests)
	{
	private:
		DataLoader m_data;

	public:

		TEST_METHOD(EnumToString)
		{
			Assert::AreEqual(std::string("BLUE"), toString(BLUE));
		}

		TEST_METHOD(LoadAlfonse)
		{
			UnitData* data = m_data.GetUnitData("alfonse");
			Assert::IsNull(data);

			data = m_data.GetUnitData("alfonse-prince-of-askr");
			Assert::IsNotNull(data);
			Assert::AreEqual(std::string("Alfonse"), data->getName());
			Assert::AreEqual(RED, data->getColor());
			Assert::AreEqual(SWORD, data->getWeaponType());
			Assert::AreEqual(INFANTRY, data->getMvtType());
			Assert::AreEqual(43, data->getBaseHP());
			Assert::AreEqual(35, data->getBaseAtk());
			Assert::AreEqual(25, data->getBaseSpd());
			Assert::AreEqual(32, data->getBaseDef());
			Assert::AreEqual(22, data->getBaseRes());
			Assert::AreEqual(157, data->getBST());
		}
	};
}