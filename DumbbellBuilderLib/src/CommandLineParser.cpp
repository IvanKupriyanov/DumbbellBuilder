#include "CommandLineParser.h"
#include <tclap\CmdLine.h>


// operator= will be used to assign to the vector

struct CPlateData
{
    CPlateData()
    {
    }
    
    CPlateData& operator=(const std::string &str)
    {
        std::istringstream iss(str);
    
        {
            float weight;
            if (!(iss >> weight))
                throw TCLAP::ArgParseException(str + " is not a plates list");
            Weight = measure::CWeight(unit::CKilogram{ weight });
        }

        {
            float width;
            if (!(iss >> width))
                throw TCLAP::ArgParseException(str + " is not a plates list");
            Width = measure::CWidth(unit::CMillimeter{ width });
        }

        {
            float height;
            if (!(iss >> height))
                throw TCLAP::ArgParseException(str + " is not a plates list");
            Height = measure::CHeight(unit::CCentimeter{ height }.To<unit::CMillimeter>());
        }

        {
            if (!(iss >> Count))
                throw TCLAP::ArgParseException(str + " is not a plates list");
        }

        return *this;
    }

    measure::CWeight Weight;
    measure::CWidth Width;
    measure::CHeight Height;
    int Count;

};

namespace TCLAP {
    template<>
    struct ArgTraits<CPlateData> {
        typedef StringLike ValueCategory;
    };
}

void CCommandLineParser::Parse(int argc, const char* const* argv)
{
    TCLAP::CmdLine cmd{ "Dumbbell config calculator" };
    TCLAP::ValueArg<bool> weightAsStringArg{
        "s", "double_to_string", "Save double as string (when weight parsed as date).",
        false, false, "bool", cmd };

    TCLAP::ValueArg<bool> useLocalArg{
        "l", "use_local", "Use local settings for double format.",
        false, false, "bool", cmd };

    TCLAP::ValueArg<double> handleWeightArg{
        "m", "handle_weight", "Weight of dumbbell handle.",
        true, 0.0, "kg", cmd };

    TCLAP::ValueArg<double> handleWidthArg{
        "w", "handle_width", "Width of plates area on dumbbell handle.",
        true, 0.0, "mm", cmd };

    TCLAP::MultiArg<CPlateData> platesArg{
        "p", "plate", "Plate description: weight(kg),width(mm),height(mm)",
        true, "double(weight_kg),double(width_mm),double(height_mm),int(count)", cmd };
    cmd.parse(argc, argv);

    for (const auto& data : platesArg)
    {
        for (int i = 0; i < data.Count; i++)
            m_Plates.Add(CPlate{ data.Weight, data.Width, data.Height });
    }
}


const CPlates& CCommandLineParser::Plates() const
{
    return m_Plates;
}