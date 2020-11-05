#include "DemoApplication.h"

void DemoApplication::Initialize()
{
    boxMain         = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
    boxHorizontal   = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_HORIZONTAL, 0);
    image           = std::make_shared<Image>();
    label           = std::make_shared<Label>();
    
    image->LoadFromData(100, 100, true);

    InitializeMenu();

    form->Add(boxMain.get());
    boxMain->Add(menubar.get(), false, false, 0);
    boxMain->Add(boxHorizontal.get(), false, false, 0);
    boxHorizontal->Add(label.get(), false, false, 5);
    boxHorizontal->Add(image.get(), false, false, 5);

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
    
    float t = Mathf::Abs(Mathf::Sin(2 * Mathf::PI * 8 * TimeUtility::GetTime() / 60));
    label->SetText(std::to_string(t));    
    
    Color colorA = { 1.0f, 0.0f, 0.0f, 1.0f };
    Color colorB = { 0.0f, 1.0f, 0.0f, 1.0f };
    Color color = Color::Lerp(colorA, colorB, t);

    image->Clear(color);
    image->Render(cr, 0, 0);
    gtk_widget_queue_draw(widget);
}

void DemoApplication::OnApplicationClosing()
{
    Console::WriteLine("Closing application");
}