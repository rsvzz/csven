#include <gtk-4.0/gtk/gtk.h>
#include "str_data.h"

typedef struct
{
    /* data */
    GtkStack *stack;
    GtkWindow *parent;
    ItemVerbs *verb;
} ItemOptVerb;

/// @brief clicked add verbs or word
/// @param  GtkWidget
/// @param  gpointer 
void on_button_add_verb_word(GtkWidget*, gpointer);
void on_save_verb(GtkWidget*, gpointer);
void on_close_verb(GtkWidget*, gpointer);