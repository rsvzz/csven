#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib-object.h>
#include "gdragdrop.h"

#define PAGE_DRAG_TYPE page_drag_get_type()

G_DECLARE_FINAL_TYPE(PageDrag, page_drag, PAGE, DRAG, GObject);

PageDrag *page_drag_new(void);
GtkWidget *page_drag_get_content(PageDrag *self);
void page_drag_set_head(PageDrag *self);