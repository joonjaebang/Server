#include "server.h"

void Server::initialize(int port){
	int sockfd;
	
	struct sockaddr_in serv_addr;
	
	//Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("Error: Failed to initialize socket.\n");
		exit(1);
	}
	
	//Bind socket
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_port			= htons(port);
	serv_addr.sin_addr.s_addr	= INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		perror("Error: Failed to bind socket to address.\n");
		exit(1);
	}
	
	start_listening(sockfd);
	return;
}

void Server::start_listening(int socket){
	while(1){
		int newsockfd;
		struct sockaddr_in cli_addr;
		socklen_t clilen = sizeof(cli_addr);
	
		listen(socket, 5);
		newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &clilen);
	
		if(newsockfd < 0){
			perror("Error: Failed to connect to incoming connection.\n");
		}
		//Start new thread to handle request
		std::thread t1 (handle_connection, newsockfd);
		//t1.detach();
	}
}

void Server::handle_connection(int sockfd){
	char buffer[256];
	recv(sockfd, buffer, 255, MSG_WAITALL);
	std::cout << buffer << "\n";
	close(sockfd);
	return;
}

	/*
	int sockfd, newsockfd, port
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;

	if(argc < 2) {
		Error("Error: No port number was provided");
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		Error("Error: Socket failed to initialize");
	bzero((char*) &serv_addr, sizeof(serv_addr));
	port = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		Error("Error: Failed to bind socket to port");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0)
		Error("Error: Failed to accept connection");
	bzero(buffer, 256);
	n = read(newsockfd, buffer, 255);
	if(n < 0)
		Error("Error: Failed to read from socket");
	printf("Message: %s", buffer);
	close(newsockfd);
	*/
