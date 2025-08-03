#include "../../include/app_main.h"

struct _AppMain
{
    GObject parent_instance;
    GtkWidget *header, *box, *btn_add, *btn_menu, *popover, *win_parent;
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

/// @brief Event click menu
/// @param btn
/// @param user_data
void on_button_menu_verb_word(GtkWidget *btn, gpointer user_data);
static void app_main_dispose(GObject *object)
{
    //g_print("llega dispose \n");
    AppMain *self = APP_MAIN(object);

    if (self->btn_add != NULL)
    {
        g_object_unref(self->btn_add);
        self->btn_add = NULL;
    }

    if(self->popover != NULL){
       
        gtk_widget_unparent(self->popover);
        self->popover = NULL;
    }

     if (self->btn_menu != NULL)
    {
        g_object_unref(self->btn_menu);
        self->btn_menu = NULL;
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
    self->btn_add = gtk_button_new_from_icon_name("window-new-symbolic");
    self->btn_menu = gtk_button_new_from_icon_name("open-menu-symbolic");
    self->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(self->box, TRUE);
    gtk_widget_set_vexpand(self->box, TRUE);
    gtk_widget_set_visible(self->btn_add, FALSE);
    adw_header_bar_pack_end(ADW_HEADER_BAR(self->header), self->btn_menu);
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

void show_about (GtkApplication *app)
{
  const char *developers[] = {
    "rsvzz",
    NULL
  };

  const char *designers[] = {
    "Free Software Contributor",
    NULL
  };

  adw_show_about_dialog (GTK_WIDGET (gtk_application_get_active_window (app)),
                         "application-name", ("csven"),
                         "application-icon", "io.github.rsvzz.csven",
                         "version", "0.1.18",
                         "copyright", "© 2025 rsvzz",
                         "issue-url", "https://github.com/rsvzz/csven/issues",
                         "license-type", GTK_LICENSE_GPL_3_0,
                         "developers", developers,
                         "designers", designers,
                         "translator-credits", ("translator-credits"),
                         NULL);
}

void on_about_activate(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
     AppMain *app = (AppMain*)user_data;

     gtk_widget_set_visible(app->popover, FALSE);

     show_about(gtk_window_get_application(GTK_WINDOW(app->win_parent)));
}

void on_popover_closed(GtkPopover *popover, gpointer user_data)
{
    //gtk_widget_unparent(GTK_WIDGET(popover));
    gtk_widget_set_visible(GTK_WIDGET(popover), FALSE);
}

void on_button_menu_verb_word(GtkWidget *btn, gpointer user_data)
{

    gtk_widget_set_visible(((AppMain*)user_data)->popover, TRUE);
}

void app_main_load_btn_add_header(AppMain *self, GtkWidget *stack, GtkWidget *window, ItemVerbs *items)
{
    ItemOptVerb *opt = malloc(sizeof(ItemOptVerb));
    opt->stack = ADW_VIEW_STACK(stack);
    opt->parent = GTK_WINDOW(window);
    opt->verb = items;
    //
    self->win_parent = window;

    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(on_button_add_verb_word), (gpointer)opt);
    g_signal_connect(self->btn_menu, "clicked", G_CALLBACK(on_button_menu_verb_word), (gpointer)self);

    GMenu *menu = g_menu_new();
    GMenuItem *m_about = g_menu_item_new("About", "app.about");
    // GMenuItem *item2 = g_menu_item_new("Opción 2", "app.opcion2");

    g_menu_append_item(menu, m_about);
    GSimpleAction *action = g_simple_action_new("about", NULL);

    g_signal_connect(action, "activate", G_CALLBACK(on_about_activate), (gpointer)self);

    g_action_map_add_action(G_ACTION_MAP(gtk_window_get_application(GTK_WINDOW(window))), G_ACTION(action));

    // g_menu_append_item(menu, item2);

    GtkWidget *popover = gtk_popover_menu_new_from_model(G_MENU_MODEL(menu));
    self->popover = popover;
    g_signal_connect(popover, "closed", G_CALLBACK(on_popover_closed), NULL);
    gtk_widget_set_parent(popover, self->btn_menu);
    gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
    gtk_popover_set_autohide(GTK_POPOVER(popover), TRUE);
    gtk_widget_set_visible(popover, FALSE);
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
        DialogWin dialog; //new memory dont need
        dialog.parent = item->parent;
        dialog.on_save = on_save_verb;
        dialog.on_close = on_close_verb;
        WinVerb *win = win_verb_new();
        win_verb_load_widget(win, item->parent, "Add Verb", 1, &dialog, item->verb);
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
    gtk_check_button_set_active(item->data->is_regular, gtk_check_button_get_active(item->isRegular));
    gtk_window_close(item->win);
}

void on_close_verb(GtkWidget *btn, gpointer data)
{
    gtk_window_close(GTK_WINDOW(data));
}

GtkWidget *app_main_get_popover(AppMain *self){
    return self->popover;
}