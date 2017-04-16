#include "computation/Calculator.h"
#include "units/Units.h"
#include "cli/CommandLineParser.h"

#include <iostream>
#include <sstream>

std::ostream& platesToCsv(std::ostream& strm, const std::vector<CPlate>& Plates, bool ExportFloatAsString)
{
    for (const auto& plate : Plates)
    {
        if (ExportFloatAsString)
            strm << "=\"" << plate.GetWeight().Kg().Value() << "\";";
        else
            strm << plate.GetWeight().Kg().Value() << ";";
    }

    return strm;
}


std::string resultToCsv(const std::map<measure::CWeight, CDumbbellConfig>& result, bool ExportFloatAsString, bool LocalAwareFormat)
{
    std::stringstream output;

    if (LocalAwareFormat)
        output.imbue(std::locale(""));

    for (const auto& cfg : result)
    {
        output << cfg.first.Kg().Value() << ";";
        platesToCsv(output, cfg.second.LeftSide().GetPlates(), ExportFloatAsString);
        output << "|===|;";
        platesToCsv(output, cfg.second.RightSide().GetPlates(), ExportFloatAsString);
        output << "\n";
    }

    return output.str();
}


int main(int argc, char** argv)
{
    using namespace unit::literals;
    argc; argv;
    CCommandLineParser options;

    try
    {
        options.Parse(argc, argv);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
        return -1;
    }

    CDumbbellHandle handle{ options.HandleWeight(), options.HandleWidth() };

    EqualWeightStrategy splitter;
    BalancedWeightEvaluator configEvaluator;

    Calculator calc{ splitter, configEvaluator };
    calc.Calculate(handle, options.Plates());

    std::cout << resultToCsv(calc.Result(), options.ExportFloatAsString(), options.LocalAwareFormat());
    return 0;
}
