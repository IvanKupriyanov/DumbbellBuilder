#pragma once
#include "Dumbbell.h"
#include <algorithm>

struct IDumbbellConfigEvaluator
{
    virtual ~IDumbbellConfigEvaluator() {};

    virtual bool Rank(const CDumbbellHandle& Dumbbellhandle, const CDumbbellConfig& Config)
    {
        if (Config.LeftSide().size() == 0 && Config.RightSide().size() == 0)
            return false;

        if (Config.LeftSide().GetWidth() > Dumbbellhandle.GetPlatesWidth())
            return false;

        if (Config.RightSide().GetWidth() > Dumbbellhandle.GetPlatesWidth())
            return false;

        return RankInternal(Dumbbellhandle, Config);
    }

    virtual void Reset()
    {
        m_Config = {};
        m_IsEmpty = true;
    }

    virtual const CDumbbellConfig& GetBest()
    {
        return m_Config;
    }

protected:
    virtual bool RankInternal(const CDumbbellHandle& Dumbbellhandle, const CDumbbellConfig& Config) = 0;
    
    bool IsBestConfigSet() const
    {
        return !m_IsEmpty;
    }

    void SetBestConfig(const CDumbbellConfig& Config)
    {
        m_Config = Config;
        m_IsEmpty = false;
        m_BestConfigWeightDelta = Config.LeftSide().GetWeight() - Config.RightSide().GetWeight();
    }

    measure::CWeight GetBestConfigWeightDelta() const
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

private:
    CDumbbellConfig m_Config;
    measure::CWeight m_BestConfigWeightDelta;
    bool m_IsEmpty;
};


class BalancedWeightEvaluator : public IDumbbellConfigEvaluator
{
protected:
    bool RankInternal(const CDumbbellHandle& /*Dumbbellhandle*/, const CDumbbellConfig& Config) override
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

        return true;
    }
};
