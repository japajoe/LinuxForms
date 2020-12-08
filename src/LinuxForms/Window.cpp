#include "Window.h"
#include <iostream>
#include "Input/Input.h"

using namespace LinuxForms;

LinuxForms::Window::Window()
{
    this->name = name;
    this->size = { 500, 500 };
	
    widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_widget_add_events(widget, GDK_KEY_PRESS_MASK | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
    
    g_signal_connect(widget, "destroy", G_CALLBACK(WindowClosing), this);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
	g_signal_connect(widget, "key-press-event", G_CALLBACK(KeyDown), this);
	g_signal_connect(widget, "key-release-event", G_CALLBACK(KeyUp), this);
    
    gtk_window_set_resizable(GTK_WINDOW(widget),true);
    gtk_window_set_title(GTK_WINDOW(widget), "Linux Forms");
    SetSize(size);
}

LinuxForms::Window::Window(const std::string& name, int width, int height)
{
    this->name = name;
    this->size = { width, height };
	
    widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_widget_add_events(widget, GDK_KEY_PRESS_MASK | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
    
    g_signal_connect(widget, "destroy", G_CALLBACK(WindowClosing), this);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
	g_signal_connect(widget, "key-press-event", G_CALLBACK(KeyDown), this);
	g_signal_connect(widget, "key-release-event", G_CALLBACK(KeyUp), this);
    
    gtk_window_set_resizable(GTK_WINDOW(widget),true);
    SetTitle(name);
    SetSize(size);
}

void LinuxForms::Window::Add(Widget* child)
{
    gtk_container_add(GTK_CONTAINER(widget), child->widget);
}

void LinuxForms::Window::Add(GtkWidget* child)
{
    gtk_container_add(GTK_CONTAINER(widget), child);
}

void LinuxForms::Window::SetStyleSheet(const std::string& cssFilePath)
{
	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, cssFilePath.c_str(), NULL);    
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void LinuxForms::Window::SetTitle(const std::string& title)
{
    gtk_window_set_title(GTK_WINDOW(widget), title.c_str());
}

void LinuxForms::Window::Show()
{
    gtk_widget_show_all(widget);
}

gboolean LinuxForms::Window::Draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    Window* window = reinterpret_cast<Window*>(data);

    if(window->onDraw != nullptr)
        window->onDraw(widget, cr, data);
    return false;
}

void LinuxForms::Window::WindowClosing(GtkWidget *widget, gpointer data)
{    
    Window* window = reinterpret_cast<Window*>(data);
    
    if(window->onClosing != nullptr)
        window->onClosing();
    else
        gtk_main_quit();    
}

gboolean LinuxForms::Window::KeyDown(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    int vkCode = event->keyval;

	KeyCode key = (KeyCode)vkCode;	
    Input::SetStateUp(key, 0);
    Input::SetStateDown(key, 1);

    Window* window = reinterpret_cast<Window*>(data);
    window->onKeyDown(key);
    return false;
}

gboolean LinuxForms::Window::KeyUp(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    int vkCode = event->keyval;
    KeyCode key = (KeyCode)vkCode;
    Input::SetStateDown(key, 0);
    Input::SetStateUp(key, 1);

    Window* window = reinterpret_cast<Window*>(data);
    window->onKeyUp(key);
    return false;
}
