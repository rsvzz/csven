#include "../../include/verbpg.h"

struct _PageVerb
{
    /* data */
    GObject parent_instance;
    GtkWidget *box_verbs;
    ItemVerbs *item_verbs;
};

G_DEFINE_TYPE(PageVerb, page_verb, G_TYPE_OBJECT);

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
/*
GtkWidget *box_verbs;
ItemVerbs *item_verbs;

void create_page_verb()
{
    box_verbs = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    item_verbs = malloc(sizeof(ItemVerbs));
    load_verb(GTK_BOX(box_verbs), item_verbs);
}

GtkWidget *get_box_verb()
{
    return box_verbs;
}

ItemVerbs *get_item_verb()
{
    return item_verbs;
}
*/