INC_FILES = include
#INC_GTK4 = -I/usr/include/gtk-4.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/sysprof-6 -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/x86_64-linux-gnu -I/usr/include/webp -I/usr/include/graphene-1.0 -I/usr/lib/x86_64-linux-gnu/graphene-1.0/include -mfpmath=sse -msse -msse2 -pthread
CFLAGS = -Wall -g -I$(INC_FILES)#$(INC_GTK4)
BIN = bin
#ruta exe
USR_DIR = $(BIN)/bin
USR_SHARE = $(USR_DIR)/share
USR_SHARE_APPGAME = $(USR_SHARE)/csven

#uso de c11 para compatibilidad
CC = clang -std=c17
#ruta exe
TARGET = $(USR_DIR)/csven
#uso de libreria dinamica libquestk.so solo es para manejar stack y queue  agregare el reposutorio mas tarde y agregare el link
LIB_SO = -lquestk#libs/libquestk.a #need install libquestk .git 
WIN_OBJS_DIR = $(BIN)/obj

C_SRC_DIR = src
C_SRC_GTK_MODEL_DIR = $(C_SRC_DIR)/model_gtk
C_SRC_MODEL_DIR = $(C_SRC_DIR)/model
C_SRC_GTK_WIN_DIR = $(C_SRC_DIR)/win

LIBS_GTK =  `pkg-config --cflags --libs gtk4`#-Llibs -lgtk-4 -lgio-2.0 -lglib-2.0 -lgobject-2.0

OBJ_SRC_FILES = $(WIN_OBJS_DIR)/createtobutton.o  $(WIN_OBJS_DIR)/app.o $(WIN_OBJS_DIR)/mapcss.o \
$(WIN_OBJS_DIR)/nav.o  $(WIN_OBJS_DIR)/wordpg.o $(WIN_OBJS_DIR)/verbpg.o \
$(WIN_OBJS_DIR)/gridtobutton.o $(WIN_OBJS_DIR)/comperetoindex.o  $(WIN_OBJS_DIR)/maptogridwithname.o \
$(WIN_OBJS_DIR)/createtobtnforgrid.o $(WIN_OBJS_DIR)/cverbwin.o $(WIN_OBJS_DIR)/createtoverb.o \
$(WIN_OBJS_DIR)/optionverb.o  $(WIN_OBJS_DIR)/main.o


all : $(TARGET)


$(TARGET) : $(OBJ_SRC_FILES)
	@mkdir -p $(BIN)
	@mkdir -p $(USR_DIR)
	@mkdir -p $(USR_SHARE)
	@mkdir -p $(USR_SHARE_APPGAME)
	@cp -r style $(USR_SHARE_APPGAME)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS_GTK) $(LIB_SO)


$(WIN_OBJS_DIR)/%.o : $(C_SRC_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBS_GTK)

$(WIN_OBJS_DIR)/%.o : $(C_SRC_GTK_MODEL_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBS_GTK)

$(WIN_OBJS_DIR)/%.o : $(C_SRC_GTK_WIN_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBS_GTK)


$(WIN_OBJS_DIR)/%.o : $(C_SRC_MODEL_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

exe :
#	@LD_LIBRARY_PATH=lib ./$(TARGET)
	./$(TARGET)


clean :
	@rm -r $(BIN)