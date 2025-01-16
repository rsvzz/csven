#pragma once
#include "queue.h"
#include <gtk-4.0/gtk/gtk.h>
/// @brief Crea los button con letras
/// @param  char* Frase
/// @param  GtkBox* a pintar
/// @param Queue** list 
void create_button_size_char(const char*, GtkBox*, Queue**);