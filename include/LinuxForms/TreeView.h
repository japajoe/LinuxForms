#ifndef TREEVIEW_HPP
#define TREEVIEW_HPP

#include "Widget.h"
#include <vector>

namespace LinuxForms
{
    enum
    {
        COL_PATH = 0,
        NUM_COLS
    };

    class TreeViewItem
    {
    public:
        std::string title;
        std::vector<std::string> entries;

        TreeViewItem(const std::string title, const std::vector<std::string>& entries)
        {
            this->title = title;
            this->entries = entries;
        }
    };

    class TreeView : public Widget
    {
    public:
        TreeView()
        {
            widget = gtk_tree_view_new();
        }

        void Add(const std::string& title, const std::vector<std::string>& entries)
        {
            items.push_back(TreeViewItem(title, entries));
        }

        void CreateModel()
        {
            GtkTreeViewColumn* col;
            GtkCellRenderer* renderer;
            GtkTreeModel* model;

            col = gtk_tree_view_column_new();
            gtk_tree_view_column_set_title(col, "Browser");
            gtk_tree_view_append_column(GTK_TREE_VIEW(widget), col);
            renderer = gtk_cell_renderer_text_new();
            gtk_tree_view_column_pack_start(col, renderer, TRUE);
            gtk_tree_view_column_add_attribute(col, renderer, "text", COL_PATH);
            model = CreateModelFromItems();
            gtk_tree_view_set_model(GTK_TREE_VIEW(widget), model);
            g_object_unref(model); /* destroy model automatically with view */
            gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(widget)), GTK_SELECTION_SINGLE);    
        }

        GtkTreeModel* CreateModelFromItems()
        {
            GtkTreeStore* treestore;
	        GtkTreeIter toplevel, child;

	        treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);
	
	        //Find all folders in samples directory
	        for(int i = 0; i < items.size(); i++)
	        {			
                /* Append a top level row, and fill it with some data */
                gtk_tree_store_append(treestore, &toplevel, NULL);
                gtk_tree_store_set(treestore, &toplevel, COL_PATH, items[i].title.c_str(), -1);        

                for (size_t j = 0; j < items[i].entries.size(); j++)
                {
                    /* Append a child to the top level row, and fill in some data */
                    gtk_tree_store_append(treestore, &child, &toplevel);
                    gtk_tree_store_set(treestore, &child, COL_PATH, items[i].entries[j].c_str(), -1);        
                }	
	        }

	        return GTK_TREE_MODEL(treestore);
        }
    private:
        std::vector<TreeViewItem> items;
    };
}

#endif
