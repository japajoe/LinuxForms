#include "Panel.h"

LinuxForms::Panel::Panel()
{
    widget = gtk_fixed_new();
	gtk_widget_set_size_request(widget, 128, 128);
}

LinuxForms::Panel::Panel(int width, int height)
{
    widget = gtk_fixed_new();    
	gtk_widget_set_size_request(widget, width, height);
}

void LinuxForms::Panel::Add(Widget* child, int x, int y)
{
    gtk_fixed_put(GTK_FIXED(widget), child->widget, x, y);
}

void LinuxForms::Panel::Add(GtkWidget* child, int x, int y)
{
    gtk_fixed_put(GTK_FIXED(widget), child, x, y);
}