#pragma once
#include <gtk-4.0/gtk/gtk.h>
/// @brief Create siderbar
/// @param  GtkWidget button add
void create_nav(GtkWidget*);
/// @brief event page change
/// @param  
/// @param  
/// @param  
void on_stack_page_changed(GObject*, GParamSpec*, gpointer);
/// @brief box page main
/// @return box main
GtkWidget* get_box_page();
/// @brief add paga stack
/// @param  GtkWidget add
/// @param  name page
/// @param  title page show
/// @return GtkStackPage
GtkStackPage* add_page_set_stack(GtkWidget*, const char*, const char*);
/// @brief Stack pages
/// @return Stack pages for siderbar
GtkWidget* get_nav_stack_pages();
