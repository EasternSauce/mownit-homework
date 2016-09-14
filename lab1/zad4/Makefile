GSL_HOME=/opt/gsl/


CFLAGS = -I/$(GSL_HOME)/include/
LDFLAGS =  -L/$(GSL_HOME)/lib -lgsl -lgslcblas -lm 


OBJ= dokladnosc.o

all: dokladnosc

dokladnosc:dokladnosc.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o
