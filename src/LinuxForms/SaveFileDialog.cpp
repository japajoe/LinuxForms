#include "SaveFileDialog.h"
#include "Form.h"

LinuxForms::SaveFileDialog::SaveFileDialog()
{
    this->parentWindow = nullptr;
}

LinuxForms::SaveFileDialog::SaveFileDialog(Form* window)
{
    this->parentWindow = window->widget;
}

LinuxForms::DialogResult LinuxForms::SaveFileDialog::ShowDialog(Form* window)
{
    if(parentWindow == nullptr)
        parentWindow = window->widget;     

	GtkFileChooser* chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;
    LinuxForms::DialogResult result;

	widget = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(parentWindow), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
	chooser = GTK_FILE_CHOOSER(widget);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

	res = gtk_dialog_run(GTK_DIALOG(widget));

	if (res == GTK_RESPONSE_ACCEPT)
	{
		char* file = gtk_file_chooser_get_filename (chooser);
        filename = std::string(file);        
		g_free(file);
        result = LinuxForms::DialogResult::OK;
	}
    else
    {
        switch(res)
        {
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
    }    

	gtk_widget_destroy(widget);
    return result;
}