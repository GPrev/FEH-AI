#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "Rules.h"
#include "DataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{
	TEST_CLASS(RulesTests)
	{
	private:
		UnitData* m_alphData, * m_sharData;
		Unit m_alphonse;
		Unit m_sharena;
		MapData mm_mapData;
		Map m_map;
		Rules m_rules;
		DataLoader m_dataLoader;

		void setup()
		{
			m_alphData = m_dataLoader.GetUnitData("alfonse-prince-of-askr");
			m_sharData = m_dataLoader.GetUnitData("sharena-princess-of-askr");
			m_alphonse = Unit(*m_alphData);
			m_sharena = Unit(*m_sharData);
			m_alphonse.makeBaseKit(m_dataLoader);
			m_sharena.makeBaseKit(m_dataLoader);

			std::vector<Position> allyPos;
			allyPos.push_back(Position(5, 5));
			std::map<Unit*, Position> foes;
			foes[&m_sharena] = Position(3, 3);
			mm_mapData = MapData(10, 10, allyPos, foes);
			m_map = Map(mm_mapData);
			m_map.init(&m_alphonse);
		}

	public:

		TEST_METHOD(SimpleBattle)
		{
			setup();
			Assert::AreEqual(43, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(43, m_map.getState(&m_sharena).getHP());

			m_rules.doBattle(m_map, &m_alphonse, &m_sharena);
			Assert::AreEqual(0, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(31, m_map.getState(&m_sharena).getHP());
		}
	};
}