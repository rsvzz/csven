#include "../../include/app.h"
#include <adwaita.h>
GtkWidget *header, *box_adw, *btn_add;
void create_app_window(GtkWidget *window, GtkApplication *app)
{
    // verificacion de ventana main para que solo una vez este abierta
    if (window != NULL)
    {
        gtk_window_present(GTK_WINDOW(window));
        return;
    }

    window = adw_application_window_new(app);
    header = adw_header_bar_new();
    box_adw = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    add_app_content(header);
    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), box_adw);
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("To Learn Words and Verbs"));
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 400);
    btn_add = gtk_button_new();
    gtk_widget_set_visible(btn_add, FALSE);
    gtk_button_set_icon_name(GTK_BUTTON(btn_add), "list-add-symbolic");
    adw_header_bar_pack_end(ADW_HEADER_BAR(header), btn_add);
    gtk_window_present(GTK_WINDOW(window));
}

void add_app_content(GtkWidget *widget)
{
    gtk_box_append(GTK_BOX(box_adw), widget);
}

GtkWidget *get_app_header_bar()
{
    return header;
}

GtkWidget *get_app_btn_add()
{
    return btn_add;
}