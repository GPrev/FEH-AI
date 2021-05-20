﻿#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "Map.h"
#include "UniversalDataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{		
	TEST_CLASS(MapTests)
	{
	private:
		DataLoader& m_dataLoader = UniversalDataLoader::m_dataLoader;
		UnitData* m_udata1;
		Unit m_ally1;
		Unit m_foe1;
		Unit m_foe2;
		MapData m_mdata;
		Map m_map;

		void setup()
		{
			m_udata1 = m_dataLoader.getUnitData(u8"PID_アルフォンス");

			m_ally1 = Unit(*m_udata1);
			m_foe1 = Unit(*m_udata1);
			m_foe2 = Unit(*m_udata1);

			m_ally1.makeBaseKit();
			m_foe1.makeBaseKit();
			m_foe2.makeBaseKit();

			std::vector<Position> allyPos{ Position(5, 5) };
			std::vector<Position> foesPos{ Position(3, 3), Position(4, 4) };
			m_mdata = MapData("map", 10, 10, allyPos, foesPos);
			m_map = Map(m_mdata);

			std::vector<Unit*> allies{ &m_ally1 };
			std::vector<Unit*> foes{ &m_foe1, &m_foe2 };
			m_map.init(&allies, &foes);
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

		TEST_METHOD(CanMakeMove)
		{
			setup();

			Assert::IsTrue(m_map.canMakeMove(&m_ally1, Position(5, 5)));
			Assert::IsTrue(m_map.canMakeMove(&m_ally1, Position(6, 6)));
			Assert::IsFalse(m_map.canMakeMove(&m_ally1, Position(4, 4)));
			Assert::IsFalse(m_map.canMakeMove(&m_ally1, Position(7, 7)));

			Assert::IsTrue(m_map.canMakeMove(&m_ally1, Position(4, 5), Position(4, 4)));
			Assert::IsTrue(m_map.canMakeMove(&m_ally1, Position(5, 4), Position(4, 4)));
			Assert::IsFalse(m_map.canMakeMove(&m_ally1, Position(5, 5), Position(4, 4)));
			Assert::IsFalse(m_map.canMakeMove(&m_ally1, Position(6, 6), Position(4, 4)));
		}

		TEST_METHOD(MakeMove)
		{
			setup();

			m_map.makeMove(&m_ally1, Position(5, 6));
			Assert::AreEqual(Position(5, 6), m_map.getPos(&m_ally1));

			m_map.makeMove(&m_ally1, Position(4, 5), Position(4, 4));
			Assert::AreEqual(Position(4, 5), m_map.getPos(&m_ally1));
			Assert::AreEqual(24, m_map.getState(&m_ally1).getHP());
			Assert::AreEqual(24, m_map.getState(&m_foe2).getHP());
			Assert::AreEqual(43, m_map.getState(&m_foe1).getHP());

			m_map.makeMove(&m_ally1, Position(4, 5), Position(4, 4));
			m_map.makeMove(&m_ally1, Position(4, 5), Position(4, 4));
			Assert::IsTrue(m_map.getState(&m_foe2).isDead());
			Assert::AreEqual(Position::nowhere, m_map.getPos(&m_foe2));
		}

		TEST_METHOD(PossibleMoves)
		{
			setup();

			auto moves = m_map.getPossibleMoves(&m_ally1);
			Assert::AreEqual(14, (int)moves.size());

			m_map.makeMove(&m_ally1, Position(8, 8));
			moves = m_map.getPossibleMoves(&m_ally1);
			Assert::AreEqual(0, (int)moves.size());

			m_map.newTurn();
			m_map.newTurn();

			Assert::IsFalse(m_map.getState(&m_ally1).hasActed());
			moves = m_map.getPossibleMoves(&m_ally1);
			Assert::AreEqual(11, (int)moves.size());
		}

		TEST_METHOD(MoveThroughTerrain)
		{
			Map map(*m_dataLoader.getMapData("F0001"));

			Unit foot(*m_dataLoader.getUnitData(u8"PID_アルフォンス"));
			Unit cav(*m_dataLoader.getUnitData(u8"PID_ラインハルト"));
			Unit armor(*m_dataLoader.getUnitData(u8"PID_ヘクトル"));
			Unit fly(*m_dataLoader.getUnitData(u8"PID_ティアモ"));
			std::vector<Unit*> allies = { &cav, &foot, &armor, &fly };
			map.init(&allies);

			// Cavalry movement
			Assert::IsTrue(map.canMakeMove(&cav, Position(1, 3))); // Up once
			Assert::IsTrue(map.canMakeMove(&cav, Position(1, 4))); // Up twice
			Assert::IsTrue(map.canMakeMove(&cav, Position(2, 4))); // Three tiles away
			Assert::IsFalse(map.canMakeMove(&cav, Position(1, 6))); // Four tiles away
			Assert::IsFalse(map.canMakeMove(&cav, Position(1, 1))); // Down to the forest

			// Infantry movement
			Assert::IsTrue(map.canMakeMove(&foot, Position(2, 1))); // Down once
			Assert::IsTrue(map.canMakeMove(&foot, Position(0, 2))); // Left twice
			Assert::IsFalse(map.canMakeMove(&foot, Position(5, 2))); // Right three times
			Assert::IsTrue(map.canMakeMove(&foot, Position(2, 3))); // Up to the forest
			Assert::IsFalse(map.canMakeMove(&foot, Position(2, 4))); // Up through the forest
			Assert::IsFalse(map.canMakeMove(&foot, Position(3, 1))); // Down right to the forest

			// Armor movement
			Assert::IsTrue(map.canMakeMove(&armor, Position(3, 3))); // Up once
			Assert::IsFalse(map.canMakeMove(&armor, Position(3, 4))); // Up twice
			Assert::IsTrue(map.canMakeMove(&armor, Position(3, 1))); // Down to the forest

			// Flying movement
			Assert::IsTrue(map.canMakeMove(&fly, Position(4, 3))); // Up to the forest
			Assert::IsTrue(map.canMakeMove(&fly, Position(4, 4))); // Up opver the forest
			Assert::IsFalse(map.canMakeMove(&fly, Position(4, 5))); // Three tiles away
		}

	};
}