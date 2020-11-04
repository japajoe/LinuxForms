#ifndef PANEL_HPP
#define PANEL_HPP

#include "Widget.h"

namespace LinuxForms    
{
    class Panel : public Widget
    {
    public:        
        Panel();
        Panel(int width, int height);
        void Add(Widget* child, int x, int y);
        void Add(GtkWidget* child, int x, int y);
    };
}

#endif