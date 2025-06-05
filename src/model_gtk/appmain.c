#include "../../include/app_main.h"
#include "../../include/option_verb.h"

struct _AppMain
{
    GObject parent_instance;
    GtkWidget *header, *box, *btn_add;
};

G_DEFINE_TYPE(AppMain, app_main, G_TYPE_OBJECT);

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
    self->header = gtk_header_bar_new();
    self->btn_add = gtk_button_new();
    self->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(self->box, TRUE);
    gtk_widget_set_vexpand(self->box, TRUE);
    gtk_widget_set_visible(self->btn_add, FALSE);
    gtk_button_set_icon_name(GTK_BUTTON(self->btn_add), "list-add-symbolic");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(self->header), self->btn_add);
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
    opt->stack = GTK_STACK(stack);
    opt->parent = GTK_WINDOW(window);
    opt->verb = items;

    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(on_button_add_verb_word), (gpointer)opt);
}

GtkWidget *app_main_get_box_child(AppMain *self)
{
    return self->box;
}

/*
GtkWidget *header, *box_content, *btn_add;
void create_app_window(GtkWidget *window, GtkApplication *app)
{
    header = gtk_header_bar_new();
    box_content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(box_content, TRUE);
    gtk_widget_set_vexpand(box_content, TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
    gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), gtk_label_new("To Learn English"));
    gtk_window_set_default_size(GTK_WINDOW(window), 720, 720);
    btn_add = gtk_button_new();
    gtk_widget_set_visible(btn_add, FALSE);
    gtk_button_set_icon_name(GTK_BUTTON(btn_add), "list-add-symbolic");
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header), btn_add);
    gtk_window_set_child(GTK_WINDOW(window), box_content);
    gtk_window_present(GTK_WINDOW(window));
}

void add_app_content(GtkWidget *widget)
{
    gtk_box_append(GTK_BOX(box_content), widget);
}

GtkWidget *get_app_header_bar()
{
    return header;
}

GtkWidget *get_app_btn_add()
{
    return btn_add;
}

void load_btn_add_header(ItemVerbs *items, GtkWidget *stack, GtkWidget *window)
{
    ItemOptVerb *opt = malloc(sizeof(ItemOptVerb));
    opt->stack = GTK_STACK(stack);
    opt->parent = GTK_WINDOW(window);
    opt->verb = items;

    g_signal_connect(btn_add, "clicked", G_CALLBACK(on_button_add_verb_word), (gpointer)opt);
}
*/