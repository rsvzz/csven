#include <gtk-4.0/gtk/gtk.h>
void create_app_window(GtkWidget*, GtkApplication*);
/// @brief Content box adwaita
/// @param  GtkWidget add box
void add_app_content(GtkWidget*);
/// @brief header_bar
/// @return GtkWidget adw_header_bar
GtkWidget* get_app_header_bar();
/// @brief btn_add
/// @return GtkWidget GtkButton
GtkWidget* get_app_btn_add();
