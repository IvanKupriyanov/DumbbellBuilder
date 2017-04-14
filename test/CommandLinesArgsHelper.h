#pragma once
#include "Measure.h"

#include <vector>
#include <memory>

typedef measure::CWeight TWeight;
typedef measure::CWidth TWidth;
typedef measure::CHeight THeight;

class Args
{
public:
    Args(const std::vector<std::string>& ArgsList) : m_Size{ 0 }
    {
        std::stringstream ss;
        m_Array.push_back(std::move(toArray("app.exe")));
        for (const auto& arg : ArgsList)
        {
            ss << arg << " ";
            m_Array.push_back(std::move(toArray(arg)));
            m_Size++;
        }

        m_CmdLine = ss.str();
    }

    char** Array() const
    {
        return (char**)m_Array.data();
    }

    size_t Count() const
    {
        return m_Size;
    }

    std::string CommandLine() const
    {
        return m_CmdLine;
    }

private:
    std::unique_ptr<char[]> toArray(const std::string& Str) const
    {
        std::unique_ptr<char[]> arr = std::make_unique<char[]>(Str.size() + 1);
        memcpy_s(arr.get(), Str.size(), Str.data(), Str.size());
        arr[Str.size()] = '\0';

        return arr;
    }

private:
    std::vector<std::unique_ptr<char[]>> m_Array;
    size_t m_Size;
    std::string m_CmdLine;
};

class ArgsBuilder
{
public:
    ArgsBuilder& HandleWeight(const TWeight& Weight)
    {
        std::stringstream ss;
        ss << "--handle_weight " << Weight.Kg().Value();
        m_Args.push_back(ss.str());

        return *this;
    }

    ArgsBuilder& HandleWidth(const TWidth& Width)
    {
        std::stringstream ss;
        ss << "--handle_width " << Width.Mm().Value();
        m_Args.push_back(ss.str());

        return *this;
    }

    ArgsBuilder Plate(TWeight Weight, TWidth Width, THeight Height, int Count)
    {
        std::stringstream ss;
        ss << "-p"
            << " " << Weight.Kg().Value()
            << " " << Width.Mm().Value()
            << " " << Height.Mm().Value()
            << " " << Count;

        m_Args.push_back(ss.str());

        return *this;
    }

    Args Build() const
    {
        return Args{ m_Args };
    }

private:
    std::vector<std::string> m_Args;
};

