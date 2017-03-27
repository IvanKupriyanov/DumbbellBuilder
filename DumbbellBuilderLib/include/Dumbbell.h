#pragma once

#include "Plate.h"
#include "Measure.h"

#include <vector>


class CDumbbellConfig
{
public:
    CDumbbellConfig()
    {}

    CDumbbellConfig(CPlates LeftSide, CPlates RightSide)
        : m_LeftSide{ LeftSide }, 
          m_RightSide{ RightSide }
	{}

    const CPlates& LeftSide() const
    {
        return m_LeftSide;
    }
    
    const CPlates& RightSide() const
    {
        return m_RightSide;
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
