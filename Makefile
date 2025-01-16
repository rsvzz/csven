INC_FILES = include
#INC_GTK4 = -I/usr/include/gtk-4.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/sysprof-6 -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/x86_64-linux-gnu -I/usr/include/webp -I/usr/include/graphene-1.0 -I/usr/lib/x86_64-linux-gnu/graphene-1.0/include -mfpmath=sse -msse -msse2 -pthread
CFLAGS = -Wall -g -I$(INC_FILES)#$(INC_GTK4)
BIN = bin
CC = clang
TARGET = $(BIN)/app
LIB_SO = -Llib -lquestk #libs/libquestk.a
WIN_OBJS_DIR = $(BIN)/obj

C_SRC_DIR = src
C_SRC_GTK_MODEL_DIR = $(C_SRC_DIR)/model_gtk
C_SRC_MODEL_DIR = $(C_SRC_DIR)/model

LIBS_GTK =  `pkg-config --cflags gtk4` `pkg-config --libs gtk4`#-Llibs -lgtk-4 -lgio-2.0 -lglib-2.0 -lgobject-2.0

OBJ_SRC_FILES = $(WIN_OBJS_DIR)/createtobutton.o \
$(WIN_OBJS_DIR)/gridtobutton.o $(WIN_OBJS_DIR)/comperetoindex.o $(WIN_OBJS_DIR)/main.o


all : $(TARGET)


$(TARGET) : $(OBJ_SRC_FILES)
	@mkdir -p $(BIN)
	@cp -r lib bin
	@cp -r style bin
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS_GTK) $(LIB_SO)


$(WIN_OBJS_DIR)/%.o : $(C_SRC_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBS_GTK)

$(WIN_OBJS_DIR)/%.o : $(C_SRC_GTK_MODEL_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBS_GTK)

$(WIN_OBJS_DIR)/%.o : $(C_SRC_MODEL_DIR)/%.c
	@mkdir -p $(BIN)
	@mkdir -p $(WIN_OBJS_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

exe :
	@LD_LIBRARY_PATH=lib:lib ./$(TARGET)


clean :
	@rm -r $(BIN)