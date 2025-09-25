#include "../../include/sv_header.h"

typedef struct
{
    GtkWidget *header, *switcher, *button_add, *button_menu, *parent, *stack;
} SvHeaderPrivate;

enum
{
    PROP_0,
    PROP_WIDGET_PARENT,
    N_PROPERTIES
};

G_DEFINE_TYPE_WITH_PRIVATE(SvHeader, sv_header, G_TYPE_OBJECT);

static GParamSpec *sv_header_properties[N_PROPERTIES] = {NULL};

static void sv_header_set_property(GObject *object, guint property_id,
                                   const GValue *value, GParamSpec *pspec)
{
    SvHeader *self = (SvHeader *)object;

    switch (property_id)
    {
    case PROP_WIDGET_PARENT:
        SvHeaderPrivate *priv = sv_header_get_instance_private(self);
        priv->parent = g_value_get_object(value);
        break;

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    }
}

static void sv_header_finalize(GObject *object)
{
    G_OBJECT_CLASS(sv_header_parent_class)->finalize(object);
}

static void sv_header_class_init(SvHeaderClass *klass)
{
    // klass->say_hello = person_say_hello_default;
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    klass->load_button_header = NULL; // default null
    gobject_class->finalize = sv_header_finalize;
    gobject_class->set_property = sv_header_set_property;

    sv_header_properties[PROP_WIDGET_PARENT] =
        g_param_spec_object("parent", "Parent", "GtkWidget parent",
                            GTK_TYPE_WIDGET,
                            G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY);

    g_object_class_install_properties(gobject_class, N_PROPERTIES, sv_header_properties);
}

static void sv_header_init(SvHeader *self)
{
    SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    priv->header = adw_header_bar_new();
    priv->button_add = gtk_button_new_from_icon_name("window-new-symbolic");
    priv->button_menu = gtk_button_new_from_icon_name("open-menu-symbolic");

    priv->switcher = adw_view_switcher_new();
    priv->stack = adw_view_stack_new();
    adw_view_switcher_set_stack(ADW_VIEW_SWITCHER(priv->switcher), ADW_VIEW_STACK(priv->stack));
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(priv->header), priv->switcher);

    gtk_widget_set_visible(priv->button_add, FALSE);
    adw_header_bar_pack_start(ADW_HEADER_BAR(priv->header), priv->button_add);
    adw_header_bar_pack_end(ADW_HEADER_BAR(priv->header), priv->button_menu);
    
}

SvHeader *sv_header_new(GtkWidget *_parent)
{
    SvHeader *self = g_object_new(SV_HEADER_TYPE, "parent", _parent, NULL);
    // SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    // priv->parent = _parent;
    return self;
}

GtkWidget *sv_header_get_header(SvHeader *self)
{
    SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    return priv->header;
}

GtkWidget *sv_header_get_parent(SvHeader *self)
{
    SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    return priv->parent;
}

GtkWidget *sv_header_get_stack(SvHeader *self)
{
    SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    return priv->stack;
}

GtkWidget *sv_header_get_button_add(SvHeader *self)
{
    SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    return priv->button_add;
}

GtkWidget *sv_header_get_button_menu(SvHeader *self)
{
    SvHeaderPrivate *priv = sv_header_get_instance_private(self);
    return priv->button_menu;
}

void sv_header_set_option_menu(SvHeader *seft, gpointer data)
{
    g_return_if_fail(SV_IS_HEADER(seft));

    SvHeaderClass *klass = SV_HEADER_GET_CLASS(seft);
    if(klass->load_button_header != NULL)
        klass->load_button_header(seft, data);
}
