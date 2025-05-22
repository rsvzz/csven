#pragma once
#include <gtk-4.0/gtk/gtk.h>
void create_page_word();
/// @brief Add b
void load_box_content();

void on_button_restare(GtkWidget *, gpointer);
void on_entry_active(GtkEntry *, gpointer);
gpointer restore_game(gpointer gdata);
gpointer create_to_name_in_grid(gpointer gdata);
/// @brief Box content page word
/// @return GtkWidget box
GtkWidget* get_box_word();
void load_game_for_grid();