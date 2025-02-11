#include <gtk-4.0/gtk/gtk.h>
#include <gtk-4.0/gdk/gdk.h>
#include "../include/ctobutton.h"
#include "../include/ctogrid.h"
#include "../include/createtobtnforgrid.h"
#include "../include/create_verb_win.h"
#include <questk/stack.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
/// @brief dont use
/// @param
void clear_grid(GtkGrid *);
gpointer restore_game(gpointer gdata);
gpointer create_to_name_in_grid(gpointer gdata);

void clear_grid(GtkGrid *grid)
{

  for (int i = 0; i < 5; i++)
  {

    for (int j = 0; j < 5; j++)
    {
      gtk_grid_remove_column(grid, j);
    }
    gtk_grid_remove_row(grid, i);
  }
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
  gtk_widget_set_sensitive(GTK_WIDGET(info->btn_restore), false);
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

static void on_menu_item_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
  // const gchar *action_name = g_action_get_name(G_ACTION(action));
  create_verb_window(GTK_WINDOW(user_data), "Create Verbs to List", FALSE);
}
static GtkWidget *window = NULL;
void activate(GtkApplication *app, gpointer user_data)
{
  //verificacion de ventana main para que solo una vez este abierta
  if (window != NULL) {
    gtk_window_present(GTK_WINDOW(window));
    return;
  }

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
  GtkWidget *header = gtk_header_bar_new();
  gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), gtk_label_new("Aprender Ingles gtk/c"));

  // GtkWidget *mnu = gtk_popover_new();
  GtkWidget *btnMenu = gtk_menu_button_new();
  gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(btnMenu), "open-menu-symbolic");

  GMenu *menu = g_menu_new();
  g_menu_append(menu, "Dev Verb", "app.new");
  GSimpleAction *option1_action = g_simple_action_new("new", NULL);
  g_signal_connect(option1_action, "activate", G_CALLBACK(on_menu_item_activated), (gpointer)window);
  g_action_map_add_action(G_ACTION_MAP(g_application_get_default()), G_ACTION(option1_action));
  GMenuModel *menu_model = G_MENU_MODEL(menu);
  GtkWidget *popover_menu = gtk_popover_menu_new_from_model(menu_model);
  gtk_menu_button_set_popover(GTK_MENU_BUTTON(btnMenu), popover_menu);
  // g_signal_connect_swapped(btnMenu, "clicked", G_CALLBACK(on_clicked_menu), (gpointer)popover);

  //gtk_header_bar_pack_end(GTK_HEADER_BAR(header), btnMenu); //comentar para flatpak stable
  gtk_window_set_titlebar(GTK_WINDOW(window), header);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *boxContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *txt_name = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(txt_name), 30);
  // GtkWidget *btnStart = gtk_button_new_with_label("Start");
  GtkWidget *btn_restare = gtk_button_new_with_label("Restore");
  gtk_button_set_icon_name(GTK_BUTTON(btn_restare), "view-refresh-symbolic");
  gtk_widget_set_sensitive(btn_restare, FALSE);
  GtkWidget *boxV = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *grid = gtk_grid_new();
  /*
    add style css application
  */
  GtkCssProvider *css_provider = gtk_css_provider_new();
  char *exe_path = g_file_read_link("/proc/self/exe", NULL); // Linux
  if (!exe_path) {
      g_printerr("No se pudo obtener la ruta del ejecutable.\n");
      return;
  }
  char *css_path;

  css_path = g_build_path(G_DIR_SEPARATOR_S, g_path_get_dirname(exe_path), "../share/csven/style/org.flathud.csven.css", NULL);
  g_free(exe_path);

  //gtk_css_provider_load_from_path(css_provider, "/usr/share/csven/style/style.css"); // uso final de compilacion he instalacion
  gtk_css_provider_load_from_path(css_provider, css_path); // para entorno flatpak
  //gtk_css_provider_load_from_path(css_provider, "style/style.css"); // descomentar para compilar local
  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(css_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_widget_add_css_class(btn_restare, "button");
  gtk_widget_add_css_class(txt_name, "txtEntry");

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

  // creando los bottones en el gridor default
  GThread *th_game = g_thread_new("th_game", createtobutonforgrid, (gpointer)glist);
  g_thread_join(th_game);
  // clear GThread
  g_thread_unref(th_game);
  // createtobutonforgrid(glist);
  //  crear nuevo struct que manipule los parametros del clicked
  //   g_signal_connect(btnStart, "clicked", G_CALLBACK(on_button_start), (gpointer)dgame);
  g_signal_connect(btn_restare, "clicked", G_CALLBACK(on_button_restare), (gpointer)glist);
  g_signal_connect(txt_name, "activate", G_CALLBACK(on_entry_active), (gpointer)glist);
  gtk_box_append(GTK_BOX(boxContent), txt_name);
  // gtk_box_append(GTK_BOX(boxContent), btnStart);
  gtk_box_append(GTK_BOX(boxContent), btn_restare);

  gtk_box_append(GTK_BOX(boxV), boxContent);
  gtk_box_append(GTK_BOX(boxV), box);
  gtk_box_append(GTK_BOX(boxV), grid);

  // center
  gtk_widget_set_halign(boxContent, GTK_ALIGN_CENTER);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);

  // gtk_box_set_homogeneous(GTK_BOX(box), true);
  gtk_widget_set_margin_top(boxContent, 10);
  gtk_widget_set_margin_top(box, 40);
  gtk_widget_set_margin_top(grid, 50);
  // asignando boxV el grid

  gtk_window_set_child(GTK_WINDOW(window), boxV);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("local.gtk.c_sven", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
