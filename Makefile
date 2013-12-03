TARGET = dist
CC = gcc
CFLAGS = -g -Wall

all: merge_sort factorial

merge_sort: merge_sort.o merge_sort_lib.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^

factorial: factorial.o factorial_lib.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^


merge_sort.o: algorithms/merge_sort.c
	$(CC) $(CFLAGS) -c -o $@ $<

factorial.o: algorithms/factorial.c
	$(CC) $(CFLAGS) -c -o $@ $<


merge_sort_lib.o: algorithms/merge_sort_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

factorial_lib.o: algorithms/factorial_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *.o
	-rm -rf $(TARGET)/*
	-cd tests && make clean
