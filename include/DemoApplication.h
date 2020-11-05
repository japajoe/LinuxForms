#ifndef DEMOAPPLICATION_HPP
#define DEMOAPPLICATION_HPP

#include "LinuxForms/Application.h"

using namespace LinuxForms;

class DemoApplication : public LinuxForms::Application
{
public:
    //Initialize widgets and register callbacks
    void Initialize() override;
    void InitializeMenu();
    void InitializeCallbacks();

    //Menu Item Callbacks
    void OnMenuItemOpenClicked();
    void OnMenuItemSaveClicked();
    void OnMenuItemExitClicked();

    //Widget Callbacks
    void OnButtonClicked();
    void OnDraw(GtkWidget* widget, cairo_t* cr, gpointer data);
    void OnApplicationClosing();
private:
    //Widgets
    std::shared_ptr<Box> boxMain;
    std::shared_ptr<Panel> panel;
    std::shared_ptr<MenuBar> menubar;
    std::shared_ptr<SplitContainer> splitContainer;
    std::shared_ptr<TabControl<TextView>> tabControl;
    std::shared_ptr<Button> button;
    std::shared_ptr<DrawingArea> drawingArea;

    //Other variables
    Color color { 1.0f, 1.0f, 0.0f, 1.0f };
};

#endif