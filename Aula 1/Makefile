#compiler
CC = gcc

#compiler flags
CFLAGS = -ggdb

#linker flags / librarys
LDFLAGS = -lm

#source files
SOURCES = main.c quad.c

#source files with the .c replaced with .o
OBJECTS = $(SOURCES:.c=.o)

#executable
TARGET = main

#&@ means the target value
#&^ means the objects value
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)