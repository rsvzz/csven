#include "../../include/createtobtnforgrid.h"
#include "../../include/maptogridforname.h"
#include "../../include/comparetoindex.h"
#include <gtk-4.0/gtk/gtk.h>
#include <stdlib.h>

void on_click_button_restore(GtkButton *, gpointer);

gpointer createtobutonforgrid(gpointer gdata)
{
    ItemListRestore *data = (ItemListRestore*)gdata;
    int n = 0;

    for (size_t i = 0; i < data->y; i++)
    {

        for (size_t j = 0; j < data->x; j++)
        {
            GtkWidget *btn = gtk_button_new();
            gtk_widget_add_css_class(btn, "game_btn");

            g_signal_connect(GTK_BUTTON(btn), "clicked", G_CALLBACK(on_click_button_restore), (gpointer)data);
            ItemGame *item = malloc(sizeof(ItemGame));
            item->btn = GTK_BUTTON(btn);
            item->index = n;
            item->status = 0;
            n++;
            queue_append(data->list, item);

            gtk_widget_set_size_request(btn, 60, 60);
            gtk_grid_attach(data->grid, btn, i, j, 1, 1);
        }
    }
    return NULL;
}

void set_grid_for_name_game(ItemListRestore *data)
{
    /*
    Queue* aux = *data->tlist;

    while (aux != NULL)
    {
        g_print("str : %c \n", ((ItemBtnGame*)aux->item)->ctr);
        aux = aux->next;
    }
    */

    set_generic_char_to_button_game(data);
}

void on_click_button_restore(GtkButton *btn, gpointer data)
{
    const char *name = gtk_button_get_label(btn);
    if (name != NULL)
    {
        ItemListRestore *saux = (ItemListRestore *)data;
        Queue *aux = *saux->tlist;

        ItemBtnGame *item = get_index_title_button_char(aux, btn);
        if (item != NULL)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(btn), false);
            gtk_widget_add_css_class(GTK_WIDGET(btn), "game_btn_complete");
            gtk_widget_add_css_class(GTK_WIDGET(item->btn), "game_btn_complete");
            // gtk_widget_set_size_request(GTK_WIDGET(item->btn), 55, 55);
            item->status = 1;

            if (item->isEnd == 1)
            {
                gtk_widget_set_sensitive(GTK_WIDGET(saux->btn_restore), true);
                gtk_widget_add_css_class(GTK_WIDGET(saux->btn_restore), "button_complete");
            }
        }
    }
}
