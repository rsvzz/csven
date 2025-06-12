#include "../../include/nav.h"

struct _StackOption
{
    /* data */
    GObject *parent_instance;
    GtkWidget *box, *stack, *siderbar;
};

G_DEFINE_TYPE(StackOption, stack_option, G_TYPE_OBJECT);
/// @brief event page change
/// @param
/// @param
/// @param
void on_stack_page_changed(GObject *, GParamSpec *, gpointer);

static void stack_option_dispose(GObject *object)
{
    StackOption *self = STACK_OPTION(object);
    /*
    if (self->box != NULL)
    {
        g_object_unref(self->box);
        self->box = NULL;
    }

    if (self->siderbar != NULL)
    {
        g_object_unref(self->siderbar);
        self->siderbar = NULL;
    }

    if (self->stack != NULL)
    {
        g_object_unref(self->stack);
        self->stack = NULL;
    }
        */

    G_OBJECT_CLASS(stack_option_parent_class)->dispose(object);
}

static void stack_option_finalize(GObject *object)
{
    G_OBJECT_CLASS(stack_option_parent_class)->finalize(object);
}

static void stack_option_class_init(StackOptionClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = stack_option_dispose;

    // Asignar la función de finalización
    object_class->finalize = stack_option_finalize;
};

static void stack_option_init(StackOption *self) {
    // obj gtk no here problem
};

void stack_option_load_all(StackOption *self)
{
    self->stack = adw_view_stack_new();
    self->siderbar = adw_view_switcher_new();
    self->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    adw_view_switcher_set_stack(ADW_VIEW_SWITCHER(self->siderbar), ADW_VIEW_STACK(self->stack));
    gtk_box_append(GTK_BOX(self->box), self->siderbar);
    gtk_box_append(GTK_BOX(self->box), self->stack);

    gtk_widget_set_hexpand(self->box, TRUE);
    gtk_widget_set_vexpand(self->box, TRUE);
}
StackOption *stack_option_new(void)
{
    return g_object_new(STACK_OPTION_TYPE, NULL);
}

void stack_option_set_button_option_add(StackOption *self, GtkWidget *optadd)
{
    g_signal_connect(self->stack, "notify::visible-child", G_CALLBACK(on_stack_page_changed), (gpointer)optadd);
}

GtkWidget *stack_option_get_box_page(StackOption *self)
{
    return self->box;
}
GtkWidget *stack_option_get_stack(StackOption *self)
{
    return self->stack;
}

AdwViewStackPage *stack_option_add_stack_child(StackOption *self, GtkWidget *child, const char *name, const char *title, const char * icon_name)
{
    return adw_view_stack_add_titled_with_icon(ADW_VIEW_STACK(self->stack), child, name, title, icon_name);
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
