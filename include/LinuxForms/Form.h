#ifndef FORM_HPP
#define FORM_HPP

#include "Widget.h"

namespace LinuxForms    
{
    class Form : public Widget
    {
    public:        
        Form();
        Form(const std::string& text, int width, int height);
        void Add(GtkWidget* child);
        void Add(Widget* child);
        void SetStyleSheet(const std::string& cssFilePath);
        void SetTitle(const std::string& title);
        EventHandler<DrawEvent> onDraw;
        EventHandler<FormClosingEvent> onClosing;
        EventHandler<KeyDownEvent> onKeyDown;
        EventHandler<KeyUpEvent> onKeyUp;        
    private:        
        static void FormClosing(GtkWidget *widget, gpointer data);
        static gboolean Draw(GtkWidget* widget, cairo_t* cr, gpointer data);
        static gboolean KeyDown(GtkWidget *widget, GdkEventKey *event, gpointer data);
        static gboolean KeyUp(GtkWidget *widget, GdkEventKey *event, gpointer data);
    };
}

#endif