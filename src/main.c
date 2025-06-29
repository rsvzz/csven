#include <gtk-4.0/gtk/gtk.h>
#include <gtk-4.0/gdk/gdk.h>
#include <stdlib.h>
#include "../include/app_main.h"
#include "../include/mapcss.h"
#include "../include/nav.h"
#include "../include/wordpg.h"
#include "../include/verbpg.h"
#include "../include/dragpg.h"

static GtkWidget *window = NULL;
void activate(GtkApplication *app, gpointer user_data)
{
  if (window != NULL)
  {
    gtk_window_present(GTK_WINDOW(window));
    return;
  }
  window = gtk_application_window_new(app);
  AppMain *w_app = app_main_new();
  app_main_set_opt_window(w_app);
  GtkWidget *header = app_main_get_header_bar(w_app);

  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("To Learn English"));
  gtk_window_set_default_size(GTK_WINDOW(window), 740, 740);
  /*
  GtkWidget *btn_word = gtk_toggle_button_new_with_label("Word");
  GtkWidget *btn_verd = gtk_toggle_button_new_with_label("Verb");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btn_word), TRUE);

  GtkWidget *box_page = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_append(GTK_BOX(box_page), btn_word);
  gtk_box_append(GTK_BOX(box_page), btn_verd);
  gtk_toggle_button_set_group(GTK_TOGGLE_BUTTON(btn_word), GTK_TOGGLE_BUTTON(btn_verd));
  gtk_header_bar_pack_start(GTK_HEADER_BAR(header), box_page);
  */
  load_path_css();

  StackOption *stack_opt = stack_option_new();
  stack_option_load_all(stack_opt);
  stack_option_set_button_option_add(stack_opt, app_main_get_option_header_add(w_app));

  PageWord *p_word = page_word_new();
  page_word_load_widget(p_word);
  page_word_load_create_grid_for_game(p_word);

  stack_option_add_stack_child(stack_opt, page_word_get_box_content(p_word), "word", "Word", "input-dialpad-symbolic");

  PageDrag *p_drag = page_drag_new();
  page_drag_set_head(p_drag);
  stack_option_add_stack_child(stack_opt, page_drag_get_content(p_drag), "drag", "Game", "list-drag-handle-symbolic");

  PageVerb *p_verb = page_verb_new();
  page_verb_load_widget(p_verb);
  app_main_load_btn_add_header(w_app, stack_option_get_stack(stack_opt), window, page_verb_get_items_verb(p_verb));

  stack_option_add_stack_child(stack_opt, page_verb_get_box(p_verb), "verb", "Verb", "input-keyboard-symbolic");

  app_main_add_widget_box_child(w_app, stack_option_get_box_page(stack_opt));

  gtk_window_set_child(GTK_WINDOW(window), app_main_get_box_child(w_app));
  gtk_window_present(GTK_WINDOW(window));
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