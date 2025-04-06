#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <questk/queue.h>
typedef struct 
{
    /* data */
    GtkButton* btn;
    int index;
    char ctr;
    /// @brief save check
    int status;
    int isEnd;
} ItemBtnGame;

typedef struct
{
    GtkButton *btn;
    int index;
    int status;
}ItemGame;

typedef struct 
{
    /* data */
    GtkButton *btn;
}ItemGridData;

/// @brief save to info game grid
typedef struct
{
    GtkButton *btn_restore;
    /// @brief list btn game
    Queue **list, *auxList;
    /// @brief list btn title
    Queue **tlist, *auxt;

    GtkGrid *grid;
    GtkEntry *txt_name;
    
    /// @brief box contenedor tittle
    GtkBox *box_name;
    int x;
    int y;
    char* name;
} ItemListRestore;

typedef struct
{
  GtkEntry *txt_name;
  GtkGrid *grid;
  ItemListRestore* item_list;
  int x;
  int y;
  char *name;
} DataGame;

typedef struct{
    GtkLabel *present;
    GtkLabel *past;
    GtkLabel *participle;
    GtkLabel *baseing;
    GtkGrid *grid;
} ItemVerbs;

typedef struct dialog_win
{
    /* data */
    GtkWindow *parent;
    void (*on_save)();
    void (*on_close)();
} DialogWin;

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
}ItemVerbWidget;
