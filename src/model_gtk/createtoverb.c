#include "../../include/createtoverb.h"

void load_verb(GtkBox* box, ItemVerbs *item){
    item->present = GTK_LABEL(gtk_label_new("Present"));
    item->past = GTK_LABEL(gtk_label_new("Past"));
    item->participle = GTK_LABEL(gtk_label_new("Participle"));
    item->baseing = GTK_LABEL(gtk_label_new("Verb ing"));

    item->grid =GTK_GRID(gtk_grid_new());
    //compare verb
    GtkWidget *op_1 = gtk_label_new("(*) Present");
    GtkWidget *op_2 = gtk_label_new("(-) Past");

    gtk_grid_attach(item->grid, GTK_WIDGET(item->present),0,0,1,1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->past),0,1,1,1);
    gtk_grid_attach(item->grid, op_1,1,1,1,1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->participle),0,2,1,1);
    gtk_grid_attach(item->grid, op_2,1,2,1,1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->baseing),0,3,1,1);

    gtk_grid_set_column_spacing(item->grid, 5);
    gtk_grid_set_row_spacing(item->grid, 5);

    gtk_widget_set_halign(GTK_WIDGET(op_1), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(op_2), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(item->present), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(item->past), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(item->participle), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(item->baseing), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_box_append(box,GTK_WIDGET(item->grid));
}