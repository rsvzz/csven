#include "../../include/nav.h"
GtkWidget *box_page, *stack, *siderbar;
void create_nav(GtkWidget *btn_add)
{
    stack = gtk_stack_new();
    siderbar = gtk_stack_sidebar_new();
    // signal page change
    g_signal_connect(stack, "notify::visible-child", G_CALLBACK(on_stack_page_changed), (gpointer)btn_add);
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(siderbar), GTK_STACK(stack));
    box_page = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(box_page), siderbar);
    gtk_box_append(GTK_BOX(box_page), stack);
}

GtkWidget* get_box_page(){
    return box_page;
}

GtkWidget* get_nav_stack_pages(){
    return stack;
}

GtkStackPage* add_page_set_stack(GtkWidget* wg, const char* name, const char* title){
    return gtk_stack_add_titled(GTK_STACK(stack), wg, name, title);
}

void on_stack_page_changed(GObject *_stack, GParamSpec *param, gpointer user_data)
{
    const char *visible_child = gtk_stack_get_visible_child_name(GTK_STACK(_stack));
    if (strcmp(visible_child, "verb") == 0)
    {
        gtk_widget_set_visible((GTK_WIDGET(user_data)), TRUE);
    }
    else
    {
        gtk_widget_set_visible(GTK_WIDGET(user_data), FALSE);
    }
}