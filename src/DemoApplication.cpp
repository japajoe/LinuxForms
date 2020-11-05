#include "DemoApplication.h"

void DemoApplication::Initialize()
{
    boxMain    = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
    tabControl = std::make_shared<TabControl<TextView>>();

    InitializeMenu();

    form->Add(boxMain.get());
    boxMain->Add(menubar.get(), false, false, 0);
    boxMain->Add(tabControl.get(), true, true, 0);
    auto tabControlItem = tabControl->AddItem();    

    if(tabControlItem != nullptr)
        tabControlItem->item->SetText("Type your text here");

    form->SetTitle("Demo Application");

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
    form->onClosing += [this] () { this->OnApplicationClosing(); };
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
            auto tabPage = tabControl->AddItem();
            
            if(tabPage != nullptr)
                tabPage->item->SetText(text);
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

void DemoApplication::OnApplicationClosing()
{
    Console::WriteLine("Closing application");
}