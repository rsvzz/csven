#include "../../include/maptogridforname.h"
#include "../../include/str_data.h"
#include <stdlib.h>
#include <time.h>
/// @brief Clear grid game para ser restablecido
/// @param list Item dentro del grid
void clear_btn_grid_game(ItemListRestore*);
int set_button_char_game(Queue *list, const char *ch, int nrandom)
{
    Queue *aux = list;

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

void clear_btn_grid_game(ItemListRestore* data)
{
    Queue *aux = *data->list;
    
    while (aux != NULL)
    {
        ItemGame *game = (ItemGame *)aux->item;
        game->status = 0;
        gtk_button_set_label(game->btn, '\0');
        gtk_widget_remove_css_class(GTK_WIDGET(game->btn), "game_btn_complete");
        gtk_widget_add_css_class(GTK_WIDGET(game->btn), "game_btn");
        gtk_widget_set_sensitive(GTK_WIDGET(game->btn), TRUE);
        
        aux = aux->next;
    }
}

void set_generic_char_to_button_game(ItemListRestore* data)
{
    int sttus = 0;
    srand(time(NULL));
    const char* name = data->name;
    int max = (data->x * data->y);
    clear_btn_grid_game(data);
    for (int i = 0; name[i] != '\0'; i++)
    {
        char ch = name[i];
        char str[2];
        str[0] = ch;
        str[1] = '\0';
        while (sttus == 0)
        {
            int nrandom = rand() % max;
            sttus = set_button_char_game(*data->list, (const char *)str, nrandom);
        }
        sttus = 0;
    }
}