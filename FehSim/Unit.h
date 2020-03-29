#pragma once

#include <algorithm>
#include "FehSim.h"
#include "UnitData.h"

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

class FEHSIM_API Unit
{
private:
	UnitData* m_data;

	int m_currentHP;
	Buffs m_buffs;

public:
	Unit() {}
	Unit(UnitData& data) : m_data(&data) {}
	~Unit() {};

	int getMaxHP() { return m_data->getBaseHP(); }
	int getHP()    { return m_currentHP; }
	int getAtk()   { return m_data->getBaseAtk() + m_buffs.getAtk(); }
	int getSpd()   { return m_data->getBaseSpd() + m_buffs.getSpd(); }
	int getDef()   { return m_data->getBaseDef() + m_buffs.getDef(); }
	int getRes()   { return m_data->getBaseRes() + m_buffs.getRes(); }
	int getMvt()   { return 2; } // TODO consider mvt types and buffs
	int getRange() { return 2; } // TODO consider weapon
	bool canCC()   { return true; } // TODO consider weapon and skills
	bool canDC()   { return false; } // TODO consider weapon and skills

	void addBuffs(Buffs buffs)   { m_buffs = Buffs::max(m_buffs, buffs); }
	void resetBuffs() { m_buffs = Buffs(); }
};

#pragma warning( pop ) 
