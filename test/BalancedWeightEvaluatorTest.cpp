#include "stdafx.h"
#include "CppUnitTest.h"

#include "DumbbellConfigEvaluator.h"
#include "Measure.h"
#include "Unit.h"

#include "ToString.h"

#include <vector>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace unit::literals;


namespace test
{		
    using TWeight = measure::CWeight;
    using TWidth  = measure::CWidth;
    using THeight = measure::CHeight;

    TEST_CLASS(BalancedWeightEvaluatorTest)
	{
	public:

        TEST_METHOD(WhenLeftPlatesWidthMoreThanHandle_ShouldReturnFalse)
        {
            Init();
            CPlates left { { plate5_0, plate5_0, plate5_0, plate5_0 } };
            CPlates rigth{ { plate5_0 } };
            CDumbbellConfig config{ left, rigth };

            Assert::IsFalse(left.GetWidth() < m_Handle.GetPlatesWidth());
            Assert::IsFalse(m_Evaluator.Rank(m_Handle, config));
        }


        TEST_METHOD(WhenRightPlatesWidthMoreThanHandle_ShouldReturnFalse)
        {
            Init();
            CPlates left { { plate5_0 } };
            CPlates right{ { plate5_0, plate5_0, plate5_0, plate5_0 } };
            CDumbbellConfig config{ left, right };

            Assert::IsFalse(right.GetWidth() < m_Handle.GetPlatesWidth());
            Assert::IsFalse(m_Evaluator.Rank(m_Handle, config));
        }


        TEST_METHOD(WhenNoPlates_ShouldReturnFalse)
        {
            Init();
            CPlates left { {} };
            CPlates right{ {} };
            CDumbbellConfig config{ left, right };

            Assert::IsFalse(m_Evaluator.Rank(m_Handle, config));
        }


        TEST_METHOD(OnFirstRank_WhenNotSorted_ShouldAdd)
        {
            Init();
            CPlates left { { plate1_25, plate0_5 } }; // not sorted
            CPlates right{ { plate0_5, plate1_25 } }; // sorted
            CDumbbellConfig config{ left, right };

            // First call - should add even not sorted.
            Assert::IsTrue(m_Evaluator.Rank(m_Handle, config));
        }


        TEST_METHOD(OnFirstRank_WhenSorted_ShouldAdd)
        {
            Init();
            CPlates left { { plate0_5, plate1_25 } }; // sorted
            CPlates right{ { plate0_5, plate1_25 } }; // sorted
            CDumbbellConfig config{ left, right };

            Assert::IsTrue(m_Evaluator.Rank(m_Handle, config));
        }


        TEST_METHOD(WithSameWeightSortedWins)
        {
            Init();

            {
                CPlates left{ { plate1_25, plate0_5 } }; // not sorted
                CPlates right{ { plate0_5, plate1_25 } }; // sorted
                CDumbbellConfig notSortedConfig { left, right };
                Assert::IsTrue(m_Evaluator.Rank(m_Handle, notSortedConfig));
            }

            {
                CPlates left{ { plate0_5, plate1_25 } }; // sorted
                CPlates right{ { plate0_5, plate1_25 } }; // sorted
                CDumbbellConfig sortedConfig { left, right };
                Assert::IsTrue(m_Evaluator.Rank(m_Handle, sortedConfig));
            }
        }


        // 17 kg.
        // 
        TEST_METHOD(WeightShouldBeBalanced)
        {
            Init();

            {
                CPlates left{ { plate10_0 } };
                CPlates right{ { plate5_0 } };
                Assert::AreEqual(TWeight{ 15.0_kg }, left.GetWeight() + right.GetWeight());

                CDumbbellConfig notBalanced { left, right };
                Assert::IsTrue(m_Evaluator.Rank(m_Handle, notBalanced));
                Assert::AreEqual(notBalanced, m_Evaluator.GetBest());
            }

            CDumbbellConfig bestConfig;
            {
                CPlates left{ { plate2_5, plate5_0 } };
                CPlates right{ { plate2_5, plate5_0 } };
                Assert::AreEqual(TWeight{ 15.0_kg }, left.GetWeight() + right.GetWeight());

                CDumbbellConfig sortedConfig { left, right };
                bestConfig = sortedConfig;
                Assert::IsTrue(m_Evaluator.Rank(m_Handle, sortedConfig));
                Assert::AreEqual(sortedConfig, m_Evaluator.GetBest());
            }

            {
                CPlates left{ { plate2_5, plate5_0, plate5_0 } };
                CPlates right{ { plate2_5 } };
                Assert::AreEqual(TWeight{ 15.0_kg }, left.GetWeight() + right.GetWeight());

                CDumbbellConfig unbalanced { left, right };
                Assert::IsFalse(m_Evaluator.Rank(m_Handle, unbalanced));
                Assert::AreEqual(bestConfig, m_Evaluator.GetBest());
            }
        }


        // 17 kg.
        // 
        TEST_METHOD(ComplexCase)
        {
            Init();

            {
                CPlates left{ { plate0_5, plate1_25, plate2_5 } };
                CPlates right{ {  } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsTrue(m_Evaluator.Rank(m_Handle, config));
            }

            {
                CPlates left{ { plate0_5, plate2_5 } };
                CPlates right{ { plate1_25 } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsTrue(m_Evaluator.Rank(m_Handle, config));
            }

            {
                CPlates left{ { plate1_25, plate0_5, plate2_5 } };
                CPlates right{ { } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsFalse(m_Evaluator.Rank(m_Handle, config));
            }

            {
                CPlates left{ { plate1_25, plate2_5 } };
                CPlates right{ { plate0_5 } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsFalse(m_Evaluator.Rank(m_Handle, config));
            }

            {
                CPlates left{ { plate2_5 } };
                CPlates right{ { plate0_5, plate1_25 } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsTrue(m_Evaluator.Rank(m_Handle, config));
            }

        }



        // 17 kg.
        // 
        TEST_METHOD(TestBalanceFor18_75kg)
        {
            Init();

            {
                CPlates left{ { plate0_5, plate2_5, plate5_0 } };
                CPlates right{ { plate1_25, plate2_5, plate5_0 } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsTrue(m_Evaluator.Rank(m_Handle, config));
            }

            {
                CPlates left{ { plate10_0 } };
                CPlates right{ { plate0_5, plate1_25, plate5_0 } };
                CDumbbellConfig config = CDumbbellConfig{ left, right };

                Assert::IsFalse(m_Evaluator.Rank(m_Handle, config));
            }
        }



    private:

        void Init()
        {
            m_Handle = CDumbbellHandle{ TWeight{ 2.0_kg }, TWidth{ 10.0_cm } };
            m_Evaluator.Reset();
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

        CDumbbellHandle m_Handle;
        BalancedWeightEvaluator m_Evaluator;

        CPlate plate0_5 { TWeight(0.5_kg),  TWidth(10.0_mm), THeight(10.0_cm) };
        CPlate plate1_25{ TWeight(1.25_kg), TWidth(18.0_mm), THeight(10.0_cm) };
        CPlate plate2_5 { TWeight(2.5_kg),  TWidth(22.0_mm), THeight(10.0_cm) };
        CPlate plate5_0 { TWeight(5.0_kg),  TWidth(30.0_mm), THeight(10.0_cm) };
        CPlate plate10_0{ TWeight(10.0_kg), TWidth(30.0_mm), THeight(10.0_cm) };

	};
}
