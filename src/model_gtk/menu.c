#include "../../include/menu.h"
#include <gtk-4.0/gtk/gtk.h>
void load_menu()
{
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
}

void on_menu_item_activated(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
  // const gchar *action_name = g_action_get_name(G_ACTION(action));
  // create_verb_window(GTK_WINDOW(user_data), "Create Verbs to List", FALSE);
}