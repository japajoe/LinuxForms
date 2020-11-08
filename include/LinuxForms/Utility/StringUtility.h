#ifndef STRINGUTILITY_HPP
#define STRINGUTILITY_HPP

#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sstream>

namespace LinuxForms
{
    class StringUtility
    {
    public:
        static std::string Replace(std::string& haystack, const std::string& needle, const std::string& replacement);
        static std::vector<std::string> Split(const std::string& text, const char* delimiter);
        static std::vector<std::string> Split(const std::string& text, char delimiter);
        static std::string GetFileNameWithExtension(const std::string& text);
        static std::string GetFileExtension(const std::string& text, bool includePeriod = false);
        static bool StartsWith(const std::string& haystack, const std::string& needle);
        static bool EndsWith(const std::string& haystack, const std::string& needle);
        static int GetLines(const std::string& text);
        static bool Contains(const std::string& haystack, const std::string& needle);
        static int Count(const std::string& haystack, const std::string& needle);
        static std::vector<int> CountWithOffset(const std::string& haystack, const std::string& needle);
        static std::string ToLower(const std::string& text);
        static std::string ToLowerCase(const std::string& text);
        static std::string ToUpperCase(const std::string& text);
        static int ToInt32(const std::string& text);

        template<typename T>
        static bool ParseNumber(const std::string& text, T& value)
        {

            std::stringstream stream(text);
            stream >> value;
            if (stream.fail())
            {
                return false;
            }
            return true;
        }		
    };
}
#endif
