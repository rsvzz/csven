#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <questk/queue.h>
#include "str_data.h"
/// @brief Generar btn para el grid
/// @param ItemListRestore GtkButton restore list queue
/// @param  x eje --- ---
/// @param  y eje |
gpointer createtobutonforgrid(gpointer);
/// @brief Agrega la palabra al juego en el grid
/// @param  ItemListRestore list
void set_grid_for_name_game(ItemListRestore*);