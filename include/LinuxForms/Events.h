#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <gtk/gtk.h>
#include <functional>
#include "Input/KeyCode.h"

namespace LinuxForms
{
    //typedef std::function<void(GtkWidget *widget, gpointer data)> FormClosingEvent;
    typedef std::function<void()> FormClosingEvent;
    typedef std::function<void()> ButtonClickedEvent;
    typedef std::function<void()> TextChangedEvent;
    typedef std::function<void()> MenuItemClickedEvent;
    typedef std::function<void(GtkWidget* widget, cairo_t* cr, gpointer data)> DrawEvent;
    typedef std::function<void()> SubmitEvent;
    typedef std::function<void(const KeyCode& keycode)> KeyDownEvent;
    typedef std::function<void(const KeyCode& keycode)> KeyUpEvent;
}

#endif