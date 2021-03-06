#pragma once

#include "DumbbellConfigEvaluator.h"
#include "PlatesSplitStrategy.h"
#include "model/Plate.h"
#include "units/Units.h"

#include <map>
#include <ostream>

inline std::ostream& operator<<(std::ostream& Stream, const measure::CWeight& Weight)
{
    Stream << Weight.Kg().Value();
    return Stream;
}

inline std::ostream& operator<<(std::ostream& Stream, const measure::CWidth& Width)
{
    Stream << Width.Mm().Value();
    return Stream;
}

class Calculator
{
public:
    Calculator(const IPlatesSplitStrategy& Splitter, IDumbbellConfigEvaluator& DumbbellConfigEvaluator);

    void Calculate(const CDumbbellHandle& DumbbellHandle, const CPlates& Plates);
    const std::map<measure::CWeight, CDumbbellConfig>& Result() const;
    const CDumbbellConfig* Result(const measure::CWeight& Weight) const;

private:
    std::map<measure::CWeight, CDumbbellConfig> m_Result;
    const IPlatesSplitStrategy& m_SplitStrategy;
    IDumbbellConfigEvaluator& m_DumbbellConfigEvaluator;
};

