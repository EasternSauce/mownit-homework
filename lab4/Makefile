GSL_HOME=/opt/gsl/


CFLAGS = -I/$(GSL_HOME)/include/
LDFLAGS =  -L/$(GSL_HOME)/lib -lgsl -lgslcblas -lm 


OBJ= interpolacja.o

all: interpolacja generator


interpolacja:interpolacja.o
	$(CC) $(LDFLAGS) -g -o $@ $^

generator: generator.o
	gcc -lm generator.c -o generator 


clean:
	rm -f *.o interpolacja generator
