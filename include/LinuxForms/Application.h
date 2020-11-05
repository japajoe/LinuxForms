#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "LinuxForms.h"
#include <memory>

namespace LinuxForms
{
    class Application
    {
    public:
        Application();
        virtual void Initialize();
        void Run(int argc, char** argv);
        void Quit();
        std::shared_ptr<Form> form;
    private:
        void OnApplicationQuit();
    };
}

#endif
