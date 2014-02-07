CC = gcc
CFLAGS = -g -Wall

all: main run

main: main.o
	$(CC) $(LDFLAGS) -lncurses -o tests $^

run: main
	-./tests

clean:
	-rm -f tests
	-rm -f *.o
