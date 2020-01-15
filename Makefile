OBJS = main.cpp Data.cpp

CC = g++ -std=c++11

LIBS = /usr/include/SDL2 

COMPILER_FLAGS = -w 

LINKER_FLAGS = -lSDL2 -lSDL2_image `sdl2-config --libs` -lSDL2_ttf

OBJ_NAME = room

all : $(OBJ_NAME)

$(OBJ_NAME) : $(OBJS)
		$(CC) $(OBJS) -I $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
clean:
	rm -f room
