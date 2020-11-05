#include "DemoApplication.h"

void DemoApplication::Initialize()
{
    boxMain    = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
    tabControl = std::make_shared<TabControl<TextView>>();

    auto textview = std::make_shared<TextView>();

    InitializeMenu();

    form->Add(boxMain.get());
    boxMain->Add(menubar.get(), false, false, 0);
    boxMain->Add(tabControl.get(), true, true, 0);
    tabControl->Add(textview);

    form->SetTitle("Demo Application");
    CreateCallbacks();

    textview->SetText("Type your text here");
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
        
        if(IO::FileExists(filename))
        {
            std::string text = IO::ReadAllText(filename);
            auto textview = std::make_shared<TextView>();
            tabControl->Add(textview);
            textview->SetText(text);
        }
        else
        {
            Console::WriteLine("File does not exist");
        }
    }
}

void DemoApplication::OnMenuItemSaveClicked()
{
    SaveFileDialog dialog;

    if(dialog.ShowDialog(form.get()) == DialogResult::OK)
    {
        std::string filename = dialog.GetFileName();

        int selectedTab = tabControl->GetSelectedIndex();

        if(selectedTab >= 0)
        {
            TabControlItem<TextView>* selected = tabControl->GetItemAtIndex(selectedTab);

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

void DemoApplication::OnDraw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    TimeUtility::Update();
    gtk_widget_queue_draw(widget);
}

void DemoApplication::OnApplicationClosing()
{
    Console::WriteLine("Closing application");
}