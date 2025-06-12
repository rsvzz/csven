#pragma once
#include <libadwaita-1/adwaita.h>
#include <glib-2.0/glib-object.h>

#define STACK_OPTION_TYPE stack_option_get_type()

G_DECLARE_FINAL_TYPE(StackOption, stack_option, STACK, OPTION, GObject);

StackOption *stack_option_new(void);
/// @brief add header button add
/// @param self obj
/// @param optadd option add button
void stack_option_set_button_option_add(StackOption *self, GtkWidget *optadd);

GtkWidget *stack_option_get_box_page(StackOption *self);
GtkWidget *stack_option_get_stack(StackOption *self);
/// @brief load define
/// @param self 
void stack_option_load_all(StackOption * self);
AdwViewStackPage *stack_option_add_stack_child(StackOption *self, GtkWidget *child, const char *name, const char *title, const char* icon_name);

/*
    /// @brief Create siderbar
    /// @param  GtkWidget button add
    void create_nav(GtkWidget *);


/// @brief box page main
/// @return box main
GtkWidget *get_box_page();
/// @brief add paga stack
/// @param  GtkWidget add
/// @param  name page
/// @param  title page show
/// @return GtkStackPage
GtkStackPage *add_page_set_stack(GtkWidget *, const char *, const char *);
/// @brief Stack pages
/// @return Stack pages for siderbar
GtkWidget *get_nav_stack_pages();
*/
