#ifndef PANED_HPP
#define PANED_HPP

#include "Widget.h"

namespace LinuxForms
{
    class SplitContainer : public Widget
    {
    public:
        SplitContainer();
        SplitContainer(const GtkOrientation& orientation);
        void Add(GtkWidget* child, unsigned int location, bool resize, bool shrink);
        void Add(Widget* child, unsigned int location, bool resize, bool shrink);
        void SetSeparatorPosition(const int& position);
    };
}
#endif