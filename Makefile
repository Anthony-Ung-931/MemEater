CC = cc
CFLAGS = -m64 -std=c89
BINS = mem_eater

all: $(BINS)

mem_eater.o: mem_eater.c
	$(CC) $(CFLAGS) -c mem_eater.c

.PHONY: clean
clean:
	rm -f $(BINS) *.o

