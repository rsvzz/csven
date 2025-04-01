#include "../../include/create_verb_win.h"
#include <stdlib.h>


void on_close_win_verb_clicked(GtkWidget *button, gpointer data){
   gtk_window_close(GTK_WINDOW(data));
}

void on_save_win_verb_clicked(GtkWidget *button, gpointer data){
   ItemVerbWidget *item = (ItemVerbWidget*)data;
   GtkEntryBuffer *bfbase = gtk_entry_get_buffer(item->base);
   g_print("%s \n", gtk_entry_buffer_get_text(bfbase));
   gtk_window_close(item->win);
}

void create_verb_window(GtkWindow *paren, const char* title, int is_modal, DialogWin *dialog, ItemVerbs* items){
   GtkWidget *new_window = gtk_window_new(); 
   GtkWidget *head = gtk_header_bar_new();
   GtkWidget *btn_cancel = gtk_button_new_with_label("Cancel");
   GtkWidget *btn_save = gtk_button_new_with_label("Save");

   GtkWidget *txt_base = gtk_entry_new();
   GtkWidget *txt_v2 = gtk_entry_new();
   GtkWidget *txt_v3 = gtk_entry_new();
   GtkWidget *txt_ing = gtk_entry_new();
   GtkWidget *txt_is_regular = gtk_check_button_new_with_label("Is Regular :");

   gtk_entry_set_placeholder_text(GTK_ENTRY(txt_base), "Present :");
   gtk_entry_set_placeholder_text(GTK_ENTRY(txt_v2), "Past :");
   gtk_entry_set_placeholder_text(GTK_ENTRY(txt_v3), "Participle :");
   gtk_entry_set_placeholder_text(GTK_ENTRY(txt_ing), "Verb ING :");

   g_signal_connect(btn_cancel, "clicked", G_CALLBACK(dialog->on_close), (gpointer)new_window);

   ItemVerbWidget *item = malloc(sizeof(ItemVerbWidget));
   item->base = GTK_ENTRY(txt_base);
   item->v2 = GTK_ENTRY(txt_v2);
   item->v3 = GTK_ENTRY(txt_v3);
   item->ing = GTK_ENTRY(txt_ing);
   item->isRegular = GTK_CHECK_BUTTON(txt_is_regular);
   item->win = GTK_WINDOW(new_window);
   item->data = items;
   g_signal_connect(btn_save, "clicked", G_CALLBACK(dialog->on_save), (gpointer)item);

   gtk_button_set_icon_name(GTK_BUTTON(btn_cancel), "edit-delete-symbolic");
   gtk_button_set_icon_name(GTK_BUTTON(btn_save), "document-save-symbolic");
   gtk_window_set_titlebar(GTK_WINDOW(new_window), head);
   gtk_header_bar_set_title_widget(GTK_HEADER_BAR(head), gtk_label_new(title));

   gtk_header_bar_pack_end(GTK_HEADER_BAR(head), btn_save);
   gtk_header_bar_pack_start(GTK_HEADER_BAR(head), btn_cancel);
   gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(head), FALSE);

   gtk_window_set_title(GTK_WINDOW(new_window), title); 
   gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 300); 
   gtk_window_set_modal(GTK_WINDOW(new_window), is_modal);
   gtk_window_set_resizable(GTK_WINDOW(new_window), FALSE);
   //gtk_window_unminimize(GTK_WINDOW(new_window));
   gtk_window_set_transient_for(GTK_WINDOW(new_window),  GTK_WINDOW(paren)); 
   //GtkWidget *box =  gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
   //gtk_widget_set_size_request(box, 400, 400);
   GtkWidget *grid = gtk_grid_new();
   gtk_widget_set_margin_start(grid, 5);
   gtk_widget_set_margin_end(grid, 5);
   gtk_widget_set_margin_top(grid, 5);
   gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
   gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
   //gtk_box_append(GTK_BOX(box), grid);
  
  

   gtk_widget_set_size_request(txt_base, 400, 40);
   gtk_widget_set_size_request(txt_v2, 400, 40);
   gtk_widget_set_size_request(txt_v3, 400, 40);
   gtk_widget_set_size_request(txt_ing, 400, 40);
   
   
   gtk_grid_attach(GTK_GRID(grid), txt_base, 0, 0, 1, 1);
   gtk_grid_attach(GTK_GRID(grid), txt_v2, 0, 1, 1, 1);
   gtk_grid_attach(GTK_GRID(grid), txt_v3, 0, 2, 1, 1);
   gtk_grid_attach(GTK_GRID(grid), txt_ing, 0, 3, 1, 1);
   gtk_grid_attach(GTK_GRID(grid), txt_is_regular, 0, 4, 1, 1);

   gtk_window_set_child(GTK_WINDOW(new_window), grid);
   gtk_window_present(GTK_WINDOW(new_window));
}