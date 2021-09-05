CFILES = $(wildcard *.c)
HFILES = $(wildcard *.h)

OFILES = $(patsubst %.c,%.o,$(CFILES))

CC = gcc
CCFLAGS = -Wall

main: $(OFILES)
	$(CC) $(CCFLAGS) -o main $(OFILES)

%.o: %.c %.h
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f main
