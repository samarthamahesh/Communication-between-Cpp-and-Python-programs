#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
static const unsigned PORT = 8080;
static const unsigned MAX_LEN = 1000;

int main(int argc, char const *argv[]) {
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	std::string hello;
	std::cout << "Your message: ";
	std::getline(std::cin, hello);
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "Socket creation error" << std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)	{
		std::cout << "Invalid address/ Address not supported" << std::endl;
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "Connection Failed" << std::endl;
		return -1;
	}
	send(sock, hello.c_str(), hello.length(), 0);
	std::cout << "Message sent" << std::endl;

	valread = read(sock, buffer, 1024);
	std::cout << "Message from server: " << buffer << std::endl;
	return 0;
}
