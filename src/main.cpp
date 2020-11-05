#include "DemoApplication.h"

int main(int argc, char** argv)
{
    auto application = std::make_shared<DemoApplication>();
    application->Run(argc, argv);
}