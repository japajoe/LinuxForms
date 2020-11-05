#include "TextView.h"

LinuxForms::TextView::TextView()
{
    widget = gtk_text_view_new();
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
    g_signal_connect(textbuffer, "changed", G_CALLBACK(TextChanged), this);
}

LinuxForms::TextView::TextView(const std::string& text)
{
    widget = gtk_text_view_new();
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
    SetText(text);
    g_signal_connect(textbuffer, "changed", G_CALLBACK(TextChanged), this);
}

void LinuxForms::TextView::SetText(const std::string& text)
{
    buffer = text;
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textbuffer), buffer.c_str(), -1);
}

void LinuxForms::TextView::AppendText(const std::string& text)
{
    buffer += text;
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textbuffer), buffer.c_str(), -1);
}

void LinuxForms::TextView::WriteLine(const std::string& text)
{
    buffer += text + "\n";
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(textbuffer), buffer.c_str(), -1);
}

std::string LinuxForms::TextView::GetText()
{
    GtkTextIter start, end;
    
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(textbuffer), &start, &end);
    char *text = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(textbuffer), &start, &end, true);
    std::string str(text);
    g_free(text);
    return str;
}

void LinuxForms::TextView::Clear()
{
    buffer = "";
    SetText(buffer);
}

void LinuxForms::TextView::SetReadOnly(bool readOnly)
{
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widget), !readOnly);
}

void LinuxForms::TextView::TextChanged(GtkTextBuffer *textbuffer, gpointer data)
{
    TextView* textView = reinterpret_cast<TextView*>(data);
    if(textView->onTextChanged != nullptr)
        textView->onTextChanged();
}