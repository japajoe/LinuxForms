#include "Widget.h"

LinuxForms::Widget::Widget()
{
    
}

void LinuxForms::Widget::Show()
{
    gtk_widget_show(widget);
}

int LinuxForms::Widget::GetId() const 
{ 
    return this->id; 
}

void LinuxForms::Widget::SetId(int id) 
{ 
    this->id = id; 
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

void LinuxForms::Widget::SetFocus()
{
    gtk_widget_grab_focus(widget);
}

void LinuxForms::Widget::SetAlignmentHorizontal(GtkAlign alignment)
{
    gtk_widget_set_halign(widget, alignment);
}

void LinuxForms::Widget::SetAlignmentVertical(GtkAlign alignment)
{
    gtk_widget_set_valign(widget, alignment);
}

void LinuxForms::Widget::SetMargins(double top, double left, double bottom, double right)
{
    if(top > 0)
    	gtk_widget_set_margin_top(widget, top);
    if(left > 0)	
        gtk_widget_set_margin_start(widget, left);
    if(bottom > 0)	
        gtk_widget_set_margin_bottom(widget, bottom);
    if(right > 0)	
        gtk_widget_set_margin_end(widget, right);
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
