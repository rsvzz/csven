#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include "create_verb_win.h"
/// @brief create inteface main
/// @param  
/// @param  
void create_app_window(GtkWidget*, GtkApplication*);
/// @brief Content box
/// @param  GtkWidget add box
void add_app_content(GtkWidget*);
/// @brief header_bar
/// @return GtkWidget adw_header_bar
GtkWidget* get_app_header_bar();
/// @brief btn_add
/// @return GtkWidget GtkButton
GtkWidget* get_app_btn_add();
/// @brief Agrega btn add to header_bar
/// @param items ItemVerb obj
/// @param stack Stack
/// @param window GtkWindow
void load_btn_add_header(ItemVerbs* items, GtkWidget* stack, GtkWidget* window);
