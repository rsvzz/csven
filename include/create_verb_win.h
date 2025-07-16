#pragma once
#include <libadwaita-1/adwaita.h>
#include <glib-2.0/glib-object.h>

typedef struct dialog_win
{
    /* data */
    GtkWindow *parent;
    void (*on_save)();
    void (*on_close)();
} DialogWin;

typedef struct{
    GtkLabel *present;
    GtkLabel *past;
    GtkLabel *participle;
    GtkLabel *baseing;
    GtkCheckButton *is_regular;
    GtkGrid *grid;
    GtkSeparator *space;
} ItemVerbs;

typedef struct
{
    /* data */
    AdwViewStack *stack;
    GtkWindow *parent;
    ItemVerbs *verb;
} ItemOptVerb;

typedef struct
{
   /* data */
   GtkEntry* base;
   GtkEntry* v2;
   GtkEntry* v3;
   GtkEntry *ing;
   GtkCheckButton *isRegular;
   GtkWindow *win;
   /// @brief show data in lbl
   ItemVerbs *data;
   // para intercambio
   char *name_v2, *name_v3, *name_ing;
} ItemVerbWidget;

#define WIN_VERB_TYPE win_verb_get_type()
G_DECLARE_FINAL_TYPE (WinVerb, win_verb, WIN, VERB, GObject);

WinVerb *win_verb_new(void);
void win_verb_load_widget(WinVerb *self, GtkWindow *paren, const char* title, int is_modal, DialogWin *dialog, ItemVerbs* items);

/*
/// @brief Crear ventana Verbs
/// @param  GtkWindow* window pared
/// @param  char* title
/// @param  int 1 true 0 false
void create_verb_window(GtkWindow*, const char*, int, DialogWin*, ItemVerbs*);
*/