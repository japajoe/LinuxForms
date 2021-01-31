#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <gtk/gtk.h>
#include <functional>
#include "Input/KeyCode.h"

namespace LinuxForms
{
    typedef std::function<void()> WindowClosingEvent;
    typedef std::function<void(gpointer data)> ButtonClickedEvent;
    typedef std::function<void(guint button, double x, double y)> ButtonPressedEvent;
    typedef std::function<void(int index)> TabButtonClickedEvent;
    typedef std::function<void()> TextChangedEvent;
    typedef std::function<void()> MenuItemClickedEvent;
    typedef std::function<void(GtkNotebook* notebook, GtkWidget* page, guint page_num, gpointer data)> SelectedTabChangedEvent;
    typedef std::function<void(GtkWidget* widget, cairo_t* cr, gpointer data)> DrawEvent;
    typedef std::function<void()> SubmitEvent;
    typedef std::function<void(const KeyCode& keycode)> KeyDownEvent;
    typedef std::function<void(const KeyCode& keycode)> KeyUpEvent;
    typedef std::function<void()> TimerTickEvent;
    typedef std::function<void(gpointer data)> ValueChangedEvent;
    typedef std::function<void(GtkGLArea* area, GdkGLContext* context, gpointer data)> GLAreaRenderEvent;
    typedef std::function<void(GtkGLArea* area, gpointer data)> GLAreaRealizeEvent;
    typedef std::function<void(GtkGLArea* area, gpointer data)> GLAreaUnRealizeEvent;
    typedef std::function<void(GtkWidget* widget, GdkEventMotion* event, gpointer data)> MouseMoveEvent;
    typedef std::function<void(GtkGLArea* area, int width, int height, gpointer data)> GLAreaResizeEvent;
}

#endif