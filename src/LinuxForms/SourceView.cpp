#include "SourceView.h"
#include <gtksourceview/completion-providers/words/gtksourcecompletionwords.h>

LinuxForms::SourceView::SourceView(void)
{
	GtkSourceLanguageManager * lm = gtk_source_language_manager_get_default();
	std::string languageString = GetLanguageString(SourceLanguage::CPP);
	GtkSourceLanguage *srcLanguage = gtk_source_language_manager_get_language(lm, languageString.c_str());
	sourcebuffer = gtk_source_buffer_new_with_language(srcLanguage);
	widget = gtk_source_view_new_with_buffer(sourcebuffer);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(widget), 4);

	GtkSourceCompletion *completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(widget));
	GtkSourceCompletionWords *word_provider = gtk_source_completion_words_new (NULL, NULL);
	gtk_source_completion_words_register(word_provider, GTK_TEXT_BUFFER(sourcebuffer));
	gtk_source_completion_add_provider(completion, GTK_SOURCE_COMPLETION_PROVIDER(word_provider), NULL);

	g_signal_connect(sourcebuffer, "changed", G_CALLBACK(TextChanged), this);

	ToggleLineNumbers(true);
}

LinuxForms::SourceView::SourceView(const SourceLanguage& language)
{
	GtkSourceLanguageManager * lm = gtk_source_language_manager_get_default();
	std::string languageString = GetLanguageString(language);
	GtkSourceLanguage *srcLanguage = gtk_source_language_manager_get_language(lm, languageString.c_str());
	sourcebuffer = gtk_source_buffer_new_with_language(srcLanguage);
	widget = gtk_source_view_new_with_buffer(sourcebuffer);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(widget), 4);

	GtkSourceCompletion *completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(widget));
	GtkSourceCompletionWords *word_provider = gtk_source_completion_words_new (NULL, NULL);
	gtk_source_completion_words_register(word_provider, GTK_TEXT_BUFFER(sourcebuffer));
	gtk_source_completion_add_provider(completion, GTK_SOURCE_COMPLETION_PROVIDER(word_provider), NULL);

	g_signal_connect(sourcebuffer, "changed", G_CALLBACK(TextChanged), this);

	ToggleLineNumbers(true);
}

void LinuxForms::SourceView::SetText(const std::string& text)
{
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(sourcebuffer), text.c_str(), -1);
}

std::string LinuxForms::SourceView::GetText()
{
	GtkTextIter start, end;

	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(sourcebuffer), &start, &end);
	char *text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(sourcebuffer), &start, &end, true);
	std::string str(text);
	g_free(text);
	return str;
}

void LinuxForms::SourceView::Clear()
{
	std::string text = "";
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(sourcebuffer), text.c_str(), -1);
}

void LinuxForms::SourceView::ToggleLineNumbers(bool enabled)
{
	gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(widget), enabled);
}

std::string LinuxForms::SourceView::GetLanguageString(const SourceLanguage& sourceLanguage)
{
	switch(sourceLanguage)
	{
		case SourceLanguage::C:
			return std::string("c");
		case SourceLanguage::CPP:
			return std::string("cpp");
		case SourceLanguage::CSHARP:
			return std::string("c-sharp");
		case SourceLanguage::GLSL:
			return std::string("glsl");
		case SourceLanguage::LUA:
			return std::string("lua");
		default:
			return std::string("c");
	}
}


void LinuxForms::SourceView::TextChanged(GtkSourceBuffer *textbuffer, gpointer data)
{
    SourceView* sourceview = reinterpret_cast<SourceView*>(data);
    if(sourceview->onTextChanged != nullptr)
        sourceview->onTextChanged();
}