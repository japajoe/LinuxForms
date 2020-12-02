#include "NumericUpDown.h"

LinuxForms::NumericUpDown::NumericUpDown()
{
    widget = gtk_spin_button_new_with_range(0, 100, 1.0);
    g_signal_connect(GTK_SPIN_BUTTON(widget), "value-changed", G_CALLBACK(ValueChanged), this);
}

LinuxForms::NumericUpDown::NumericUpDown(double value, double valueMin, double valueMax, double stepSize)
{
    widget = gtk_spin_button_new_with_range(valueMin, valueMax, stepSize);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), value);
    g_signal_connect(GTK_SPIN_BUTTON(widget), "value-changed", G_CALLBACK(ValueChanged), this);
}

double LinuxForms::NumericUpDown::GetValue() const
{
    return gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
}

void LinuxForms::NumericUpDown::SetValue(double value)
{
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), value);
}

void LinuxForms::NumericUpDown::ValueChanged(GtkSpinButton* spinButton, gpointer data)
{
    NumericUpDown* numeric = reinterpret_cast<NumericUpDown*>(data);

    numeric->onValueChanged(data);
}