CCFLAGS=-std=gnu99 -Wall -lm -lgsl -lgslcblas
TARGETS=gsl_qagiu
all: $(TARGETS)

%: %.c
	$(CC) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(TARGETS)
