# Simple SDL mini
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`
SRCDIR=../image_processing
all: main

main: main.o   display.o rlsa.o cut.o matrix.o 
main.o: display.o rlsa.h cut.h matrix.h 


clean:
	${RM} *.o
	${RM} *~
	${RM} *.d
	${RM} main


# END
