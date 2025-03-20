#pragma once
#include <questk/queue.h>
#include <gtk-4.0/gtk/gtk.h>
#include "str_data.h"

/// @brief Comparar index de los caractares de la palabra
/// @param  Queue* list palabra
/// @param  GtkButton button event
/// @return Item index null empty
ItemBtnGame* get_index_title_button_char(Queue*, GtkButton*);