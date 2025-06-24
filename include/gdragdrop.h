#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>

#define DRAG_GAME_TYPE drag_game_get_type()

G_DECLARE_FINAL_TYPE(DragGame, drag_game, DRAG, GAME, GObject); 

DragGame *drag_game_new(void);
/// @brief grid generic for word
/// @param self DragGame
/// @param word char * word
void drag_game_set_word_grid(DragGame *self, const char *word);

/// @brief get GtkWidget
/// @param self 
/// @return 
GtkWidget *drag_game_get_content(DragGame *self);

/// @brief set button title game
/// @param self DragGame
void drag_game_set_data_button(DragGame * self);
const char* drag_game_get_name(DragGame *self);
/// @brief set button for restare game
/// @param self
/// @param button 
void drag_game_set_button_restare(DragGame *self, GtkWidget *button);