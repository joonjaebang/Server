#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <thread>


//vector<std::thread> threads;
//size_t curThread = 0;

class Server{
	private:
		void handle_connection(int sockfd);
	public:
		Server() {}
		void initialize(int port);
		void start_listening(int socket);
		~Server() {}
};

