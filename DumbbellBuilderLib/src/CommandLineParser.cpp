#include "CommandLineParser.h"
#include <tclap\CmdLine.h>

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
    TCLAP::SwitchArg exportFloatAsStringArg{
        "s", "float_to_string", "Save float as string (when Excel parses weight as date).", false};
    cmd.add(exportFloatAsStringArg);

    TCLAP::SwitchArg localAwareFormatArg{
        "l", "local_aware_format", "Use local settings for double format.", false};
    cmd.add(localAwareFormatArg);

    TCLAP::ValueArg<float> handleWeightArg{
        "m", "handle_weight", "Weight of dumbbell handle.",
        true, 0.0, "kg", cmd };

    TCLAP::ValueArg<float> handleWidthArg{
        "w", "handle_plates_area_width", "Width of plates area on dumbbell handle.",
        true, 0.0, "mm", cmd };

    TCLAP::MultiArg<CPlateData> platesArg{
        "p", "plate", "Plate description: weight(kg), width(mm), height(mm), available plates count",
        true, "float(weight_kg) float(width_mm) float(height_mm) int(count)", cmd };

    cmd.parse(argc, argv);

    m_ExportFloatAsString = exportFloatAsStringArg.getValue();
    m_LocalAwareFormat = localAwareFormatArg.getValue();
    m_HandleWeight = measure::CWeight{ unit::CKilogram { handleWeightArg.getValue() } };
    m_HandleWidth = measure::CWidth{ unit::CMillimeter { handleWidthArg.getValue() } };
    for (const auto& data : platesArg)
    {
        for (int i = 0; i < data.Count; i++)
            m_Plates.Add(CPlate{ data.Weight, data.Width, data.Height });
    }
}


bool CCommandLineParser::ExportFloatAsString() const
{
    return m_ExportFloatAsString;
}

bool CCommandLineParser::LocalAwareFormat() const
{
    return m_LocalAwareFormat;
}

measure::CWeight CCommandLineParser::HandleWeight() const
{
    return m_HandleWeight;
}

measure::CWidth CCommandLineParser::HandleWidth() const
{
    return m_HandleWidth;
}

const CPlates& CCommandLineParser::Plates() const
{
    return m_Plates;
}
