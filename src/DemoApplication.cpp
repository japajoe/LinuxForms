#include "DemoApplication.h"

void DemoApplication::Initialize()
{
    boxMain         = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
    panel           = std::make_shared<Panel>(200, 80);
    tabControl      = std::make_shared<TabControl<TextView>>();
    splitContainer  = std::make_shared<SplitContainer>(GtkOrientation::GTK_ORIENTATION_VERTICAL);
    button          = std::make_shared<Button>("Change Color");
    drawingArea     = std::make_shared<DrawingArea>(50, 50);

    InitializeMenu();

    window->Add(boxMain.get());
    boxMain->Add(menubar.get(), false, false, 5);
    boxMain->Add(splitContainer.get(), true, true, 5);
    splitContainer->Add(tabControl.get(), 0, true, false);
    splitContainer->Add(panel.get(), 1, true, false);
    panel->Add(button.get(), 5, 0);
    panel->Add(drawingArea.get(), 5, 30);
    
    auto tabControlItem = tabControl->AddItem();

    if(tabControlItem != nullptr)
        tabControlItem->item->SetText("Type your text here");

    window->SetTitle("Demo Application");

    int height = window->rectangle.height - 120;

    splitContainer->SetSeparatorPosition(height);

    InitializeCallbacks();
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

void DemoApplication::InitializeCallbacks()
{
    window->onClosing     += [this] () { this->OnApplicationClosing(); };
    button->onClicked   += [this] () { this->OnButtonClicked(); };
    drawingArea->onDraw += [this] (GtkWidget* widget, cairo_t* cr, gpointer data) { this->OnDraw(widget, cr, data); };
}

void DemoApplication::OnMenuItemOpenClicked()
{
    OpenFileDialog dialog;

    if(dialog.ShowDialog(window.get()) == DialogResult::OK)
    {
        std::string filename = dialog.GetFileName();
        
        if(IO::FileExists(filename))
        {
            std::string text = IO::ReadAllText(filename);            
            auto tabPage = tabControl->AddItem();
            
            if(tabPage != nullptr)
                tabPage->item->SetText(text);
        }
    }
}

void DemoApplication::OnMenuItemSaveClicked()
{
    SaveFileDialog dialog;

    if(dialog.ShowDialog(window.get()) == DialogResult::OK)
    {
        std::string filename = dialog.GetFileName();

        int selectedTab = tabControl->GetSelectedIndex();

        if(selectedTab >= 0)
        {
            auto selected = tabControl->GetItemAtIndex(selectedTab);

            if(selected != nullptr)
            {
                std::string text = selected->item->GetText();
                IO::WriteAllText(text, filename);
                Console::WriteLine("Saved file as " + filename);
            }
        }
    }
}

void DemoApplication::OnMenuItemExitClicked()
{
    Quit();
}

void DemoApplication::OnButtonClicked()
{
    ColorPickerDialog dialog(window.get());

    if(dialog.ShowDialog(window.get()) == DialogResult::OK)
    {
        color = dialog.GetColor();
    }
}

void DemoApplication::OnDraw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    cairo_set_source_rgba(cr, color.r, color.g, color.b, color.a);
    cairo_rectangle(cr, 0, 0, 50, 50);
    cairo_fill(cr);
    gtk_widget_queue_draw(widget);
}

void DemoApplication::OnApplicationClosing()
{
    Console::WriteLine("Closing application");
}