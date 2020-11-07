#include "DemoApplication.h"

std::shared_ptr<Window> window;

void OnClose()
{
    gtk_main_quit();
}

int main(int argc, char** argv)
{
    auto application = std::make_shared<DemoApplication>();
    application->Run(argc, argv);
}