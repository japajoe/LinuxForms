#ifndef COLORPICKERDIALOG_HPP
#define COLORPICKERDIALOG_HPP

#include "Widget.h"
#include "DialogResult.h"
#include "Window.h"

namespace LinuxForms
{
    class ColorPickerDialog : public Widget
    {
    public:
        ColorPickerDialog(Window* window = nullptr);        
        DialogResult ShowDialog(Window* window = nullptr);
        Color GetColor() const
        {
            return color;
        }
    private:
        GdkRGBA selectedColor;
        Color color;
        GtkWidget* parentWindow;
    };
}

#endif