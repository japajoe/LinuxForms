#include "Application.h"
#include <iostream>

LinuxForms::Application::Application()
{
    
}

void LinuxForms::Application::Run(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    
    form = Widget::Create<Form>();      
    
    Initialize();

    form->onClosing += [this] () { this->OnApplicationQuit(); };

    TimeUtility::Initialize();
    Input::Initialize();    
    
    form->Show();

    gtk_main();
}

void LinuxForms::Application::Initialize()
{
    
}

void LinuxForms::Application::Quit()
{
    gtk_widget_destroy(form->widget);
}

void LinuxForms::Application::OnApplicationQuit()
{
    gtk_main_quit();
}
