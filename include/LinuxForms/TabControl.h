#ifndef TABCONTROL_HPP
#define TABCONTROL_HPP

#include "Widget.h"
#include <vector>
#include "Utility/Console.h"

namespace LinuxForms
{   
    class TabButton
    {
    public:
        GtkWidget* image;
        std::shared_ptr<Button> closeButton;        
        std::shared_ptr<Box> box;
        std::shared_ptr<Label> label;
        EventHandler<TabButtonClickedEvent> onButtonCloseClicked;
        int index;
        bool preventClosing;
        
        TabButton(int index, bool preventClosing)
        {
            this->index = index;
            this->preventClosing = preventClosing;
            image = gtk_image_new_from_icon_name("gtk-close", GtkIconSize::GTK_ICON_SIZE_MENU);            
            closeButton = std::make_shared<Button>();
            closeButton->onClicked += [this] (gpointer data) { this->OnButtonClicked(nullptr); };
            gtk_button_set_image(GTK_BUTTON(closeButton->widget), image);
            box = std::make_shared<Box>(GtkOrientation::GTK_ORIENTATION_HORIZONTAL, 5);
            label = std::make_shared<Label>("Text");
            box->Add(label->widget, false, false, 0);
            box->Add(closeButton->widget, false, false, 0);
        }
        
        void Show()
        {
            gtk_widget_show(closeButton->widget);            
            gtk_widget_show(box->widget);
            gtk_widget_show(label->widget);
            gtk_widget_show(image);
        }
        
        void SetText(const std::string& text)
        {
            label->SetText(text);
        }
        
        void OnButtonClicked(gpointer data)
        {
            if(preventClosing)
                return;

            if(onButtonCloseClicked != nullptr)
                onButtonCloseClicked(index);
        }
    };    
    
    template<typename T>
    class TabControlItem
    {
    public:
        std::shared_ptr<T> item;
        std::shared_ptr<TabButton> button;
        std::shared_ptr<Box> box;
        std::shared_ptr<ScrolledWindow> scrolledWindow;
    };

    template<typename T>
    class TabControl : public Widget
    {
    public:
        EventHandler<SelectedTabChangedEvent> onSelectedIndexChanged;
    
        TabControl()
        {                
            widget = gtk_notebook_new();
            g_signal_connect_after(widget, "switch-page", G_CALLBACK(OnSelectedIndexChanged), this);
        }
        
        TabControlItem<T>* AddItem(bool addScrollView = true, bool preventClosing = false)
        {
            auto item = std::make_shared<T>();
            Widget* itemWidget = dynamic_cast<Widget*>(item.get());

            if(itemWidget != nullptr)
            {                
                std::string labelText = "Page " + std::to_string(items.size() + 1);

                TabControlItem<T> tabItem;
                tabItem.item = item;
                tabItem.button = std::make_shared<TabButton>(items.size(), preventClosing);
                tabItem.button->SetText(labelText);                
                
                items.push_back(tabItem);                
                
                tabItem.button->onButtonCloseClicked += [this] (int index) { this->OnTabClose(index); };

                if(addScrollView)
                {
                    tabItem.scrolledWindow = Widget::Create<ScrolledWindow>();
                    tabItem.scrolledWindow->Add(item->widget);
                    gtk_notebook_append_page(GTK_NOTEBOOK(widget), tabItem.scrolledWindow->widget, tabItem.button->box->widget);
                    tabItem.item->Show();                
                    tabItem.button->Show();
                    tabItem.scrolledWindow->Show();                    
                }
                else
                {
                    tabItem.box = Widget::Create<Box>();
                    tabItem.box->Add(item->widget, true, true, 0);
                    gtk_notebook_append_page(GTK_NOTEBOOK(widget), tabItem.box->widget, tabItem.button->box->widget);
                    tabItem.item->Show();                
                    tabItem.box->Show();
                    tabItem.button->Show();
                }

                int currentPage = items.size() - 1;
                SetSelectedIndex(currentPage);

                return &items[currentPage];
            }

            return nullptr;          
        }

        void RemoveItem(size_t index)
        {
            if(index >= items.size())
                return;

            gtk_notebook_remove_page(GTK_NOTEBOOK(widget), index);
            items.erase(items.begin() + index);
            
            for(size_t i = 0; i < items.size(); i++)
                items[i].button->index = i;
        }

        void SetTitle(size_t index, const std::string& title)
        {
            if(index >= items.size())
                return;
            
            items[index].button->SetText(title);
        }

        int GetSelectedIndex() const
        {
            if(items.size() == 0)
                return -1;
            
            int index = gtk_notebook_get_current_page(GTK_NOTEBOOK(widget));
            return index;
        }

        void SetSelectedIndex(size_t index)
        {
            if(items.size() == 0)
                return;

            if(index <= 0 || index >= items.size())
                return;

            gtk_notebook_set_current_page(GTK_NOTEBOOK(widget), index);
        }

        TabControlItem<T>* GetItemAtIndex(size_t index)
        {
            if(items.size() == 0)
                return nullptr;

            if(index < 0 || index >= items.size())
                return nullptr;

            return &items[index];
        }
        
        T* GetSelectedItem()
        {
            int selected = GetSelectedIndex();
                    
            if(selected >= 0)
            {
                auto tabItem = GetItemAtIndex(selected);
                return tabItem->item.get();            
            }
            
            return nullptr;
        }
        
        void OnTabClose(int index)
        {
            RemoveItem(index);
        }
        
        static void OnSelectedIndexChanged(GtkNotebook* notebook, GtkWidget* page, guint page_num, gpointer data)
        {
            TabControl<T>* tabControl = reinterpret_cast<TabControl<T>*>(data);
 
            if(tabControl->onSelectedIndexChanged != nullptr)
                tabControl->onSelectedIndexChanged(notebook, page, page_num, data);
        }
        
    private:
        std::vector<TabControlItem<T>> items;
    };
}

#endif
