#include "../../include/create_verb_win.h"
#include <stdlib.h>

struct _WinVerb
{
   /* data */
   GObject parent_instance;
   GtkWidget *win, *head, *btn_cancel, *btn_save, *txt_base, *txt_v2, *txt_v3, *txt_ing, *txt_is_regular, *grid;
};

G_DEFINE_TYPE (WinVerb, win_verb, G_TYPE_OBJECT);

void on_close_win_verb_clicked(GtkWidget *button, gpointer data);
void on_save_win_verb_clicked(GtkWidget *button, gpointer data);

static void win_verb_dispose(GObject *object)
{
  WinVerb *self = WIN_VERB(object);
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

  G_OBJECT_CLASS(win_verb_parent_class)->dispose(object);
}

static void win_verb_finalize(GObject *object)
{
  G_OBJECT_CLASS(win_verb_parent_class)->finalize(object);
}

static void win_verb_class_init(WinVerbClass *Klass)
{
  // add signal and property
  GObjectClass *object_class = G_OBJECT_CLASS(Klass);

  // Asignar la función de destrucción
  object_class->dispose = win_verb_dispose;

  // Asignar la función de finalización
  object_class->finalize = win_verb_finalize;
};

/// @brief init all data.
/// @param self
static void win_verb_init(WinVerb *self)
{

};

WinVerb* win_verb_new(void){
   return g_object_new(WIN_VERB_TYPE, NULL);
}

void win_verb_load_widget(WinVerb *self, GtkWindow *paren, const char* title, int is_modal, DialogWin *dialog, ItemVerbs* items){
   self->win = gtk_window_new(); 
   self->head = gtk_header_bar_new();
   self->btn_cancel = gtk_button_new_with_label("Cancel");
   self->btn_save = gtk_button_new_with_label("Save");

   self->txt_base = gtk_entry_new();
   self->txt_v2 = gtk_entry_new();
   self->txt_v3 = gtk_entry_new();
   self->txt_ing = gtk_entry_new();
   self->txt_is_regular = gtk_check_button_new_with_label("Is Regular :");

   gtk_entry_set_placeholder_text(GTK_ENTRY(self->txt_base), "Present :");
   gtk_entry_set_placeholder_text(GTK_ENTRY(self->txt_v2), "Past :");
   gtk_entry_set_placeholder_text(GTK_ENTRY(self->txt_v3), "Participle :");
   gtk_entry_set_placeholder_text(GTK_ENTRY(self->txt_ing), "Verb ING :");

   g_signal_connect(self->btn_cancel, "clicked", G_CALLBACK(dialog->on_close), (gpointer)self->win);

   ItemVerbWidget *item = malloc(sizeof(ItemVerbWidget));
   item->base = GTK_ENTRY(self->txt_base);
   item->v2 = GTK_ENTRY(self->txt_v2);
   item->v3 = GTK_ENTRY(self->txt_v3);
   item->ing = GTK_ENTRY(self->txt_ing);
   item->isRegular = GTK_CHECK_BUTTON(self->txt_is_regular);
   item->win = GTK_WINDOW(self->win);
   item->data = items;
   g_signal_connect(self->btn_save, "clicked", G_CALLBACK(dialog->on_save), (gpointer)item);

   gtk_button_set_icon_name(GTK_BUTTON(self->btn_cancel), "edit-clear-symbolic");
   gtk_button_set_icon_name(GTK_BUTTON(self->btn_save), "bookmark-new-symbolic");
   gtk_window_set_titlebar(GTK_WINDOW(self->win), self->head);
   gtk_header_bar_set_title_widget(GTK_HEADER_BAR(self->head), gtk_label_new(title));

   gtk_header_bar_pack_end(GTK_HEADER_BAR(self->head), self->btn_save);
   gtk_header_bar_pack_start(GTK_HEADER_BAR(self->head), self->btn_cancel);
   gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(self->head), FALSE);

   gtk_window_set_title(GTK_WINDOW(self->win), title); 
   gtk_window_set_default_size(GTK_WINDOW(self->win), 400, 300); 
   gtk_window_set_modal(GTK_WINDOW(self->win), is_modal);
   gtk_window_set_resizable(GTK_WINDOW(self->win), FALSE);
   //gtk_window_unminimize(GTK_WINDOW(new_window));
   gtk_window_set_transient_for(GTK_WINDOW(self->win),  GTK_WINDOW(paren)); 
   //GtkWidget *box =  gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
   //gtk_widget_set_size_request(box, 400, 400);
   self->grid = gtk_grid_new();
   gtk_widget_set_margin_start(self->grid, 5);
   gtk_widget_set_margin_end(self->grid, 5);
   gtk_widget_set_margin_top(self->grid, 5);
   gtk_widget_set_halign(self->grid, GTK_ALIGN_CENTER);
   gtk_grid_set_row_spacing(GTK_GRID(self->grid), 5);

   gtk_widget_set_size_request(self->txt_base, 400, 40);
   gtk_widget_set_size_request(self->txt_v2, 400, 40);
   gtk_widget_set_size_request(self->txt_v3, 400, 40);
   gtk_widget_set_size_request(self->txt_ing, 400, 40);
   
   
   gtk_grid_attach(GTK_GRID(self->grid), self->txt_base, 0, 0, 1, 1);
   gtk_grid_attach(GTK_GRID(self->grid), self->txt_v2, 0, 1, 1, 1);
   gtk_grid_attach(GTK_GRID(self->grid), self->txt_v3, 0, 2, 1, 1);
   gtk_grid_attach(GTK_GRID(self->grid), self->txt_ing, 0, 3, 1, 1);
   gtk_grid_attach(GTK_GRID(self->grid), self->txt_is_regular, 0, 4, 1, 1);

   gtk_window_set_child(GTK_WINDOW(self->win), self->grid);
   gtk_window_present(GTK_WINDOW(self->win));
}


void on_close_win_verb_clicked(GtkWidget *button, gpointer data){
   gtk_window_close(GTK_WINDOW(data));
}

void on_save_win_verb_clicked(GtkWidget *button, gpointer data){
   ItemVerbWidget *item = (ItemVerbWidget*)data;
   GtkEntryBuffer *bfbase = gtk_entry_get_buffer(item->base);
   //g_print("%s \n", gtk_entry_buffer_get_text(bfbase));
   gtk_window_close(item->win);
}
