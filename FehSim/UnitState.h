#pragma once

#include "Unit.h"
#include "Stats.h"

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API UnitState
{
private:
	Unit* m_unit = nullptr;

	UnitColor m_side = COLORLESS;
	int m_currentHP = 0;
	Stats m_buffs;

	bool m_hasActed = false;

public:
	UnitState() {}
	UnitState(Unit& unit, UnitColor side) : m_unit(&unit), m_side(side), m_currentHP(unit.getStats().getHp()) {}
	~UnitState() {};

	Unit* getUnit() { return m_unit; }

	UnitColor getSide() const { return m_side; }

	bool hasActed() const { return m_hasActed; }
	void setHasActed(bool hasActed) { m_hasActed = hasActed; }

	int getHP() const { return m_currentHP; }
	bool isDead() const { return m_currentHP <= 0; }
	Stats getStats() const { return m_unit->getStats() + m_buffs; }
	int getMvt() const { return m_unit->getMvt(); } // TODO consider buffs
	int getRange() const { return m_unit->getRange(); }
	bool canAttack() const { return m_unit->canAttack(); }
	bool canCC() const { return m_unit->canCC(); } // TODO consider debuffs
	bool canDC() const { return m_unit->canDC(); } // TODO consider debuffs

	void addBuffs(Stats buffs) { m_buffs = Stats::max(m_buffs, buffs); }
	void resetBuffs() { m_buffs = Stats(); }

	void loseLife(int amount, bool canKill = true) { m_currentHP -= std::min(amount, m_currentHP - (canKill ? 0 : 1)); }
	void gainLife(int amount) { m_currentHP = std::min(getStats().getHp(), m_currentHP + amount); }
};

