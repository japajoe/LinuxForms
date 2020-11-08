#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>

namespace LinuxForms
{
class Console
{
    public:
        template<typename T>
        static T Read()
        {
            T value;
            std::cin >> value;
            return value;
        }

        template<typename T>
        static T ReadLine()
        {
            T value;
            std::getline (std::cin, value);
            return value;
        }

        template<typename T>
        static void Write(const T& message)
        {
            std::cout << message;
        }

        template<typename T>
        static void WriteLine(const T& message)
        {
            std::cout << message << '\n';
        }

        template<typename T>
        static void WriteHex(const T& message)
        {
            std::cout << std::hex << message << std::dec;
        }

        template<typename T>
        static void WriteHexLine(const T& message)
        {
            std::cout << std::hex << message << std::dec << '\n';
        }        

        template<typename T>
        static void WriteError(const T& message)
        {
            std::cerr << message << '\n';
        }    
    };
}
#endif
