#include "DrawingArea.h"

LinuxForms::DrawingArea::DrawingArea()
{
    widget = gtk_drawing_area_new();
    gtk_widget_set_size_request(widget, 128, 64);
    gtk_widget_add_events(widget, GDK_BUTTON_PRESS_MASK);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
    g_signal_connect(widget, "button-press-event", G_CALLBACK(ButtonPressed), this);
}

LinuxForms::DrawingArea::DrawingArea(const int& width, const int& height)
{
    widget = gtk_drawing_area_new();
    gtk_widget_set_size_request(widget, width, height);
    gtk_widget_add_events(widget, GDK_BUTTON_PRESS_MASK);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
    g_signal_connect(widget, "button-press-event", G_CALLBACK(ButtonPressed), this);
}

gboolean LinuxForms::DrawingArea::Draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    DrawingArea* drawingArea = reinterpret_cast<DrawingArea*>(data);

    if(drawingArea->onDraw != nullptr)
        drawingArea->onDraw(widget, cr, data);
    return false;
}

gboolean LinuxForms::DrawingArea::ButtonPressed(GtkWidget* widget, GdkEventButton* event, gpointer data)
{
    DrawingArea* drawingArea = reinterpret_cast<DrawingArea*>(data);    

    if(drawingArea->onButtonPressed != nullptr)
        drawingArea->onButtonPressed(event->button, event->x, event->y);
    return true;    
}