#include <gtk-4.0/gtk/gtk.h>
#include <questk/stack.h>
#include <questk/queue.h>

/// @brief Create button en grid para el game
/// @param  char* frase
/// @param  GtkGrid* grid a asignar button
/// @param  Stack* Lista que administrara el contenido de los button del juego
/// @param  Queue* list title frase
void map_grid_create_game(const char *, GtkGrid *, Stack *, Queue *, GtkButton *);