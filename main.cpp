#include <iostream>
#include <sstream>
#include "server.h"

using namespace std;

map<string, string> authentication;

void Error(const char *msg){
	perror(msg);
	exit(1);
}

int main(int argc, char* argv[]){
	if(argc < 2){
		Error("Error: No port number was provided.");
	}
	
	//INSERT strtol CHECKING HERE
	if(strtol(argv[1], nullptr, 10) == 0){
		Error("Error: Invalid port number. Must be a nonzero integer.");
	}
			
	int port = atoi(argv[1]);
	
	string inputLine;	

	while(getline(cin, inputLine, '\n')){
		stringstream ss;
		ss << inputLine;
		string username, password;
		ss >> username >> password;
		authentication.insert(authentication.begin(), pair<string, string>(username, password));
	}

	Server server;
	server.initialize(port);
	return 0;

}
