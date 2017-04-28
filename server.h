#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <thread>

//vector<std::thread> threads;
//size_t curThread = 0;

class Server{
	private:
		void handle_connection();
	public:
		Server() {}
		void initialize(int port);
		void start_listening(int socket);
		void handle_connection(int sockfd);
		~Server() {}
};

