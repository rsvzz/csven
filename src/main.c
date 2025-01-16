#include <gtk-4.0/gtk/gtk.h>
#include "../include/ctobutton.h"
#include "../include/ctogrid.h"
#include "../include/stack.h"
#include <gtk-4.0/gdk/gdk.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  GtkEntry *txt_name;
  GtkBox *box_content;
  GtkButton *btn_restore;
  GtkGrid *grid;
  char *name;
  /// @brief Lista de char de la frace
  Queue **qlist;
  /// @brief lista de char queue para los paremetros de funciones
  Queue *list;
} DataGame;

void clear_grid(GtkGrid*);

void clear_grid(GtkGrid* grid){

    for (int i = 0; i < 5; i++)
    {
    
      for (int j = 0; j < 5; j++)
        {
            gtk_grid_remove_column(grid, j);
        }
      gtk_grid_remove_row(grid, i);
     
    }
  
}
void on_button_restare(GtkWidget *btn, gpointer user_data)
{
  DataGame *info = (DataGame *)user_data;
  Stack *map_btn = NULL;
  GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(info->box_content));
  while (child != NULL)
  {
    /* code */
    GtkWidget *aux = gtk_widget_get_next_sibling(child);
    ;
    gtk_widget_unparent(child);
    child = aux;
  }
  info->list = NULL; //figar nuevo;
  create_button_size_char(info->name, info->box_content, info->qlist);

  clear_grid(info->grid);
  
  map_grid_create_game(info->name, info->grid, map_btn, info->list, info->btn_restore);
  gtk_widget_remove_css_class(btn, "button_complete");
  gtk_widget_add_css_class(btn, "button");
}
void on_button_start(GtkWidget *btn, gpointer user_data)
{
  DataGame *info = (DataGame *)user_data;
  clear_grid(info->grid);
}

void on_entry_active(GtkEntry *entry, gpointer user_data){
    //g_print("Llega active entry");
     
     DataGame *info = (DataGame *)user_data;
     /**/
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(info->txt_name);
  const char *name = gtk_entry_buffer_get_text(buffer);
  char* str = (char*)malloc(strlen(name) + 1); 
  //info->name = NULL;
  strcpy(str, name);
  info->name = str;
  gtk_widget_remove_css_class(GTK_WIDGET(info->btn_restore), "button_complete");
  gtk_widget_add_css_class(GTK_WIDGET(info->btn_restore), "button");
  //g_print("Asig: %s \n", info->name);
  if (strlen(name) > 0)
  {
    // g_print("%s \n",name);
    gtk_widget_add_css_class(GTK_WIDGET(info->btn_restore), "button");
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(info->box_content));
    Stack *map_btn = NULL;
    
    if (child == NULL)
    {
      

      create_button_size_char(name, info->box_content, info->qlist);
      // funcion crear botones
      clear_grid(info->grid);
      map_grid_create_game(name, info->grid, map_btn, info->list, info->btn_restore);
      gtk_entry_buffer_set_text(buffer, "", 0);
      gtk_entry_set_buffer(info->txt_name, buffer);
      gtk_widget_set_sensitive(GTK_WIDGET(info->btn_restore), true);
    }
    else
    {

      while (child != NULL)
      {
        /* code */
        GtkWidget *aux = gtk_widget_get_next_sibling(child);
        gtk_widget_unparent(child);
        child = aux;
      }
      
      //liberando lista en memoria
      while (info->list != NULL)
      {
        queue_remove(&info->list);
      }
      
      create_button_size_char(name, info->box_content, info->qlist);
      // funcion crear botones
      clear_grid(info->grid);
      map_grid_create_game(name, info->grid, map_btn, info->list, info->btn_restore);
      gtk_widget_set_sensitive(GTK_WIDGET(info->btn_restore), true);
      gtk_entry_buffer_set_text(buffer, "", 0);
      gtk_entry_set_buffer(info->txt_name, buffer);
    }
  }
    
}

void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *boxContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *txt_name = gtk_entry_new();
  //GtkWidget *btnStart = gtk_button_new_with_label("Start");
  GtkWidget *btn_restare = gtk_button_new_with_label("Restore");
  gtk_widget_set_sensitive(btn_restare, FALSE);
  GtkWidget *boxV = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *grid = gtk_grid_new();
  /*
    add style css application
  */
  GtkCssProvider *css_provider = gtk_css_provider_new();
    //gtk_css_provider_load_from_path(css_provider, "/usr/share/appgame/style/style.css"); //deb
    gtk_css_provider_load_from_path(css_provider, "style/style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), 
                                                GTK_STYLE_PROVIDER(css_provider),
                                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_widget_add_css_class(btn_restare, "button");
  gtk_widget_add_css_class(txt_name, "txtEntry");
  DataGame *dgame = malloc(sizeof(DataGame));
  dgame->box_content = GTK_BOX(box);
  dgame->btn_restore = GTK_BUTTON(btn_restare);
  //dgame->btn_start = GTK_BUTTON(btnStart);
  dgame->txt_name = GTK_ENTRY(txt_name);
  dgame->grid = GTK_GRID(grid);
  dgame->list = NULL;
  dgame->qlist = &dgame->list;
  //g_signal_connect(btnStart, "clicked", G_CALLBACK(on_button_start), (gpointer)dgame);
  g_signal_connect(btn_restare, "clicked", G_CALLBACK(on_button_restare), (gpointer)dgame);
  g_signal_connect(txt_name, "activate", G_CALLBACK(on_entry_active), (gpointer)dgame);
  gtk_box_append(GTK_BOX(boxContent), txt_name);
  //gtk_box_append(GTK_BOX(boxContent), btnStart);
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
