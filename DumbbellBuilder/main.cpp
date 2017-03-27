#include "Calculator.h"
#include "Measure.h"
#include "Unit.h"

int main()
{
    using namespace unit::literals;

    CPlate plate05 { measure::CWeight(0.5_kg),  measure::CWidth(10.0_mm), measure::CHeight(10.0_mm) };
    CPlate plate125{ measure::CWeight(1.25_kg), measure::CWidth(18.0_mm), measure::CHeight(10.0_mm) };
    CPlate plate25 { measure::CWeight(2.5_kg),  measure::CWidth(22.0_mm), measure::CHeight(10.0_mm) };
    CPlate plate5  { measure::CWeight(5.0_kg),  measure::CWidth(30.0_mm), measure::CHeight(10.0_mm) };
    CPlate plate10 { measure::CWeight(10.0_kg), measure::CWidth(30.0_mm), measure::CHeight(10.0_mm) };

    CPlates plates;
    plates.Add(plate05);

    plates.Add(plate125);

    plates.Add(plate25);
    plates.Add(plate25);
    
    plates.Add(plate5);
    plates.Add(plate5);
    plates.Add(plate5);

    plates.Add(plate10);

    CDumbbellHandle handle{ measure::CWeight{2.0_kg}, measure::CWidth{10.0_cm} };

    EqualWeightStrategy splitter;
    BalancedWeightEvaluator configEvaluator;

    Calculator calc{ splitter, configEvaluator };
    calc.Calculate(handle, plates);

    for (const auto& cfg : calc.Result())
    {
        std::cout << cfg.first.Kg().Value() << ": ";
        for (const auto& plate : cfg.second.LeftSide().GetPlates())
            std::cout << plate.GetWeight().Kg().Value() << " ";

        std::cout << " |===| ";

        for (const auto& plate : cfg.second.RightSide().GetPlates())
            std::cout << plate.GetWeight().Kg().Value() << " ";

        std::cout << "\n";
    }
    return 0;
}
