#include "stdafx.h"
#include "CppUnitTest.h"

#include "CommandLinesArgsHelper.h"
#include "Measure.h"
#include "CommandLineParser.h"
#include "Plate.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace unit::literals;

namespace test
{
    TEST_CLASS(CommandLineParserTest)
    {
    public:
        TEST_METHOD(SimpleParserTest)
        {
            Args args = 
                ArgsBuilder()
                 .HandleWeight(TWeight{ 2.0_kg })
                 .HandleWidth(TWidth{ 20.0_cm })
                 .Plate(TWeight{ 0.5_kg }, TWidth{ 10.0_mm }, THeight{ 80.0_cm }, 1)
                 .Plate(TWeight{ 1.25_kg }, TWidth{ 18.0_mm }, THeight{ 100.0_cm }, 1)
                 .Plate(TWeight{ 2.5_kg }, TWidth{ 22.0_mm }, THeight{ 120.0_cm }, 2)
                 .Plate(TWeight{ 5.0_kg }, TWidth{ 30.0_mm }, THeight{ 150.0_cm }, 3)
                 .Plate(TWeight{ 10.0_kg }, TWidth{ 30.0_mm }, THeight{ 210.0_cm }, 1)
                .Build();

            Logger::WriteMessage(args.CommandLine().c_str());
            CCommandLineParser parser;
            parser.Parse(args.Count(), args.Array());

            Assert::AreEqual<size_t>(8, parser.Plates().size());
        }
    };
}
