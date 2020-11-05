#include "DemoApplication.h"
#include <iostream>
#include <memory>

using namespace LinuxForms;

void Close()
{
    gtk_main_quit();
}

int main(int argc, char** argv)
{
    auto application = std::make_shared<DemoApplication>();
    application->Run(argc, argv);
}