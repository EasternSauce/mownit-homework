CCFLAGS=-std=gnu99 -Wall -lm -lgsl -lgslcblas
TARGETS=gsl_qag gsl_qawo gsl_qng 

all: $(TARGETS)

%: %.c
	$(CC) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(TARGETS)
