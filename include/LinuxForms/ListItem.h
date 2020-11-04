#ifndef LISTITEM_HPP
#define LISTITEM_HPP

#include <memory>

template <typename T>
class ListItem
{
public:
    std::shared_ptr<T> item;
    std::string text;
    
    ListItem(const std::shared_ptr<T>& item, const std::string text)
    {
        this->item = item;
        this->text = text;
    }
};

#endif