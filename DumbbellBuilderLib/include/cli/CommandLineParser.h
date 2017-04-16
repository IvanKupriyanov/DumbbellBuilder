#pragma once
#include "units/Units.h"
#include "model/Plate.h"

class CCommandLineParser
{
public:
    void Parse(int argc, const char* const* argv);

    bool ExportFloatAsString() const;
    bool LocalAwareFormat() const;
    measure::CWeight HandleWeight() const;
    measure::CWidth HandleWidth() const;
    const CPlates& Plates() const;

private:
    bool m_ExportFloatAsString;
    bool m_LocalAwareFormat;
    measure::CWeight m_HandleWeight;
    measure::CWidth m_HandleWidth;
    CPlates m_Plates;

};
