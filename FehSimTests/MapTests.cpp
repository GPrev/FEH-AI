#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{		
	TEST_CLASS(MapTests)
	{
	private:
		UnitData m_udata1;
		Unit m_ally1;
		Unit m_foe1;
		MapData m_mdata;
		Map m_map;

		void setup()
		{
			m_ally1 = Unit(m_udata1);
			m_foe1 = Unit(m_udata1);

			std::vector<Position> allyPos;
			allyPos.push_back(Position(5, 5));
			std::map<Unit*, Position> foes;
			foes[&m_foe1] = Position(3, 3);
			m_mdata = MapData(10, 10, allyPos, foes);
			m_map = Map(m_mdata);
			m_map.init(&m_ally1);
		}

	public:
		
		TEST_METHOD(IsFree)
		{
			setup();

			Assert::IsTrue(m_map.isFree(Position(0, 0)));
			Assert::IsFalse(m_map.isFree(Position(3, 3)));
			Assert::IsFalse(m_map.isFree(Position(5, 5)));
		}

		TEST_METHOD(GetPos)
		{
			setup();

			Assert::AreEqual(Position(5, 5), m_map.getPos(&m_ally1));
			Assert::AreEqual(Position(3, 3), m_map.getPos(&m_foe1));
		}

	};
}