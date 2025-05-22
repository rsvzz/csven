#include <gtk-4.0/gtk/gtk.h>
#include <gtk-4.0/gdk/gdk.h>
#include <questk/stack.h>
#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <string.h>
#include "../include/app.h"
#include "../include/mapcss.h"
#include "../include/nav.h"
#include "../include/wordpg.h"
#include "../include/verbpg.h"

static GtkWidget *window = NULL;
void activate(GtkApplication *app, gpointer user_data)
{
  if (window != NULL)
  {
    gtk_window_present(GTK_WINDOW(window));
    return;
  }
  window = gtk_application_window_new(app);
  //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  create_app_window(window, app);
  load_path_css();
  create_nav(get_app_btn_add());
  create_page_word();
  load_game_for_grid();
  add_page_set_stack(get_box_word(), "word", "Word");
  create_page_verb();
  load_btn_add_header(get_item_verb(), get_nav_stack_pages(), window);
  add_page_set_stack(get_box_verb(), "verb", "Verb");
  add_app_content(get_box_page());
}

int main(int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new("io.github.rsvzz.csven", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}