#include "../../include/app_main.h"

struct _AppMain
{
    GObject parent_instance;
    GtkWidget *header, *box, *btn_add;
};

G_DEFINE_TYPE(AppMain, app_main, G_TYPE_OBJECT);

/// @brief Event save dialog window
/// @param
/// @param
void on_save_verb(GtkWidget *, gpointer);
/// @brief event close dialog window
/// @param
/// @param
void on_close_verb(GtkWidget *, gpointer);

/// @brief get it compere verb
/// @param
/// @param
/// @param
/// @return
static char *get_compare_verb(const char *, const char *, char);

/// @brief Event click button add of header
/// @param btn 
/// @param user_data 
void on_button_add_verb_word(GtkWidget *btn, gpointer user_data);

static void app_main_dispose(GObject *object)
{
    AppMain *self = APP_MAIN(object);

    if (self->btn_add != NULL)
    {
        g_object_unref(self->btn_add);
        self->btn_add = NULL;
    }

    if (self->header != NULL)
    {
        g_object_unref(self->header);
        self->header = NULL;
    }

    if (self->box != NULL)
    {
        g_object_unref(self->box);
        self->box = NULL;
    }

    G_OBJECT_CLASS(app_main_parent_class)->dispose(object);
}

static void app_main_finalize(GObject *object)
{
    G_OBJECT_CLASS(app_main_parent_class)->finalize(object);
}

static void app_main_class_init(AppMainClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = app_main_dispose;

    // Asignar la función de finalización
    object_class->finalize = app_main_finalize;
};

static void app_main_init(AppMain *self) {
    // obj gtk no here

};

AppMain *app_main_new(void)
{
    return g_object_new(APP_MAIN_TYPE, NULL);
}

void app_main_set_opt_window(AppMain *self)
{
    self->header = adw_header_bar_new();
    self->btn_add = gtk_button_new();
    self->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(self->box, TRUE);
    gtk_widget_set_vexpand(self->box, TRUE);
    gtk_widget_set_visible(self->btn_add, FALSE);
    gtk_button_set_icon_name(GTK_BUTTON(self->btn_add), "window-new-symbolic");
    adw_header_bar_pack_end(ADW_HEADER_BAR(self->header), self->btn_add);
}

GtkWidget *app_main_get_option_header_add(AppMain *self)
{
    return self->btn_add;
}

GtkWidget *app_main_get_header_bar(AppMain *self)
{
    return self->header;
}

void app_main_add_widget_box_child(AppMain *self, GtkWidget *child)
{
    gtk_box_append(GTK_BOX(self->box), child);
}

void app_main_load_btn_add_header(AppMain *self, GtkWidget *stack, GtkWidget *window, ItemVerbs *items)
{
    ItemOptVerb *opt = malloc(sizeof(ItemOptVerb));
    opt->stack = ADW_VIEW_STACK(stack);
    opt->parent = GTK_WINDOW(window);
    opt->verb = items;

    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(on_button_add_verb_word), (gpointer)opt);
}

GtkWidget *app_main_get_box_child(AppMain *self)
{
    return self->box;
}

void on_button_add_verb_word(GtkWidget *btn, gpointer user_data)
{
  ItemOptVerb *item = (ItemOptVerb *)user_data;
  GtkSelectionModel *pages = adw_view_stack_get_pages(item->stack);

  if (gtk_selection_model_is_selected(pages, 0) == 1)
  {
    // g_message("seleccionado word");
    return;
  }
  else
  {
    DialogWin *dialog = malloc(sizeof(DialogWin));
    dialog->parent = item->parent;
    dialog->on_save = on_save_verb;
    dialog->on_close = on_close_verb;
    WinVerb *win = win_verb_new();
    win_verb_load_widget(win,item->parent, "Add Verb", 1, dialog, item->verb);
    free(dialog);
    dialog = NULL;
  }
}

static char *get_compare_verb(const char *value, const char *compare, char replace)
{
    char *str = malloc(strlen(value) + 1);
    strcpy(str, value);

    for (int i = 0; i < strlen(value); i++)
    {

        if (strlen(value) >= strlen(compare))
        {
            if (value[i] == compare[i])
            {
                str[i] = replace;
            }
            else
            {
                str[i] = value[i];
            }
        }
    }
    return str;
}

void on_save_verb(GtkWidget *btn, gpointer data)
{
    ItemVerbWidget *item = (ItemVerbWidget *)data;
    GtkEntryBuffer *bfbase = gtk_entry_get_buffer(item->base);
    GtkEntryBuffer *bfv2 = gtk_entry_get_buffer(item->v2);
    GtkEntryBuffer *bfv3 = gtk_entry_get_buffer(item->v3);
    GtkEntryBuffer *bfing = gtk_entry_get_buffer(item->ing);

    gtk_label_set_label(item->data->present, gtk_entry_buffer_get_text(bfbase));

    char *new_v2 = get_compare_verb(gtk_entry_buffer_get_text(bfv2), gtk_entry_buffer_get_text(bfbase), '*');
    char *new_v3 = get_compare_verb(gtk_entry_buffer_get_text(bfv3), gtk_entry_buffer_get_text(bfv2), '-');
    char *new_ing = get_compare_verb(gtk_entry_buffer_get_text(bfing), gtk_entry_buffer_get_text(bfbase), '*');

    gtk_label_set_label(item->data->past, new_v2);
    gtk_label_set_label(item->data->participle, new_v3);
    gtk_label_set_label(item->data->baseing, new_ing);

    gtk_window_close(item->win);
}

void on_close_verb(GtkWidget *btn, gpointer data)
{
    gtk_window_close(GTK_WINDOW(data));
}