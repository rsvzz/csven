#include <gtk-4.0/gtk/gtk.h>
#include <gtk-4.0/gdk/gdk.h>
#include <libadwaita-1/adwaita.h>
#include <stdlib.h>
#include "../include/app_main.h"
#include "../include/mapcss.h"
#include "../include/nav.h"
#include "../include/wordpg.h"
#include "../include/verbpg.h"
#include "../include/dragpg.h"

#include "../include/nav_main.h"

static GtkWidget *window = NULL;

// Función callback que se ejecuta al cerrar la ventana
static gboolean on_window_close_request(GtkWindow *window, gpointer user_data)
{
  // g_print("🧹 Cerrando ventana...\n");

  gtk_widget_unparent((GtkWidget *)user_data);

  // Aquí puedes liberar recursos o cancelar el cierre si lo deseas
  // return TRUE para evitar que se cierre
  // return FALSE para permitir el cierre
  return FALSE;
}

void activate(GtkApplication *app, gpointer user_data)
{
  if (window != NULL)
  {
    gtk_window_present(GTK_WINDOW(window));
    return;
  }
  window = adw_application_window_new(app);
  gtk_window_set_default_size(GTK_WINDOW(window), 740, 740);
  NavMain *n_main = nav_main_new(window);
  nav_main_load_content(n_main);
  adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), nav_main_get_box_main(n_main));
  load_path_css();
  
  PageWord *p_word = page_word_new();
  page_word_load_widget(p_word);
  page_word_load_create_grid_for_game(p_word);
  nav_main_add_stack_page(n_main, page_word_get_box_content(p_word), "word", "Word", "input-dialpad-symbolic");

  PageDrag *p_drag = page_drag_new();
  page_drag_set_head(p_drag);
  nav_main_add_stack_page(n_main, page_drag_get_content(p_drag), "drag", "Game", "list-drag-handle-symbolic");

  PageVerb *p_verb = page_verb_new();
  page_verb_load_widget(p_verb);
  nav_main_add_stack_page(n_main, page_verb_get_box(p_verb), "verb", "Verb", "input-keyboard-symbolic");
  sv_header_set_option_menu(SV_HEADER(n_main), page_verb_get_items_verb(p_verb));

  g_signal_connect(window, "close-request", G_CALLBACK(on_window_close_request), nav_main_get_popover(n_main));
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
  AdwApplication *app;
  int status;
  app = adw_application_new("io.github.rsvzz.csven", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}