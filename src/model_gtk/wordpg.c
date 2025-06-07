#include "../../include/wordpg.h"
#include "../../include/word_game.h"
struct _PageWord
{
  GObject parent_instance;
  WordGame *game;
  GtkWidget *box, *boxContent, *boxV, *grid, *txt_name, *btn_restare;
};

G_DEFINE_TYPE(PageWord, page_word, G_TYPE_OBJECT);

/// @brief load entry button restare
/// @param
void load_box_content_for_edit(PageWord *);

/// @brief create game for grid
/// @param
void load_create_grid_for_game(PageWord *);
/// @brief Event restare button
/// @param
/// @param
void on_button_restare(GtkWidget *, gpointer);
/// @brief event entry
/// @param
/// @param
void on_entry_active(GtkEntry *, gpointer);
/// @brief event click button restore
/// @param gdata
/// @return
gpointer restore_game(gpointer gdata);
/// @brief create char in button for grid
/// @param gdata
/// @return
gpointer create_to_name_in_grid(gpointer gdata);

/// @brief to create grid for game
/// @param gdata WordGame
/// @return
gpointer thread_create_grid_for_game(gpointer gdata);

static void page_word_dispose(GObject *object)
{
  PageWord *self = PAGE_WORD(object);
  /*
  if (self->btn_restare != NULL)
  {
    g_object_unref(self->btn_restare);
    self->btn_restare = NULL;
  }

  if (self->txt_name != NULL)
  {
    g_object_unref(self->txt_name);
    self->txt_name = NULL;
  }

  if (self->grid != NULL)
  {
    g_object_unref(self->grid);
    self->grid = NULL;
  }
    */

  G_OBJECT_CLASS(page_word_parent_class)->dispose(object);
}

static void page_word_finalize(GObject *object)
{
  G_OBJECT_CLASS(page_word_parent_class)->finalize(object);
}

static void page_word_class_init(PageWordClass *Klass)
{
  // add signal and property
  GObjectClass *object_class = G_OBJECT_CLASS(Klass);

  // Asignar la función de destrucción
  object_class->dispose = page_word_dispose;

  // Asignar la función de finalización
  object_class->finalize = page_word_finalize;
};

/// @brief init all data.
/// @param self
static void page_word_init(PageWord *self) {

};

void page_word_load_widget(PageWord *self)
{
  self->boxV = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);         // box main in page word
  self->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);        // Word load read
  self->boxContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // entry  word
  self->grid = gtk_grid_new();
  self->game = word_game_new();

  // title button add box content
  word_game_set_box_title(self->game, GTK_BOX(self->box));

  gtk_widget_set_hexpand(self->boxV, TRUE);
  gtk_widget_set_halign(self->boxV, GTK_ALIGN_CENTER);
  // gtk_widget_set_valign(self->boxV, GTK_ALIGN_CENTER);

  gtk_widget_set_margin_top(self->box, 10);
  gtk_widget_set_margin_bottom(self->box, 10);
  gtk_widget_set_halign(self->box, GTK_ALIGN_CENTER);

  gtk_widget_set_margin_top(self->boxContent, 10);
  gtk_widget_set_margin_bottom(self->boxContent, 10);

  gtk_widget_set_halign(self->boxContent, GTK_ALIGN_CENTER);

  gtk_widget_set_halign(self->grid, GTK_ALIGN_CENTER);
  // load content boxV main

  gtk_box_append(GTK_BOX(self->boxV), self->boxContent);
  gtk_box_append(GTK_BOX(self->boxV), self->box);
  gtk_box_append(GTK_BOX(self->boxV), self->grid);

  load_box_content_for_edit(self);
}

PageWord *page_word_new(void)
{
  return g_object_new(PAGE_WORD_TYPE, NULL);
}

void load_box_content_for_edit(PageWord *self)
{
  self->txt_name = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(self->txt_name), "type ..");
  self->btn_restare = gtk_button_new_with_label("Restore");

  // add button WordGame
  word_game_set_btn_restore(self->game, GTK_BUTTON(self->btn_restare));

  gtk_entry_set_max_length(GTK_ENTRY(self->txt_name), 30);

  gtk_button_set_icon_name(GTK_BUTTON(self->btn_restare), "view-refresh-symbolic");
  gtk_widget_set_sensitive(self->btn_restare, FALSE);
  // class css
  gtk_widget_add_css_class(self->btn_restare, "button");
  gtk_widget_add_css_class(self->txt_name, "txtEntry");

  gtk_box_append(GTK_BOX(self->boxContent), self->txt_name);
  gtk_box_append(GTK_BOX(self->boxContent), self->btn_restare);

  g_signal_connect(self->txt_name, "activate", G_CALLBACK(on_entry_active), (gpointer)self->game);
  g_signal_connect(self->btn_restare, "clicked", G_CALLBACK(on_button_restare), (gpointer)self->game);
}

void page_word_load_create_grid_for_game(PageWord *self)
{
  word_game_load_button(self->game, GTK_GRID(self->grid), 7, 7);
}

GtkWidget *page_word_get_box_content(PageWord *self)
{
  return self->boxV;
}

void on_button_restare(GtkWidget *btn, gpointer user_data)
{
  gtk_widget_remove_css_class(btn, "button_complete");
  gtk_widget_add_css_class(btn, "button");
  gtk_widget_set_sensitive(btn, FALSE);

  WordGame *game = (WordGame *)user_data;
  GThread *r_game = g_thread_new("create_game", thread_create_grid_for_game, game);
  g_thread_join(r_game);
  g_thread_unref(r_game);
}

void on_entry_active(GtkEntry *entry, gpointer user_data)
{
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  const char *name = gtk_entry_buffer_get_text(buffer);
  char *str = (char *)malloc(strlen(name) + 1);
  // info->name = NULL;
  strcpy(str, name);

  WordGame *game = (WordGame *)user_data;
  word_game_set_name_word(game, name);
  GThread *create_game = g_thread_new("create_game", thread_create_grid_for_game, user_data);
  g_thread_join(create_game);
  g_thread_unref(create_game);
  // clear entry
  gtk_entry_buffer_set_text(buffer, "", 0);
  gtk_entry_set_buffer(entry, buffer);
}

gpointer thread_create_grid_for_game(gpointer gdata)
{
  WordGame *game = (WordGame *)gdata;
  word_game_set_name_to_button(game);
  return NULL;
}