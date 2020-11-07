#ifndef TABLE_HPP
#define TABLE_HPP

#include "Widget.h"
#include <vector>
#include <memory>

namespace LinuxForms
{
    template<typename T>
    class Table : public Widget
    {
    public:
        Table(const GtkOrientation& orientation = GtkOrientation::GTK_ORIENTATION_VERTICAL, int spacing = 0)
        {
            widget = gtk_box_new(orientation, spacing);
        }
        
        T* Add()
        {
            auto item = std::make_shared<T>();
            Widget* itemWidget = dynamic_cast<Widget*>(item.get());

            if(itemWidget == nullptr)
                return nullptr;

            gtk_box_pack_start(GTK_BOX(widget), itemWidget->widget, false, false, 0);
            
            items.push_back(item);
            size_t last = items.size() - 1;
            return items[last].get();
        }

        bool Add(const std::shared_ptr<T>& item)
        {
            Widget* itemWidget = dynamic_cast<Widget*>(item.get());

            if(itemWidget == nullptr)
                return false;

            gtk_box_pack_start(GTK_BOX(widget), itemWidget->widget, false, false, 0);
            
            items.push_back(item);

            return true;
        }
    private:
        std::vector<std::shared_ptr<T>> items;
    };
}
#endif