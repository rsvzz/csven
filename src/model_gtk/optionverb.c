#include "../../include/option_verb.h"
#include "../../include/create_verb_win.h"
#include "string.h"
#include "stdio.h"

void on_button_add_verb_word(GtkWidget *btn, gpointer user_data)
{
  ItemOptVerb *item = (ItemOptVerb *)user_data;
  GtkSelectionModel *pages = gtk_stack_get_pages(item->stack);

  if (gtk_selection_model_is_selected(pages, 0) == 1)
  {
    g_message("seleccionado word");
  }
  else
  {
    DialogWin *dialog = malloc(sizeof(DialogWin));
    dialog->parent = item->parent;
    dialog->on_save = on_save_verb;
    dialog->on_close = on_close_verb;
    create_verb_window(item->parent, "Add Verb", 1, dialog, item->verb);
  }
}

char *convertir_a_utf8(const char *input, const char *encoding_origen)
{
  gsize bytes_leidos, bytes_escritos;
  GError *error = NULL;

  // Realizar conversión desde la codificación de origen a UTF-8
  char *utf8 = g_convert(input, -1, "UTF-8", encoding_origen, &bytes_leidos, &bytes_escritos, &error);

  if (!utf8)
  {
    fprintf(stderr, "Error al convertir a UTF-8: %s\n", error->message);
    g_error_free(error);
    return g_strdup(""); // Devuelve una cadena vacía si la conversión falla
  }
  return utf8; // Recuerda liberar la memoria con g_free() después de usarla
}

char *get_compare_verb(const char *value, const char *compare, char replace)
{
  char *str = malloc(sizeof(char) + 1);
  strcpy(str, value);
  for (size_t i = 0; i < strlen(value); i++)
  {

    if (strlen(value) >= strlen(compare))
    {
      if (value[i] == compare[i])
      {
        str[i] = replace;
      }
      else
      {
        str[i] = value[i];
      }
    }
  }

  return str;
}

void on_save_verb(GtkWidget *btn, gpointer data)
{
  ItemVerbWidget *item = (ItemVerbWidget *)data;
  GtkEntryBuffer *bfbase = gtk_entry_get_buffer(item->base);
  GtkEntryBuffer *bfv2 = gtk_entry_get_buffer(item->v2);
  GtkEntryBuffer *bfv3 = gtk_entry_get_buffer(item->v3);
  GtkEntryBuffer *bfing = gtk_entry_get_buffer(item->ing);

  gtk_label_set_label(item->data->present, gtk_entry_buffer_get_text(bfbase));

  const char *new_v2 = get_compare_verb(gtk_entry_buffer_get_text(bfv2), gtk_entry_buffer_get_text(bfbase), '*');
  const char *new_v3 = get_compare_verb(gtk_entry_buffer_get_text(bfv3), gtk_entry_buffer_get_text(bfv2), '-');
  const char *new_ing = get_compare_verb(gtk_entry_buffer_get_text(bfing), gtk_entry_buffer_get_text(bfbase), '*');

  gtk_label_set_label(item->data->past, new_v2);
  gtk_label_set_label(item->data->participle, new_v3);
  gtk_label_set_label(item->data->baseing, new_ing);

  gtk_window_close(item->win);
}

void on_close_verb(GtkWidget *btn, gpointer data)
{
  gtk_window_close(GTK_WINDOW(data));
}
