TARGET = dist
CC = gcc
CFLAGS = -g -Wall

all: merge_sort

merge_sort: merge_sort.o
	$(CC) $(LDFLAGS) -o $(TARGET)/$@ $^

merge_sort.o: algorithms/merge_sort.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *.o
	-rm -rf $(TARGET)/*
