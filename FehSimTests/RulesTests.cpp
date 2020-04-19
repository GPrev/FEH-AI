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
		UnitData* m_alphData, * m_sharData, * m_takData, * m_ninoData;
		Unit m_alphonse, m_sharena, m_takumi, m_nino;
		MapData m_mapData;
		Map m_map;
		Rules m_rules;
		DataLoader m_dataLoader;

		void setup()
		{
			m_alphData = m_dataLoader.GetUnitData("alfonse-prince-of-askr");
			m_sharData = m_dataLoader.GetUnitData("sharena-princess-of-askr");
			m_ninoData = m_dataLoader.GetUnitData("nino-pious-mage");
			m_takData  = m_dataLoader.GetUnitData("takumi-wild-card");
			m_alphonse = Unit(*m_alphData);
			m_sharena = Unit(*m_sharData);
			m_nino = Unit(*m_ninoData);
			m_takumi = Unit(*m_takData);
			m_alphonse.makeBaseKit(m_dataLoader);
			m_sharena.makeBaseKit(m_dataLoader);
			m_nino.makeBaseKit(m_dataLoader);
			m_takumi.makeBaseKit(m_dataLoader);

			std::vector<Position> allyPos;
			allyPos.push_back(Position(5, 5));
			std::map<Unit*, Position> foes;
			foes[&m_sharena] = Position(3, 3);
			foes[&m_nino] = Position(2, 2);
			foes[&m_takumi] = Position(1, 1);
			m_mapData = MapData(10, 10, allyPos, foes);
			m_map = Map(m_mapData);
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

		TEST_METHOD(OneWayBattle)
		{
			setup();
			Assert::AreEqual(43, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(43, m_map.getState(&m_sharena).getHP());
			Assert::AreEqual(33, m_map.getState(&m_nino).getHP());

			m_rules.doBattle(m_map, &m_sharena, &m_nino);
			Assert::AreEqual(43, m_map.getState(&m_sharena).getHP());
			Assert::AreEqual(13, m_map.getState(&m_nino).getHP());

			m_rules.doBattle(m_map, &m_nino, &m_alphonse);
			Assert::AreEqual(13, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(13, m_map.getState(&m_nino).getHP());
		}
	};
}