#include "ColorPickerDialog.h"
#include "Console.h"

LinuxForms::ColorPickerDialog::ColorPickerDialog(Form* form)
{
    this->parentWindow = form->widget;
}

LinuxForms::DialogResult LinuxForms::ColorPickerDialog::ShowDialog(Form* window)
{
    if(parentWindow == nullptr)
        parentWindow = window->widget;

    gint res;
    LinuxForms::DialogResult result;    	

    widget = gtk_color_chooser_dialog_new("Choose Color", GTK_WINDOW(parentWindow));

	res = gtk_dialog_run(GTK_DIALOG(widget));

    switch(res)
    {
        case GTK_RESPONSE_OK:
            gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), &selectedColor);
            color.r = selectedColor.red;
            color.g = selectedColor.green;
            color.b = selectedColor.blue;
            color.a = selectedColor.alpha;
            result = LinuxForms::DialogResult::OK;
            break;

        case GTK_RESPONSE_CANCEL:
            result = LinuxForms::DialogResult::Cancel;
            break;
        case GTK_RESPONSE_YES:
            result = LinuxForms::DialogResult::Yes;
            break;
        case GTK_RESPONSE_NO:
            result = LinuxForms::DialogResult::No;
            break;
        default:
            result = LinuxForms::DialogResult::None;
            break;
    }

    gtk_widget_destroy(widget);
    return result;
}

