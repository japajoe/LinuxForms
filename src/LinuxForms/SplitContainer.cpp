#include "SplitContainer.h"

LinuxForms::SplitContainer::SplitContainer()
{
    widget = gtk_paned_new(GtkOrientation::GTK_ORIENTATION_HORIZONTAL);
}

LinuxForms::SplitContainer::SplitContainer(const GtkOrientation& orientation)
{
    widget = gtk_paned_new(orientation);
}

void LinuxForms::SplitContainer::Add(GtkWidget* child, unsigned int location, bool resize, bool shrink)
{
	if(location == 0)
		gtk_paned_pack1(GTK_PANED(widget), child, resize, shrink);
	else
		gtk_paned_pack2(GTK_PANED(widget), child, resize, shrink);	
}

void LinuxForms::SplitContainer::Add(Widget* child, unsigned int location, bool resize, bool shrink)
{
	if(location == 0)
		gtk_paned_pack1(GTK_PANED(widget), child->widget, resize, shrink);
	else
		gtk_paned_pack2(GTK_PANED(widget), child->widget, resize, shrink);	
}

void LinuxForms::SplitContainer::SetSeparatorPosition(const int& position)
{
    gtk_paned_set_position(GTK_PANED(widget), position);
}