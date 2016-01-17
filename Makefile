OBJS = mTexture.cpp Game.cpp Graph.cpp 

CC = g++

COMPILER_FLAGS = -g -std=c++11

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = game

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 
