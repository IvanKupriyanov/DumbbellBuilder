#pragma once
#include "Measure.h"
#include "Plate.h"

class CCommandLineParser
{
public:
    void Parse(int argc, const char* const* argv);

    bool WeightAsString() const;
    bool UseLocal() const;
    measure::CWeight HandleWeight() const;
    measure::CWidth HandleWidth() const;
    const CPlates& Plates() const;

private:
    bool m_WeightAsString;
    bool m_UseLocal;
    measure::CWeight m_HandleWeight;
    measure::CWidth m_HandleWidth;
    CPlates m_Plates;

};
