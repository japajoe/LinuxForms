#include "Box.h"

LinuxForms::Box::Box()
{
    widget = gtk_box_new(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
}

LinuxForms::Box::Box(const GtkOrientation& orientation, unsigned int spacing)
{
    widget = gtk_box_new(orientation, spacing);
}

void LinuxForms::Box::Add(GtkWidget* target, bool expand, bool fill, unsigned int padding)
{
    gtk_box_pack_start(GTK_BOX(widget), target, expand, fill, padding);    
}

void LinuxForms::Box::Add(Widget* target, bool expand, bool fill, unsigned int padding)
{
    gtk_box_pack_start(GTK_BOX(widget), target->widget, expand, fill, padding);    
}