#include "TextEntry.h"

LinuxForms::TextEntry::TextEntry()
{
    widget = gtk_entry_new();
    textbuffer = gtk_entry_get_buffer(GTK_ENTRY(widget));
    g_signal_connect(widget, "activate", G_CALLBACK(Submit), this);	
    g_signal_connect(textbuffer, "changed", G_CALLBACK(TextChanged), this);    
}

LinuxForms::TextEntry::TextEntry(const std::string& text)
{
    widget = gtk_entry_new();
    textbuffer = gtk_entry_get_buffer(GTK_ENTRY(widget));	
    SetText(text);
    g_signal_connect(widget, "activate", G_CALLBACK(Submit), this);
    g_signal_connect(textbuffer, "changed", G_CALLBACK(TextChanged), this);
}

void LinuxForms::TextEntry::SetText(const std::string& text)
{
    buffer = text;    
    gtk_entry_buffer_set_text(GTK_ENTRY_BUFFER(textbuffer), text.c_str(), -1);
}

void LinuxForms::TextEntry::AppendText(const std::string& text)
{
    buffer += text;
    gtk_entry_buffer_set_text(GTK_ENTRY_BUFFER(textbuffer), buffer.c_str(), -1);
}

std::string LinuxForms::TextEntry::GetText()
{   
    const char *text = gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(textbuffer));
    std::string str(text);    
    return str;
}

void LinuxForms::TextEntry::Clear()
{
    buffer = "";
    SetText(buffer);
}

void LinuxForms::TextEntry::SetReadOnly(bool readOnly)
{
    gtk_editable_set_editable(GTK_EDITABLE(widget), !readOnly);
}

void LinuxForms::TextEntry::Submit(GtkWidget* widget, gpointer data)
{
    TextEntry* entry = reinterpret_cast<TextEntry*>(data);
    entry->onSubmit();
}

void LinuxForms::TextEntry::TextChanged(GtkEntryBuffer *textbuffer, gpointer data)
{
    TextEntry* textEntry = reinterpret_cast<TextEntry*>(data);
    if(textEntry->onTextChanged != nullptr)
        textEntry->onTextChanged();
}