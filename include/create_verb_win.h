#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include "str_data.h"
typedef struct {
    int id;
    const char* base;
    const char* v2;
    const char* v3;
    const char* ing;
    int isRegular;
} ItemVerb;

/// @brief Crear ventana Verbs
/// @param  GtkWindow* window pared
/// @param  char* title
/// @param  int 1 true 0 false
void create_verb_window(GtkWindow*, const char*, int, DialogWin*, ItemVerbs*);