#include "Application.h"
#include <iostream>
#include <memory>

using namespace LinuxForms;

void Close()
{
    gtk_main_quit();
}

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    
    auto form = Widget::Create<Form>();
    auto box = Widget::Create<Box>();
    auto button = Widget::Create<Button>();

    form->Add(box.get());
    box->Add(button.get(), false, false, 0);
    form->onClosing += Close;
    form->Show();

    gtk_main();
}