#include "CheckBox.h"

LinuxForms::CheckBox::CheckBox()
{
    widget = gtk_toggle_button_new();
    g_signal_connect(GTK_TOGGLE_BUTTON(widget), "toggled", G_CALLBACK(Toggled), this);
}

LinuxForms::CheckBox::CheckBox(const std::string& text)
{
    widget = gtk_toggle_button_new_with_label(text.c_str());
    g_signal_connect(GTK_TOGGLE_BUTTON(widget), "toggled", G_CALLBACK(Toggled), this);
}

bool LinuxForms::CheckBox::GetValue() const
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}

void LinuxForms::CheckBox::SetValue(bool checked)
{
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), checked);
}

void LinuxForms::CheckBox::Toggled(GtkToggleButton *widget, gpointer data)
{
    CheckBox* checkbox = reinterpret_cast<CheckBox*>(data);
    checkbox->onValueChanged(data);
}