INCDIR=include
CC=gcc
CFLAGS=-g -I$(INCDIR) -std=c99 -Wextra -Wall
SRCDIR=src
OBJDIR=$(SRCDIR)/obj
OUTDIR=bin
LIBS=
_DEPS=mapa.h fronteira.h busca.h
DEPS=$(patsubst %,$(INCDIR)/%,$(_DEPS))
_OBJ=mapa.o fronteira.o busca.o inunda.o
OBJ=$(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/inunda: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*.o *~ *.swp core $(INCDIR)/*~ $(INCDIR)/*.swp
