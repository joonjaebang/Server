#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <map>

extern std::map<std::string, std::string> authentication;

class Server{
	private:
		void handle_connection(int sockfd);
	public:
		Server() {}
		void initialize(int port);
		void start_listening(int socket);
		void authenticate(int sockfd);
		void sendMessage(int sockfd, std::string prompt);
		~Server() {}
};

