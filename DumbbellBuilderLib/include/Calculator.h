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

inline std::ostream& operator<<(std::ostream& Stream, const measure::CWeight& Weight)
{
    Stream << Weight.Kg().Value();
    return Stream;
}

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
        do
        {
            CPlates combination{ comb.GetItems() };
            std::cout << "Combination: ";
            log(combination);
            std::cout << "(" << combination.GetWeight().Kg().Value() << "kg)\n";

            CPermutationsGenerator<CPlate> perm(combination.GetPlates());
            m_DumbbellConfigEvaluator.Reset();
            do
            {
                auto pair = m_SplitStrategy.Split(perm.GetItems());
                std::cout << "Permutation: [";
                log(pair.first);
                std::cout << "] {" << pair.first.GetWeight() << "} | [";
                log(pair.second);
                std::cout << "] {" << pair.second.GetWeight() << "}";
                std::cout << " ~ delta: " << pair.first.GetWeight() - pair.second.GetWeight();

                if (m_DumbbellConfigEvaluator.Rank(DumbbellHandle, CDumbbellConfig{ pair.first, pair.second }))
                {
                    std::cout << " - USE";
                }
                else
                {
                    std::cout << " - SKIP";
                }
                std::cout << '\n';

            } while (perm.Next());
            std::cout << '\n';

            auto best = m_DumbbellConfigEvaluator.GetBest();
            m_Result[DumbbellHandle.GetWeigth() + best.LeftSide().GetWeight() + best.RightSide().GetWeight()] = best;
        } while (comb.Next());
    }

    const std::map<measure::CWeight, CDumbbellConfig>& Result() const
    {
        return m_Result;
    }

private:
    void log(const CPlates& Plates)
    {
        for (auto it = Plates.begin(), end = Plates.end(); it != end; ++it)
        {
            std::cout << it->GetWeight().Kg().Value();
            if (it + 1 != end)
                std::cout << ", ";
        }
    }
private:
    std::map<measure::CWeight, CDumbbellConfig> m_Result;
    const IPlatesSplitStrategy& m_SplitStrategy;
    IDumbbellConfigEvaluator& m_DumbbellConfigEvaluator;
};

