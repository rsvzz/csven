#include "../../include/gdragdrop.h"
#include <glib-2.0/glib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct
{
    GtkWidget *btn, *btn_restare;
    GtkDragSource *drag;
    GtkDropTarget *drop;
    /// @brief all button random
    GQueue *qb_game;
    /// @brief all button title
    GQueue *gb_title;
    int index;
    int status;
} ItemMove;

struct _DragGame
{
    /* data */
    GObject parent_instance;
    GtkWidget *grid, *btn_restare;
    /// @brief button game list randon
    GQueue *qb_game;
    /// @brief add title button list
    GQueue *qb_title;
    /// @brief word name
    char *name;
    /// @brief create button total
    int max;
};

static GdkContentProvider *on_prepare_data(GtkDragSource *source, double x, double y, gpointer user_data);
static gboolean on_drop(GtkDropTarget *target, const GValue *value, double x, double y, gpointer user_data);

G_DEFINE_TYPE(DragGame, drag_game, G_TYPE_OBJECT);

/// @brief title char button list
/// @param  GQueue
void set_button_title_game(DragGame *, const char *);
/// @brief Random char button list
/// @param
void set_button_random_game(GQueue *, const char *);

static void drag_game_class_init(DragGameClass *Klass) {
};

void on_restare_button_game(ItemMove* self, gpointer data){
    g_print("End Game");
}

static void drag_game_init(DragGame *self)
{
    // obj gtk no here
    self->grid = gtk_grid_new();
};

DragGame *drag_game_new(void)
{
    return g_object_new(DRAG_GAME_TYPE, NULL);
}

void drag_game_set_word_grid(DragGame *self, const char *word)
{

    if (self->name != NULL)
    {
        g_free(self->name);
    }

    self->name = malloc(strlen(word) + 1);
    strcpy(self->name, word);

    int x = 2, y = strlen(word);

    if (self->qb_title != NULL)
    {
        g_queue_clear_full(self->qb_title, free);
        g_queue_free(self->qb_title);
    }

    if (self->qb_game != NULL)
    {
        g_queue_clear_full(self->qb_game, free);
        g_queue_free(self->qb_game);
    }

    if (self->grid != NULL)
    {
        GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(self->grid));
        while (child != NULL)
        {
            /* code */
            GtkWidget *aux = gtk_widget_get_next_sibling(child);
            gtk_widget_unparent(child);
            child = aux;
        }
    }

    self->qb_game = g_queue_new();
    self->qb_title = g_queue_new();

    for (size_t i = 0; i < x; i++)
    {

        for (size_t j = 0; j < y; j++)
        {
            /*
            char ch = word[j];
            char str[2];
            str[0] = ch;
            str[1] = '\0';
            */
            // create to Button for game
            GtkWidget *btn = gtk_button_new_with_label(NULL);
            gtk_widget_set_size_request(btn, 70, 70);
            gtk_widget_set_margin_end(btn, 5);
            gtk_widget_set_margin_top(btn, 5);

            ItemMove *item = malloc(sizeof(ItemMove));
            item->btn = btn;
            if (i == 0)
            {
                item->btn_restare = self->btn_restare;
                g_queue_push_tail(self->qb_title, item);
            }

            if (i == 1)
            {
                g_queue_push_tail(self->qb_game, item);
            }
            gtk_grid_attach(GTK_GRID(self->grid), btn, j, i, 1, 1);
        }
    }
}

GtkWidget *drag_game_get_content(DragGame *self)
{
    return self->grid;
}
const char* drag_game_get_name(DragGame *self){
    return self->name;
}

void drag_game_set_data_button(DragGame *self)
{
    set_button_title_game(self, self->name);
    set_button_random_game(self->qb_game, self->name);
    //drag_game_set_word_grid(self, self->name);
    //reiniciar los button
}

void drag_game_set_refresh_button(DragGame *self)
{
    set_button_title_game(self, self->name);
    set_button_random_game(self->qb_game, self->name);
}

void drag_game_set_button_restare(DragGame *self, GtkWidget *button){
    self->btn_restare = button;
}

void set_button_title_game(DragGame *self, const char *name)
{
    GQueue *aux = self->qb_title;
    int max = g_queue_get_length(aux);
    // g_print("%s ,\n", name);

    for (int i = 0; i < max; i++)
    {
        ItemMove *item = g_queue_peek_nth(aux, i);
        item->index = i;
        item->status = 0;
        item->qb_game = self->qb_game;
        item->gb_title = aux;

        if(gtk_widget_get_sensitive(item->btn) == FALSE){
            gtk_widget_set_sensitive(item->btn, TRUE);
            gtk_widget_unset_state_flags(item->btn, GTK_STATE_FLAG_DROP_ACTIVE);
        }
        GtkDropTarget *drop_target = gtk_drop_target_new(G_TYPE_STRING, GDK_ACTION_COPY);
        g_signal_connect(drop_target, "drop", G_CALLBACK(on_drop), item);
        gtk_widget_add_controller(item->btn, GTK_EVENT_CONTROLLER(drop_target));

        item->drop = drop_target;

        char ch = name[i];
        char str[2];
        str[0] = ch;
        str[1] = '\0';

        gtk_button_set_label(GTK_BUTTON(item->btn), str);
    }
}

void set_button_random_game(GQueue *queue, const char *name)
{
    GQueue *aux = queue;
    int max = g_queue_get_length(aux), val = 0;
    char *new_name = malloc(strlen(name) + 1);
    strcpy(new_name, name);
    srand(time(NULL));
    for (int i = 0; i < max; i++)
    {

        ItemMove *item = g_queue_peek_nth(aux, i);
        item->index = i;

        if(gtk_widget_get_sensitive(item->btn) == FALSE){
            gtk_widget_set_sensitive(item->btn, TRUE);
        }

        GtkDragSource *drag_source = gtk_drag_source_new();
        gtk_drag_source_set_actions(drag_source, GDK_ACTION_COPY);
        g_signal_connect(drag_source, "prepare", G_CALLBACK(on_prepare_data), item);
        gtk_widget_add_controller(item->btn, GTK_EVENT_CONTROLLER(drag_source));
        item->drag = drag_source;

        val = rand() % strlen(new_name);

        char ch = new_name[val];
        char str[2];
        str[0] = ch;
        str[1] = '\0';

        int n = 0, l = 0, status = 0;
        while (n < strlen(new_name))
        {
            /* code */
            if (ch != new_name[n] || status == 1)
            {
                // g_print("%d position \n", l);
                new_name[l++] = new_name[n];
            }
            // validar la primera letra parecida despues puede existir otra
            if (ch == new_name[n])
            {
                status = 1;
            }

            n++;
        }

        new_name[l] = '\0';

        gtk_button_set_label(GTK_BUTTON(item->btn), str);

        

        
    }

    g_free(new_name);
    // g_queue_free(aux);
}

static GdkContentProvider *on_prepare_data(GtkDragSource *source, double x, double y, gpointer user_data)
{
    ItemMove *item = (ItemMove *)user_data;
    gchar *text = g_strdup_printf("%d", item->index);
    // const char *text = gtk_button_get_label(GTK_BUTTON(item->btn));
    GValue value = G_VALUE_INIT;
    g_value_init(&value, G_TYPE_STRING);
    g_value_set_string(&value, text);
    // g_print("prepare %d \n", item->index);
    return gdk_content_provider_new_for_value(&value);
}

static gboolean on_drop(GtkDropTarget *target, const GValue *value, double x, double y, gpointer user_data)
{
    ItemMove *item = (ItemMove *)user_data; // drop data receptor

    int index = atoi(g_value_get_string(value)); // llega de prepare

    GQueue *aux = item->qb_game;
    int max = g_queue_get_length(aux);
    ItemMove *item_b, *item_t;

    GQueue *aux2 = item->gb_title;
    int len = g_queue_get_length(aux2);
    for (int i = 0; i < len; i++)
    {
        /* code */

        item_t = g_queue_peek_nth(aux2, i);
        if (item_t->status == 0)
        {
            break;
        }
    }

    for (int i = 0; i < max; i++)
    {

        item_b = g_queue_peek_nth(aux, i);
        if (index == item_b->index)
        {
            break;
        }
    }

    if (item_t != NULL)
    {

        const char *str_r, *str_d; //*str_t
        // str_t = gtk_button_get_label(GTK_BUTTON(item->btn));
        str_r = gtk_button_get_label(GTK_BUTTON(item_b->btn));
        str_d = gtk_button_get_label(GTK_BUTTON(item_t->btn));
        // g_print("(%d, %d) \n", item_b->index, item_t->index);
        // g_print("(%s, %s, %s) \n", str_t, str_r, str_d);

        if (strcmp(str_d, str_r) == 0 && item_t->index == item->index)
        {
            //g_print("remove event and #%d status %d \n", item_t->index, item_t->status);
            // gtk_button_set_label(GTK_BUTTON(item->btn), text);
            gtk_widget_remove_controller(item_t->btn, GTK_EVENT_CONTROLLER(target));
            gtk_widget_set_sensitive(GTK_WIDGET(item_t->btn), FALSE);

            gtk_widget_remove_controller(item_b->btn, GTK_EVENT_CONTROLLER(item_b->drag));
            gtk_widget_set_sensitive(GTK_WIDGET(item_b->btn), FALSE);

            // g_queue_free(aux);
            item_t->status = 1;

            if(item_t->index == (len - 1)){
                gtk_widget_set_sensitive(item->btn_restare, TRUE);
            }
                
            return TRUE;
        }
    }

    return FALSE;

    // g_print("(%d, %d) \n", item_b->index, item->index);
}