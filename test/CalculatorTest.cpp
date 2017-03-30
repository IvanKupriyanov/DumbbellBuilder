#include "stdafx.h"
#include "CppUnitTest.h"

#include "Calculator.h"
#include "PlatesSplitStrategy.h"
#include "DumbbellConfigEvaluator.h"

#include "Measure.h"
#include "Unit.h"

#include <vector>
#include <iostream>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace unit::literals;

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            template <> std::wstring ToString(const measure::CWeight& q)
            {
                std::wstringstream ss;
                ss << L"Weight: " << q.Kg().Value() << L" kg";

                return ss.str();
            }
        }
    }
}


namespace test
{		
    using TWeight = measure::CWeight;
    using TWidth  = measure::CWidth;
    using THeight = measure::CHeight;

    TEST_CLASS(CalculatorTest)
	{
	public:

        TEST_METHOD(WithOnePlate_ShouldMakeConfigWithThisPlate)
        {
            Init();

            CPlates plates;
            plates.Add(plate0_5);

            m_Calculator->Calculate(m_Handle, plates);

            Assert::AreEqual<size_t>(1, GetCalculator().Result().size());
        }


        TEST_METHOD(WithThreePlates)
        {
            Init();

            CPlates plates;
            plates.Add(plate0_5);
            plates.Add(plate1_25);
            plates.Add(plate5_0);

            GetCalculator().Calculate(m_Handle, plates);

            Assert::AreEqual<size_t>(6, GetCalculator().Result().size());
        }


    private:

        void Init()
        {
            m_Handle = CDumbbellHandle{ TWeight{ 2.0_kg }, TWidth{ 10.0_cm } };
            m_Calculator = std::make_unique<Calculator>(m_SplitStrategy, m_Evaluator);
        }

        template<typename ... Types>
        CPlates Plates(Types ... args)
        {
            CPlates plates;
            for (const auto& weight : { args... })
            {
                plates.Add(Plate(weight));
            }

            return plates;
        }


        CPlate Plate(unit::CKilogram Weight)
        {
            return CPlate{ TWeight{Weight}, TWidth(20.0_mm), THeight(10.0_cm) };
        }

        Calculator& GetCalculator() const
        {
            return *m_Calculator;
        }

        CDumbbellHandle m_Handle;
        BalancedWeightEvaluator m_Evaluator;
        EqualWeightStrategy m_SplitStrategy;
        std::unique_ptr<Calculator> m_Calculator;

        CPlate plate0_5 { TWeight(0.5_kg),  TWidth(10.0_mm), THeight(10.0_cm) };
        CPlate plate1_25{ TWeight(1.25_kg), TWidth(18.0_mm), THeight(10.0_cm) };
        CPlate plate2_5 { TWeight(2.5_kg),  TWidth(22.0_mm), THeight(10.0_cm) };
        CPlate plate5_0 { TWeight(5.0_kg),  TWidth(30.0_mm), THeight(10.0_cm) };
        CPlate plate10_0{ TWeight(10.0_kg), TWidth(30.0_mm), THeight(10.0_cm) };

	};
}