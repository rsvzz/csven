#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>

typedef struct
{
    /* data */
    GtkButton *btn;
    int index;
    char ctr;
    /// @brief save check
    int status;
    int isEnd;
} ItemBtnGame;

#define WORD_GAME_TYPE word_game_get_type()

G_DECLARE_FINAL_TYPE(WordGame, word_game, WORD, GAME, GObject);

WordGame *word_game_new(void);

/// @brief generic button for game
/// @param self 
/// @param x int
/// @param y int
void word_game_load_button(WordGame* self, GtkGrid* grid, int x, int y);
/// @brief set name 
/// @param self 
/// @param name word
void word_game_set_name_word(WordGame *self, const char *name);
/// @brief set name to button
/// @param self GameWord *obj
void word_game_set_name_to_button(WordGame* self);
/// @brief set GtkButton restore
/// @param self 
/// @param btn GtkButton
void word_game_set_btn_restore(WordGame *self, GtkButton *btn);
/// @brief clear char to button of grid
/// @param self 
void word_game_clear_char_to_button_for_grid(WordGame* self);

/// @brief change char to button for game and status
/// @param self 
/// @param ch 
/// @param nrandom 
/// @return status change
int word_game_get_status_change_char_to_button(WordGame* self, const char *ch, int nrandom);

/// @brief Title button
/// @param self 
/// @param name word
void word_game_load_char_title_game(WordGame *self, const char *name);

/// @brief set box content title button game
/// @param self 
/// @param box 
void word_game_set_box_title(WordGame* self, GtkBox *box);

/// @brief Get ItemBtnGame of list
/// @param self 
/// @param btn GtkButton from GQueue
/// @return GtkButton
ItemBtnGame *word_game_get_index_title_button_char(WordGame *self, GtkButton *btn);

