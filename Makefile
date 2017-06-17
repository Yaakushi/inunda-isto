INCDIR=include
CC=gcc
CFLAGS=-g -I$(INCDIR) -std=c99 -Wextra -Wall
SRCDIR=src
OBJDIR=$(SRCDIR)/obj
OUTDIR=bin
LIBS=
_DEPS=mapa.h fronteira.h busca.h heuristics.h
DEPS=$(patsubst %,$(INCDIR)/%,$(_DEPS))
_OBJ=mapa.o fronteira.o heuristics busca.o inunda.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

.PHONY: all directories clean

all: directories $(OUTDIR)/inunda

directories:
	mkdir -p $(OBJDIR) $(OUTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/inunda: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)


clean:
	rm -rf $(OBJDIR)/*.o *~ *.swp core $(INCDIR)/*~ $(INCDIR)/*.swp
