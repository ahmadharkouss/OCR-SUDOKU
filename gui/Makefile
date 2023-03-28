# Makefile

CC = gcc
CPPFLAGS=`pkg-config --cflags gtk+-3.0 sdl`-MMD
CFLAGS = -Wall -Wextra 
LDFLAGS=-L /lib64
LDLIBS = `pkg-config --libs gtk+-3.0 sdl SDL_image` -lm
SRCDIR=../image_processing
SRCDIR2=../
SRCDIR3=../test_NN
SRCDIR4=../training_NN
SRCDIR5=../Detection
EXE = main_application

all: main_application $(EXE) 
main_application: main_application.o $(SRCDIR)/pixel_operations.o $(SRCDIR)/SDL_rotozoom.o $(SRCDIR)/binarize.o $(SRCDIR)/filters.o $(SRCDIR)/display.o $(SRCDIR)/rotate.o $(SRCDIR3)/softmax.o  $(SRCDIR4)/relu.o $(SRCDIR5)/display.o $(SRCDIR5)/rlsa.o  $(SRCDIR5)/cut.o  $(SRCDIR5)/matrix.o 
main_application.o:$(SRCDIR)/pixel_operations.h $(SRCDIR)/SDL_rotozoom.h $(SRCDIR)/binarize.h $(SRCDIR)/filters.h $(SRCDIR)/display.h $(SRCDIR)/rotate.h $(SRCDIR3)/softmax.h $(SRCDIR4)/relu.h  $(SRCDIR5)/display.h  $(SRCDIR5)/rlsa.h  $(SRCDIR5)/cut.h  $(SRCDIR5)/matrix.h 

$(foreach f, $(EXE), $(eval $(f):))

.PHONY: clean

clean:
	${RM} $(EXE)
	${RM} *.o
	${RM} *.d
	${RM} main
	${RM} *~

# END