#ifndef TEXTENTRY_HPP
#define TEXTENTRY_HPP

#include "Widget.h"

namespace LinuxForms
{
    class TextEntry : public Widget
    {
    public:
        TextEntry();
        TextEntry(const std::string& text);
        void SetText(const std::string& text);
        void SetPlaceholderText(const std::string& text);
        void AppendText(const std::string& text);
        std::string GetText();
        void Clear();
        void SetReadOnly(bool readOnly);
        void SetVisibility(bool visible);
        EventHandler<SubmitEvent> onSubmit;
        EventHandler<TextChangedEvent> onTextChanged;
    private:
        GtkEntryBuffer* textbuffer;
        std::string buffer;
        static void Submit(GtkWidget* widget, gpointer data);
        static void TextDeleted(GtkEntryBuffer* textbuffer, guint position, guint n_chars, gpointer data);
        static void TextInserted(GtkEntryBuffer* textbuffer, guint position, char* chars, guint n_chars, gpointer data);
        static void TextChanged(GtkEntryBuffer* textbuffer, gpointer data);
    };
}
#endif
