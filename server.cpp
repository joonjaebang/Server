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
		int newsockfd = -1;
		struct sockaddr_in cli_addr;
		socklen_t clilen = sizeof(cli_addr);
	
		listen(socket, 5);
		newsockfd = accept(socket, (struct sockaddr *) &cli_addr, &clilen);
	
		if(newsockfd < 0){
			perror("Error: Failed to connect to incoming connection.\n");
		}

		//Start new thread to handle request
		std::thread t1 (&Server::handle_connection, this, newsockfd);
		t1.detach();
	}
}

void Server::handle_connection(int sockfd){
	char buffer[256];
	std::string response = "Thank you for your response.\n";
	const char* responseChar = response.c_str();
	authenticate(sockfd);
	while(recv(sockfd, buffer, 255, 0) > 0){
		std::cout << buffer;
		send(sockfd, (void*)responseChar, strlen(responseChar), MSG_NOSIGNAL);
		bzero(buffer, 256);
	}
	close(sockfd);
	return;
}

void Server::authenticate(int sockfd){
	char buffer[256];
	sendMessage(sockfd, "Please enter your username: ");
	if(recv(sockfd, buffer, 255, 0) > 0){
		if(authentication.find((std::string)buffer) == authentication.end()){
			sendMessage(sockfd, "Username not found. Closing connection.\n");
			close(sockfd);
		} else {
			std::string username(buffer);
			if(recv(sockfd, buffer, 255, 0) > 0){
				if(authentication[username] != (std::string)buffer){
					sendMessage(sockfd, "Incorrect password. Closing connection.\n");
					close(sockfd);
				}
			}
		}
	}
	
}

void Server::sendMessage(int sockfd, std::string prompt){
	const char * promptChar = prompt.c_str();
	send(sockfd, (void*)promptChar, strlen(promptChar), MSG_NOSIGNAL);
}
