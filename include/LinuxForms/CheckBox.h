#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "Widget.h"

namespace LinuxForms
{
    class CheckBox : public Widget
    {
    public:
        CheckBox();
        CheckBox(const std::string& text);
        bool GetValue() const;
        void SetValue(bool checked);
        static void Toggled(GtkToggleButton *widget, gpointer data);
        EventHandler<ValueChangedEvent> onValueChanged;
    };
}
#endif