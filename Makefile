OBJFILES	=	server.o
CC		=	g++
FLAG		=	-std=c++11 -pthread -ldl
DEBUG		=	-g
LFLAG		=	-Wall $(DEBUG)
CFLAG		=	-Wall -c $(DEBUG)
MAINEXEC	=	main

main: server.o
	$(CC) $(FLAG) main.cpp server.o -o main

server.o: server.h server.cpp
	$(CC) $(FLAG) server.cpp $(CFLAG)

clean:
	\rm $(OBJFILES) $(MAINEXEC)
