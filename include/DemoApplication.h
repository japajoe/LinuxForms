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
    void OnApplicationClosing();
private:
    //Widgets
    std::shared_ptr<Box> boxMain;
    std::shared_ptr<MenuBar> menubar;
    std::shared_ptr<TabControl<TextView>> tabControl;
};

#endif