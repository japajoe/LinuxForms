#include "DemoApplication.h"
#include "Mathf.h"

void DemoApplication::Initialize()
{
    boxMain = std::make_shared<Box>();
    image   = std::make_shared<Image>("earth.jpg");

    InitializeMenu();

    form->Add(boxMain.get());
    boxMain->Add(menubar.get(), false, false, 0);
    boxMain->Add(image.get(), true, true, 0);

    form->SetTitle("Demo Application");
    CreateCallbacks();
}

void DemoApplication::InitializeMenu()
{
    MenuInfo menuInfoFile("File");	

    menuInfoFile.AddItem("Open", [this]() { this->OnMenuItemOpenClicked(); });
    menuInfoFile.AddItem("Save", [this]() { this->OnMenuItemSaveClicked(); });
    menuInfoFile.AddItem("Exit", [this]() { this->OnMenuItemExitClicked(); });

    std::vector<MenuInfo> menuInfo;
    menuInfo.push_back(menuInfoFile);

    menubar = std::make_shared<MenuBar>(menuInfo);    
}

void DemoApplication::CreateCallbacks()
{
    form->onClosing += [this]() { this->OnApplicationClosing(); };
    form->onDraw    += [this] (GtkWidget* widget, cairo_t* cr, gpointer data) { this->OnDraw(widget, cr, data); };
}

void DemoApplication::OnMenuItemOpenClicked()
{
    OpenFileDialog dialog;

    if(dialog.ShowDialog(form.get()) == DialogResult::OK)
    {
        std::string filename = dialog.GetFileName();
    }
}

void DemoApplication::OnMenuItemSaveClicked()
{
    SaveFileDialog dialog;

    if(dialog.ShowDialog(form.get()) == DialogResult::OK)
    {
        std::string filename = dialog.GetFileName();
    }
}

void DemoApplication::OnMenuItemExitClicked()
{
    Quit();
}

void DemoApplication::OnDraw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    image->Render(cr, 0, 0);
    gtk_widget_queue_draw(widget);
}

void DemoApplication::OnApplicationClosing()
{

}