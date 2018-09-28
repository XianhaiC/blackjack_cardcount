# Makefile
LDFLAGS = -lncurses

all: demo.c
	gcc -o demo demo.c $(LDFLAGS)
