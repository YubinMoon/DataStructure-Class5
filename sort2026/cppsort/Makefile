CC = g++
CFLAG = -Wall -02

sort_test: main.o SortManager.o
	$(CC) $(CFLAGS) -o sort_test main.o SortManager.o

main.o: main.cpp SortManager.h
	$(CC) $(CFLAGS) -c main.cpp

SortManager.o: SortManager.cpp SortManager.h
	$(CC) $(CFLAGS) -c SortManager.cpp

clean:
	rm -f *.o sort_test