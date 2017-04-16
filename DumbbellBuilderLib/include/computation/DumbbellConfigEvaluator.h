#pragma once
#include "model/Dumbbell.h"
#include <algorithm>

struct IDumbbellConfigEvaluator
{
    virtual ~IDumbbellConfigEvaluator();

    bool Rank(const CDumbbellHandle& Dumbbellhandle, const CDumbbellConfig& Config);
    void Reset();
    void Reset(const CDumbbellConfig& Best);
    const CDumbbellConfig& GetBest();

protected:
    virtual bool RankInternal(const CDumbbellHandle& Dumbbellhandle, const CDumbbellConfig& Config) = 0;
    
    bool IsBestConfigSet() const;
    void SetBestConfig(const CDumbbellConfig& Config);
    measure::CWeight GetBestConfigWeightDelta() const;

private:
    CDumbbellConfig m_Config;
    measure::CWeight m_BestConfigWeightDelta;
    bool m_IsEmpty;
};


class BalancedWeightEvaluator : public IDumbbellConfigEvaluator
{
protected:
    bool RankInternal(const CDumbbellHandle& /*Dumbbellhandle*/, const CDumbbellConfig& Config) override;
};
