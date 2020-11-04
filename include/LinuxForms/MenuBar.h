#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include "Widget.h"
#include <vector>

namespace LinuxForms
{
    class MenuInfo
    {
    public:
        std::string name;
        std::vector<std::string> items;
        std::vector<MenuItemClickedEvent> callbacks;

        MenuInfo(const std::string& name)
        {
            this->name = name;
        }

        void AddItem(const std::string& itemName, MenuItemClickedEvent callback)
        {
            items.push_back(itemName);
            callbacks.push_back(callback);
        }
    };

    class MenuBar : public Widget
    {
    public:
        MenuBar();
        MenuBar(const std::vector<MenuInfo>& menuInfo);
        void AddMenu(const MenuInfo& name);        
    private:
        std::vector<MenuInfo> menu;
        static void MenuItemClicked(GtkWidget *widget, gpointer data);
    };
}
#endif