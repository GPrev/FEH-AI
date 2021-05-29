#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "Rules.h"
#include "UniversalDataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{
	TEST_CLASS(RulesTests)
	{
	private:
		DataLoader& m_dataLoader = UniversalDataLoader::m_dataLoader;
		UnitData* m_alphData, * m_sharData, * m_takData, * m_ninoData;
		Unit m_alphonse, m_sharena, m_takumi, m_nino;
		MapData m_mapData;
		Map m_map;
		Rules m_rules;

		void setup()
		{
			m_alphData = m_dataLoader.getUnitData(u8"PID_アルフォンス");
			m_sharData = m_dataLoader.getUnitData(u8"PID_シャロン");
			m_ninoData = m_dataLoader.getUnitData(u8"PID_ニノ");
			m_takData  = m_dataLoader.getUnitData(u8"PID_タクミ");
			m_alphonse = Unit(*m_alphData);
			m_sharena = Unit(*m_sharData);
			m_nino = Unit(*m_ninoData);
			m_takumi = Unit(*m_takData);
			m_alphonse.makeBaseKit();
			m_sharena.makeBaseKit();
			m_nino.makeBaseKit();
			m_takumi.makeBaseKit();

			std::vector<Position> allyPos{ Position(5, 5) };
			std::vector<Position> foesPos{ Position(3, 3), Position(2, 2), Position(1, 1) };
			m_mapData = MapData("map", 10, 10, allyPos, foesPos);
			m_map = Map(m_mapData);

			std::vector<Unit*> allies{ &m_alphonse };
			std::vector<Unit*> foes{ &m_sharena, &m_nino, &m_takumi };
			m_map.init(&allies, &foes);
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

		TEST_METHOD(WeaponEffectiveness)
		{
			Unit takumi(*m_dataLoader.getUnitData(u8"PID_タクミ"));
			Unit cordelia(*m_dataLoader.getUnitData(u8"PID_ティアモ"), 5, 40, 10); // 5*+10
			takumi.makeBaseKit();
			cordelia.makeBaseKit();

			std::vector<Position> allyPos{ Position(5, 5) };
			std::vector<Position> foesPos{ Position(4, 4) };
			m_mapData = MapData("map", 10, 10, allyPos, foesPos);
			m_map = Map(m_mapData);

			std::vector<Unit*> allies{ &takumi };
			std::vector<Unit*> foes{ &cordelia };
			m_map.init(&allies, &foes);

			Assert::AreEqual(40, m_map.getState(&takumi).getHP());
			Assert::AreEqual(45, m_map.getState(&cordelia).getHP());
			m_rules.doBattle(m_map, &takumi, &cordelia);
			Assert::AreEqual(40, m_map.getState(&takumi).getHP());
			Assert::AreEqual(2, m_map.getState(&cordelia).getHP());
		}

		TEST_METHOD(SkillDeathBlow3)
		{
			// When attacking

			setup();

			m_alphonse.makeFullKit();
			Assert::AreEqual(std::string(u8"SID_鬼神の一撃3"), m_alphonse.getSkill(SkillCategory::PASSIVE_A)->getId());

			Assert::AreEqual(43, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(43, m_map.getState(&m_sharena).getHP());

			m_rules.doBattle(m_map, &m_alphonse, &m_sharena);
			Assert::AreEqual(0, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(26, m_map.getState(&m_sharena).getHP());

			// When attacked

			setup();

			m_alphonse.makeFullKit();
			Assert::AreEqual(std::string(u8"SID_鬼神の一撃3"), m_alphonse.getSkill(SkillCategory::PASSIVE_A)->getId());
			Skill* ironLance = m_dataLoader.getSkillData(u8"SID_鉄の槍");
			m_sharena.setSkill(ironLance);

			Assert::AreEqual(43, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(43, m_map.getState(&m_sharena).getHP());

			m_rules.doBattle(m_map, &m_sharena, &m_alphonse);
			Assert::AreEqual(17, m_map.getState(&m_alphonse).getHP());
			Assert::AreEqual(31, m_map.getState(&m_sharena).getHP());
		}
	};
}