#include "Label.h"

LinuxForms::Label::Label()
{
	widget = gtk_label_new("Label");
}

LinuxForms::Label::Label(const std::string& text)
{
	widget = gtk_label_new(text.c_str());
}

void LinuxForms::Label::SetText(const std::string& text)
{
	gtk_label_set_text(GTK_LABEL(widget), text.c_str());
}