#pragma once
#include "Measure.h"

#include <vector>


struct CPlate
{
    CPlate(measure::CWeight Weight, measure::CWidth Width, measure::CHeight Height)
        : m_Weight(Weight), m_Width(Width), m_Height(Height)
    {
    }

    measure::CWeight GetWeight() const
    {
        return m_Weight;
    }

    measure::CWidth GetWidth() const
    {
        return m_Width;
    }

    measure::CHeight GetHeight() const
    {
        return m_Height;
    }

    bool operator < (const CPlate& Rhs) const
    {
        return m_Weight < Rhs.m_Weight;
    }

    bool operator == (const CPlate& Other) const
    {
        if (m_Weight != Other.m_Weight)
            return false;

        return true;
    }
private:
    measure::CWeight m_Weight;
    measure::CWidth  m_Width;
    measure::CHeight m_Height;

};

struct CPlates
{
    using It = std::vector<CPlate>::const_iterator;
    CPlates()
    {}

    CPlates(const std::vector<CPlate>& Plates)
    {
        for (const auto& plate : Plates)
        {
            Add(plate);
        }
    }

    std::vector<CPlate> GetPlates() const
    {
        return m_Plates;
    }

    void Add(const CPlate& Plate)
    {
        m_Weight += Plate.GetWeight();
        m_Width += Plate.GetWidth();

        m_Plates.push_back(Plate);
    }

    measure::CWeight GetWeight() const
    {
        return m_Weight;
    }

    measure::CWidth GetWidth() const
    {
        return m_Width;
    }

    const CPlate& operator[](size_t Index) const
    {
        return m_Plates[Index];
    }

    It begin() const
    {
        return m_Plates.begin();
    }


    It end() const
    {
        return m_Plates.end();
    }

    size_t size() const
    {
        return m_Plates.size();
    }


private:
    std::vector<CPlate> m_Plates;
    measure::CWeight m_Weight;
    measure::CWidth m_Width;
};


