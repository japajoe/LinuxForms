#ifndef DEMOAPPLICATION_HPP
#define DEMOAPPLICATION_HPP

#include "Application.h"

using namespace LinuxForms;

class DemoApplication : public LinuxForms::Application
{
public:
    //Initialize widgets and register callbacks
    void Initialize() override;
    void InitializeMenu();
    void CreateCallbacks();

    //Menu Item Callbacks
    void OnMenuItemOpenClicked();
    void OnMenuItemSaveClicked();
    void OnMenuItemExitClicked();

    //Widget Callbacks
    void OnDraw(GtkWidget* widget, cairo_t* cr, gpointer data);
    void OnApplicationClosing();
private:
    //Widgets
    std::shared_ptr<Box> boxMain;
    std::shared_ptr<Box> boxHorizontal;
    std::shared_ptr<MenuBar> menubar;
    std::shared_ptr<Image> image;
    std::shared_ptr<Label> label;
};

#endif