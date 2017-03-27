#pragma once

#include "Unit.h"

namespace measure
{

template <typename T, typename TUnit>
struct CMeasure
{
    using TMeasure = CMeasure<T, TUnit>;
    explicit CMeasure() : m_Value{}
    {}

    explicit CMeasure(TUnit Val)
    {
        m_Value = Val;
    }

    TUnit Unit() const
    {
        return m_Value;
    }

    void Set(const TUnit& Value)
    {
        m_Value = Value;
    }

protected:
    TUnit m_Value;
};


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
    return T(res);
}


template <typename T, typename TUnit>
T operator+ (const CMeasure<T, TUnit>& Lhs, const CMeasure<T, TUnit>& Rhs)
{
    const TUnit& lhs{ Lhs.Unit() };
    const TUnit& rhs{ Rhs.Unit() };
    TUnit res = lhs + rhs;
    return T(res);
}


template <typename T>
struct CLength : public CMeasure<T, unit::CMillimeter>
{
public:
    using TBase = CMeasure<T, unit::CMillimeter>;
    unit::CMillimeter Mm() const
    {
        return m_Value;
    }

protected:
    CLength() : TBase()
    {}

    CLength(unit::CMillimeter Val) : TBase(Val)
    {}

    CLength(const CLength& Val) : TBase<T>(Val.Mm())
    {}
};


struct CWeight : public CMeasure<CWeight, unit::CKilogram>
{
    typedef CMeasure<CWeight, unit::CKilogram> TBase;

    CWeight() : TBase()
    {}

    explicit CWeight(unit::CKilogram Val) : TBase(Val)
    {}

    CWeight(const CWeight& Val) : TBase(Val.Kg())
    {}

    unit::CKilogram Kg() const
    {
        return m_Value;
    }
};


struct CWidth : public CLength<CWidth>
{
    typedef CLength<CWidth> TBase;

    CWidth() : TBase()
    {}

    explicit CWidth(unit::CMillimeter Val) : TBase(Val)
    {}

    CWidth(const CWidth& Val) : TBase(Val.Mm())
    {}
};


struct CHeight : public CLength<CHeight>
{
    typedef CLength<CHeight> TBase;

    explicit CHeight(unit::CMillimeter Val) : TBase(Val)
    {}

    CHeight(const CHeight& Val) : TBase(Val.Mm())
    {}
};

} // namespace measure
