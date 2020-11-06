#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Widget.h"

namespace LinuxForms    
{
    class Window : public Widget
    {
    public:        
        Window();
        Window(const std::string& text, int width, int height);
        void Add(GtkWidget* child);
        void Add(Widget* child);
        void SetStyleSheet(const std::string& cssFilePath);
        void SetTitle(const std::string& title);
        void Show() override;
        EventHandler<DrawEvent> onDraw;
        EventHandler<WindowClosingEvent> onClosing;
        EventHandler<KeyDownEvent> onKeyDown;
        EventHandler<KeyUpEvent> onKeyUp;        
    private:        
        static void WindowClosing(GtkWidget *widget, gpointer data);
        static gboolean Draw(GtkWidget* widget, cairo_t* cr, gpointer data);
        static gboolean KeyDown(GtkWidget *widget, GdkEventKey *event, gpointer data);
        static gboolean KeyUp(GtkWidget *widget, GdkEventKey *event, gpointer data);
    };
}

#endif