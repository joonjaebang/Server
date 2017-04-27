CC	=	g++
DEBUG	=	-g
LFLAG	=	-Wall $(DEBUG)
CFLAG	=	-Wall -c $(DEBUG)

server: server.c
	$(CC) server.c -o server

clean:
	\rm *.o *~ server
