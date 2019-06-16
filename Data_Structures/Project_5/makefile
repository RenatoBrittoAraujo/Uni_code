IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =./lib

SRCR =./src

_DEPS = BinaryIndexedTree.h TreePrinter.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = BinaryIndexedTree.o TreePrinter.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# toda vez que eu viajava pela estrada de ouro fino

$(ODIR)/%.o: $(SRCR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm program

run:
	./program