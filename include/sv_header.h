#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>
#include <libadwaita-1/adwaita.h>

#define SV_HEADER_TYPE sv_header_get_type()

G_DECLARE_DERIVABLE_TYPE(SvHeader, sv_header, SV, HEADER, GObject)

struct _SvHeaderClass
{
    GObjectClass parent_class;
    void (*load_button_header)(SvHeader*, gpointer);
};

SvHeader *sv_header_new(GtkWidget*);

GtkWidget *sv_header_get_header(SvHeader *);

GtkWidget *sv_header_get_parent(SvHeader *);

GtkWidget *sv_header_get_stack(SvHeader *);

GtkWidget *sv_header_get_button_add(SvHeader*);
GtkWidget *sv_header_get_button_menu(SvHeader*);

void sv_header_set_option_menu(SvHeader*, gpointer);


