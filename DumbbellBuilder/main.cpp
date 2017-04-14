#include "Calculator.h"
#include "Measure.h"
#include "Unit.h"
#include "CommandLineParser.h"

#include <iostream>
#include <sstream>

std::ostream& platesToCsv(std::ostream& strm, const std::vector<CPlate>& Plates, bool saveWeightAsString)
{
    for (const auto& plate : Plates)
    {
        if (saveWeightAsString)
            strm << "=\"" << plate.GetWeight().Kg().Value() << "\";";
        else
            strm << plate.GetWeight().Kg().Value() << ";";
    }

    return strm;
}


std::string resultToCsv(const std::map<measure::CWeight, CDumbbellConfig>& result, bool saveWeightAsString, bool useLocal)
{
    std::stringstream output;

    if (useLocal)
        output.imbue(std::locale(""));

    for (const auto& cfg : result)
    {
        output << cfg.first.Kg().Value() << ";";
        platesToCsv(output, cfg.second.LeftSide().GetPlates(), saveWeightAsString);
        output << "|===|;";
        platesToCsv(output, cfg.second.RightSide().GetPlates(), saveWeightAsString);
        output << "\n";
    }

    return output.str();
}


int main(int argc, char** argv)
{
    using namespace unit::literals;
    argc; argv;


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

    // Duplicate weights
    if (0)
    {
        plates.Add(plate05);

        plates.Add(plate125);

        plates.Add(plate25);
        plates.Add(plate25);

        plates.Add(plate5);
        plates.Add(plate5);
        plates.Add(plate5);

        plates.Add(plate10);
    }


    CDumbbellHandle handle{ measure::CWeight{2.0_kg}, measure::CWidth{10.0_cm} };

    EqualWeightStrategy splitter;
    BalancedWeightEvaluator configEvaluator;

    Calculator calc{ splitter, configEvaluator };
    calc.Calculate(handle, plates);

    std::cout << resultToCsv(calc.Result(), false, true);
    return 0;
}
