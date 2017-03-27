#pragma once

namespace unit
{

template <typename T>
struct CUnit
{
    using TUnit = CUnit<T>;

	explicit CUnit()
	{
		m_Value = 0.0f;
	}


    CUnit(const TUnit& Val) : m_Value{ Val.m_Value }
    {
    }

    explicit CUnit(float Val)
    {
        m_Value = Val;
    }

    float Value() const
	{
		return m_Value;
	}

    void Set(float NewValue)
    {
        m_Value = NewValue;
    }

private:
	float m_Value;
};


struct CMillimeter : CUnit<CMillimeter>
{
    using TBase = CUnit<CMillimeter>;

    CMillimeter() : TBase()
    {}

    explicit CMillimeter(float Val) : CUnit<CMillimeter>(Val)
	{}

	CMillimeter(const CMillimeter& Val) : CUnit<CMillimeter>(Val.Value())
	{}
};


struct CCentimeter : CUnit<CCentimeter>
{
    using TBase = CUnit<CCentimeter>;

    CCentimeter() : TBase()
    {}

    explicit CCentimeter(float Val) : CUnit<CCentimeter>(Val)
    {}

    CCentimeter(const CCentimeter& Val) : CUnit<CCentimeter>(Val.Value())
    {}

    operator CMillimeter() const
    {
        return CMillimeter(Value() * 10.0f);
    }
};


struct CKilogram : CUnit<CKilogram>
{
    using TBase = CUnit<CKilogram>;

    CKilogram() : TBase()
    {}
    
    explicit CKilogram(float Val) : TBase(Val)
	{}

	CKilogram(const CKilogram& Val) : TBase(Val.Value())
	{}
};


namespace literals
{

inline CMillimeter operator "" _mm(long double Val)
{
    return CMillimeter(static_cast<float>(Val));
}


inline CKilogram operator "" _kg(long double Val)
{
    return CKilogram(static_cast<float>(Val));
}


inline CCentimeter operator "" _cm(long double Val)
{
    return CCentimeter(static_cast<float>(Val));
}

} // namespace literals



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


} // namespace metric
