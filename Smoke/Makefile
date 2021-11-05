.DEFAULT_GOAL := all

OBJS = main.cpp graphics.cpp draw.cpp rules.cpp utils.cpp
CC = g++

COMPILER_FLAGS = -w # suppresses all warnings

# link to SDL2
LINKER_FLAGS = -lSDL2 -pthread

OBJ_NAME = main

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -I. -o $(OBJ_NAME)
