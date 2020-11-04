#ifndef SCROLLEDWINDOW_HPP
#define SCROLLEDWINDOW_HPP

#include "Widget.h"
#include "ScrollBarPolicy.h"
#include "Vector2.h"

namespace LinuxForms
{
    class ScrolledWindow : public Widget
    {
    public:
        ScrolledWindow();
        ScrolledWindow(const ScrollBarPolicy& horizontalPolicy, const ScrollBarPolicy& verticalPolicy);
        void Add(GtkWidget* child);
        void Add(Widget* child);
        Vector2 GetScrollPosition();
    private:
        GtkAdjustment* hAdjustment;
        GtkAdjustment* vAdjustment;
    };
}

#endif