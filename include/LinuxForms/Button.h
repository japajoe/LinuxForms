#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Widget.h"

namespace LinuxForms    
{
    class Button : public Widget
    {
    public:        
        Button();
        Button(const std::string& text, int width = 100, int height = 20);
        void SetText(const std::string& text);
        EventHandler<ButtonClickedEvent> onClicked;
    private:        
        static void Clicked(GtkWidget *widget, gpointer data);
    };
}

#endif