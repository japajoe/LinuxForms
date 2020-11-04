#include "DrawingArea.h"

LinuxForms::DrawingArea::DrawingArea()
{
    //this->onDraw = nullptr;
    widget = gtk_drawing_area_new();
    gtk_widget_set_size_request(widget, 128, 64);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
}

LinuxForms::DrawingArea::DrawingArea(const int& width, const int& height)
{
    //this->onDraw = nullptr;
    widget = gtk_drawing_area_new();
    gtk_widget_set_size_request(widget, width, height);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
}

gboolean LinuxForms::DrawingArea::Draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    DrawingArea* drawingArea = reinterpret_cast<DrawingArea*>(data);

    if(drawingArea->onDraw != nullptr)
        drawingArea->onDraw(widget, cr, data);
    return false;
}