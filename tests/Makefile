CC = gcc
CFLAGS = -g -Wall

all: merge_sort
	-./merge_sort

merge_sort: merge_sort_test.o
	$(CC) $(LDFLAGS) -o $@ $^

merge_sort.o: merge_sort_test.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *.o
	-rm -f merge_sort
