#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>

#define PAGE_WORD_TYPE page_word_get_type()

G_DECLARE_FINAL_TYPE(PageWord, page_word, PAGE, WORD, GObject);

PageWord *page_word_new(void);
/// @brief Get box content for info the game
/// @param self 
/// @return GtkWidget box
GtkWidget * page_word_get_box_content(PageWord *self);

/// @brief load gtk control
/// @param self 
void page_word_load_widget(PageWord *self);
/// @brief load game for grid
/// @param self 
void page_word_load_create_grid_for_game(PageWord *self);


/*
void create_page_word();
/// @brief Add b
void load_box_content();
/// @brief Box content page word
/// @return GtkWidget box
GtkWidget* get_box_word();
void load_game_for_grid();
*/