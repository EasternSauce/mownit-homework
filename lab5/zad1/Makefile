CCFLAGS=-std=gnu99 -Wall -lm -lgsl -lgslcblas
TARGETS=gsl_qag gsl_qng gsl_qagp gsl_qags trap

all: $(TARGETS)

%: %.c
	$(CC) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(TARGETS)
