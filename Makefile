CC	=	g++ -std=c++11 -pthread
DEBUG	=	-g
LFLAG	=	-Wall $(DEBUG)
CFLAG	=	-Wall -c $(DEBUG)

main: server.o
	$(CC) main.cpp server.o -o main

server: server.h server.cpp
	$(CC) server.cpp $(CFLAG)

clean:
	\rm *.o *~ main
