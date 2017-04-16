#pragma once
#include <vector>
#include <algorithm>


template <typename T>
class CPermutationsGenerator
{
public:
	CPermutationsGenerator(const std::vector<T>& ItemsSet) : m_ItemsSet(ItemsSet)
	{
		std::sort(m_ItemsSet.begin(), m_ItemsSet.end());
	}

	bool Next()
	{
		return std::next_permutation(m_ItemsSet.begin(), m_ItemsSet.end());
	}

	std::vector<T> GetItems() const
	{
		return m_ItemsSet;
	}

private:
	std::vector<T> m_ItemsSet;
};
