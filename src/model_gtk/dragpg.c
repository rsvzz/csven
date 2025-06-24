#include "../../include/dragpg.h"

struct _PageDrag
{
  /* data */
  GObject parent_instance;
  GtkWidget *bx_page, *bx_head, *bx_content, *txt_name, *btn_restore;
  DragGame *game;
};

G_DEFINE_TYPE(PageDrag, page_drag, G_TYPE_OBJECT);

/// @brief Event restare button
/// @param
/// @param
void on_button_drag_restare(GtkWidget *, gpointer);
/// @brief event entry
/// @param
/// @param
void on_entry_drag_active(GtkEntry *, gpointer);

static void page_drag_class_init(PageDragClass *Klass) {
};

static void page_drag_init(PageDrag *self)
{
  self->bx_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  self->bx_head = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  self->bx_content = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  self->txt_name = gtk_entry_new();
  self->btn_restore = gtk_button_new();
  self->game = drag_game_new();
  gtk_box_append(GTK_BOX(self->bx_page), self->bx_head);
  gtk_box_append(GTK_BOX(self->bx_page), self->bx_content);
  // send btn_restare drag_game
  drag_game_set_button_restare(self->game, self->btn_restore);
  gtk_widget_add_css_class(self->btn_restore, "button");
  gtk_widget_add_css_class(self->txt_name, "txtEntry");

  gtk_widget_set_margin_top(self->bx_head, 20);
  gtk_widget_set_margin_top(self->bx_content, 20);

  gtk_widget_set_margin_end(self->txt_name, 5);
  gtk_widget_set_halign(self->bx_head, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(self->bx_content, GTK_ALIGN_CENTER);
  gtk_widget_set_sensitive(self->btn_restore, FALSE);
  gtk_box_append(GTK_BOX(self->bx_head), self->txt_name);
  gtk_box_append(GTK_BOX(self->bx_head), self->btn_restore);
};

PageDrag *page_drag_new(void)
{
  return g_object_new(PAGE_DRAG_TYPE, NULL);
}

GtkWidget *page_drag_get_content(PageDrag *self)
{
  return self->bx_page;
}

void page_drag_set_head(PageDrag *self)
{
  gtk_entry_set_placeholder_text(GTK_ENTRY(self->txt_name), "type ..");
  gtk_button_set_icon_name(GTK_BUTTON(self->btn_restore), "view-refresh-symbolic");

  g_signal_connect(self->txt_name, "activate", G_CALLBACK(on_entry_drag_active), (gpointer)self);
  g_signal_connect(self->btn_restore, "clicked", G_CALLBACK(on_button_drag_restare), (gpointer)self);
}

void on_entry_drag_active(GtkEntry *entry, gpointer user_data)
{
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(entry);
  const char *name = gtk_entry_buffer_get_text(buffer);
  char *str = (char *)malloc(strlen(name) + 1);
  // info->name = NULL;
  strcpy(str, name);

  PageDrag *obj = (PageDrag *)user_data;
  gtk_widget_set_sensitive(obj->btn_restore, FALSE);

  drag_game_set_word_grid(obj->game, str);

  drag_game_set_data_button(obj->game);
  gtk_box_append(GTK_BOX(obj->bx_content), drag_game_get_content(obj->game));

  // clear entry
  gtk_entry_buffer_set_text(buffer, "", 0);
  gtk_entry_set_buffer(entry, buffer);
}

void on_button_drag_restare(GtkWidget *btn, gpointer user_data)
{
  gtk_widget_remove_css_class(btn, "button_complete");
  gtk_widget_add_css_class(btn, "button");
  gtk_widget_set_sensitive(btn, FALSE);

  PageDrag *obj = (PageDrag *)user_data;
  drag_game_set_data_button(obj->game);
}