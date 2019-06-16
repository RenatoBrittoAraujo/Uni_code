IDIR=inc
CC=gcc
CFLAGS=-lm

ODIR=obj
LDIR =lib

SRCR =src

_DEPS =  features.h util.h neural_network.h neuron.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =  features.o util.o main.o neural_network.o neuron.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm program

run:
	./program ${hidden_layer_neurons}