#pragma once
#include "Plate.h"
#include "Units.h"

struct IPlatesSplitStrategy
{
    using TPair = std::pair<CPlates, CPlates>;
    virtual ~IPlatesSplitStrategy() {};
    TPair Split(const CPlates& Plates) const
    {
        long middle = FindMiddle(Plates);

        if (middle <= 0)
        {
            return TPair{ Plates , CPlates() };
        }

        auto leftStart = Plates.begin();
        auto leftEnd = Plates.begin() + middle;
        CPlates left{ std::vector<CPlate>{leftStart, leftEnd} };

        auto rightStart = Plates.begin() + middle;
        auto rightEnd = Plates.end();
        CPlates right{ std::vector<CPlate>{rightStart, rightEnd} };

        return TPair{ left, right };
    }

protected:
    virtual long FindMiddle(const CPlates& Plates) const = 0;
};

struct EqualWeightStrategy : public IPlatesSplitStrategy
{

protected:
    long FindMiddle(const CPlates& Plates) const override
    {
        measure::CWeight leftSide;
        for (size_t i = 0, n = Plates.GetPlates().size(); i < n; i++)
        {
            if (leftSide < Plates.GetWeight() - leftSide)
                leftSide += Plates[i].GetWeight();
            else
                return i;
        }

        return -1;
    }
};

