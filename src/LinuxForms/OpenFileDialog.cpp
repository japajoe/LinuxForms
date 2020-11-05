#include "OpenFileDialog.h"
#include "Form.h"

LinuxForms::OpenFileDialog::OpenFileDialog()
{
    this->parentWindow = nullptr;
}

LinuxForms::OpenFileDialog::OpenFileDialog(Form* window)
{
    this->parentWindow = window->widget;
}

LinuxForms::DialogResult LinuxForms::OpenFileDialog::ShowDialog(Form* window)
{
    if(parentWindow == nullptr)
        parentWindow = window->widget;
        
	GtkWidget *dialog;
    GtkFileChooser* chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
    LinuxForms::DialogResult result;    

	dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(parentWindow), action, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER (dialog);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
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

	gtk_widget_destroy (dialog);
    return result;  
}