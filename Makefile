# Compiler
CC = g++

# Source files
SOURCES = main.cpp scene/_scene.cpp misc/_misc.cpp inv/_inv.cpp

# Executable name
EXECUTABLE = main

all: $(SOURCES)
	$(CC) -o $(EXECUTABLE) $(SOURCES) -lncurses -lsfml-audio -lsfml-system
