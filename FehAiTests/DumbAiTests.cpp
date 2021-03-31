#include "stdafx.h"
#include "CppUnitTest.h"
#include "DumbAI.h"
#include "Rules.h"
#include "DataLoader.h"
#include "ToString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehAiTests
{		
	TEST_CLASS(DumbAiTests)
	{
	private:
		MapData m_mapData;
		Unit m_alphonse, m_sharena, m_nino;
		Map m_map;
		Rules m_rules;
		DataLoader m_dataLoader;
		DumbAI m_ai;

		void setup()
		{
			UnitData* aData = m_dataLoader.getUnitData(u8"PID_アルフォンス");
			UnitData* sData = m_dataLoader.getUnitData(u8"PID_シャロン");
			UnitData* nData = m_dataLoader.getUnitData(u8"PID_ニノ");
			m_alphonse = Unit(*aData);
			m_sharena = Unit(*sData);
			m_nino = Unit(*nData);
			m_alphonse.makeBaseKit();
			m_sharena.makeBaseKit();
			m_nino.makeBaseKit();

			std::vector<Position> allyPos;
			allyPos.push_back(Position(5,8));
			std::map<Unit*, Position> foes;
			foes[&m_sharena] = Position(4, 2);
			foes[&m_nino] = Position(7, 2);
			m_mapData = MapData(10, 10, allyPos, foes);
			m_map = Map(m_mapData);
			m_map.init(&m_alphonse);
		}


	public:
		
		TEST_METHOD(DumbAiTest)
		{
			setup();
			Assert::AreEqual(Position(5, 8), m_map.getPos(&m_alphonse));
			Assert::AreEqual(Position(4, 2), m_map.getPos(&m_sharena));
			Assert::AreEqual(Position(7, 2), m_map.getPos(&m_nino));
			Assert::AreEqual(7, m_map.getPos(&m_alphonse).distance(m_map.getPos(&m_sharena)));
			Assert::AreEqual(8, m_map.getPos(&m_alphonse).distance(m_map.getPos(&m_nino)));

			m_ai.makeMove(m_map, BLUE);
			Assert::AreEqual(5, m_map.getPos(&m_alphonse).distance(m_map.getPos(&m_sharena)));

			m_map.newTurn();

			m_ai.makeMove(m_map, RED);
			Assert::AreEqual(3, m_map.getPos(&m_alphonse).distance(m_map.getPos(&m_sharena)));
			m_ai.makeMove(m_map, RED);
			Assert::AreEqual(6, m_map.getPos(&m_alphonse).distance(m_map.getPos(&m_nino)));

			m_map.newTurn();

			m_ai.makeMove(m_map, BLUE);
			Assert::IsTrue(m_map.getState(&m_alphonse).isDead());
			Assert::AreNotEqual(43, m_map.getState(&m_sharena).getHP());
		}

	};
}