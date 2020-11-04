#include "ScrolledWindow.h"

LinuxForms::ScrolledWindow::ScrolledWindow()
{
    GtkPolicyType policyHorizontal = GTK_POLICY_AUTOMATIC;
    GtkPolicyType policyVertical = GTK_POLICY_AUTOMATIC;

    widget = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget), policyHorizontal, policyVertical);    
	hAdjustment = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(widget));
	vAdjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(widget));
}

LinuxForms::ScrolledWindow::ScrolledWindow(const ScrollBarPolicy& horizontalPolicy, const ScrollBarPolicy& verticalPolicy)
{
    GtkPolicyType policyHorizontal;
    GtkPolicyType policyVertical;

    switch(horizontalPolicy)
    {
    case ScrollBarPolicy::Always:
        policyHorizontal = GTK_POLICY_ALWAYS;
        break;
    case ScrollBarPolicy::Automatic:
        policyHorizontal = GTK_POLICY_AUTOMATIC;
        break;
    case ScrollBarPolicy::Hidden:
        policyHorizontal = GTK_POLICY_NEVER;
        break;                
    default:
        policyHorizontal = GTK_POLICY_AUTOMATIC;
        break;
    }

    switch(verticalPolicy)
    {
    case ScrollBarPolicy::Always:
        policyVertical = GTK_POLICY_ALWAYS;
        break;
    case ScrollBarPolicy::Automatic:
        policyVertical = GTK_POLICY_AUTOMATIC;
        break;
    case ScrollBarPolicy::Hidden:
        policyVertical = GTK_POLICY_NEVER;
        break;                
    default:
        policyVertical = GTK_POLICY_AUTOMATIC;
        break;
    }

    widget = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widget), policyHorizontal, policyVertical);    
	hAdjustment = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(widget));
	vAdjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(widget));
}

void LinuxForms::ScrolledWindow::Add(GtkWidget* child)
{
	gtk_container_add(GTK_CONTAINER(widget), child);
}

void LinuxForms::ScrolledWindow::Add(Widget* child)
{
	gtk_container_add(GTK_CONTAINER(widget), child->widget);
}

LinuxForms::Vector2 LinuxForms::ScrolledWindow::GetScrollPosition()
{
	double x = gtk_adjustment_get_value(hAdjustment);
	double y = gtk_adjustment_get_value(vAdjustment);
	return {x, y};
}