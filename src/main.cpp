#include "DemoApplication.h"
#include <iostream>
#include <memory>

using namespace LinuxForms;

int main(int argc, char** argv)
{
    auto application = std::make_shared<DemoApplication>();
    application->Run(argc, argv);
}