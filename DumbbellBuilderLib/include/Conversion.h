#pragma once

#include "Unit.h"

namespace unit
{

template <typename TOut, typename TIn>
inline TOut Convert(const TIn& Value)
{
    static_assert(false, "Should provide proper specialization");
    return TOut();
}

template<>
inline CMillimeter Convert(const CCentimeter& Value)
{
    return CMillimeter{ Value.Value() * 10.0f };
}

template<>
inline CMillimeter Convert(const CMillimeter& Value)
{
    return Value;
}

template<>
inline CKilogram Convert(const CKilogram& Value)
{
    return Value;
}

} // namespace unit
