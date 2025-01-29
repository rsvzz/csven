
#include "../../include/ctobutton.h"
#include "../../include/comparetoindex.h"
#include <stdlib.h>

void create_button_size_char(const char *name, GtkBox *box, Queue **list)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        char ch = name[i];
        char str[2];
        str[0] = ch;
        str[1] = '\0';

        GtkWidget *btn = gtk_button_new_with_label((const char *)str);
        gtk_widget_add_css_class(btn, "title_btn");
        ItemBtnGame *item = malloc(sizeof(ItemBtnGame));
        item->btn = GTK_BUTTON(btn);
        item->ctr = ch;
        item->index = i;
        item->status = 0;

        queue_append(list, item);
        gtk_widget_set_size_request(btn, 50, 50);
        gtk_box_append(box, btn);
    }
    /*
    Queue *aux = list;
    g_print("QUEUE RUN \n");
    while (aux != NULL)
    {
            g_print("# %c \n", ((ItemBtnGame*)aux->item)->ctr);
            aux = aux->next;
    }
    free(aux);
    */
}
