#pragma once

#include "Plate.h"
#include "Measure.h"

#include <vector>
#include <cassert>


class CDumbbellConfig
{
public:
    CDumbbellConfig()
    {}

    CDumbbellConfig(const CPlates& LeftSide, const CPlates& RightSide)
        : m_LeftSide{ LeftSide }, 
          m_RightSide{ RightSide }
	{
    }

    const CPlates& LeftSide() const
    {
        return m_LeftSide;
    }
    
    const CPlates& RightSide() const
    {
        return m_RightSide;
    }

    bool operator ==(const CDumbbellConfig& Other) const
    {
        const auto& left1 = m_LeftSide;
        const auto& left2 = Other.m_LeftSide;
        if (!std::equal(left1.begin(), left1.end(),
            left2.begin(), left2.end()))
            return false;

        const auto& right1 = m_RightSide;
        const auto& right2 = Other.m_RightSide;
        if (!std::equal(right1.begin(), right1.end(),
            right2.begin(), right2.end()))
            return false;

        return true;
    }
private:
	CPlates m_LeftSide, m_RightSide;
};


class CDumbbellHandle
{
public:
    CDumbbellHandle(const measure::CWeight& Weigth, const measure::CWidth& PlatesWidth)
        : m_Weigth{ Weigth }, m_PlatesWidth{ PlatesWidth }
    {
    }

    CDumbbellHandle()
    {}

    measure::CWeight GetWeigth() const
    {
        return m_Weigth;
    }

    measure::CWidth  GetPlatesWidth() const
    {
        return m_PlatesWidth;
    }

private:
    measure::CWeight m_Weigth;
    measure::CWidth  m_PlatesWidth;
};
