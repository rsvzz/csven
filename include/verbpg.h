#pragma once
#include "createtoverb.h"
#include <gtk-4.0/gtk/gtk.h>
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