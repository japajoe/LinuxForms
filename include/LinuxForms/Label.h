#ifndef LABEL_HPP
#define LABEL_HPP

#include "Widget.h"

namespace LinuxForms
{
    class Label : public Widget
    {
    public:
        Label();
        Label(const std::string& text);
        void SetText(const std::string& text);
    };
}
#endif