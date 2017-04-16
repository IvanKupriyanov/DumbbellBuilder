#pragma once

#include "Unit.h"

namespace measure
{

template <typename TMeasureType, typename TMeasureUnit>
struct CMeasure
{
    using TMeasure = CMeasure<TMeasureType, TMeasureUnit>;
    using TUnit = TMeasureUnit;

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


template <typename T>
struct CLength : public CMeasure<T, unit::CMillimeter>
{
public:
    using TBase = CMeasure<T, unit::CMillimeter>;

    unit::CMillimeter Mm() const
    {
        return m_Value;
    }

    CLength() : TBase()
    {}

    CLength(unit::CMillimeter Val) : TBase(Val)
    {}

    CLength(const CLength& Val) : TBase<T>(Val.Mm())
    {}
};


struct CWeight : public CMeasure<CWeight, unit::CKilogram>
{
    using TBase = CMeasure<CWeight, unit::CKilogram>;

    template <typename T>
    static CWeight Create(const T& Unit)
    {
        return CWeight(Unit.To<CMeasure::TUnit>());
    }

    CWeight() : TBase()
    {}

    CWeight(const CWeight& Val) : TBase(Val.Kg())
    {}

    unit::CKilogram Kg() const
    {
        return m_Value;
    }

private:
    explicit CWeight(unit::CKilogram Val) : TBase(Val)
    {}
};


struct CWidth : public CLength<CWidth>
{
    typedef CLength<CWidth> TBase;

    CWidth() : TBase()
    {}

    CWidth(const CWidth& Val) : TBase(Val.Mm())
    {}

    template <typename T>
    static CWidth Create(const T& Unit)
    {
        return CWidth(Unit.To<CMeasure::TUnit>());
    }

private:
    explicit CWidth(unit::CMillimeter Val) : TBase(Val)
    {}
};


struct CHeight : public CLength<CHeight>
{
    typedef CLength<CHeight> TBase;

    template <typename T>
    static CHeight Create(const T& Unit)
    {
        return CHeight(Unit.To<CMeasure::TUnit>());
    }

    CHeight() : TBase()
    {}

    CHeight(const CHeight& Val) : TBase(Val.Mm())
    {}

private:
    explicit CHeight(unit::CMillimeter Val) : TBase(Val)
    {}
};

} // namespace measure
