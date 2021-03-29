#pragma once

class FEHSIM_API Stats
{
private:
	int m_hp = 0;
	int m_atk = 0;
	int m_spd = 0;
	int m_def = 0;
	int m_res = 0;

public:
	Stats() {}

	Stats(int atk, int spd, int def, int res) : m_atk(atk), m_spd(spd), m_def(def), m_res(res) {}
	Stats(int hp, int atk, int spd, int def, int res) : m_hp(hp), m_atk(atk), m_spd(spd), m_def(def), m_res(res) {}

	int getHp() const { return m_hp; }
	int getAtk() const { return m_atk; }
	int getSpd() const { return m_spd; }
	int getDef() const { return m_def; }
	int getRes() const { return m_res; }

	Stats operator+(const Stats& b) const
	{
		return Stats(m_hp + b.m_hp, m_atk + b.m_atk, m_spd + b.m_spd, m_def + b.m_def, m_res + b.m_res);
	}

	Stats operator-() const
	{
		return Stats(-m_atk, -m_spd, -m_def, -m_res);
	}

	Stats operator-(const Stats& b) const
	{
		return *this + (-b);
	}

	static Stats max(const Stats& a, const Stats& b) { return Stats(std::max(a.m_hp, b.m_hp), std::max(a.m_atk, b.m_atk), std::max(a.m_spd, b.m_spd), std::max(a.m_def, b.m_def), std::max(a.m_res, b.m_res)); }

	static Stats hpStat (int hp)  { return Stats(hp, 0, 0, 0, 0);  }
	static Stats atkStat(int atk) { return Stats(0, atk, 0, 0, 0); }
	static Stats spdStat(int spd) { return Stats(0, 0, spd, 0, 0); }
	static Stats defStat(int def) { return Stats(0, 0, 0, def, 0); }
	static Stats resStat(int res) { return Stats(0, 0, 0, 0, res); }
};
