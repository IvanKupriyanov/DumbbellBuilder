#pragma once

namespace unit
{

template <typename T>
bool operator < (const CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    return Lhs.Value() < Rhs.Value();
}

template <typename T>
bool operator > (const CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    return Lhs.Value() > Rhs.Value();
}

template <typename T>
bool operator >= (const CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    return Lhs.Value() >= Rhs.Value();
}

template <typename T>
bool operator == (const CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    return Lhs.Value() == Rhs.Value();
}

template <typename T>
CUnit<T>& operator+= (CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    Lhs.Set(Lhs.Value() + Rhs.Value());
    return Lhs;
}

template <typename T>
T operator- (const CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    return T(Lhs.Value() - Rhs.Value());
}

template <typename T>
T operator+ (const CUnit<T>& Lhs, const CUnit<T>& Rhs)
{
    return T(Lhs.Value() + Rhs.Value());
}

template <typename T>
T operator* (const CUnit<T>& Lhs, const float& Rhs)
{
    return T(Lhs.Value() * Rhs);
}

} // namespace unit
