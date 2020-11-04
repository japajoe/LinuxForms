#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <vector>

namespace LinuxForms
{
    template<typename T>
    class EventHandler
    {
    public:
        std::vector<T> callbacks;

        template<typename ... Param>
        void operator () (const Param& ... param)
        {
            for(size_t i = 0; i < callbacks.size(); i++)
            {
                if(callbacks[i] != nullptr)
                {
                    callbacks[i](param...);
                }
            }
        }        

        void operator += (T callback)
        {
            callbacks.push_back(callback);
        }

        uintptr_t GetAddress(T e)
        {
            long address = *(long *)(char *)&e;
            return static_cast<uintptr_t>(address);
        }

        uintptr_t* operator != (uintptr_t* nullPointer)
        {
            if(callbacks.size() == 0)
                return nullPointer;
            
            uintptr_t address = GetAddress(callbacks[0]);
            return reinterpret_cast<uintptr_t*>(address);
        }               
    };
}

#endif
