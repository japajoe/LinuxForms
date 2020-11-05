#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>

namespace LinuxForms
{
    class Console
    {
    public:
        template <typename T>
        static void Write(const T& value)
        {
            std::cout << value;
        }
        
        template <typename T>
        static void WriteLine(const T& value)
        {
            std::cout << value << '\n';
        }      
    };
}
#endif