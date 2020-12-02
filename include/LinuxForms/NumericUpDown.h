#ifndef NUMERICUPDOWN_HPP
#define NUMERICUPDOWN_HPP

#include "Widget.h"

namespace LinuxForms
{
    class NumericUpDown : public Widget
    {
    public:
        NumericUpDown();
        NumericUpDown(double value, double valueMin, double valueMax, double stepSize = 1.0);
        double GetValue() const;
        void SetValue(double value);
        static void ValueChanged(GtkSpinButton* spinButton, gpointer data);
        EventHandler<ValueChangedEvent> onValueChanged;
    };
}
#endif