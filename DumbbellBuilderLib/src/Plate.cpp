#include "Plate.h"
#include "Measure.h"

#include <vector>


CPlate::CPlate(measure::CWeight Weight, measure::CWidth Width, measure::CHeight Height)
    : m_Weight(Weight), m_Width(Width), m_Height(Height)
{
}

measure::CWeight CPlate::GetWeight() const
{
    return m_Weight;
}

measure::CWidth CPlate::GetWidth() const
{
    return m_Width;
}

measure::CHeight CPlate::GetHeight() const
{
    return m_Height;
}

bool CPlate::operator < (const CPlate& Rhs) const
{
    return m_Weight < Rhs.m_Weight;
}

bool CPlate::operator == (const CPlate& Other) const
{
    if (m_Weight != Other.m_Weight)
        return false;

    return true;
}

CPlates::CPlates()
{
}

CPlates::CPlates(const std::vector<CPlate>& Plates)
{
    for (const auto& plate : Plates)
    {
        Add(plate);
    }
}


std::vector<CPlate> CPlates::GetPlates() const
{
    return m_Plates;
}

void CPlates::Add(const CPlate& Plate)
{
    m_Weight += Plate.GetWeight();
    m_Width += Plate.GetWidth();

    m_Plates.push_back(Plate);
}

measure::CWeight CPlates::GetWeight() const
{
    return m_Weight;
}

measure::CWidth CPlates::GetWidth() const
{
    return m_Width;
}

const CPlate& CPlates::operator[](size_t Index) const
{
    return m_Plates[Index];
}

CPlates::It CPlates::begin() const
{
    return m_Plates.begin();
}


CPlates::It CPlates::end() const
{
    return m_Plates.end();
}

size_t CPlates::size() const
{
    return m_Plates.size();
}

