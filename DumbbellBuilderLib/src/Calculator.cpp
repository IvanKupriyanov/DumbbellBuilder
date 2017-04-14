#include "Calculator.h"

#include "CombinationsGenerator.h"
#include "PermutationsGenerator.h"
#include "Dumbbell.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

//#define LOG

#ifdef LOG
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
#endif

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

#ifdef LOG
        std::cout << "Combination: " << log(combination) << "(" << combination.GetWeight() << "kg)\n";
#endif
        if (combination.GetWidth() >= DumbbellHandle.GetPlatesWidth() * 2.0f)
        {
#ifdef LOG
            std::cout << "Width " << combination.GetWidth() << " more than " << DumbbellHandle.GetPlatesWidth() * 2.0f << "\n";
#endif
            continue;
        }

        CPermutationsGenerator<CPlate> perm(combination.GetPlates());

        const auto weightConfig = Result(combination.GetWeight() + DumbbellHandle.GetWeigth());
        if (weightConfig == nullptr)
            m_DumbbellConfigEvaluator.Reset();
        else
            m_DumbbellConfigEvaluator.Reset(*weightConfig);

        do
        {
            auto pair = m_SplitStrategy.Split(perm.GetItems());

            assert(pair.first.size()  > 0 || pair.second.size() > 0);

            bool isNewBetter = m_DumbbellConfigEvaluator.Rank(DumbbellHandle, CDumbbellConfig{ pair.first, pair.second }); isNewBetter;
            
#ifdef LOG
            std::cout << permutationToString(pair) << (isNewBetter ? " - USE" : " - SKIP") << '\n';
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

const CDumbbellConfig* Calculator::Result(const measure::CWeight& Weight) const
{
    auto it = m_Result.find(Weight);
    if (it == m_Result.end())
    {
        return nullptr;
    }

    return &it->second;
}
