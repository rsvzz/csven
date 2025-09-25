#pragma once

#include "sv_header.h"

#define NAV_MAIN_TYPE nav_main_get_type()

G_DECLARE_FINAL_TYPE (NavMain, nav_main, NAV, MAIN, SvHeader);

NavMain *nav_main_new(GtkWidget *);

GtkWidget * nav_main_get_popover(NavMain*);
GtkWidget * nav_main_get_box_main(NavMain*);

void nav_main_load_content(NavMain*);

/// @brief 
/// @param self 
/// @param  GtkWidget child
/// @param  char* const name
/// @param  char* const title
/// @param  char* const icon_name
/// @return AdwViewStackPage 
AdwViewStackPage *nav_main_add_stack_page(NavMain *, GtkWidget *, const char*, const char*, const char*);