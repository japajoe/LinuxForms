#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <gtk/gtk.h>
#include <string>
#include <map>
#include <memory>
#include "Size.h"
#include "Rectangle.h"
#include "Events.h"
#include "EventHandler.h"
#include "Color.h"

namespace LinuxForms
{
    class Widget
    {
    public:
        GtkWidget* widget;
        std::string name;
        Size size;
        Rectangle rectangle;
        std::map<std::string,glong> signalID;
        Widget();
        Widget& operator = (const Widget& other) = delete;
        virtual void Show();
        int GetId() const;
        void SetId(int id);
        void SetSize(const Size& size);
        void SetAlignmentHorizontal(GtkAlign alignment);
        void SetAlignmentVertical(GtkAlign alignment);
        void SetMargins(double top, double left, double bottom, double right);
        void CalculatePreferredSize();
        void SetFocus();
        void Destroy();

        template <typename T>
        static std::shared_ptr<T> Create()
        {
            auto ptr = std::make_shared<T>();
            Widget* widget = dynamic_cast<Widget*>(ptr.get());

            if(widget != nullptr)
                return ptr;
            return nullptr;
        }
    private:
        int id;
    };
}

#endif
