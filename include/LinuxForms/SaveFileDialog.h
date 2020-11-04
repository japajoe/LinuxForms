#ifndef SAVEFILEDIALOG_HPP
#define SAVEFILEDIALOG_HPP

#include "Widget.h"
#include "DialogResult.h"
#include <vector>

namespace LinuxForms
{
    class Form;

    class SaveFileDialog : public Widget
    {
    public:
        SaveFileDialog();
        SaveFileDialog(Form* window);
        DialogResult ShowDialog(Form* window = nullptr);
        std::string GetFileName() const { return filename; }
        std::vector<std::string> GetFileNames() const { return filenames; }
    private:
        GtkWidget* parentWindow;
        std::string filename;
        std::vector<std::string> filenames;
    };
}

#endif