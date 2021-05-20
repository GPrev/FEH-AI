#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToString.h"
#include "UniversalDataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FehSimTests
{
	TEST_CLASS(DataTests)
	{
	private:
		DataLoader& m_dataLoader = UniversalDataLoader::m_dataLoader;

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
			Assert::AreEqual(std::string(u8"MPID_マルス"), data->getName());
			
			Assert::AreEqual(RED, data->getColor());
			Assert::AreEqual(SWORD, data->getWeaponType());
			Assert::AreEqual(INFANTRY, data->getMvtType());

			Assert::AreEqual(18, data->getBaseStats().getHp());
			Assert::AreEqual(6, data->getBaseStats().getAtk());
			Assert::AreEqual(7, data->getBaseStats().getSpd());
			Assert::AreEqual(6, data->getBaseStats().getDef());
			Assert::AreEqual(5, data->getBaseStats().getRes());

			// Base weapon and max weapon at 2 stars
			Assert::AreEqual(std::string(u8"SID_鉄の剣"), data->getLearnedSkills(2).getSkill(SkillCategory::WEAPON)->getId());
			Assert::AreEqual(std::string(u8"SID_鋼の剣"), data->getLearnableSkills(2).getSkill(SkillCategory::WEAPON)->getId());
			// Base weapon at 5 stars
			Assert::AreEqual(std::string(u8"SID_ファルシオン"), data->getLearnedSkills(5).getSkill(SkillCategory::WEAPON)->getId());
			// Base assist and max assist at 3 stars
			Assert::IsNull(data->getLearnedSkills(3).getSkill(SkillCategory::ASSIST));
			Assert::AreEqual(std::string(u8"SID_回り込み"), data->getLearnableSkills(3).getSkill(SkillCategory::ASSIST)->getId());

		}

		TEST_METHOD(LoadSieglinde)
		{
			Skill* weapon = m_dataLoader.getSkillData(u8"SID_ジークリンデ");
			Assert::IsNotNull(weapon);
			Assert::AreEqual(std::string(u8"MSID_ジークリンデ"), weapon->getName());
			Assert::AreEqual(toString(SkillCategory::WEAPON), toString(weapon->getCategory()));
			Assert::AreEqual(16, weapon->getMight());
		}

		TEST_METHOD(LoadBaseKit)
		{
			UnitData* data = m_dataLoader.getUnitData(u8"PID_マルス");

			Unit unit(*data);
			Assert::IsNull(unit.getSkill(SkillCategory::WEAPON));

			unit.makeBaseKit();
			Assert::IsNotNull(unit.getSkill(SkillCategory::WEAPON));
			Assert::AreEqual(std::string(u8"SID_ファルシオン"), unit.getSkill(SkillCategory::WEAPON)->getId());
			Assert::AreEqual(std::string(u8"SID_回り込み"), unit.getSkill(SkillCategory::ASSIST)->getId());
			Assert::IsNull(unit.getSkill(SkillCategory::PASSIVE_B));
		}

		void TestUnit(const Unit& unit, const Stats& expectedStats)
		{
			const Stats& actualStats = unit.getStats();
			Assert::AreEqual(expectedStats.getHp(), actualStats.getHp());
			Assert::AreEqual(expectedStats.getAtk(), actualStats.getAtk());
			Assert::AreEqual(expectedStats.getSpd(), actualStats.getSpd());
			Assert::AreEqual(expectedStats.getDef(), actualStats.getDef());
			Assert::AreEqual(expectedStats.getRes(), actualStats.getRes());
		}

		TEST_METHOD(StatCalculation)
		{
			UnitData* data = m_dataLoader.getUnitData(u8"PID_マルス");

			TestUnit(Unit(*data, 1, 1), Stats(17, 5, 6, 5, 4));
			TestUnit(Unit(*data, 2, 1), Stats(17, 6, 7, 5, 4));
			TestUnit(Unit(*data, 3, 1), Stats(18, 6, 7, 6, 5));
			TestUnit(Unit(*data, 4, 1), Stats(18, 7, 8, 6, 5));
			TestUnit(Unit(*data, 5, 1), Stats(19, 7, 8, 7, 6));

			TestUnit(Unit(*data, 1, 40), Stats(33, 23, 25, 21, 17));
			TestUnit(Unit(*data, 2, 40), Stats(34, 25, 28, 22, 18));
			TestUnit(Unit(*data, 3, 40), Stats(37, 27, 30, 25, 20));
			TestUnit(Unit(*data, 4, 40), Stats(38, 29, 32, 26, 21));
			TestUnit(Unit(*data, 5, 40), Stats(41, 31, 34, 29, 23));
		}

		void TestTerrain(uint terrainID, int expectedFlyCost, int expectedCrawlCost, int expectedWalkCost, int expectedRideCost)
		{
			const Terrain* terrain = m_dataLoader.getTerrain(terrainID);
			Assert::AreEqual(expectedFlyCost, terrain->moveCost(MvtType::FLYING));
			Assert::AreEqual(expectedCrawlCost, terrain->moveCost(MvtType::ARMORED));
			Assert::AreEqual(expectedWalkCost, terrain->moveCost(MvtType::INFANTRY));
			Assert::AreEqual(expectedRideCost, terrain->moveCost(MvtType::CAVALRY));
		}

		TEST_METHOD(LoadTerrain)
		{
			int n = Terrain::noMove;
			TestTerrain(0, 1, 1, 1, 1); //Outdoor
			TestTerrain(1, 1, 1, 1, 1); //Indoor
			TestTerrain(2, 1, 1, 1, 1); //Desert
			TestTerrain(3, 1, 1, 2, n); //Forest
			TestTerrain(4, 1, n, n, n); //Mountain
			TestTerrain(5, 1, n, n, n); //River
			TestTerrain(6, 1, n, n, n); //Sea
			TestTerrain(7, 1, n, n, n); //Lava
			TestTerrain(8, n, n, n, n); //Wall
			TestTerrain(22, 1, 1, 1, 2); //Outdoor trench
			TestTerrain(23, 1, 1, 1, 2); //Indoor trench
		}

		TEST_METHOD(LoadMap)
		{
			std::vector<std::string>& mapNames = m_dataLoader.getMapNames();
			Assert::AreNotEqual((size_t)0, mapNames.size());
			MapData* data = m_dataLoader.getMapData("F0001");
			Assert::AreEqual(std::string("F0001"), data->getId());

			Assert::AreEqual(6, data->getWidth());
			Assert::AreEqual(8, data->getHeight());

			auto& allyPos = data->getAllyPositions();
			auto& enemyPos = data->getEnemyPositions();
			auto& foes = data->getFoes();

			Assert::AreEqual((size_t)4, allyPos.size());
			Assert::AreEqual(1, allyPos[0].getX());
			Assert::AreEqual(2, allyPos[0].getY());

			Assert::AreEqual((size_t)10, enemyPos.size());
			Assert::AreEqual(1, enemyPos[0].getX());
			Assert::AreEqual(7, enemyPos[0].getY());

			Assert::AreEqual((size_t)10, foes.size());
			Assert::IsNotNull(foes[0].getData());
			Assert::AreEqual(std::string(u8"EID_ソードファイター"), foes[0].getData()->getId());
			Assert::AreEqual(18, foes[0].getStats().getHp());
			Assert::AreEqual(5, foes[0].getStats().getSpd());
			Assert::AreEqual(std::string(u8"SID_鉄の剣"), foes[0].getSkill(SkillCategory::WEAPON)->getId());

			Assert::AreEqual((uint)4, data->getTerrain(Position(5, 0))->getId());
			Assert::AreEqual((uint)4, data->getTerrain(Position(0, 7))->getId());
		}
	};
}