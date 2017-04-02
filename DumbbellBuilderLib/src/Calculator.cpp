#include "Calculator.h"

#include "CombinationsGenerator.h"
#include "PermutationsGenerator.h"
#include "Dumbbell.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

static std::string log(const CPlates& Plates)
{
    std::stringstream strm;
    for (auto it = Plates.begin(), end = Plates.end(); it != end; ++it)
    {
        strm << it->GetWeight();
        if (it + 1 != end)
            strm << ", ";
    }

    return strm.str();
}

static std::string permutationToString(const std::pair<CPlates, CPlates>& Weights)
{
    std::stringstream strm;
    strm << "Permutation: [";
    strm << log(Weights.first);
    strm << "] {" << Weights.first.GetWeight() << "} | [";
    strm << log(Weights.second);
    strm << "] {" << Weights.second.GetWeight() << "}";
    strm << " ~ delta: " << Weights.first.GetWeight() - Weights.second.GetWeight();

    return strm.str();
}

Calculator::Calculator(const IPlatesSplitStrategy& Splitter, IDumbbellConfigEvaluator& DumbbellConfigEvaluator)
    : m_SplitStrategy{ Splitter }, m_DumbbellConfigEvaluator{ DumbbellConfigEvaluator }
{
}

void Calculator::Calculate(const CDumbbellHandle & DumbbellHandle, const CPlates & Plates)
{
    CCombinationsGenerator<CPlate> comb(Plates.GetPlates());
    do
    {
        CPlates combination{ comb.GetItems() };

        if (combination.GetWidth() >= DumbbellHandle.GetPlatesWidth() * 2.0f)
        {
#ifdef LOG
            std::cout << "Combination: " << log(combination) << " width " << combination.GetWidth() << " more than " << DumbbellHandle.GetPlatesWidth() * 2.0f << "\n";
#endif
            continue;
        }

#ifdef LOG
        std::cout << "Combination: " << log(combination) << "(" << combination.GetWeight() << "kg)\n";
#endif
        CPermutationsGenerator<CPlate> perm(combination.GetPlates());
        m_DumbbellConfigEvaluator.Reset();
        do
        {
            auto pair = m_SplitStrategy.Split(perm.GetItems());

#ifdef LOG
            std::cout << permutationToString(pair);
#endif

            assert(pair.first.size()  > 0 || pair.second.size() > 0);

            bool isNewBetter = m_DumbbellConfigEvaluator.Rank(DumbbellHandle, CDumbbellConfig{ pair.first, pair.second });
#ifdef LOG
            std::cout << (isNewBetter ? " - USE" : " - SKIP") << '\n';
#endif

        } while (perm.Next());
#ifdef LOG
        std::cout << '\n';
#endif

        auto best = m_DumbbellConfigEvaluator.GetBest();
        m_Result[DumbbellHandle.GetWeigth() + best.LeftSide().GetWeight() + best.RightSide().GetWeight()] = best;
    } while (comb.Next());
}

const std::map<measure::CWeight, CDumbbellConfig>& Calculator::Result() const
{
    return m_Result;
}
