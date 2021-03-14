#pragma once

#include <Windows.h>
#undef max //get rid of max macro from windows.h

enum class FontColor { green = 2, cyan = 11, red = 12, purple = 13, white = 15};

struct Utility
{
    static void setFontColor(const FontColor color)
    {
        auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //console handle
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }

    static void wflush()
    {
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void flush()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    template<typename charT>
    static std::basic_string<charT> trim(std::basic_string<charT> s)
    {
        if(!s.empty())
        {
            auto start = s.begin();
            while (start != s.end() && std::isspace(*start)) //while there are leading spaces
            {
                start++;
            }

            auto end = s.end();
            do
            {
                end--;
            } while (std::distance(start, end) > 0 && std::isspace(*end)); //while there are trailing spaces

            return std::basic_string<charT>(start, end + 1); //return new string without leading and trailing spaces
        }
        return std::basic_string<charT>();
    }
};




