#include "MenuBar.h"

LinuxForms::MenuBar::MenuBar()
{
	widget = gtk_menu_bar_new();	
}

LinuxForms::MenuBar::MenuBar(const std::vector<MenuInfo>& menuInfo)
{
	widget = gtk_menu_bar_new();
	
	for(size_t i = 0; i < menuInfo.size(); i++)
		AddMenu(menuInfo[i]);
}

void LinuxForms::MenuBar::AddMenu(const MenuInfo& menuInfo)
{
    this->menu.push_back(menuInfo);

    int currentIndex = menu.size() - 1;    

	GtkWidget* menuWidget = gtk_menu_new();
	GtkWidget* menuItem = gtk_menu_item_new_with_label(menuInfo.name.c_str());	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menuWidget);  
	gtk_menu_shell_append(GTK_MENU_SHELL(widget), menuItem);
	
	for(size_t i = 0; i < menu[currentIndex].items.size(); i++)
	{
        int index = i;
		GtkWidget* item = gtk_menu_item_new_with_label(menu[currentIndex].items[i].c_str());	
		gtk_menu_shell_append(GTK_MENU_SHELL(menuWidget), item);
		g_signal_connect(item, "activate", G_CALLBACK(MenuItemClicked), &menu[currentIndex].callbacks[index]);
	}
}

void LinuxForms::MenuBar::MenuItemClicked(GtkWidget *widget, gpointer data)
{
    MenuItemClickedEvent callback = *(reinterpret_cast<MenuItemClickedEvent*>(data));

    if(callback != nullptr)
        callback();
}