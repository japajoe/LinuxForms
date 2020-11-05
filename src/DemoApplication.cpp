#include "DemoApplication.h"

void DemoApplication::Initialize()
{
    boxMain    = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
    tabControl = std::make_shared<TabControl<TextView>>();

    auto textview1 = std::make_shared<TextView>();
    auto textview2 = std::make_shared<TextView>();
    auto textview3 = std::make_shared<TextView>();    

    InitializeMenu();

    form->Add(boxMain.get());
    boxMain->Add(menubar.get(), false, false, 0);
    boxMain->Add(tabControl.get(), true, true, 0);
    tabControl->Add(textview1);
    tabControl->Add(textview2);
    tabControl->Add(textview3);

    form->SetTitle("Demo Application");
    CreateCallbacks();
}

void DemoApplication::InitializeMenu()
{
    MenuInfo menuInfoFile("File");	

    menuInfoFile.AddItem("Open", [this] () { this->OnMenuItemOpenClicked(); });
    menuInfoFile.AddItem("Save", [this] () { this->OnMenuItemSaveClicked(); });
    menuInfoFile.AddItem("Exit", [this] () { this->OnMenuItemExitClicked(); });

    std::vector<MenuInfo> menuInfo;
    menuInfo.push_back(menuInfoFile);

    menubar = std::make_shared<MenuBar>(menuInfo);
}

void DemoApplication::CreateCallbacks()
{
    form->onClosing += [this] () { this->OnApplicationClosing(); };
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
    TimeUtility::Update();
    gtk_widget_queue_draw(widget);
}

void DemoApplication::OnApplicationClosing()
{
    Console::WriteLine("Closing application");
}