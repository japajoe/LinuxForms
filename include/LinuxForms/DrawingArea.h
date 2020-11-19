#ifndef DRAWINGAREA_HPP
#define DRAWINGAREA_HPP

#include "Widget.h"

namespace LinuxForms
{
    class DrawingArea : public Widget
    {
    public:
        DrawingArea();
        DrawingArea(const int& width, const int& height);
        EventHandler<DrawEvent> onDraw;
        EventHandler<ButtonPressedEvent> onButtonPressed;
    private:
        static gboolean Draw(GtkWidget* widget, cairo_t* cr, gpointer data);
        static gboolean ButtonPressed(GtkWidget* widget, GdkEventButton* event, gpointer data);
    };
}
#endif