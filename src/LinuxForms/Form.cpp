#include "Form.h"
#include <iostream>
#include "Input/Input.h"

using namespace LinuxForms;

LinuxForms::Form::Form()
{
    this->name = name;
    this->size = { 500, 500 };
	
    widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_widget_add_events(widget, GDK_KEY_PRESS_MASK | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
    
    g_signal_connect(widget, "destroy", G_CALLBACK(FormClosing), this);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
	g_signal_connect(widget, "key-press-event", G_CALLBACK(KeyDown), this);
	g_signal_connect(widget, "key-release-event", G_CALLBACK(KeyUp), this);
    
    gtk_window_set_resizable(GTK_WINDOW(widget),true);
    gtk_window_set_title(GTK_WINDOW(widget), "Linux Forms");
    SetSize(size);
}

LinuxForms::Form::Form(const std::string& name, int width, int height)
{
    this->name = name;
    this->size = { width, height };
	
    widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_widget_add_events(widget, GDK_KEY_PRESS_MASK | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);
    
    g_signal_connect(widget, "destroy", G_CALLBACK(FormClosing), this);
    g_signal_connect(widget, "draw", G_CALLBACK(Draw), this);
	g_signal_connect(widget, "key-press-event", G_CALLBACK(KeyDown), this);
	g_signal_connect(widget, "key-release-event", G_CALLBACK(KeyUp), this);
    
    gtk_window_set_resizable(GTK_WINDOW(widget),true);
    SetTitle(name);
    SetSize(size);
}

void LinuxForms::Form::Add(Widget* child)
{
    gtk_container_add(GTK_CONTAINER(widget), child->widget);
}

void LinuxForms::Form::Add(GtkWidget* child)
{
    gtk_container_add(GTK_CONTAINER(widget), child);
}

void LinuxForms::Form::SetStyleSheet(const std::string& cssFilePath)
{
	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, cssFilePath.c_str(), NULL);    
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void LinuxForms::Form::SetTitle(const std::string& title)
{
    gtk_window_set_title(GTK_WINDOW(widget), title.c_str());
}

gboolean LinuxForms::Form::Draw(GtkWidget* widget, cairo_t* cr, gpointer data)
{
    Form* form = reinterpret_cast<Form*>(data);

    if(form->onDraw != nullptr)
        form->onDraw(widget, cr, data);
    return false;
}

void LinuxForms::Form::FormClosing(GtkWidget *widget, gpointer data)
{    
    Form* form = reinterpret_cast<Form*>(data);
    
    if(form->onClosing != nullptr)
        form->onClosing();
    else
        gtk_main_quit();    
}

gboolean LinuxForms::Form::KeyDown(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    int vkCode = event->keyval;
	KeyCode key = (KeyCode)vkCode;	
    Input::SetStateUp(key, 0);
    Input::SetStateDown(key, 1);

    Form* form = reinterpret_cast<Form*>(data);
    form->onKeyDown(key);
    return false;
}

gboolean LinuxForms::Form::KeyUp(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    int vkCode = event->keyval;
    KeyCode key = (KeyCode)vkCode;
    Input::SetStateDown(key, 0);
    Input::SetStateUp(key, 1);

    Form* form = reinterpret_cast<Form*>(data);
    form->onKeyUp(key);
    return false;
}