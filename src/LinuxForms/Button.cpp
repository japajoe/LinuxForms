#include "Button.h"

LinuxForms::Button::Button()
{
    this->name = name;
    
	widget = gtk_button_new();
    g_signal_connect(widget, "clicked", G_CALLBACK(Clicked), this);
    
}

LinuxForms::Button::Button(const std::string& text, int width, int height)
{
    this->name = name;
    this->size = { width, height };
	widget = gtk_button_new_with_label(text.c_str());
    g_signal_connect(widget, "clicked", G_CALLBACK(Clicked), this);
    SetSize(size);
}

void LinuxForms::Button::SetText(const std::string& text)
{
    gtk_button_set_label(GTK_BUTTON(widget), text.c_str());
}

void LinuxForms::Button::Clicked(GtkWidget* widget, gpointer data)
{
    Button* button = reinterpret_cast<Button*>(data);
    button->onClicked(data);
}