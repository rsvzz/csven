#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include "create_verb_win.h"
#include <glib-2.0/glib-object.h>

/// @brief Crear ventana Verbs
/// @param  GtkWindow* window pared
/// @param  char* title
/// @param  int 1 true 0 false
void create_verb_window(GtkWindow*, const char*, int, DialogWin*, ItemVerbs*);

#define PAGE_VERB_TYPE page_verb_get_type()

G_DECLARE_FINAL_TYPE(PageVerb, page_verb, PAGE, VERB, GObject);

PageVerb *page_verb_new(void);
/// @brief load widget first
/// @param self 
void page_verb_load_widget(PageVerb * self);
GtkWidget *page_verb_get_box(PageVerb* self);
/// @brief items verb for add header needed
/// @param selft 
/// @return 
ItemVerbs* page_verb_get_items_verb(PageVerb *self);

/// @brief create box verb for show page
void create_page_verb();
/// @brief get box
/// @return Box verb
GtkWidget* get_box_verb();
/// @brief add btn header
void load_btn_add_header();
/// @brief item verbs
/// @return ItemVerbs obj
ItemVerbs *get_item_verb();