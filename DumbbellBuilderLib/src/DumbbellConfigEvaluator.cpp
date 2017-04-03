#include "DumbbellConfigEvaluator.h"

#include "Dumbbell.h"
#include <algorithm>

IDumbbellConfigEvaluator::~IDumbbellConfigEvaluator()
{
}

bool IDumbbellConfigEvaluator::Rank(const CDumbbellHandle& Dumbbellhandle, const CDumbbellConfig& Config)
{
    if (Config.LeftSide().size() == 0 && Config.RightSide().size() == 0)
        return false;

    if (Config.LeftSide().GetWidth() > Dumbbellhandle.GetPlatesWidth())
        return false;

    if (Config.RightSide().GetWidth() > Dumbbellhandle.GetPlatesWidth())
        return false;

    return RankInternal(Dumbbellhandle, Config);
}

void IDumbbellConfigEvaluator::Reset()
{
    m_Config = {};
    m_IsEmpty = true;
}


void IDumbbellConfigEvaluator::Reset(const CDumbbellConfig& Best)
{
    m_Config = Best;
    m_IsEmpty = false;
}

const CDumbbellConfig& IDumbbellConfigEvaluator::GetBest()
{
    return m_Config;
}

bool IDumbbellConfigEvaluator::IsBestConfigSet() const
{
    return !m_IsEmpty;
}

void IDumbbellConfigEvaluator::SetBestConfig(const CDumbbellConfig& Config)
{
    m_Config = Config;
    m_IsEmpty = false;
    m_BestConfigWeightDelta = Config.LeftSide().GetWeight() - Config.RightSide().GetWeight();
}

measure::CWeight IDumbbellConfigEvaluator::GetBestConfigWeightDelta() const
{
    return m_BestConfigWeightDelta;
}


static bool ArePlatesSorted(const CPlates& Plates)
{
    return std::is_sorted(Plates.begin(), Plates.end());
}

static measure::CWeight CalcWeightDelta(const CDumbbellConfig& Config)
{
    return Config.LeftSide().GetWeight() - Config.RightSide().GetWeight();
}



bool BalancedWeightEvaluator::RankInternal(const CDumbbellHandle& /*Dumbbellhandle*/, const CDumbbellConfig& Config) 
{
    if (!IsBestConfigSet())
    {
        SetBestConfig(Config);
        return true;
    }
        
    if (CalcWeightDelta(Config) > GetBestConfigWeightDelta())
        return false;

    if (!ArePlatesSorted(Config.LeftSide()))
        return false;

    if (!ArePlatesSorted(Config.RightSide()))
        return false;

    SetBestConfig(Config);
    return true;
}
