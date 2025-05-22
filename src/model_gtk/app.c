#include "../../include/app.h"
#include "../../include/option_verb.h"
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