#pragma once
#include <vector>

template <typename T>
class CCombinationsGenerator
{
public:
    CCombinationsGenerator(const std::vector<T>& ItemsSet)
    {
        m_ItemsSet = ItemsSet;
        Increment(0);
    }

    bool Next()
    {
        return Increment(0);
    }

    std::vector<T> GetItems() const
    {
        std::vector<T> result;
        for (size_t i = 0, n = m_Value.size(); i < n; i++)
        {
            if (m_Value[i])
                result.push_back(m_ItemsSet[i]);
        }

        return result;
    }

private:
    bool Increment(size_t Index)
    {
        if (m_ItemsSet.size() <= Index)
            return false;

        if (m_Value.size() <= Index)
            m_Value.push_back(false);

        if (m_Value[Index])
        {
			// carry
            m_Value[Index] = false;
            return Increment(Index + 1);
        }
        else
        {
            m_Value[Index] = true;
        }

        return true;
    }

private:
    std::vector<T> m_ItemsSet;
    std::vector<bool> m_Value;
};
