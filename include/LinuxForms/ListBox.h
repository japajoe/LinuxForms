#ifndef LISTBOX_HPP
#define LISTBOX_HPP

#include "Widget.h"
#include "ListItem.h"
#include "Button.h"
#include "Box.h"
#include "ScrolledWindow.h"
#include <vector>

namespace LinuxForms
{
    template <typename T>
    class ListBox : public Widget
    {
    public:
        std::shared_ptr<ScrolledWindow> scrolledWindow;
        
        ListBox()
        {
            this->numberOfItems = 0;
            widget = gtk_list_box_new();
            scrolledWindow = std::make_shared<ScrolledWindow>();
            scrolledWindow->Add(widget);          
        }

        ListItem<T>* AddItem(const std::string& text = "ListItem", int position = -1)
        {
            auto item = std::make_shared<T>();
            Widget* itemWidget = dynamic_cast<Widget*>(item.get());

            if(itemWidget != nullptr)
            {
                ListItem<T> listItem(item, text);
                items.push_back(listItem);
                GtkWidget* child = itemWidget->widget;
                gtk_list_box_insert(GTK_LIST_BOX(widget), child, position);
                gtk_widget_show_all(child);
                this->numberOfItems++;
                int index = items.size() - 1;
                return &items[index];
            }
            
            return nullptr;
        }

        void RemoveItem(int index)
        {
            GList* childrenList = gtk_container_get_children(GTK_CONTAINER(widget));
            GList* iter;
            
            int currentIndex = 0;

            for(iter = childrenList; iter != NULL; iter = g_list_next(iter))
            {
                if(currentIndex == index)
                {
                    gtk_widget_destroy(GTK_WIDGET(iter->data));
                    items.erase(items.begin() + index);
                    this->numberOfItems--;
                    break;
                }
                currentIndex++;
            }
            
            g_list_free(childrenList);
        }

        void Clear()
        {
            GList* childrenList = gtk_container_get_children(GTK_CONTAINER(widget));
            GList* iter;    

            for(iter = childrenList; iter != NULL; iter = g_list_next(iter))
            {
                gtk_widget_destroy(GTK_WIDGET(iter->data));
            }
            
            g_list_free(childrenList);
            items.clear();
            this->numberOfItems = 0;
        }

        int GetSelectedIndex()
        {
            GtkListBoxRow* selectedItem = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
            
            int selectedIndex = -1;
            
            if(selectedItem != nullptr)
                selectedIndex = gtk_list_box_row_get_index(selectedItem);

            return selectedIndex;
        }

        int GetItemCount() const { return numberOfItems; };

        ListItem<T>* GetItemAtIndex(size_t index)
        {
            if(items.empty() || items >= items.size())
                return nullptr;

            return &items[index];
        }

        void SetItemAtIndex(const ListItem<T>& item, int index)
        {
            RemoveItem(index);
            AddItem(item, item.text, index);
        }

    private:
        int numberOfItems;
        std::vector<ListItem<T>> items;
    };
}
#endif