SRCDIR = src
INCDIR = include
OUTDIR = bin
OBJDIR = build

CC = gcc
CFLAGS = -I$(INCDIR) -g
LIBS = -lncurses

_DEPS = macros.h sprites.h draw.h util.h
DEPS = $(patsubst %, $(INCDIR)/%, $(_DEPS))

_OBJ = draw.o util.o
OBJ = $(patsubst %, $(OBJDIR)/%, $(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o $(SRCDIR)/*~ $(INCDIR)/*~ $(OUTDIR)/*

engine: $(OBJDIR)/engine.o $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS) $(LIBS)

blackjack: $(OBJDIR)/blackjack.o $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ include/blackjack.h $(CFLAGS) $(LIBS)
