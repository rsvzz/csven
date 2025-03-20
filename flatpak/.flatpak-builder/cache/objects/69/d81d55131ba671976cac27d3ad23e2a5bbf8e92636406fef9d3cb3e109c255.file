#pragma once
#include <gtk-4.0/gtk/gtk.h>
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