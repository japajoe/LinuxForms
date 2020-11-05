#ifndef COLORPICKERDIALOG_HPP
#define COLORPICKERDIALOG_HPP

#include "Widget.h"
#include "DialogResult.h"
#include "Form.h"

namespace LinuxForms
{
    class ColorPickerDialog : public Widget
    {
    public:
        ColorPickerDialog(Form* window = nullptr);        
        DialogResult ShowDialog(Form* window = nullptr);
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