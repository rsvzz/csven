#include "../../include/mapcss.h"
#include <gtk-4.0/gtk/gtk.h>

void load_path_css()
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    char *exe_path = g_file_read_link("/proc/self/exe", NULL); //only Linux for windows dont work
    if (!exe_path)
    {
        g_printerr("No se pudo obtener la ruta del ejecutable.\n");
        return;
    }
    char *css_path;

    css_path = g_build_path(G_DIR_SEPARATOR_S, g_path_get_dirname(exe_path), "../share/csven/style/io.github.rsvzz.csven.css", NULL); // publish
    g_free(exe_path);
    gtk_css_provider_load_from_path(css_provider, css_path); // meson install publish
    //gtk_css_provider_load_from_path(css_provider, "../style/io.github.rsvzz.csven.css"); // make only dev

    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                               GTK_STYLE_PROVIDER(css_provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}