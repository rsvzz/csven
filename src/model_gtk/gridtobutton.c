#include "../../include/ctogrid.h"
#include "../../include/comparetoindex.h"
#include <stdlib.h>
#include <time.h>
void on_button_clicked(GtkButton*, gpointer);
void generic_char_to_button(Stack*, const char *);
int set_button_char(Stack *, const char *, int);
typedef struct {
    GtkButton *btn_restore;
    Queue* list;
} ItemListRestore;
int set_button_char(Stack *list, const char *ch, int nrandom)
{
    Stack *aux = list;

    int status = 0;
    while (aux != NULL)
    {
        ItemGame *game = (ItemGame *)aux->item;
        // g_print("idex = %d \n", game->index);
        if (game->index == nrandom && game->status == 0)
        {
            gtk_button_set_label(game->btn, ch);
            game->status = 1;
            status = 1;
            aux = NULL;
        }
        else if (game->index == nrandom && game->status == 1)
        {
            status = 0;
            aux = NULL;
        }
        else
        {
            aux = aux->next;
        }
    }

    free(aux);
    return status;
}

void set_generic_char_to_button(Stack *list, const char *name)
{
    int sttus = 0;
    srand(time(NULL));
    for (int i = 0; name[i] != '\0'; i++)
    {
        char ch = name[i];
        char str[2];
        str[0] = ch;
        str[1] = '\0';

        while (sttus == 0)
        {

            int nrandom = rand() % 25;
            sttus = set_button_char(list, (const char *)str, nrandom);
        }
        sttus = 0;
    }
}

void on_button_clicked(GtkButton *btn, gpointer data)
{
    const char *name = gtk_button_get_label(btn);
    if (name != NULL)
    {
        ItemListRestore *saux =(ItemListRestore*)data;
        Queue* aux = saux->list;

        ItemBtnGame *item = get_index_title_button_char(aux, btn);
        if (item != NULL)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(btn), false);
            gtk_widget_add_css_class(GTK_WIDGET(btn), "game_btn_complete");
            gtk_widget_add_css_class(GTK_WIDGET(item->btn), "game_btn_complete");
            //gtk_widget_set_size_request(GTK_WIDGET(item->btn), 55, 55);
            item->status = 1;

            if(item->isEnd == 1)
                 gtk_widget_add_css_class(GTK_WIDGET(saux->btn_restore), "button_complete");
            
        }

    }
}
void map_grid_create_game(const char *name, GtkGrid *grid, Stack *list, Queue *list_t, GtkButton *btn)
{

    int x = 5, y = x, n = 0;
    gtk_grid_set_row_spacing(grid, 5);
    gtk_grid_set_column_spacing(grid, 5);

    ItemListRestore *data = malloc(sizeof(ItemListRestore));
    data->btn_restore = btn;
    data->list = list_t;

    for (size_t i = 0; i < y; i++)
    {

        for (size_t j = 0; j < x; j++)
        {
            GtkWidget *btn = gtk_button_new();
            gtk_widget_add_css_class(btn, "game_btn");
           
            g_signal_connect(GTK_BUTTON(btn), "clicked", G_CALLBACK(on_button_clicked), (gpointer)data);
            ItemGame *item = malloc(sizeof(ItemGame));
            item->btn = GTK_BUTTON(btn);
            item->index = n;
            item->status = 0;
            n++;
            stack_append(&list, item);

            gtk_widget_set_size_request(btn, 60, 60);
            gtk_grid_attach(grid, btn, i, j, 1, 1);
        }
    }

    set_generic_char_to_button(list, name);
}