#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>

using namespace std;

void Error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char* argv[]){
	int sockfd, newsockfd, port;
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
	return 0;

}
