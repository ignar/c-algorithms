TARGET = dist
CC = gcc
CFLAGS = -g -Wall

all: merge_sort factorial fibonacci

OBJECTS = $(patsubst %.c, %.o, $(wildcard algorithms/*.c))
HEADERS = $(wildcard algorithms/*_lib.h)


merge_sort: merge_sort.o merge_sort_lib.o common_lib.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^

factorial: factorial.o factorial_lib.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^

fibonacci: fibonacci.o fibonacci_lib.o common_lib.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^

merge_sort.o: algorithms/merge_sort.c
	$(CC) $(CFLAGS) -c -o $@ $<

factorial.o: algorithms/factorial.c
	$(CC) $(CFLAGS) -c -o $@ $<

fibonacci.o: algorithms/fibonacci.c
	$(CC) $(CFLAGS) -c -o $@ $<


merge_sort_lib.o: algorithms/merge_sort_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

factorial_lib.o: algorithms/factorial_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

fibonacci_lib.o: algorithms/fibonacci_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

common_lib.o: algorithms/common_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	-rm -f *.o
	-rm -rf $(TARGET)/*
	-cd tests && make clean
