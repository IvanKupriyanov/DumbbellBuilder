#include "stdafx.h"
#include "CppUnitTest.h"

#include "computation/PlatesSplitStrategy.h"
#include "units/Units.h"

#include "ToString.h"

#include <vector>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace unit::literals;

namespace test
{		
    
    TEST_CLASS(EqualWeightStrategyTest)
	{
        measure::CWeight w0_5 { measure::CWeight::Create(0.5_kg) };
        measure::CWeight w1_25{ measure::CWeight::Create(1.25_kg) };
        measure::CWeight w2_5 { measure::CWeight::Create(2.5_kg) };
        measure::CWeight w5_0 { measure::CWeight::Create(5.0_kg) };
        measure::CWeight w10_0{ measure::CWeight::Create(10.0_kg) };

	public:
        TEST_METHOD(FindMiddle_SimpleCase)
        {
            EqualWeightStrategy splitter;
            CPlates plates = Plates(1.25_kg, 5.0_kg, 5.0_kg, 0.5_kg);
            auto pair = splitter.Split(plates);

            Assert::AreEqual<size_t>(2, pair.first.size());
            Assert::AreEqual(w1_25, pair.first[0].GetWeight());
            Assert::AreEqual(w5_0, pair.first[1].GetWeight());

            Assert::AreEqual<size_t>(2, pair.second.size());
            Assert::AreEqual(w5_0, pair.second[0].GetWeight());
            Assert::AreEqual(w0_5, pair.second[1].GetWeight());
        }


        TEST_METHOD(FindMiddle_SimmetricShouldBeDividedProperly)
        {
            EqualWeightStrategy splitter;
            CPlates plates = Plates(1.25_kg, 5.0_kg, 5.0_kg, 1.25_kg);
            auto pair = splitter.Split(plates);

            Assert::AreEqual<size_t>(2, pair.first.size());
            Assert::AreEqual(w1_25, pair.first[0].GetWeight());
            Assert::AreEqual(w5_0, pair.first[1].GetWeight());

            Assert::AreEqual<size_t>(2, pair.second.size());
            Assert::AreEqual(w5_0, pair.second[0].GetWeight());
            Assert::AreEqual(w1_25, pair.second[1].GetWeight());
        }


        TEST_METHOD(FindMiddle_WhenNoPlates_ShouldReturnNegative)
        {
            EqualWeightStrategy splitter;
            CPlates plates;
            auto pair = splitter.Split(plates);

            Assert::AreEqual<size_t>(0, pair.first.size());
            Assert::AreEqual<size_t>(0, pair.second.size());
        }


        TEST_METHOD(FindMiddle_WhenOnePlate_ShouldReturnNegative)
        {
            EqualWeightStrategy splitter;
            CPlates plates = Plates(1.25_kg);
            auto pair = splitter.Split(plates);

            Assert::AreEqual<size_t>(1, pair.first.size());
            Assert::AreEqual(w1_25, pair.first[0].GetWeight());

            Assert::AreEqual<size_t>(0, pair.second.size());
        }


    private:

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
            return CPlate{ measure::CWeight::Create(Weight), measure::CWidth::Create(20.0_mm), measure::CHeight::Create(10.0_cm) };
        }
	};
}
