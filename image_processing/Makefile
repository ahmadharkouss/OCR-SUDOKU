# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`-MMD
CFLAGS= -Wall
LDFLAGS=-L /lib64
LDLIBS= `pkg-config --libs sdl SDL_image` -lm

all: main

main: main.o pixel_operations.o SDL_rotozoom.o binarize.o filters.o display.o rotate.o
main.o: pixel_operations.h SDL_rotozoom.h binarize.h filters.h display.h rotate.h


clean:
	${RM} *.o
	${RM} *.d
	${RM} main
	${RM} *~

# END
