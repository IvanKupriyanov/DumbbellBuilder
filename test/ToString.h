#include "Measure.h"
#include "Dumbbell.h"

#include <vector>
#include <sstream>

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            template <> inline std::wstring ToString(const measure::CWeight& q)
            {
                std::wstringstream ss;
                ss << L"Weight: " << q.Kg().Value() << L" kg";

                return ss.str();
            }

            template <> inline std::wstring ToString(const measure::CWidth& q)
            {
                std::wstringstream ss;
                ss << L"Width: " << q.Mm().Value() << L" mm";

                return ss.str();
            }

            template <> inline std::wstring ToString(const CPlate& Plate)
            {
                std::wstringstream ss;
                ss << L"Plate{ " << ToString(Plate.GetWeight()) << ", " << ToString(Plate.GetWidth()) << "}";
                return ss.str();
            }

            template <> inline std::wstring ToString(const CPlates& Plates)
            {
                std::wstringstream ss;

                for (auto it = Plates.begin(), end = Plates.end(); it != end; ++it)
                {
                    ss << it->GetWeight().Kg().Value();
                    if (it + 1 != end)
                        ss << ", ";
                }

                return ss.str();
            }

            template <> inline std::wstring ToString(const CDumbbellConfig& q)
            {
                std::wstringstream ss;
                ss << L"Left: [" << ToString(q.LeftSide()) << L"], Right: [" << ToString(q.RightSide()) << L"]";

                return ss.str();
            }
        }
    }
}

