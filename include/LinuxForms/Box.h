#ifndef BOX_HPP
#define BOX_HPP

#include "Widget.h"

namespace LinuxForms
{
    class Box : public Widget
    {
    public:
        Box();
        Box(const GtkOrientation& orientation, unsigned int spacing);    
        void Add(GtkWidget* target, bool expand, bool fill, unsigned int padding);
        void Add(Widget* target, bool expand, bool fill, unsigned int padding);
    };
}
#endif