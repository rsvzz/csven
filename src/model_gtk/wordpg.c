#include "../../include/wordpg.h"
#include "../../include/createtobtnforgrid.h"
#include "../../include/ctobutton.h"
GtkWidget *box, *boxContent, *boxV, *grid, *txt_name, *btn_restare;
void create_page_word()
{
  boxV = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // box main in page word
  gtk_widget_set_hexpand(boxV, TRUE);
  gtk_widget_set_halign(boxV, GTK_ALIGN_CENTER);
  //gtk_widget_set_valign(boxV, GTK_ALIGN_CENTER);
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Word load read
  gtk_widget_set_margin_top(box, 10);
  gtk_widget_set_margin_bottom(box, 10);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  boxContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // entry  word
  gtk_widget_set_margin_top(boxContent, 10);
  gtk_widget_set_margin_bottom(boxContent, 10);

  gtk_widget_set_halign(boxContent, GTK_ALIGN_CENTER);
  grid = gtk_grid_new();
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
  // load content boxV main
  gtk_box_append(GTK_BOX(boxV), boxContent);
  gtk_box_append(GTK_BOX(boxV), box);
  gtk_box_append(GTK_BOX(boxV), grid);

  load_box_content();
}

GtkWidget *get_box_word()
{
  return boxV;
}

void load_box_content()
{
  txt_name = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(txt_name), 30);

  btn_restare = gtk_button_new_with_label("Restore");
  gtk_button_set_icon_name(GTK_BUTTON(btn_restare), "view-refresh-symbolic");
  gtk_widget_set_sensitive(btn_restare, FALSE);
  // class css
  gtk_widget_add_css_class(btn_restare, "button");
  gtk_widget_add_css_class(txt_name, "txtEntry");

  gtk_box_append(GTK_BOX(boxContent), txt_name);
  gtk_box_append(GTK_BOX(boxContent), btn_restare);
}

void load_game_for_grid()
{
  ItemListRestore *glist = malloc(sizeof(ItemListRestore));
  glist->btn_restore = GTK_BUTTON(btn_restare);
  glist->grid = GTK_GRID(grid);
  glist->x = 7;
  glist->y = 7;
  glist->box_name = GTK_BOX(box);
  glist->txt_name = GTK_ENTRY(txt_name);
  // porque queue requiere al principio null en el puntero doble
  glist->auxList = NULL;
  glist->auxt = NULL;
  glist->list = &glist->auxList;
  glist->tlist = &glist->auxt;

  g_signal_connect(btn_restare, "clicked", G_CALLBACK(on_button_restare), (gpointer)glist);
  g_signal_connect(txt_name, "activate", G_CALLBACK(on_entry_active), (gpointer)glist);

  // creando los bottones en el gridor default
  GThread *th_game = g_thread_new("th_game", createtobutonforgrid, (gpointer)glist);
  g_thread_join(th_game);
  // clear GThread
  g_thread_unref(th_game);
}

void on_button_restare(GtkWidget *btn, gpointer user_data)
{
  GThread *r_game = g_thread_new("create_game", restore_game, user_data);
  g_thread_join(r_game);
  g_thread_unref(r_game);
}

void on_entry_active(GtkEntry *entry, gpointer user_data)
{
  GThread *create_game = g_thread_new("create_game", create_to_name_in_grid, user_data);
  g_thread_join(create_game);
  g_thread_unref(create_game);
}

gpointer restore_game(gpointer gdata)
{
  ItemListRestore *info = (ItemListRestore *)gdata;
  GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(info->box_name));
  while (child != NULL)
  {
    /* code */
    GtkWidget *aux = gtk_widget_get_next_sibling(child);
    gtk_widget_unparent(child);
    child = aux;
  }

  create_button_size_char(info->name, info->box_name, info->tlist);
  set_grid_for_name_game(info);
  gtk_widget_remove_css_class(GTK_WIDGET(info->btn_restore), "button_complete");
  gtk_widget_add_css_class(GTK_WIDGET(info->btn_restore), "button");
  gtk_widget_set_sensitive(GTK_WIDGET(info->btn_restore), FALSE);

  return NULL;
}

gpointer create_to_name_in_grid(gpointer gdata)
{
  ItemListRestore *info = (ItemListRestore *)gdata;
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(info->txt_name);
  const char *name = gtk_entry_buffer_get_text(buffer);
  char *str = (char *)malloc(strlen(name) + 1);
  // info->name = NULL;
  strcpy(str, name);
  info->name = str;
  gtk_widget_remove_css_class(GTK_WIDGET(info->btn_restore), "button_complete");
  gtk_widget_add_css_class(GTK_WIDGET(info->btn_restore), "button");
  gtk_widget_set_sensitive(GTK_WIDGET(info->btn_restore), FALSE);
  // g_print("Asig: %s \n", info->name);
  if (strlen(name) > 0)
  {
    // g_print("%s \n",name);

    gtk_widget_add_css_class(GTK_WIDGET(info->btn_restore), "button");

    // set_grid_for_name_game(info->list, info->name, (info->x * info->y));

    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(info->box_name));

    while (child != NULL)
    {
      GtkWidget *aux = gtk_widget_get_next_sibling(child);
      gtk_widget_unparent(child);
      child = aux;
    }
    // limpiando palabra titulo del juego
    if (info->auxt != NULL)
    {
      Queue *aux = info->auxt;
      while (aux != NULL)
      {
        queue_remove(&aux);
      }
      info->auxt = NULL;
    }

    create_button_size_char(name, info->box_name, info->tlist);
    set_grid_for_name_game(info);
    gtk_entry_buffer_set_text(buffer, "", 0);
    gtk_entry_set_buffer(info->txt_name, buffer);
  }

  return NULL;
}