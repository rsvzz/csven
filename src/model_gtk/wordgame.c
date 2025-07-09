#include "../../include/word_game.h"
#include <glib-2.0/glib.h>
#include <stdlib.h>
#include <time.h>
/// @brief struct button game queue
typedef struct
{
    GtkButton *btn;
    /// @brief index main
    int index;
    int status;
    /// @brief index remove list 
    int idex;
    /// @brief button pending
    int max;
} ItemGameButton;

struct _WordGame
{
    /* data */
    GObject parent_instance;
    /// @brief add button of de game
    GQueue *qbutton;
    /// @brief add title button list
    GQueue *qtbutton;
    /// @brief remove list
    GQueue *qbutton_aux;
    char *name;
    /// @brief create button total
    int max;
    /// @brief Content title button for game
    GtkBox *box;
    GtkButton *btn_restore;
};

G_DEFINE_TYPE(WordGame, word_game, G_TYPE_OBJECT);

/// @brief event click button game add all
/// @param btn
/// @param data
void on_click_button_restore(GtkButton *btn, gpointer data);

static void word_game_dispose(GObject *object)
{
    WordGame *self = WORD_GAME(object);
    if(self->qbutton != NULL)
        g_queue_free(self->qbutton);

    if(self->qtbutton != NULL)
        g_queue_free(self->qtbutton);
    
    if(self->qbutton_aux != NULL)
        g_queue_free(self->qbutton_aux);
    

    G_OBJECT_CLASS(word_game_parent_class)->dispose(object);
}

static void word_game_finalize(GObject *object)
{
    G_OBJECT_CLASS(word_game_parent_class)->finalize(object);
}

static void word_game_class_init(WordGameClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = word_game_dispose;

    // Asignar la función de finalización
    object_class->finalize = word_game_finalize;
};

static void word_game_init(WordGame *self)
{
}

WordGame *word_game_new(void)
{
    return g_object_new(WORD_GAME_TYPE, NULL);
}

void word_game_set_box_title(WordGame *self, GtkBox *box)
{
    self->box = box;
}
void word_game_load_button(WordGame *self, GtkGrid *grid, int x, int y)
{
    int n = 0;
    self->qbutton = g_queue_new();
    self->qtbutton = g_queue_new();
    self->qbutton_aux = NULL;
    
    for (size_t i = 0; i < y; i++)
    {

        for (size_t j = 0; j < x; j++)
        {
            // create to Button for game
            GtkWidget *btn = gtk_button_new();
            // add style button
            gtk_widget_add_css_class(btn, "game_btn");
            // signal click btn
            g_signal_connect(GTK_BUTTON(btn), "clicked", G_CALLBACK(on_click_button_restore), (gpointer)self);

            ItemGameButton *item = malloc(sizeof(ItemGameButton));
            item->btn = GTK_BUTTON(btn);
            item->index = n;
            item->status = 0;
            n++;

            gtk_widget_set_size_request(btn, 70, 70);

            g_queue_push_tail(self->qbutton, item);
            gtk_grid_attach(grid, btn, i, j, 1, 1);
        }
    }
    // requeri after
    self->max = x * y;
}

void word_game_clear_char_to_button_for_grid(WordGame *self)
{
    GQueue *aux = self->qbutton;
    if(self->qbutton_aux != NULL){
        g_queue_free(self->qbutton_aux);
        self->qbutton_aux = NULL;
    }
        
        
    
    
    for (guint i = 0; i < g_queue_get_length(aux); i++)
    {
        ItemGameButton *game = g_queue_peek_nth(aux, i);
        //g_print("clear : %s \n",  gtk_button_get_label(game->btn));
        game->status = 0; // set no click
        gtk_button_set_label(game->btn, '\0');
        gtk_widget_remove_css_class(GTK_WIDGET(game->btn), "game_btn_complete");
        gtk_widget_add_css_class(GTK_WIDGET(game->btn), "game_btn");
        gtk_widget_set_sensitive(GTK_WIDGET(game->btn), TRUE);
    }
}

void word_game_get_status_change_char_to_button(WordGame *self, const char *ch, int nrandom)
{

    GQueue *aux = self->qbutton_aux;
    if(self->qbutton_aux == NULL){
        aux = g_queue_copy(self->qbutton);
    }

    //order idex
    int j = 0;
    for (guint i = 0; i < g_queue_get_length(aux); i++)
    {
         ItemGameButton *game = g_queue_peek_nth(aux, i);
         game->idex = j;
         j++;
    }
    //j + 1 rand() % self->max remove 1 add 1 ++ 
    self->max =j;
    //g_print("#%d = %s -> #%d", nrandom, ch, self->max);
    for (guint i = 0; i < g_queue_get_length(aux); i++)
    {
        ItemGameButton *game = g_queue_peek_nth(aux, i);
        if (game->idex == nrandom && game->status == 0)
        {
            gtk_button_set_label(game->btn, ch);
            g_queue_remove(aux, game);
            self->max --;
            //g_print(" :) \n");
            game->status = 1;
            break;
        }
        else if (game->idex == nrandom && game->status == 1)
        {
            //g_print("fail #%d \n", nrandom);
            break;
        }
    }

    //change 
    self->qbutton_aux = aux;
}

void word_game_load_char_title_game(WordGame *self, const char *name)
{
    if(self->qtbutton != NULL){
        g_queue_free(self->qtbutton);
        self->qtbutton = NULL;
    }
        
    self->qtbutton = g_queue_new();
    // clear box content
    //*********
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(self->box));
    while (child != NULL)
    {
        /* code */
        GtkWidget *aux = gtk_widget_get_next_sibling(child);
        gtk_widget_unparent(child);
        child = aux;
    }
    // *********
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

        g_queue_push_tail(self->qtbutton, item);
        gtk_widget_set_size_request(btn, 50, 50);
        gtk_box_append(self->box, btn);
    }
}

void word_game_set_btn_restore(WordGame *self, GtkButton *btn)
{
    self->btn_restore = btn;
}

void word_game_set_name_word(WordGame *self, const char *name)
{
    if (self->name != NULL)
        g_free(self->name);

    self->name = g_strdup((char *)name);
}

ItemBtnGame *word_game_get_index_title_button_char(WordGame *self, GtkButton *btn)
{
    const char *name = gtk_button_get_label(btn);
    ItemBtnGame *item_result = NULL;

    if (name == NULL)
        return NULL;

    // GtkButton from Word Title
    GQueue *aux = self->qtbutton;

    for (guint i = 0; i < g_queue_get_length(aux); i++)
    {
        ItemBtnGame *item = g_queue_peek_nth(aux, i);

        if (item->status == 0 && item->ctr == name[0])
        {
            item_result = item;

            if (i == g_queue_get_length(aux) - 1)
                item_result->isEnd = 1;

            break;
        }
        else if (item->status == 0 && item->ctr != name[0])
        {
            break;
        }
    }

    return item_result;
}

void word_game_set_name_to_button(WordGame *self)
{
    srand(time(NULL));
    GtkWidget *btn = GTK_WIDGET(self->btn_restore);
    if (gtk_widget_get_sensitive(btn) == TRUE)
    {
        gtk_widget_remove_css_class(btn, "button_complete");
        gtk_widget_add_css_class(btn, "button");
        gtk_widget_set_sensitive(btn, FALSE);
    }
    word_game_clear_char_to_button_for_grid(self);
    //g_print("********************** \n");
    for (int i = 0; self->name[i] != '\0'; i++)
    {
        char ch = self->name[i];
        char str[2];
        str[0] = ch;
        str[1] = '\0';
        int nrandom = rand() % self->max;
 
        word_game_get_status_change_char_to_button(self, (const char *)str, nrandom);
    }
    // g_print("name : %s \n", self->name );
    word_game_load_char_title_game(self, self->name);
}

void on_click_button_restore(GtkButton *btn, gpointer data)
{
    WordGame *game = (WordGame *)data;
    const char *name = gtk_button_get_label(btn);
    if (name != NULL)
    {

        ItemBtnGame *item = word_game_get_index_title_button_char(game, btn);
        if (item != NULL)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(btn), FALSE);
            gtk_widget_add_css_class(GTK_WIDGET(btn), "game_btn_complete");
            gtk_widget_add_css_class(GTK_WIDGET(item->btn), "game_btn_complete");
            // gtk_widget_set_size_request(GTK_WIDGET(item->btn), 55, 55);
            item->status = 1;

            if (item->isEnd == 1)
            {
                gtk_widget_set_sensitive(GTK_WIDGET(game->btn_restore), TRUE);
                gtk_widget_add_css_class(GTK_WIDGET(game->btn_restore), "button_complete");
            }
        }
    }
}