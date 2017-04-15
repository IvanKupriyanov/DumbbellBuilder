#include "stdafx.h"
#include "CppUnitTest.h"

#include "CommandLinesArgsHelper.h"
#include "Measure.h"
#include "CommandLineParser.h"
#include "Plate.h"

#include "ToString.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace unit::literals;

namespace test
{
    TEST_CLASS(CommandLineParserTest)
    {
    public:
        TEST_METHOD(SimpleParserTest)
        {
            CPlate plate0_5{ TWeight(0.5_kg),  TWidth(10.0_mm), THeight(10.0_cm) };
            CPlate plate1_25{ TWeight(1.25_kg), TWidth(18.0_mm), THeight(10.0_cm) };
            CPlate plate2_5{ TWeight(2.5_kg),  TWidth(22.0_mm), THeight(10.0_cm) };
            CPlate plate5_0{ TWeight(5.0_kg),  TWidth(30.0_mm), THeight(10.0_cm) };
            CPlate plate10_0{ TWeight(10.0_kg), TWidth(30.0_mm), THeight(10.0_cm) };

            Args args = 
                ArgsBuilder()
                 .HandleWeight(TWeight{ 2.0_kg })
                 .HandleWidth(TWidth{ 20.0_cm })
                 .ExportFloatAsString(true)
                 .LocalAwareFormat(true)
                 .Plate(plate0_5, 1)
                 .Plate(plate1_25, 1)
                 .Plate(plate2_5, 2)
                 .Plate(plate5_0, 3)
                 .Plate(plate10_0, 1)
                .Build();

            Logger::WriteMessage(args.CommandLine().c_str());
            CCommandLineParser parser;
            try 
            {
                parser.Parse(args.Count(), args.Array());
            }
            catch (std::exception ex)
            {
                Logger::WriteMessage(ex.what());
            }

            Assert::AreEqual<size_t>(8, parser.Plates().size());

            Assert::AreEqual(plate0_5,  parser.Plates()[0]);
            Assert::AreEqual(plate1_25, parser.Plates()[1]);
            Assert::AreEqual(plate2_5,  parser.Plates()[2]);
            Assert::AreEqual(plate2_5,  parser.Plates()[3]);
            Assert::AreEqual(plate5_0,  parser.Plates()[4]);
            Assert::AreEqual(plate5_0,  parser.Plates()[5]);
            Assert::AreEqual(plate5_0,  parser.Plates()[6]);
            Assert::AreEqual(plate10_0, parser.Plates()[7]);

            Assert::AreEqual(TWeight{ 2.0_kg }, parser.HandleWeight());
            Assert::AreEqual(TWidth{ 20.0_cm }, parser.HandleWidth());
            Assert::IsTrue(parser.ExportFloatAsString());
            Assert::IsTrue(parser.LocalAwareFormat());
        }
    };
}
