#ifndef SOURCEVIEW_HPP
#define SOURCEVIEW_HPP

#include "Widget.h"
#include <gtksourceview/gtksource.h>

namespace LinuxForms
{
    enum class SourceLanguage
    {
        C,
        CPP,
        CSHARP,
        GLSL,
        LUA
    };

    class SourceView : public Widget
    {
    public:
        SourceView(void);
        SourceView(const SourceLanguage& language);
        void SetText(const std::string& text);
        std::string GetText();
        void Clear();
        void ToggleLineNumbers(bool enabled);
        std::string GetLanguageString(const SourceLanguage& sourceLanguage);
        GtkSourceBuffer* GetBuffer() const;
        EventHandler<TextChangedEvent> onTextChanged;
    private:
        GtkSourceBuffer *sourcebuffer;
        static void TextChanged(GtkSourceBuffer *textbuffer, gpointer data);
    };
}
#endif