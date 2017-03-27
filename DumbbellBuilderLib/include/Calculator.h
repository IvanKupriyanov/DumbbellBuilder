#pragma once

#include "CombinationsGenerator.h"
#include "PermutationsGenerator.h"
#include "DumbbellConfigEvaluator.h"
#include "PlatesSplitStrategy.h"
#include "Dumbbell.h"
#include "Plate.h"
#include "Measure.h"
#include "Unit.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>


class Calculator
{
public:

    Calculator(const IPlatesSplitStrategy& Splitter, IDumbbellConfigEvaluator& DumbbellConfigEvaluator)
        : m_SplitStrategy{ Splitter }, m_DumbbellConfigEvaluator{ DumbbellConfigEvaluator }
    {
    }

    void Calculate(const CDumbbellHandle& DumbbellHandle, const CPlates& Plates)
    {
        CCombinationsGenerator<CPlate> comb(Plates.GetPlates());
        while (comb.Next())
        {
            CPermutationsGenerator<CPlate> perm(comb.GetItems());
            m_DumbbellConfigEvaluator.Reset();
            while (perm.Next())
            {
                auto pair = m_SplitStrategy.Split(perm.GetItems());
                m_DumbbellConfigEvaluator.Rank(DumbbellHandle, CDumbbellConfig{ pair.first, pair.second });
            }

            auto best = m_DumbbellConfigEvaluator.GetBest();
            m_Result[DumbbellHandle.GetWeigth() + best.LeftSide().GetWeight() + best.RightSide().GetWeight()] = best;
        }
    }

    const std::map<measure::CWeight, CDumbbellConfig>& Result() const
    {
        return m_Result;
    }

private:
    std::map<measure::CWeight, CDumbbellConfig> m_Result;
    const IPlatesSplitStrategy& m_SplitStrategy;
    IDumbbellConfigEvaluator& m_DumbbellConfigEvaluator;
};

