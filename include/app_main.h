#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>
#include "create_verb_win.h"

#define APP_MAIN_TYPE app_main_get_type()

G_DECLARE_FINAL_TYPE(AppMain, app_main, APP, MAIN, GObject);

AppMain *app_main_new(void);

/// @brief option windown
/// @param self 
void app_main_set_opt_window(AppMain *self);
void app_main_set_header_bar(AppMain *self, GtkHeaderBar* header);

GtkWidget* app_main_get_option_header_add(AppMain *self);
GtkWidget* app_main_get_header_bar(AppMain *self);
/// @brief dialog window show
/// @param self 
/// @param stack 
/// @param window 
/// @param items 
void app_main_load_btn_add_header(AppMain *self, GtkWidget *stack, GtkWidget * window, ItemVerbs* items);

/// @brief add box to window for main
/// @param self window
/// @param child box content
void app_main_add_widget_box_child(AppMain *self, GtkWidget* child);

/// @brief box content all widget in this class
/// @param self 
/// @return 
GtkWidget *app_main_get_box_child(AppMain *self);
/*
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
*/