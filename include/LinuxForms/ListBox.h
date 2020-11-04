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
        ListBox()
        {
            this->numberOfItems = 0;
            widget = gtk_list_box_new();

            buttonToTop = std::make_shared<Button>("↟", 20, 20);
            buttonUp = std::make_shared<Button>("↑", 20, 20);
            buttonDown = std::make_shared<Button>("↓", 20, 20);
            buttonToBottom = std::make_shared<Button>("↡", 20, 20);

            buttonToTop->onClicked += [this]() { this->OnButtonToTopClicked(); };
            buttonUp->onClicked += [this]() { this->OnButtonUpClicked(); };
            buttonDown->onClicked += [this]() { this->OnButtonDownClicked(); };
            buttonToBottom->onClicked += [this]() { this->OnButtonToBottomClicked(); };

            scrolledWindow = std::make_shared<ScrolledWindow>();
            box = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_HORIZONTAL, 0);
            box2 = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
            
            box->Add(scrolledWindow.get(), true, true, 0);
            box->Add(box2.get(), false, true, 5);

            scrolledWindow->Add(widget);

            box2->Add(buttonToTop.get(), false, false, 0);
            box2->Add(buttonUp.get(), false, false, 5);
            box2->Add(buttonDown.get(), false, false, 0);
            box2->Add(buttonToBottom.get(), false, false, 5);            
        }

        ListBox& operator = (const ListBox& other) = delete;        
        
        void AddItem(std::shared_ptr<T> item, const std::string& text, int index = -1)
        {
            Widget* itemWidget = dynamic_cast<Widget*>(item.get());

            if(itemWidget != nullptr)
            {
                ListItem<T> listItem(item, text);
                items.push_back(listItem);
                GtkWidget* child = itemWidget->widget;
                gtk_list_box_insert(GTK_LIST_BOX(widget), child, index);
                gtk_widget_show_all(child);
                this->numberOfItems++;
            }
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
        
        void OnButtonToTopClicked()
        {
            if(GetItemCount() > 1)
            {
                int selectedIndex = GetSelectedIndex();

                if(selectedIndex > 0)
                {

                }
            }
        }

        void OnButtonUpClicked()
        {
            if(GetItemCount() > 1)
            {
                int selectedIndex = GetSelectedIndex();

                if(selectedIndex > 0)
                {

                }
            }            
        }
        void OnButtonDownClicked()
        {
            if(GetItemCount() > 1)
            {
                int selectedIndex = GetSelectedIndex();

                if(selectedIndex > 0)
                {

                }
            }
        }

        void OnButtonToBottomClicked()
        {
            if(GetItemCount() > 1)
            {
                int selectedIndex = GetSelectedIndex();

                if(selectedIndex > 0)
                {

                }
            }           
        }
        
        std::shared_ptr<Button> buttonToTop;        
        std::shared_ptr<Button> buttonUp;
        std::shared_ptr<Button> buttonDown;
        std::shared_ptr<Button> buttonToBottom;
        std::shared_ptr<Box> box;
        std::shared_ptr<Box> box2;
        std::shared_ptr<ScrolledWindow> scrolledWindow;

    private:
        int numberOfItems;
        std::vector<ListItem<T>> items;
    };
}
#endif