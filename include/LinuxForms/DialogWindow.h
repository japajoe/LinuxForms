#ifndef DIALOGWINDOW_HPP
#define DIALOGWINDOW_HPP

#include "Widget.h"
#include "Box.h"
#include "Label.h"
#include "Button.h"
#include "DialogResult.h"

namespace LinuxForms
{
    class DialogWindow : public Widget
    {
    public:
        DialogWindow(const std::string& title, const std::string& message);
        void Add(GtkWidget* child);
        void Add(Widget* child);
        void SetTitle(const std::string& title);
        void Show() override;
        EventHandler<WindowClosingEvent> onClosing;
    private:
        std::shared_ptr<Box> box;
        std::shared_ptr<Label> label;
        std::shared_ptr<Button> buttonOk;
        std::shared_ptr<Button> buttonCancel;
        void OnButtonOkClicked();
        void OnButtonCancelClicked();
        static void WindowClosing(GtkWidget *widget, gpointer data);
    };
}

#endif