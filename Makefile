TARGET = dist
CC = gcc
CFLAGS = -g -Wall

all: merge_sort

merge_sort: merge_sort.o merge_sort_lib.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^

merge_sort.o: algorithms/merge_sort.c
	$(CC) $(CFLAGS) -c -o $@ $<

merge_sort_lib.o: algorithms/merge_sort_lib.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *.o
	-rm -rf $(TARGET)/*
	-cd tests && make clean
