#pragma once
#include "units/Units.h"

#include <vector>


struct CPlate
{
    CPlate(measure::CWeight Weight, measure::CWidth Width, measure::CHeight Height);

    measure::CWeight GetWeight() const;
    measure::CWidth GetWidth() const;
    measure::CHeight GetHeight() const;

    bool operator < (const CPlate& Rhs) const;
    bool operator == (const CPlate& Other) const;

private:
    measure::CWeight m_Weight;
    measure::CWidth  m_Width;
    measure::CHeight m_Height;
};

struct CPlates
{
    using It = std::vector<CPlate>::const_iterator;
    CPlates();
    CPlates(const std::vector<CPlate>& Plates);

    std::vector<CPlate> GetPlates() const;
    void Add(const CPlate& Plate);
    measure::CWeight GetWeight() const;
    measure::CWidth GetWidth() const;

    const CPlate& operator[](size_t Index) const;

    It begin() const;
    It end() const;
    size_t size() const;

private:
    std::vector<CPlate> m_Plates;
    measure::CWeight m_Weight;
    measure::CWidth m_Width;
};


