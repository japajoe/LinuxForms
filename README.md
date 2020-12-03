# LinuxForms

This project is created because I don't like how I have to interact with GTK+ to get things done. The toolkit is complete and mature, but its namingconventions are terrible and the documentation doesn't help much either in my opinion. Often one has to do many searches to find an example of how to use a specific but yet very basic mechanism, only to find out that it's not as straightforward as it could be. Sure I could use gtkmm because it surely is more consistent and elegant, but ultimately GTK+ is a C-library which means it's very doable to wrap things up yourself.

I do not intend to make a replacement for gtkmm however, I'm merely trying to make an alternative object oriented library which solepurpose is to aid me in my UI projects. I'm heavily inspired by the design of Windows Forms because I think it has a great API which makes a lot of sense to me and it allows me to easily navigate my way through it and get things done quickly.

# Dependencies
- libgtk-3-dev
- glib 2.0
- libgtksourceview-3.0-dev

# Example application made with LinuxForms
![alt text](https://github.com/japajoe/LinuxForms/tree/main/Example/SharpAudioPreview.png?raw=true)

# How to use


- Creating an application
```cpp
#include "LinuxForms/Application.h"
#include <memory>

using namespace LinuxForms;

class MyApplication : public LinuxForms::Application
{
public:
    void Initialize() override;
    std::shared_ptr<Box> box;
    std::shared_ptr<Button> button;
private:
    void OnButtonClicked(gpointer data);
    void OnApplicationQuit();
};
```

```cpp
#include "MyApplication.h"
#include <iostream>

void MyApplication::Initialize()
{
    //Create widgets and set up callbacks
    box = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0, false);
    button = std::make_shared<Button>("Click");

    window->Add(box->widget);
    box->Add(button->widget, false, false, 0);

    window->onClosing += [this] () { this->OnApplicationQuit(); };
    button->onClicked += [this] (gpointer data) { this->OnButtonClicked(data); };

    window->SetSize({ 512, 512 });
    window->SetTitle("Demo Application");
    window->Show();
}

void MyApplication::OnButtonClicked(gpointer data)
{
    std::cout << "Button clicked\n";
}

void MyApplication::OnApplicationQuit()
{
    //Clean up stuff before programs exits
}
```

- Starting an application
```cpp
#include "MyApplication.h"
#include <memory>

int main(int argc, char** argv)
{
    auto application = std::make_unique<MyApplication>();
    application->Run(argc, argv);
    return 0;
}
```
