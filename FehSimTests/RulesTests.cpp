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
		UnitData* _udata1, * _udata2;
		Unit _ally1;
		Unit _foe1;
		MapData _mdata;
		Map _map;
		Rules _rules;
		DataLoader _loader;

		void setup()
		{
			_udata1 = _loader.GetUnitData("alfonse-prince-of-askr");
			_udata2 = _loader.GetUnitData("sharena-princess-of-askr");
			_ally1 = Unit(*_udata1);
			_foe1 = Unit(*_udata2);

			std::vector<Position> allyPos;
			allyPos.push_back(Position(5, 5));
			std::map<Unit*, Position> foes;
			foes[&_foe1] = Position(3, 3);
			_mdata = MapData(10, 10, allyPos, foes);
			_map = Map(_mdata);
			_map.init(&_ally1);
		}

	public:

		TEST_METHOD(SimpleBattle)
		{
			setup();
			Assert::AreEqual(43, _map.getState(&_ally1).getHP());
			Assert::AreEqual(43, _map.getState(&_foe1).getHP());

			_rules.doBattle(_map, &_ally1, &_foe1);
			Assert::AreEqual(43, _map.getState(&_ally1).getHP()); // Should be 0 with weapon and WT
			Assert::AreEqual(37, _map.getState(&_foe1).getHP()); // Should be 31 with weapon and WT
		}
	};
}