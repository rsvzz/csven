#include "../../include/comparetoindex.h"
#include <stdlib.h>

ItemBtnGame *get_index_title_button_char(Queue *list, GtkButton *btn)
{
    const char *name = gtk_button_get_label(btn);
    ItemBtnGame *item_result = NULL;
    if (list == NULL)
        g_print("queue es null get_title");

    if (name == NULL)
        return NULL;

    Queue *aux = list;
    while (aux != NULL)
    {

        ItemBtnGame *item = (ItemBtnGame *)aux->item;

        if (item->status == 0 && item->ctr == name[0])
        {
            item_result = item;
            if (aux->next == NULL)
                item_result->isEnd = 1;

            aux = NULL;
        }
        else if (item->status == 0 && item->ctr != name[0])
        {
            aux = NULL;
        }
        else
        {
            aux = aux->next;
        }
    }

    free(aux);
    return item_result;
}