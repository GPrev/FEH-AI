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
		UnitData _udata1;
		Unit _ally1;
		Unit _foe1;
		MapData _mdata;
		Map _map;

		void setup()
		{
			_ally1 = Unit(_udata1);
			_foe1 = Unit(_udata1);

			std::vector<Position> allyPos;
			allyPos.push_back(Position(5, 5));
			std::map<Unit*, Position> foes;
			foes[&_foe1] = Position(3, 3);
			_mdata = MapData(10, 10, allyPos, foes);
			_map = Map(_mdata);
			_map.init(&_ally1);
		}

	public:
		
		TEST_METHOD(IsFree)
		{
			setup();

			Assert::IsTrue(_map.isFree(Position(0, 0)));
			Assert::IsFalse(_map.isFree(Position(3, 3)));
			Assert::IsFalse(_map.isFree(Position(5, 5)));
		}

		TEST_METHOD(GetPos)
		{
			setup();

			Assert::AreEqual(Position(5, 5), _map.getPos(&_ally1));
			Assert::AreEqual(Position(3, 3), _map.getPos(&_foe1));
		}

	};
}