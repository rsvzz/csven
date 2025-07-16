#include "../../include/verbpg.h"

struct _PageVerb
{
    /* data */
    GObject parent_instance;
    GtkWidget *box_verbs;
    ItemVerbs *item_verbs;
};

G_DEFINE_TYPE(PageVerb, page_verb, G_TYPE_OBJECT);

/// @brief show control window dialog
/// @param  Box content
/// @param  Items ItemVerbs
void load_verb(GtkBox*, ItemVerbs*);
static void page_verb_dispose(GObject *object)
{
  PageVerb *self = PAGE_VERB(object);
    /*
   
  if (self->btn_restare != NULL)
  {
    g_object_unref(self->btn_restare);
    self->btn_restare = NULL;
  }

  if (self->txt_name != NULL)
  {
    g_object_unref(self->txt_name);
    self->txt_name = NULL;
  }

  if (self->grid != NULL)
  {
    g_object_unref(self->grid);
    self->grid = NULL;
  }
     */

  G_OBJECT_CLASS(page_verb_parent_class)->dispose(object);
}

static void page_verb_finalize(GObject *object)
{
  G_OBJECT_CLASS(page_verb_parent_class)->finalize(object);
}

static void page_verb_class_init(PageVerbClass *Klass)
{
  // add signal and property
  GObjectClass *object_class = G_OBJECT_CLASS(Klass);

  // Asignar la función de destrucción
  object_class->dispose = page_verb_dispose;

  // Asignar la función de finalización
  object_class->finalize = page_verb_finalize;
};

/// @brief init all data.
/// @param self
static void page_verb_init(PageVerb *self)
{

};

PageVerb *page_verb_new(void){
    return g_object_new(PAGE_VERB_TYPE, NULL);
}

void page_verb_load_widget(PageVerb * self){
    self->box_verbs = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    self->item_verbs = malloc(sizeof(ItemVerbs));
    load_verb(GTK_BOX(self->box_verbs), self->item_verbs);
}

GtkWidget *page_verb_get_box(PageVerb* self){
    return self->box_verbs;
}

ItemVerbs* page_verb_get_items_verb(PageVerb *self){
    return self->item_verbs;
}

void load_verb(GtkBox *box, ItemVerbs *item)
{
    item->present = GTK_LABEL(gtk_label_new("Present"));
    item->past = GTK_LABEL(gtk_label_new("Past"));
    item->participle = GTK_LABEL(gtk_label_new("Participle"));
    item->baseing = GTK_LABEL(gtk_label_new("Verb ing"));
    item->is_regular = GTK_CHECK_BUTTON(gtk_check_button_new_with_label("Is Regular"));
    gtk_widget_set_sensitive(GTK_WIDGET(item->is_regular), FALSE);
    // item->space = GTK_SEPARATOR(gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));

    gtk_widget_add_css_class(GTK_WIDGET(item->present), "lbl_compare");
    gtk_widget_add_css_class(GTK_WIDGET(item->past), "lbl_compare");
    gtk_widget_add_css_class(GTK_WIDGET(item->participle), "lbl_compare");
    gtk_widget_add_css_class(GTK_WIDGET(item->baseing), "lbl_compare");

    item->grid = GTK_GRID(gtk_grid_new());
    /// gtk_widget_add_css_class(GTK_WIDGET(item->grid), "grid_table");

    // compare verb
    GtkWidget *op_1 = gtk_label_new("(*) Present");
    GtkWidget *op_2 = gtk_label_new("(-) Past");

    gtk_grid_attach(item->grid, GTK_WIDGET(item->present), 0, 0, 1, 1);
    // gtk_grid_attach(item->grid, GTK_WIDGET(item->space),1,1,2,1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->past), 0, 1, 1, 1);
    gtk_grid_attach(item->grid, op_1, 1, 1, 1, 1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->participle), 0, 2, 1, 1);
    gtk_grid_attach(item->grid, op_2, 1, 2, 1, 1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->baseing), 0, 3, 1, 1);
    gtk_grid_attach(item->grid, GTK_WIDGET(item->is_regular), 0, 4, 1, 1);

    gtk_grid_set_column_spacing(item->grid, 5);
    gtk_grid_set_row_spacing(item->grid, 5);

    gtk_widget_set_halign(GTK_WIDGET(op_1), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(op_2), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(item->present), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(item->past), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(item->participle), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(item->baseing), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(item->is_regular), GTK_ALIGN_END);
    gtk_box_append(box, GTK_WIDGET(item->grid));
}