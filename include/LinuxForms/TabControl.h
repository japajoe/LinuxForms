#ifndef TABCONTROL_HPP
#define TABCONTROL_HPP

#include "Widget.h"
#include <vector>

namespace LinuxForms
{    
    template<typename T>
    class TabControlItem
    {
    public:        
        GtkWidget* widget;
        std::shared_ptr<T> item;        
        std::shared_ptr<Label> label;
        std::shared_ptr<Box> box;
        std::shared_ptr<ScrolledWindow> scrolledWindow;
    };

    template<typename T>
    class TabControl : public Widget
    {
    public:
        TabControl()
        {
            widget = gtk_notebook_new();
        }

        void Add(const std::shared_ptr<T>& item, bool addScrollView = true)
        {
            Widget* itemWidget = dynamic_cast<Widget*>(item.get());

            if(itemWidget != nullptr)
            {
                std::string labelText = "Page " + std::to_string(items.size() + 1);

                TabControlItem<T> tabItem;
                tabItem.item = item;
                tabItem.widget = itemWidget->widget;
                tabItem.box = Widget::Create<Box>();
                tabItem.label = Widget::Create<Label>();
                tabItem.label->SetText(labelText);

                items.push_back(tabItem);

                if(addScrollView)
                {
                    tabItem.scrolledWindow = Widget::Create<ScrolledWindow>();
                    tabItem.box->Add(tabItem.scrolledWindow.get(), true, true, 0);
                    tabItem.scrolledWindow->Add(tabItem.widget);
                    gtk_notebook_append_page(GTK_NOTEBOOK(widget), tabItem.box->widget, tabItem.label->widget);
                }
                else
                {
                    tabItem.box->Add(tabItem.widget, true, true, 0);
                    gtk_notebook_append_page(GTK_NOTEBOOK(widget), tabItem.box->widget, tabItem.label->widget);
                }                
            }           
        }

        void Remove(size_t index)
        {
            if(index >= items.size())
                return;

            gtk_notebook_remove_page(GTK_NOTEBOOK(widget), index);
            items.erase(items.begin() + index);
        }

        void SetTitle(size_t index, const std::string& title)
        {
            if(index >= items.size())
                return;
            
            items[index].label->SetText(title);
        }
    private:
        std::vector<TabControlItem<T>> items;
    };
}

#endif