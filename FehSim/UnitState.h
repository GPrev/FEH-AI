#pragma once

#include "Unit.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API Buffs
{
private:
	int m_atk = 0;
	int m_spd = 0;
	int m_def = 0;
	int m_res = 0;

public:
	Buffs() {}

	Buffs(int atk, int spd, int def, int res) : m_atk(atk), m_spd(spd), m_def(def), m_res(res) {}

	int getAtk() { return m_atk; }
	int getSpd() { return m_spd; }
	int getDef() { return m_def; }
	int getRes() { return m_res; }

	Buffs operator+(const Buffs& b) const
	{
		return Buffs(m_atk + b.m_atk, m_spd + b.m_spd, m_def + b.m_def, m_res + b.m_res);
	}

	Buffs operator-() const
	{
		return Buffs(-m_atk, -m_spd, -m_def, -m_res);
	}

	Buffs operator-(Buffs b) const
	{
		return *this + (-b);
	}

	static Buffs max(const Buffs& a, const Buffs& b) { return Buffs(std::max(a.m_atk, b.m_atk), std::max(a.m_spd, b.m_spd), std::max(a.m_def, b.m_def), std::max(a.m_res, b.m_res)); }

	static Buffs atkBuff(int atk) { return Buffs(atk, 0, 0, 0); }
	static Buffs spdBuff(int spd) { return Buffs(0, spd, 0, 0); }
	static Buffs defBuff(int def) { return Buffs(0, 0, def, 0); }
	static Buffs resBuff(int res) { return Buffs(0, 0, 0, res); }
};

class FEHSIM_API UnitState
{
private:
	Unit* m_unit;

	UnitColor m_side = COLORLESS;
	int m_currentHP;
	Buffs m_buffs;

public:
	UnitState() {}
	UnitState(Unit& unit, UnitColor side) : m_unit(&unit), m_side(side), m_currentHP(unit.getMaxHP()) {}
	~UnitState() {};

	Unit* getUnit() { return m_unit; }

	UnitColor getSide() const { return m_side; }

	int getMaxHP() { return m_unit->getMaxHP(); }
	int getHP() { return m_currentHP; }
	bool isDead() { return m_currentHP <= 0; }
	int getAtk() { return m_unit->getAtk() + m_buffs.getAtk(); }
	int getSpd() { return m_unit->getSpd() + m_buffs.getSpd(); }
	int getDef() { return m_unit->getDef() + m_buffs.getDef(); }
	int getRes() { return m_unit->getRes() + m_buffs.getRes(); }
	int getMvt() { return m_unit->getMvt(); } // TODO consider buffs
	int getRange() { return m_unit->getRange(); }
	bool canAttack() { return m_unit->canAttack(); }
	bool canCC() { return m_unit->canCC(); } // TODO consider debuffs
	bool canDC() { return m_unit->canDC(); } // TODO consider debuffs

	void addBuffs(Buffs buffs) { m_buffs = Buffs::max(m_buffs, buffs); }
	void resetBuffs() { m_buffs = Buffs(); }

	void loseLife(int amount, bool canKill = true) { m_currentHP -= std::min(amount, m_currentHP - (canKill ? 0 : 1)); }
	void gainLife(int amount) { m_currentHP = std::min(getMaxHP(), m_currentHP + amount); }
};

