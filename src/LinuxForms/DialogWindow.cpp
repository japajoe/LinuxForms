#include "DialogWindow.h"

LinuxForms::DialogWindow::DialogWindow(const std::string& title, const std::string& message)
{
    this->name = title;
    this->size = { 256, 256 };
	
    widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect(widget, "destroy", G_CALLBACK(WindowClosing), this);

    box = std::make_shared<Box>();
    label = std::make_shared<Label>(message);
    buttonOk = std::make_shared<Button>("Ok");
    buttonCancel = std::make_shared<Button>("Cancel");

    Add(box.get());
    box->Add(label.get(), true, true, 0);
    box->Add(buttonOk.get(), true, true, 0);
    box->Add(buttonCancel.get(), true, true, 0);

    buttonOk->onClicked += [this] () { this->OnButtonOkClicked(); };
    buttonCancel->onClicked += [this] () { this->OnButtonCancelClicked(); };
    
    gtk_window_set_resizable(GTK_WINDOW(widget), false);
    SetTitle(name);
    SetSize(size);
}

void LinuxForms::DialogWindow::Add(Widget* child)
{
    gtk_container_add(GTK_CONTAINER(widget), child->widget);
}

void LinuxForms::DialogWindow::Add(GtkWidget* child)
{
    gtk_container_add(GTK_CONTAINER(widget), child);
}

void LinuxForms::DialogWindow::SetTitle(const std::string& title)
{
    gtk_window_set_title(GTK_WINDOW(widget), title.c_str());
}

void LinuxForms::DialogWindow::Show()
{
    gtk_widget_show_all(widget);
}

void LinuxForms::DialogWindow::OnButtonOkClicked()
{

}

void LinuxForms::DialogWindow::OnButtonCancelClicked()
{

}

void LinuxForms::DialogWindow::WindowClosing(GtkWidget *widget, gpointer data)
{    
    DialogWindow* window = reinterpret_cast<DialogWindow*>(data);
    
    if(window->onClosing != nullptr)
        window->onClosing();  
}