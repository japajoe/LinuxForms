#include "Application.h"
#include <iostream>

LinuxForms::Application::Application()
{
    
}

void LinuxForms::Application::Run(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    
    window = Widget::Create<Window>();      
    
    Initialize();

    window->onClosing += [this] () { this->OnApplicationQuit(); };

    TimeUtility::Initialize();
    Input::Initialize();    
    
    window->Show();

    gtk_main();
}

void LinuxForms::Application::Initialize()
{
    
}

void LinuxForms::Application::Quit()
{
    gtk_widget_destroy(window->widget);
}

void LinuxForms::Application::OnApplicationQuit()
{
    gtk_main_quit();
}
