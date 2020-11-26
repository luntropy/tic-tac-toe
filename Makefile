CC = g++
CFLAGS = -Wall -g -O3

main: main.o Board.o Game.o
	$(CC) $(CFLAGS) -o main main.o Board.o Game.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp

Game.o: Board.cpp Game.cpp
	$(CC) $(CFLAGS) -c Board.cpp Game.cpp

clean:
	rm -f core *.o
