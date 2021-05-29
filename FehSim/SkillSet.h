#pragma once

#include "Enums.h"
#include "Skill.h"
#include <numeric>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

#pragma warning( push )
#pragma warning( disable : 4251)

class FEHSIM_API SkillSet
{
public:

	SkillSet() { };

	const Skill* getSkill(SkillCategory slot) const;
	void setSkill(const Skill* skill);
	void setSkillIfMoreExpensive(const Skill* skill);

	void addAll(const SkillSet& skills);
	void addAllIfMoreExpensive(const SkillSet& skills);

	int getWeaponEffectiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponEffectiveMask()); });
	}
	int getMovementEffectiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementEffectiveMask()); });
	}
	int getWeaponProtectionMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponProtectionMask()); });
	}
	int getMovementProtectionMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementProtectionMask()); });
	}
	int getWeaponWeaknessMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponWeaknessMask()); });
	}
	int getMovementWeaknessMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementWeaknessMask()); });
	}
	int getWeaponAdaptiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getWeaponAdaptiveMask()); });
	}
	int getMovementAdaptiveMask() const {
		return std::accumulate(std::begin(m_skills), std::end(m_skills), 0,
			[](int sum, const Skill* skill) { return sum + (skill == nullptr ? 0 : skill->getMovementAdaptiveMask()); });
	}

protected:
	Skill const* m_skills[7] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

public:
	// https://internalpointers.com/post/writing-custom-iterators-modern-cpp
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Skill const*;
		using pointer = value_type*;
		using reference = value_type&;

		Iterator(pointer ptr, pointer end) : m_ptr(ptr), m_end(end) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		Iterator& operator++() { m_ptr++; while (m_ptr < m_end && *m_ptr == nullptr) { m_ptr++; }  return *this; }

		// Postfix increment
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
		pointer m_end;
	};

	struct ConstantIterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Skill const*;
		using pointer = const value_type*;
		using reference = const value_type&;

		ConstantIterator(pointer ptr, pointer end) : m_ptr(ptr), m_end(end) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }

		// Prefix increment
		ConstantIterator& operator++() { m_ptr++; while (m_ptr < m_end && *m_ptr == nullptr) { m_ptr++; }  return *this; }

		// Postfix increment
		ConstantIterator operator++(int) { ConstantIterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const ConstantIterator& a, const ConstantIterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const ConstantIterator& a, const ConstantIterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
		pointer m_end;
	};

	typedef typename Iterator iterator;
	typedef typename ConstantIterator const_iterator;

	iterator begin() { return Iterator(&m_skills[0], &m_skills[7]); }
	iterator end() { return Iterator(&m_skills[7], &m_skills[7]); } // 7 is out of bounds
	const_iterator cbegin() const { return ConstantIterator(&m_skills[0], &m_skills[7]); }
	const_iterator cend() const { return ConstantIterator(&m_skills[7], &m_skills[7]); } // 7 is out of bounds
	const_iterator begin() const { return ConstantIterator(&m_skills[0], &m_skills[7]); }
	const_iterator end() const { return ConstantIterator(&m_skills[7], &m_skills[7]); } // 7 is out of bounds
};

#pragma warning( pop ) 
