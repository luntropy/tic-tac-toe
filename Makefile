CC = g++
CFLAGS = -Wall -g -O3

main: main.o Board.o
	$(CC) $(CFLAGS) -o main main.o Board.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp

clean:
	rm -f core *.o
