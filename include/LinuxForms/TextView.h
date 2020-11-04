#ifndef TEXTVIEW_HPP
#define TEXTVIEW_HPP

#include "Widget.h"

namespace LinuxForms
{
    class TextView : public Widget
    {
    public:
        TextView();
        TextView(const std::string& text);
        void SetText(const std::string& text);
        void AppendText(const std::string& text);
        void WriteLine(const std::string& text);
        std::string GetText();
        void Clear();
        void SetReadOnly(bool readOnly);        
        EventHandler<TextChangedEvent> onTextChanged;
    private:    
        GtkTextBuffer* textbuffer;
        std::string buffer;
        static void TextChanged(GtkTextBuffer *textbuffer, gpointer data);
    };
}
#endif