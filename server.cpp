#include "server.h"

void foo(){

}

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
		int newsockfd = -1;
		struct sockaddr_in cli_addr;
		socklen_t clilen = sizeof(cli_addr);
	
		listen(socket, 5);
		newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &clilen);
	
		if(newsockfd < 0){
			perror("Error: Failed to connect to incoming connection.\n");
		}
		//Start new thread to handle request
		//handle_connection(newsockfd);
		std::thread t1 (&Server::handle_connection, this, newsockfd);
		t1.detach();
	}
}

void Server::handle_connection(int sockfd){
	char buffer[256];
	std::string response = "Thank you for your response.\n";
	const char* responseChar = response.c_str();
	recv(sockfd, buffer, 255, 0);
	std::cout << buffer;
	send(sockfd, (void*)responseChar, strlen(responseChar), MSG_NOSIGNAL);
	close(sockfd);
	return;
}
