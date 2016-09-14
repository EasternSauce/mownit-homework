GSL_HOME=/opt/gsl/


CFLAGS = -I/$(GSL_HOME)/include/ -Wall
LDFLAGS =  -L/$(GSL_HOME)/lib -lgsl -lgslcblas -lm -g -Wall


all: main

main:main.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o
