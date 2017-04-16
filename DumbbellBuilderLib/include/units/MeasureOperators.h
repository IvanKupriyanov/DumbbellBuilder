#pragma once

#include "Measure.h"

namespace measure
{

template <typename T, typename TUnit>
bool operator > (const CMeasure<T, TUnit>& Left, const CMeasure<T, TUnit>& Right)
{
    return Left.Unit() > Right.Unit();
}


template <typename T, typename TUnit>
bool operator >= (const CMeasure<T, TUnit>& Left, const CMeasure<T, TUnit>& Right)
{
    return Left.Unit() >= Right.Unit();
}


template <typename T, typename TUnit>
bool operator < (const CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    return Lhs.Unit() < Rhs.Unit();
}


template <typename T, typename TUnit>
bool operator == (const CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    return Lhs.Unit() == Rhs.Unit();
}


template <typename T, typename TUnit>
bool operator != (const CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    return !(Lhs == Rhs);
}


template <typename T, typename TUnit>
const CMeasure<T, TUnit>& operator+= (CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    Lhs.Set(Lhs.Unit() + Rhs.Unit());
    return Lhs;
}


template <typename T, typename TUnit>
T operator- (const CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    const TUnit& lhs{ Lhs.Unit() };
    const TUnit& rhs{ Rhs.Unit() };
    TUnit res = lhs - rhs;
    return T::Create(res);
}


template <typename T, typename TUnit>
T operator+ (const CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    const TUnit& lhs{ Lhs.Unit() };
    const TUnit& rhs{ Rhs.Unit() };
    TUnit res = lhs + rhs;
    return T::Create(res);
}


template <typename T, typename TUnit>
T operator* (const CMeasure<T, TUnit>& Lhs, const float& Rhs)
{
    const TUnit& lhs{ Lhs.Unit() };
    TUnit res = lhs * Rhs;
    return T::Create(res);
}

} // namespace measure
