#pragma once

#include <Windows.h>
#undef max //get rid of max macro from windows.h
#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert

enum class FontColor { green = 2, cyan = 11, red = 12, purple = 13, white = 15};

struct Utility
{
    static void setFontColor(const FontColor color)
    {
        auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //console handle
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }

    static void flush()
    {
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

    // encoding function
    static std::string utf8_encode(std::wstring& wide_string)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
        return utf8_conv.to_bytes(wide_string);
    }

    // decoding function
    static std::wstring utf8_decode(std::basic_string<char, std::char_traits<char>, std::allocator<char>> normal_string)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
        return utf8_conv.from_bytes(normal_string);
    }
};




