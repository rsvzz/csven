#include "../../include/verbpg.h"
GtkWidget *box_verbs;
ItemVerbs *item_verbs;
void create_page_verb()
{
    box_verbs = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    item_verbs = malloc(sizeof(ItemVerbs));
    load_verb(GTK_BOX(box_verbs), item_verbs);
}

GtkWidget *get_box_verb()
{
    return box_verbs;
}

ItemVerbs *get_item_verb()
{
    return item_verbs;
}