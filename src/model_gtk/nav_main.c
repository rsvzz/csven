#include "../../include/nav_main.h"
#include "../../include/create_verb_win.h"
struct _NavMain
{
    GObject parent_instance;
    GtkWidget *popover, *box;
};

G_DEFINE_TYPE (NavMain, nav_main, SV_HEADER_TYPE);

static void nav_main_finalize(GObject *object)
{
    G_OBJECT_CLASS(nav_main_parent_class)->finalize(object);
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
                         "version", "0.1.19",
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
     NavMain *app = (NavMain*)user_data;

     gtk_widget_set_visible(app->popover, FALSE);

     show_about(gtk_window_get_application(GTK_WINDOW(sv_header_get_parent(SV_HEADER(app)))));
}

void on_popover_closed(GtkPopover *popover, gpointer user_data)
{
    //gtk_widget_unparent(GTK_WIDGET(popover));
    gtk_widget_set_visible(GTK_WIDGET(popover), FALSE);
}

void on_button_menu_verb_word(GtkWidget *btn, gpointer user_data)
{
    NavMain *m_obj = (NavMain *) user_data;
    gtk_widget_set_visible(m_obj->popover, TRUE);
}

static void nav_main_set_option_menu(NavMain *self, gpointer data){
    //GtkWidget *button_add = sv_header_get_button_add(SV_HEADER(self));
    GtkWidget *window = sv_header_get_parent(SV_HEADER(self));
    ItemVerbs *items = (ItemVerbs *) data;
    ItemOptVerb *opt = malloc(sizeof(ItemOptVerb));
    opt->stack = ADW_VIEW_STACK(sv_header_get_stack(SV_HEADER(self)));
    opt->parent = GTK_WINDOW(window);
    opt->verb = items;
    //
    //self->win_parent = window;

    g_signal_connect(sv_header_get_button_add(SV_HEADER(self)), "clicked", G_CALLBACK(on_button_add_verb_word), (gpointer)opt);
    g_signal_connect(sv_header_get_button_menu(SV_HEADER(self)), "clicked", G_CALLBACK(on_button_menu_verb_word), (gpointer)self);

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
    gtk_widget_set_parent(popover, sv_header_get_button_menu(SV_HEADER(self)));
    gtk_popover_set_position(GTK_POPOVER(popover), GTK_POS_BOTTOM);
    gtk_popover_set_autohide(GTK_POPOVER(popover), TRUE);
    gtk_widget_set_visible(popover, FALSE);

}

static void nav_main_set_option_menu_wrapper(SvHeader *self, gpointer data){
    nav_main_set_option_menu(NAV_MAIN(self), data);
}

static void nav_main_class_init(NavMainClass *klass){
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    SvHeaderClass *kclass_header = SV_HEADER_CLASS(klass);
    kclass_header->load_button_header = nav_main_set_option_menu_wrapper;
    gobject_class->finalize = nav_main_finalize;
}

static void nav_main_init(NavMain *self){
    self->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    self->popover = gtk_popover_new();
}

NavMain *nav_main_new(GtkWidget *_parent){
    NavMain *obj = g_object_new(NAV_MAIN_TYPE, "parent", _parent, NULL);
    return obj;
}

void on_stack_page_changed(GObject *_stack, GParamSpec *param, gpointer user_data)
{
    const char *visible_child = adw_view_stack_get_visible_child_name(ADW_VIEW_STACK(_stack));
    if (strcmp(visible_child, "verb") == 0)
    {
        gtk_widget_set_visible((GTK_WIDGET(user_data)), TRUE);
    }
    else
    {
        gtk_widget_set_visible(GTK_WIDGET(user_data), FALSE);
    }
}

void nav_main_load_content(NavMain *self){
    gtk_box_append(GTK_BOX(self->box), sv_header_get_header(SV_HEADER(self)));
    gtk_box_append(GTK_BOX(self->box), sv_header_get_stack(SV_HEADER(self)));
    GtkWidget *button_add = sv_header_get_button_add(SV_HEADER(self));
    GtkWidget *stack = sv_header_get_stack(SV_HEADER(self));
    g_signal_connect(stack, "notify::visible-child", G_CALLBACK(on_stack_page_changed), (gpointer)button_add);
}

GtkWidget * nav_main_get_popover(NavMain *self){
    return self->popover;
}

GtkWidget * nav_main_get_box_main(NavMain *self){
    return self->box;
}

AdwViewStackPage *nav_main_add_stack_page(NavMain *self, GtkWidget *child, const char *name, const char *title, const char *icon_name){
    return adw_view_stack_add_titled_with_icon(ADW_VIEW_STACK(sv_header_get_stack(SV_HEADER(self))), child, name, title, icon_name);
}


