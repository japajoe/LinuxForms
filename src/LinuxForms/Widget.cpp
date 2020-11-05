#include "Widget.h"

LinuxForms::Widget::Widget()
{
    
}

void LinuxForms::Widget::Show()
{
    gtk_widget_show_all(widget);
}

void LinuxForms::Widget::SetSize(const Size& size)
{
    this->size = size;
    gtk_widget_set_size_request(widget, size.width, size.height);
	CalculatePreferredSize();
}

void LinuxForms::Widget::CalculatePreferredSize()
{
	GtkRequisition naturalSize;	
	
	gtk_widget_get_preferred_size(widget, NULL, &naturalSize);
	
    this->size.width = naturalSize.width;
    this->size.height = naturalSize.height;
	this->rectangle.width = naturalSize.width;
	this->rectangle.height = naturalSize.height;
}

void LinuxForms::Widget::Destroy()
{
    if(GTK_IS_WIDGET(widget))
    {
        if(widget != nullptr)
        {
            gtk_widget_destroy(widget);
            widget = nullptr;
        }
    }
}